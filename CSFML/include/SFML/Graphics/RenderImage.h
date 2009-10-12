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

#ifndef SFML_RENDERIMAGE_H
#define SFML_RENDERIMAGE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Types.h>


////////////////////////////////////////////////////////////
/// Construct a new renderimage
///
/// \param width :       Width of the renderimage
/// \param height :      Height of the renderimage
/// \param depthBuffer : Do you want a depth-buffer attached? (useful only if you're doing 3D OpenGL on the renderimage)
///
////////////////////////////////////////////////////////////
CSFML_API sfRenderImage* sfRenderImage_Create(unsigned int width, unsigned int height, sfBool depthBuffer);

////////////////////////////////////////////////////////////
/// Destroy an existing renderimage
///
/// \param renderImage : renderimage to destroy
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderImage_Destroy(sfRenderImage* renderImage);

////////////////////////////////////////////////////////////
/// Get the width of the rendering region of a renderimage
///
/// \param renderImage : Renderimage object
///
/// \return Width in pixels
///
////////////////////////////////////////////////////////////
CSFML_API unsigned int sfRenderImage_GetWidth(sfRenderImage* renderImage);

////////////////////////////////////////////////////////////
/// Get the height of the rendering region of a renderimage
///
/// \param renderImage : Renderimage object
///
/// \return Height in pixels
///
////////////////////////////////////////////////////////////
CSFML_API unsigned int sfRenderImage_GetHeight(sfRenderImage* renderImage);

////////////////////////////////////////////////////////////
/// Activate or deactivate a renderimage as the current target for rendering
///
/// \param renderImage : Renderimage object
/// \param active :      sfTrue to activate, sfFalse to deactivate
///
/// \return True if operation was successful, false otherwise
///
////////////////////////////////////////////////////////////
CSFML_API sfBool sfRenderImage_SetActive(sfRenderImage* renderImage, sfBool active);

////////////////////////////////////////////////////////////
/// Make sure that what has been drawn so far is rendered
///
/// Use this function if you use OpenGL rendering commands,
/// and you want to make sure that things will appear on top
/// of all the SFML objects that have been drawn so far.
/// This is needed because SFML doesn't use immediate rendering,
/// it first accumulates drawables into a queue and
/// trigger the actual rendering afterwards.
///
/// You don't need to call this function if you're not
/// dealing with OpenGL directly.
///
/// \param Renderimage : Renderwindow object
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderImage_Flush(sfRenderImage* renderImage);

////////////////////////////////////////////////////////////
/// Draw something on a renderimage
///
/// \param renderImage :                      Renderimage to draw in
/// \param postFX / sprite / string / shape : Object to draw
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderImage_DrawPostFX(sfRenderImage* renderImage, sfPostFX* postFX);
CSFML_API void sfRenderImage_DrawSprite(sfRenderImage* renderImage, sfSprite* sprite);
CSFML_API void sfRenderImage_DrawShape (sfRenderImage* renderImage, sfShape*  shape);
CSFML_API void sfRenderImage_DrawString(sfRenderImage* renderImage, sfString* string);

////////////////////////////////////////////////////////////
/// Clear the renderimage with the given color
///
/// \param renderImage : Renderimage to modify
/// \param color :       Fill color
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderImage_Clear(sfRenderImage* renderImage, sfColor color);

////////////////////////////////////////////////////////////
/// Change the current active view of a renderimage
///
/// \param renderImage : Renderimage to modify
/// \param view :        Pointer to the new view
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderImage_SetView(sfRenderImage* renderImage, sfView* view);

////////////////////////////////////////////////////////////
/// Get the current active view of a renderimage
///
/// \param renderImage : Renderimage
///
/// \return Current active view
///
////////////////////////////////////////////////////////////
CSFML_API const sfView* sfRenderImage_GetView(sfRenderImage* renderImage);

////////////////////////////////////////////////////////////
/// Get the default view of a renderimage
///
/// \param renderImage : Renderimage
///
/// \return Default view of the renderimage
///
////////////////////////////////////////////////////////////
CSFML_API sfView* sfRenderImage_GetDefaultView(sfRenderImage* renderImage);

////////////////////////////////////////////////////////////
/// Get the viewport of a view applied to this target
///
/// \param renderImage : Renderimage object
/// \param view :        Target view
///
/// \return Viewport rectangle, expressed in pixels in the current target
///
////////////////////////////////////////////////////////////
CSFML_API sfIntRect sfRenderImage_GetViewport(sfRenderImage* renderImage, sfView* view);

////////////////////////////////////////////////////////////
/// Convert a point in image coordinates into view coordinates
///
/// \param renderImage : Renderimage object
/// \param windowX :     X coordinate of the point to convert, relative to the image
/// \param windowY :     Y coordinate of the point to convert, relative to the image
/// \param viewX :       Pointer to fill with the X coordinate of the converted point
/// \param viewY :       Pointer to fill with the Y coordinate of the converted point
/// \param targetView :  Target view to convert the point to (pass NULL to use the current view)
///
////////////////////////////////////////////////////////////
CSFML_API void sfRenderImage_ConvertCoords(sfRenderImage* renderImage, unsigned int windowX, unsigned int windowY, float* viewX, float* viewY, sfView* targetView);

////////////////////////////////////////////////////////////
/// Get the target image
///
/// \param renderImage : Renderimage object
///
/// \return Pointer to the target image
///
////////////////////////////////////////////////////////////
CSFML_API sfImage* sfRenderImage_GetImage(sfRenderImage* renderImage);

////////////////////////////////////////////////////////////
/// Check whether the system supports render images or not
///
/// \return sfTrue if the RenderImage class can be used
///
////////////////////////////////////////////////////////////
CSFML_API sfBool sfRenderImage_CanUseRenderImage();


#endif // SFML_RENDERIMAGE_H
