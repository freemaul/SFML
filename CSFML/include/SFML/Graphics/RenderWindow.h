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

#ifndef SFML_RENDERWINDOW_H
#define SFML_RENDERWINDOW_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/WindowHandle.h>
#include <SFML/Window/Window.h>


////////////////////////////////////////////////////////////
/// Construct a new renderwindow
///
/// \param mode :     Video mode to use
/// \param title :    Title of the window
/// \param style :    Window style
/// \param settings : Creation settings
///
////////////////////////////////////////////////////////////
CSFML_API sfRenderWindow* sfRenderWindow_Create(sfVideoMode mode, const char* title, unsigned long style, sfContextSettings settings);

////////////////////////////////////////////////////////////
/// Construct a renderwindow from an existing control
///
/// \param handle :   Platform-specific handle of the control
/// \param settings : Creation settings
///
////////////////////////////////////////////////////////////
CSFML_API sfRenderWindow* sfRenderWindow_CreateFromHandle(sfWindowHandle handle, sfContextSettings settings);

////////////////////////////////////////////////////////////
/// Destroy an existing renderwindow
///
/// \param renderWindow : Renderwindow to destroy
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_Destroy(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Close a renderwindow (but doesn't destroy the internal data)
///
/// \param renderWindow : Renderwindow to close
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_Close(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Tell whether or not a renderwindow is opened
///
/// \param renderWindow : Renderwindow object
///
////////////////////////////////////////////////////////////
CSFML_API sfBool sfRenderWindow_IsOpened(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Get the width of the rendering region of a window
///
/// \param renderWindow : Renderwindow object
///
/// \return Width in pixels
///
////////////////////////////////////////////////////////////
CSFML_API unsigned int sfRenderWindow_GetWidth(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Get the height of the rendering region of a window
///
/// \param renderWindow : Renderwindow object
///
/// \return Height in pixels
///
////////////////////////////////////////////////////////////
CSFML_API unsigned int sfRenderWindow_GetHeight(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Get the creation settings of a window
///
/// \param renderWindow : Renderwindow object
///
/// \return Settings used to create the window
///
////////////////////////////////////////////////////////////
CSFML_API sfContextSettings sfRenderWindow_GetSettings(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Get the event on top of events stack of a window, if any, and pop it
///
/// \param renderWindow : Renderwindow object
/// \param event :        Event to fill, if any
///
/// \return sfTrue if an event was returned, sfFalse if events stack was empty
///
////////////////////////////////////////////////////////////
CSFML_API sfBool sfRenderWindow_GetEvent(sfRenderWindow* renderWindow, sfEvent* event);

////////////////////////////////////////////////////////////
/// Enable / disable vertical synchronization on a window
///
/// \param renderWindow : Renderwindow object
/// \param enabled :      sfTrue to enable v-sync, sfFalse to deactivate
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_UseVerticalSync(sfRenderWindow* renderWindow, sfBool enabled);

////////////////////////////////////////////////////////////
/// Show or hide the mouse cursor on a window
///
/// \param renderWindow : RenderWindow object
/// \param show :         sfTrue to show, sfFalse to hide
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_ShowMouseCursor(sfRenderWindow* renderWindow, sfBool show);

////////////////////////////////////////////////////////////
/// Change the position of the mouse cursor on a window
///
/// \param renderWindow : Renderwindow object
/// \param left :         Left coordinate of the cursor, relative to the window
/// \param top :          Top coordinate of the cursor, relative to the window
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_SetCursorPosition(sfRenderWindow* renderWindow, unsigned int left, unsigned int top);

////////////////////////////////////////////////////////////
/// Change the position of a window on screen.
/// Only works for top-level windows
///
/// \param renderWindow : Renderwindow object
/// \param left :         Left position
/// \param top :          Top position
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_SetPosition(sfRenderWindow* renderWindow, int left, int top);

////////////////////////////////////////////////////////////
/// Change the size of the rendering region of a window
///
/// \param renderWindow : Renderwindow object
/// \param width :        New Width
/// \param height :       New Height
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_SetSize(sfRenderWindow* renderWindow, unsigned int width, unsigned int height);

////////////////////////////////////////////////////////////
/// Show or hide a window
///
/// \param renderWindow : Renderwindow object
/// \param show :         sfTrue to show, sfFalse to hide
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_Show(sfRenderWindow* renderWindow, sfBool show);

////////////////////////////////////////////////////////////
/// Enable or disable automatic key-repeat for keydown events.
/// Automatic key-repeat is enabled by default
///
/// \param renderWindow : Renderwindow object
/// \param enabled :      sfTrue to enable, sfFalse to disable
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_EnableKeyRepeat(sfRenderWindow* renderWindow, sfBool enabled);

////////////////////////////////////////////////////////////
/// Change the window's icon
///
/// \param renderWindow : Renderwindow object
/// \param width :        Icon's width, in pixels
/// \param height :       Icon's height, in pixels
/// \param pixels :       Pointer to the pixels in memory, format must be RGBA 32 bits
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_SetIcon(sfRenderWindow* renderWindow, unsigned int width, unsigned int height, sfUint8* pixels);

////////////////////////////////////////////////////////////
/// Activate or deactivate a window as the current target for rendering
///
/// \param renderWindow : Renderwindow object
/// \param active :       sfTrue to activate, sfFalse to deactivate
///
/// \return True if operation was successful, false otherwise
///
////////////////////////////////////////////////////////////
CSFML_API sfBool sfRenderWindow_SetActive(sfRenderWindow* renderWindow, sfBool active);

////////////////////////////////////////////////////////////
/// Display a window on screen
///
/// \param renderWindow : Renderwindow object
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_Display(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Get the input manager of a window
///
/// \param renderWindow : Renderwindow object
///
/// \return Reference to the input
///
////////////////////////////////////////////////////////////
CSFML_API sfInput* sfRenderWindow_GetInput(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Limit the framerate to a maximum fixed frequency for a window
///
/// \param renderWindow : Renderwindow object
/// \param limit :        Framerate limit, in frames per seconds (use 0 to disable limit)
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_SetFramerateLimit(sfRenderWindow* renderWindow, unsigned int limit);

////////////////////////////////////////////////////////////
/// Get time elapsed since last frame of a window
///
/// \param renderWindow : Renderwindow object
///
/// \return Time elapsed, in seconds
///
////////////////////////////////////////////////////////////
CSFML_API float sfRenderWindow_GetFrameTime(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Change the joystick threshold, ie. the value below which
/// no move event will be generated
///
/// \param renderWindow : Renderwindow object
/// \param threshold :    New threshold, in range [0, 100]
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_SetJoystickThreshold(sfRenderWindow* renderWindow, float threshold);

////////////////////////////////////////////////////////////
/// Draw something on a renderwindow
///
/// \param renderWindow :                     Renderwindow to draw in
/// \param postFX / sprite / string / shape : Object to draw
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_DrawPostFX(sfRenderWindow* renderWindow, sfPostFX* postFX);
CSFML_API void sfRenderWindow_DrawSprite(sfRenderWindow* renderWindow, sfSprite* sprite);
CSFML_API void sfRenderWindow_DrawShape (sfRenderWindow* renderWindow, sfShape*  shape);
CSFML_API void sfRenderWindow_DrawString(sfRenderWindow* renderWindow, sfString* string);

////////////////////////////////////////////////////////////
/// Save the content of a renderwindow to an image
///
/// \param renderWindow : Renderwindow to capture
///
/// \return Image instance containing the contents of the screen
///
////////////////////////////////////////////////////////////
CSFML_API sfImage* sfRenderWindow_Capture(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Clear the screen with the given color
///
/// \param renderWindow : Renderwindow to modify
/// \param color :        Fill color
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_Clear(sfRenderWindow* renderWindow, sfColor color);

////////////////////////////////////////////////////////////
/// Change the current active view of a renderwindow
///
/// \param renderWindow : Renderwindow to modify
/// \param view :         Pointer to the new view
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_SetView(sfRenderWindow* renderWindow, sfView* view);

////////////////////////////////////////////////////////////
/// Get the current active view of a renderwindow
///
/// \param renderWindow : Renderwindow
///
/// \return Current active view
///
////////////////////////////////////////////////////////////
CSFML_API const sfView* sfRenderWindow_GetView(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Get the default view of a renderwindow
///
/// \param renderWindow : Renderwindow
///
/// \return Default view of the render window
///
////////////////////////////////////////////////////////////
CSFML_API sfView* sfRenderWindow_GetDefaultView(sfRenderWindow* renderWindow);

////////////////////////////////////////////////////////////
/// Convert a point in window coordinates into view coordinates
///
/// \param renderWindow : Target Renderwindow
/// \param windowX :      X coordinate of the point to convert, relative to the window
/// \param windowY :      Y coordinate of the point to convert, relative to the window
/// \param viewX :        Pointer to fill with the X coordinate of the converted point
/// \param viewY :        Pointer to fill with the Y coordinate of the converted point
/// \param targetView :   Target view to convert the point to (pass NULL to use the current view)
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_ConvertCoords(sfRenderWindow* renderWindow, unsigned int windowX, unsigned int windowY, float* viewX, float* viewY, sfView* targetView);

////////////////////////////////////////////////////////////
/// Tell SFML to preserve external OpenGL states, at the expense of
/// more CPU charge. Use this function if you don't want SFML
/// to mess up your own OpenGL states (if any).
/// Don't enable state preservation if not needed, as it will allow
/// SFML to do internal optimizations and improve performances.
/// This parameter is false by default
///
/// \param renderWindow : Target Renderwindow
/// \param preserve :     True to preserve OpenGL states, false to let SFML optimize
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderWindow_PreserveOpenGLStates(sfRenderWindow* renderWindow, sfBool preserve);


#endif // SFML_RENDERWINDOW_H
