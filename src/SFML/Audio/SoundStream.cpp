////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio/SoundStream.hpp>
#include <SFML/Audio/AudioDevice.hpp>
#include <SFML/Audio/ALCheck.hpp>
#include <SFML/System/Sleep.hpp>


namespace sf
{
////////////////////////////////////////////////////////////
SoundStream::SoundStream() :
myIsStreaming     (false),
myChannelsCount   (0),
mySampleRate      (0),
myFormat          (0),
myLoop            (false),
mySamplesProcessed(0)
{

}


////////////////////////////////////////////////////////////
SoundStream::~SoundStream()
{
    // Stop the sound if it was playing
    Stop();
}


////////////////////////////////////////////////////////////
void SoundStream::Initialize(unsigned int channelsCount, unsigned int sampleRate)
{
    myChannelsCount = channelsCount;
    mySampleRate    = sampleRate;

    // Deduce the format from the number of channels
    myFormat = priv::AudioDevice::GetFormatFromChannelsCount(channelsCount);

    // Check if the format is valid
    if (myFormat == 0)
    {
        myChannelsCount = 0;
        mySampleRate    = 0;
        std::cerr << "Unsupported number of channels (" << myChannelsCount << ")" << std::endl;
    }
}


////////////////////////////////////////////////////////////
void SoundStream::Play()
{
    // Check if the sound parameters have been set
    if (myFormat == 0)
    {
        std::cerr << "Failed to play audio stream: sound parameters have not been initialized (call Initialize first)" << std::endl;
        return;
    }

    // If the sound is already playing (probably paused), just resume it
    if (myIsStreaming)
    {
        ALCheck(alSourcePlay(mySource));
        return;
    }

    // Move to the beginning
    OnSeek(0);

    // Start updating the stream in a separate thread to avoid blocking the application
    mySamplesProcessed = 0;
    myIsStreaming = true;
    Launch();
}


////////////////////////////////////////////////////////////
void SoundStream::Pause()
{
    ALCheck(alSourcePause(mySource));
}


////////////////////////////////////////////////////////////
void SoundStream::Stop()
{
    // Wait for the thread to terminate
    myIsStreaming = false;
    Wait();
}


////////////////////////////////////////////////////////////
unsigned int SoundStream::GetChannelsCount() const
{
    return myChannelsCount;
}


////////////////////////////////////////////////////////////
unsigned int SoundStream::GetSampleRate() const
{
    return mySampleRate;
}


////////////////////////////////////////////////////////////
SoundStream::Status SoundStream::GetStatus() const
{
    Status status = SoundSource::GetStatus();

    // To compensate for the lag between Play() and alSourcePlay()
    if ((status == Stopped) && myIsStreaming)
        status = Playing;

    return status;
}


////////////////////////////////////////////////////////////
void SoundStream::SetPlayingOffset(float timeOffset)
{
    // Stop the stream
    Stop();

    // Let the derived class update the current position
    OnSeek(timeOffset);

    // Restart streaming
    mySamplesProcessed = static_cast<unsigned int>(timeOffset * mySampleRate * myChannelsCount);
    myIsStreaming = true;
    Launch();
}


////////////////////////////////////////////////////////////
float SoundStream::GetPlayingOffset() const
{
    ALfloat seconds = 0.f;
    ALCheck(alGetSourcef(mySource, AL_SEC_OFFSET, &seconds));

    return seconds + static_cast<float>(mySamplesProcessed) / mySampleRate / myChannelsCount;
}


////////////////////////////////////////////////////////////
void SoundStream::SetLoop(bool loop)
{
    myLoop = loop;
}


////////////////////////////////////////////////////////////
bool SoundStream::GetLoop() const
{
    return myLoop;
}


////////////////////////////////////////////////////////////
void SoundStream::Run()
{
    // Create buffers
    ALCheck(alGenBuffers(BuffersCount, myBuffers));
    unsigned int endBuffer = 0xFFFF;

    // Fill the queue
    bool requestStop = FillQueue();

    // Play the sound
    ALCheck(alSourcePlay(mySource));

    while (myIsStreaming)
    {
        // The stream has been interrupted!
        if (SoundSource::GetStatus() == Stopped)
        {
            if (!requestStop)
            {
                // Just continue
                ALCheck(alSourcePlay(mySource));
            }
            else
            {
                // End streaming
                myIsStreaming = false;
            }
        }

        // Get the number of buffers that have been processed (ie. ready for reuse)
        ALint nbProcessed;
        ALCheck(alGetSourcei(mySource, AL_BUFFERS_PROCESSED, &nbProcessed));

        while (nbProcessed--)
        {
            // Pop the first unused buffer from the queue
            ALuint buffer;
            ALCheck(alSourceUnqueueBuffers(mySource, 1, &buffer));

            // Retrieve its size and add it to the samples count
            if (buffer == endBuffer)
            {
                // This was the last buffer: reset the sample count
                mySamplesProcessed = 0;
                endBuffer = 0xFFFF;
            }
            else
            {
                ALint size;
                ALCheck(alGetBufferi(buffer, AL_SIZE, &size));
                mySamplesProcessed += size / sizeof(Int16);
            }

            // Fill it and push it back into the playing queue
            if (!requestStop)
            {
                if (FillAndPushBuffer(buffer))
                {
                    // User requested to stop: check if we must loop or really stop
                    if (myLoop)
                    {
                        // Looping: restart and mark the current buffer as the last one
                        // (to know when to reset the sample count)
                        OnSeek(0);
                        endBuffer = buffer;
                    }
                    else
                    {
                        // Not looping: request stop
                        requestStop = true;
                    }
                }
            }
        }

        // Leave some time for the other threads if the stream is still playing
        if (SoundSource::GetStatus() != Stopped)
            Sleep(0.1f);
    }

    // Stop the playback
    ALCheck(alSourceStop(mySource));

    // Unqueue any buffer left in the queue
    ClearQueue();

    // Delete the buffers
    ALCheck(alSourcei(mySource, AL_BUFFER, 0));
    ALCheck(alDeleteBuffers(BuffersCount, myBuffers));
}


////////////////////////////////////////////////////////////
bool SoundStream::FillAndPushBuffer(unsigned int buffer)
{
    bool requestStop = false;

    // Acquire audio data
    Chunk data = {NULL, 0};
    if (!OnGetData(data))
        requestStop = true;

    // Create and fill the buffer, and push it to the queue
    if (data.Samples && data.NbSamples)
    {
        // Fill the buffer
        ALsizei size = static_cast<ALsizei>(data.NbSamples) * sizeof(Int16);
        ALCheck(alBufferData(buffer, myFormat, data.Samples, size, mySampleRate));

        // Push it into the sound queue
        ALCheck(alSourceQueueBuffers(mySource, 1, &buffer));
    }

    return requestStop;
}


////////////////////////////////////////////////////////////
bool SoundStream::FillQueue()
{
    // Fill and enqueue all the available buffers
    bool requestStop = false;
    for (int i = 0; (i < BuffersCount) && !requestStop; ++i)
    {
        if (FillAndPushBuffer(myBuffers[i]))
            requestStop = true;
    }

    return requestStop;
}


////////////////////////////////////////////////////////////
void SoundStream::ClearQueue()
{
    // Get the number of buffers still in the queue
    ALint nbQueued;
    ALCheck(alGetSourcei(mySource, AL_BUFFERS_QUEUED, &nbQueued));

    // Unqueue them all
    ALuint buffer;
    for (ALint i = 0; i < nbQueued; ++i)
        ALCheck(alSourceUnqueueBuffers(mySource, 1, &buffer));
}

} // namespace sf
