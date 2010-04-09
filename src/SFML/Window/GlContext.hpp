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

#ifndef SFML_GLCONTEXT_HPP
#define SFML_GLCONTEXT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/System/NonCopyable.hpp>


namespace sf
{
namespace priv
{
class WindowImpl;

////////////////////////////////////////////////////////////
/// \brief Abstract class representing an OpenGL context
///
////////////////////////////////////////////////////////////
class GlContext : NonCopyable
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Create a new context, not associated to a window
    ///
    /// This function automatically chooses the specialized class
    /// to use according to the OS.
    ///
    /// \return Pointer to the created context (don't forget to delete it)
    ///
    ////////////////////////////////////////////////////////////
    static GlContext* New();

    ////////////////////////////////////////////////////////////
    /// \brief Create a new context attached to a window
    ///
    /// This function automatically chooses the specialized class
    /// to use according to the OS.
    ///
    /// \param owner        Pointer to the owner window
    /// \param bitsPerPixel Pixel depth (in bits per pixel)
    /// \param settings     Creation parameters
    ///
    /// \return Pointer to the created context (don't forget to delete it)
    ///
    ////////////////////////////////////////////////////////////
    static GlContext* New(const WindowImpl* owner, unsigned int bitsPerPixel, const ContextSettings& settings);

public :

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GlContext();

    ////////////////////////////////////////////////////////////
    /// \brief Get the settings of the context
    ///
    /// Note that these settings may be different than the ones
    /// passed to the constructor; they are indeed adjusted if the
    /// original settings are not directly supported by the system.
    ///
    /// \return Structure containing the settings
    ///
    ////////////////////////////////////////////////////////////
    const ContextSettings& GetSettings() const;

    ////////////////////////////////////////////////////////////
    /// \brief Activate or deactivate the context as the current target
    ///        for rendering
    ///
    /// A context is active only on the current thread, if you want to
    /// make it active on another thread you have to deactivate it
    /// on the previous thread first if it was active.
    /// Only one context can be active on a thread at a time, thus
    /// the context previously active (if any) automatically gets deactivated.
    ///
    /// \param active True to activate, false to deactivate
    ///
    /// \return True if operation was successful, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    bool SetActive(bool active);

    ////////////////////////////////////////////////////////////
    /// \brief Display what has been rendered to the context so far
    ///
    ////////////////////////////////////////////////////////////
    virtual void Display() = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable vertical synchronization
    ///
    /// Activating vertical synchronization will limit the number
    /// of frames displayed to the refresh rate of the monitor.
    /// This can avoid some visual artifacts, and limit the framerate
    /// to a good value (but not constant across different computers).
    ///
    /// \param enabled True to enable v-sync, false to deactivate
    ///
    ////////////////////////////////////////////////////////////
    virtual void UseVerticalSync(bool enabled) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Make the current thread's reference context active
    ///
    /// This function is meant to be called internally; it is used
    /// to deactivate the current context by activating another one
    /// (so that we still have an active context on the current thread).
    ///
    /// \return True if operation was successful, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool SetReferenceActive();

protected :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor is meant for derived classes only.
    ///
    ////////////////////////////////////////////////////////////
    GlContext();

    ////////////////////////////////////////////////////////////
    /// \brief Activate the context as the current target
    ///        for rendering
    ///
    /// \return True on success, false if any error happened
    ///
    ////////////////////////////////////////////////////////////
    virtual bool MakeCurrent() = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Evaluate a pixel format configuration
    ///
    /// This functions can be used by implementations that have
    /// several valid formats and want to get the best one.
    /// A score is returned for the given configuration: the
    /// lower the score is, the better the configuration is.
    ///
    /// \param bitsPerPixel Requested pixel depth (bits per pixel)
    /// \param settings     Requested additionnal settings
    /// \param colorBits    Color bits of the configuration to evaluate
    /// \param depthBits    Depth bits of the configuration to evaluate
    /// \param stencilBits  Stencil bits of the configuration to evaluate
    /// \param antialiasing Antialiasing level of the configuration to evaluate
    ///
    /// \return Score of the configuration
    ///
    ////////////////////////////////////////////////////////////
    static int EvaluateFormat(unsigned int bitsPerPixel, const ContextSettings& settings, int colorBits, int depthBits, int stencilBits, int antialiasing);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ContextSettings mySettings; ///< Creation settings of the context
};

} // namespace priv

} // namespace sf


#endif // SFML_GLCONTEXT_HPP
