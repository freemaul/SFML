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

#ifndef SFML_AUDIODEVICE_HPP
#define SFML_AUDIODEVICE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio/ALCheck.hpp>
#include <set>
#include <string>


namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief High-level wrapper around the audio API, it manages
///        the creation and destruction of the audio device and
///        context and stores the device capabilities
///
////////////////////////////////////////////////////////////
class AudioDevice
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    AudioDevice();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~AudioDevice();

    ////////////////////////////////////////////////////////////
    /// \brief Get the unique instance of the class
    ///
    /// \return Unique instance of the class
    ///
    ////////////////////////////////////////////////////////////
    static AudioDevice& GetInstance();

    ////////////////////////////////////////////////////////////
    /// \brief Get the OpenAL audio device
    ///
    /// \return OpenAL device (cannot be NULL)
    ///
    ////////////////////////////////////////////////////////////
    ALCdevice* GetDevice() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the OpenAL format that matches the given number of channels
    ///
    /// \param channelsCount Number of channels
    ///
    /// \return Corresponding format
    ///
    ////////////////////////////////////////////////////////////
    ALenum GetFormatFromChannelsCount(unsigned int channelsCount) const;

private :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ALCdevice*  myDevice;  ///< Audio device
    ALCcontext* myContext; ///< Audio context
};

} // namespace priv

} // namespace sf


#endif // SFML_AUDIODEVICE_HPP
