
#ifndef WXSFMLCANVAS_HPP
#define WXSFMLCANVAS_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <wx/wx.h>


////////////////////////////////////////////////////////////
/// wxSFMLCanvas allows to run SFML in a wxWidgets control
////////////////////////////////////////////////////////////
class wxSFMLCanvas : public wxControl, public sf::RenderWindow
{
public :

    ////////////////////////////////////////////////////////////
    /// Construct the wxSFMLCanvas
    ///
    /// \param Parent :   Parent of the control (NULL by default)
    /// \param Id :       Identifier of the control (-1 by default)
    /// \param Position : Position of the control (wxDefaultPosition by default)
    /// \param Size :     Size of the control (wxDefaultSize by default)
    /// \param Style :    Style of the control (0 by default)
    ///
    ////////////////////////////////////////////////////////////
    wxSFMLCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);

    ////////////////////////////////////////////////////////////
    /// Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~wxSFMLCanvas();

private :

    DECLARE_EVENT_TABLE()

    ////////////////////////////////////////////////////////////
    /// Notification for the derived class that moment is good
    /// for doing its update and drawing stuff
    ///
    ////////////////////////////////////////////////////////////
    virtual void OnUpdate();

    ////////////////////////////////////////////////////////////
    /// Called when the window is idle - we can refresh our
    /// SFML window
    ///
    ////////////////////////////////////////////////////////////
    void OnIdle(wxIdleEvent&);

    ////////////////////////////////////////////////////////////
    /// Called when the window is repainted - we can display our
    /// SFML window
    ///
    ////////////////////////////////////////////////////////////
    void OnPaint(wxPaintEvent&);

    ////////////////////////////////////////////////////////////
    /// Called when the window needs to draw its background
    ///
    ////////////////////////////////////////////////////////////
    void OnEraseBackground(wxEraseEvent&);
};


#endif // WXSFMLCANVAS_HPP
