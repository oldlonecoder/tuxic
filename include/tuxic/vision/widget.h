
/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all Code in this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/



#pragma once

#include <tuxic/tools/object.h>
#include <tuxic/vision/tuxns.h>
#include <tuxic/vision/terminal.h>
#include <tuxic/vision/vchar.h>
#include <list>

namespace tux::ui
{


namespace terminal
{
class desktop;
}


class TUXIC_FRM widget : public object
{
    CLASSNAME(widget)

    terminal::vchar::back_buffer _back_buffer_{nullptr};

    friend class terminal::desktop;

public:
    widget();
    widget(object* _parent_obj, const std::string& _id);

    ~widget() override;


    log::code set_geometry(const rectangle& r);
    log::code set_theme(const std::string& theme_id);
    std::string theme_name(){ return _theme_id_; };

    log::code peek_xy(ui::cxy xy);
    terminal::vchar::string::iterator at(ui::cxy xy);
    terminal::vchar::string::iterator operator[](ui::cxy xy);
    widget& operator*() { return *this; }
    log::code set_anchor(ui::anchor::value _ank);
    virtual log::code show(ui::uistate::Type st);
    virtual log::code show();
    virtual log::code hide();



    // --------- State modifiers --------------------------------------------------------
    virtual void activate();

    virtual void set_focus();
    bool is_visible();
    [[nodiscard]] bool is_active() const;
    [[nodiscard]] bool is_focus() const;
    [[nodiscard]] bool is_hidden() const;
    [[nodiscard]] bool is_window() const { return _uistyle_& ui::uistyle::Window; }


    class TUXIC_FRM painter_dc
    {
        rectangle _geometry_{};
        widget* _widget_{nullptr};
        color::pair _colors_{};
        terminal::vchar::string::iterator _iterator_{};
        friend class widget;
        friend class screen;
        friend class window;
        //...
    public:
        painter_dc() = default;
        ~painter_dc() = default;
        painter_dc(widget* parent_widget, const rectangle& r);
        log::code at(ui::cxy xy);
        log::code sync();
        painter_dc& home();
        painter_dc& clear(const rectangle& r={});
        painter_dc& operator << (ui::cxy new_xy);
        painter_dc& operator << (char ch);
        painter_dc& operator << (const char* str);
        painter_dc& operator << (const std::string& str);
        painter_dc& operator << (const tux::string& str);
        painter_dc& operator << (color::code fgcol);
        painter_dc& operator << (color::pair colp);
        painter_dc& operator << (cadre::index ci);
        painter_dc& operator << (glyph::type ic);
        painter_dc& operator << (accent_fr::type fr);
        painter_dc& operator << (terminal::vchar vch);
        painter_dc& operator << (terminal::vchar::string strvch);
        painter_dc& set_background_color(color::code bgcol);
        painter_dc& operator*() { return *this; }
        log::code operator ++();
        log::code operator +=(size_t _offset);
    };

    virtual log::code draw();
    widget::painter_dc begin_draw(const rectangle& sub_area={});
    void end_draw(widget::painter_dc& edc);
    void clear();
    virtual log::code update();

/*
    static constexpr u16 None      = 0;
    static constexpr u16 Caption   = 0x0001; ///< Caption widget
    static constexpr u16 Glyph     = 0x0002; ///< Glyph widget
    static constexpr u16 StatusBar = 0x0004; ///< Status bar
    static constexpr u16 HScrollBar= 0x0008; ///< horizontal scrollbar
    static constexpr u16 VScrollBar= 0x0010; ///< vertical scrollbar
    static constexpr u16 Frame     = 0x0020; ///< Widget has a frame surrounding it (within geometry)
    static constexpr u16 MenuBar   = 0x0040; ///< Widget has a MenuBar system

 */
    bool has_frame();
    bool has_caption();
    bool has_glyph();
    bool has_status_bar();
    bool has_horizontal_scroll_bar();
    bool has_vertical_scroll_bar();
    bool has_menu_bar();
    bool has_component(ui::uistyle::Type b);
    bool has_style(ui::uistyle::Type b);
    bool has_status(ui::uistate::Type b);
    bool has_class(ui::uiclass::Type b);

    log::code anchor_widget(widget* w);

    virtual log::code setup_ui();

protected:
    ui::size _size_limits_{0,0, ui::cxy{1,1},ui::cxy{0xFFFF,0xFFFF}};
    rectangle _geometry_{}; ///< Dimensions, internal cursor position
    rectangle _dirty_area_{};

    void set_components(ui::components::type c);
    void set_uistyle(ui::uistyle::Type s);
    void set_uiclass(ui::uiclass::Type cls);

    std::string _theme_id_{"Default"};
    // --------- UI style and State----------------
    color::pair                          _colors_{};
    ui::colors::attr_db::components _states_colors_{}; ///< Widget States colors database.
    ui::colors::attr_db::elements   _elements_{};  ///< Widget colors elements database
    ui::anchor::value               _anchor_       {ui::anchor::None};     ///< AutoFit values for widget placements within the parent 's widget.
    ui::uistate::Type               _uistate_      {ui::uistate::Active};  ///< ...widget state...{ visible, active,focus, etc ... }
    ui::uistyle::Type               _uistyle_      {ui::uistyle::None};    ///< Toplevel Window or child widget components
    ui::uiclass::Type               _uiclass_      {ui::uiclass::None};    ///< css-like named class property of this widget ( ex. : Error,Warning,Fatal,Information, etc... )
    ui::components::type            _uicomponents_ {ui::components::None}; ///< Sub/child-widgets components


    // --------------------------------------------

    virtual log::code auto_fit();
    virtual log::code resize(ui::size new_sz);
    virtual log::code draw_frame(const rectangle& r);
    virtual log::code dirty(const rectangle& dirty_rect);
    terminal::vchar::string::iterator _iterator_{}; ///< Normal std::vector iterator available for navigation and io.
    log::code update_child(widget* w);
    log::code render();
    log::code position_child(widget* w);
    virtual log::code setup_components();

public:
    void set_minimum_size(int w, int h){_size_limits_.min_size = ui::cxy{w,h};}
    void set_maximum_size(int w, int h){_size_limits_.max_size = ui::cxy{w,h};}
private:

    friend class screen;


};




} // namespace tux::ui
