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


//#include <tuxvision/ui/widget/window.h>
#include <tuxvision/ui/widget/uiscreen.h>

namespace tux::ui
{



/*!
 * \brief window::window
 * \param _parent
 * \param _id
 * \param _components additional window;s sub-components
 * @note Window class objects are systematically toplevel widget.
 */
window::window(object *_parent, const std::string &_id, ui::components::type _components): widget(_parent,_id)
{
    _anchor_=0;
    set_components(_components); // |ui::components::MenuBar|ui::components::StatusBar);
    set_uistyle(ui::uistyle::Window);

}



window::~window()
= default;

book::code window::hide()
{
    //_desktop_->hide_window(this);
    return book::code::notimplemented;
}


/*!
 * @brief Show on the screen.
 * @return done;
 */
book::code window::show()
{
    //if(!_screen_) return book::code::rejected;
    //...
    //_screen_->add_window(this);
    _uistate_ |= ui::uistate::Visible;
    render();
    return book::code::done;
}


book::code window::setup_ui()
{
    if(_uicomponents_ == ui::components::StatusBar)
    {
        book::log() << book::fn::func << pretty_id() << " Adding StatusBar component:" << book::eol;
        _status_bar_ = new status_bar(this,id() + "_status_bar");
        anchor_widget(_status_bar_);
    }
    return book::code::done;
}


/*!
 * @brief  window::dirty addresses directly the screen's dirty function that owns this window
 * @param _dirty_rect
 * @return
 */
book::code window::dirty(const rectangle& _dirty_rect)
{
    auto r = widget::dirty(_dirty_rect);
    if(!r)
        return book::code::rejected;
    if(_desktop_)
        return _desktop_->dirty(_dirty_area_);
    return book::code::null_ptr;

}


}
