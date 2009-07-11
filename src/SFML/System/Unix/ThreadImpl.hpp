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

#ifndef SFML_THREADIMPL_HPP
#define SFML_THREADIMPL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/NonCopyable.hpp>
#include <pthread.h>


namespace sf
{
class Thread;

namespace priv
{
////////////////////////////////////////////////////////////
/// Unix implementation of threads
////////////////////////////////////////////////////////////
class ThreadImpl : NonCopyable
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor, launch the thread
    ///
    /// \param owner : Owner Thread instance to run
    ///
    ////////////////////////////////////////////////////////////
    ThreadImpl(Thread* owner);

    ////////////////////////////////////////////////////////////
    /// Wait until the thread finishes
    ///
    ////////////////////////////////////////////////////////////
    void Wait();

    ////////////////////////////////////////////////////////////
    /// Terminate the thread
    /// Terminating a thread with this function is not safe,
    /// you should rather try to make the thread function
    /// terminate by itself
    ///
    ////////////////////////////////////////////////////////////
    void Terminate();

private :

    ////////////////////////////////////////////////////////////
    /// Global entry point for all threads
    ///
    /// \param userData : User-defined data (contains the Thread instance)
    ///
    /// \return Error code
    ///
    ////////////////////////////////////////////////////////////
    static void* EntryPoint(void* userData);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    pthread_t myThread;   ///< pthread thread instance
    bool      myIsActive; ///< Thread state (active or inactive)
};

} // namespace priv

} // namespace sf


#endif // SFML_THREADIMPL_HPP
