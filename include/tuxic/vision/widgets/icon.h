//
// Created by oldlonecoder on 24-11-08.
//

//#ifndef ICON_H
//#define ICON_H
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
#include <tuxic/vision/widget.h>
namespace tux::ui
{

class TUXIC_FRM icon : public widget
{
    glyph::type _icon_{glyph::alien};

public:
    icon()=default;
    icon(object* _parent, const std::string& ic_id, glyph::type _type_value);
    ~icon() override = default;

    log::code draw() override;
    void set(glyph::type _type_value) { _icon_ = _type_value; }

};


} // namespace tux::ui
