//
// Created by oldlonecoder on 24-11-08.
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


#include <tuxic/vision/widgets/icon.h>


namespace tux::ui
{
icon::icon(object* _parent, const std::string& ic_id, glyph::type _type_value):widget(_parent, ic_id), _icon_(_type_value)
{
}



log::code icon::draw()
{
    clear();
    auto p = begin_draw();
    p.home() << ui::cxy{0,0} << _icon_;
    end_draw(p);
    return log::code::done;
}


} // namespace tux::ui
