//#ifndef TUX_STRING_H
//#define TUX_STRING_H
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
#include <tuxvision/ui/widget/window.h>


namespace tux::ui::terminal
{
/*!
 * @brief screen's double back-buffer to be studied...
 */
class _TUXVISION_ desktop : public widget
{
    CLASSNAME(desktop)

    terminal::vchar::back_buffer _screen_buffer_{nullptr};

    std::vector<rectangle> _dirty_stack_{};
    std::list<window*> _windows_{};


    static desktop* the_screen;
    void refresh_zorder();
    void render_dirty(const ui::rectangle& rect);

    terminal::vchar::string::iterator peek_sb(ui::cxy xy);
public:
    desktop();
    explicit desktop(const std::string& _id);
    ~desktop() override;


    book::code update() override;
protected:
    friend class tux::ui::window;
    friend class tux::ui::widget;

    book::code dirty(const rectangle& _dirty_rect) override;

};

}
