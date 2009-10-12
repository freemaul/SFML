using System;
using System.Runtime.InteropServices;
using System.Security;
using SFML.Window;

namespace SFML
{
    namespace Graphics
    {
        ////////////////////////////////////////////////////////////
        /// <summary>
        /// Abstract base class for render targets (renderwindow, renderimage)
        /// </summary>
        ////////////////////////////////////////////////////////////
        public interface RenderTarget
        {
            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Width of the rendering region of the window
            /// </summary>
            ////////////////////////////////////////////////////////////
            uint Width {get;}

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Height of the rendering region of the window
            /// </summary>
            ////////////////////////////////////////////////////////////
            uint Height {get;}

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Default view of the window
            /// </summary>
            ////////////////////////////////////////////////////////////
            View DefaultView {get;}

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Current view active in the window
            /// </summary>
            ////////////////////////////////////////////////////////////
            View CurrentView {get;}

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Get the viewport of a view applied to this target
            /// </summary>
            /// <param name="view">Target view</param>
            /// <returns>Viewport rectangle, expressed in pixels in the current target</returns>
            ////////////////////////////////////////////////////////////
            IntRect GetViewport(View view);

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Convert a point in target coordinates into view coordinates
            /// This version uses the current view of the window
            /// </summary>
            /// <param name="x">X coordinate of the point to convert, relative to the target</param>
            /// <param name="y">Y coordinate of the point to convert, relative to the target</param>
            /// <returns>Converted point</returns>
            ////////////////////////////////////////////////////////////
            Vector2 ConvertCoords(uint x, uint y);

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Convert a point in target coordinates into view coordinates
            /// This version uses the given view
            /// </summary>
            /// <param name="x">X coordinate of the point to convert, relative to the target</param>
            /// <param name="y">Y coordinate of the point to convert, relative to the target</param>
            /// <param name="view">Target view to convert the point to</param>
            /// <returns>Converted point</returns>
            ////////////////////////////////////////////////////////////
            Vector2 ConvertCoords(uint x, uint y, View view);

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Clear the entire window with black color
            /// </summary>
            ////////////////////////////////////////////////////////////
            void Clear();

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Clear the entire window with a single color
            /// </summary>
            /// <param name="color">Color to use to clear the window</param>
            ////////////////////////////////////////////////////////////
            void Clear(Color color);

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Draw something into the window
            /// </summary>
            /// <param name="objectToDraw">Object to draw</param>
            ////////////////////////////////////////////////////////////
            void Draw(Drawable objectToDraw);

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Apply a post-fx to the window
            /// </summary>
            /// <param name="postFx">PostFx to apply</param>
            ////////////////////////////////////////////////////////////
            void Draw(PostFx postFx);

            ////////////////////////////////////////////////////////////
            /// <summary>
            /// Make sure that what has been drawn so far is rendered.
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
            /// </summary>
            ////////////////////////////////////////////////////////////
            void Flush();
        }
    }
}
