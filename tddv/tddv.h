//
// Created by oldlonecoder on 24-11-05.
//

//#ifndef TDDV_H
//#define TDDV_H
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

#include <tuxic/vision/application.h>
#include <tuxic/vision/events.h>
namespace tux
{

class tddv : public ui::application
{

    CLASSNAME(tddv)

public:

    ~tddv()override;
    tddv(std::string app_name, int argc, char **argv);

    log::code run() override;
    log::code terminate() override;

protected:
    log::code setup() override;
    log::code setup_ui()  override;

    //size_t push_event(ui::event&& ev) override;
    //ui::event pop_event() override;

};

} // tux

//#endif //TDDV_H
