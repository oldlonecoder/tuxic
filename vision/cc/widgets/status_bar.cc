//
// Created by oldlonecoder on 24-11-01.
//



/******************************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                                        *
 *   serge.lussier@oldlonecoder.club                                                      *
 *                                                                                        *
 *                                                                                        *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (Serge Lussier)                                                        *
 *   and no one else then not even {copilot, chatgpt, or any other AI calamities}         *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply To the Code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 ******************************************************************************************/

//#pragma once


#include <tuxvision/ui/widget/status_bar.h>

namespace tux::ui
{
status_bar::status_bar(widget* _parent, const std::string& _id):widget(_parent, _id)
{
    set_components(ui::components::None);
    set_anchor(ui::anchor::Width|ui::anchor::Bottom);
    set_geometry({{0,0},ui::size{1,1}});
    _geometry_.dwh.set_min_size(-1,1);
    _geometry_.dwh.set_max_size(-1,1);
    log::test() << pretty_id() << " min-max size are set" << log::eol;
    log::debug() << " check log::contents size: " << log::current_section->contents.size() << log::eol;
}


log::code status_bar::show()
{
    return widget::show();
}


void status_bar::activate()
{
    widget::activate();
}


void status_bar::set_focus()
{
    widget::set_focus();
}


log::code status_bar::update()
{
    return widget::update();
}


log::code status_bar::draw()
{
    widget::draw();

    return widget::draw();
}


/*!
 * @brief Add a child widge
 * @param wid Widget ID
 * @param av Anchor value
 * @return pointer to the newly created widgets
 */
widget* status_bar::add_widget(const std::string& wid, ui::anchor::value av)
{
    auto w = new widget(this, wid);
    w->set_anchor(av);
    position_child(w);
    return w;
}


/*!
 * 
 * @param lid
 * @param av 
 * @param cc 
 * @param _initial_text 
 * @return 
 */
label* status_bar::add_label(const std::string& lid, ui::anchor::value av, ui::components::type cc, const std::string& _initial_text)
{
    auto lbl = new label(this, lid);
    lbl->set_anchor(av);
    if(!+_initial_text.empty()) lbl->set_text(_initial_text);
    
    position_child(lbl);
    return lbl;
}


log::code status_bar::dirty(const rectangle& dirty_rect)
{
    return widget::dirty(dirty_rect);
}
} // namespace tux::ui
