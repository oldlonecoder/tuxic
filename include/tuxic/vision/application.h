// Created by oldlonecoder on 8/13/24.
//

//#ifndef INTUI_GLOBALS_H
//#define INTUI_GLOBALS_H
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


#include <tuxic/vision/events.h>
#include <csignal>
#include <memory>
#include <tuxic/tools/cadres.h>


namespace tux::ui
{

class TUXIC_FRM application
{

    CLASSNAME_START(application)

    static void sig_interrupted(int);
    static void sig_aborted(int);
    static void sig_crash(int);
    static void sig_winch(int);

    std::vector<std::string_view> _args_{};
    std::string _app_name_{};
    static application* _app_;

    event::stream _events_stack_{};

public:
    application() = delete;
    virtual ~application();
    application(std::string app_name, int argc, char **argv);

    virtual log::code run() = 0; //{ return log::code::notimplemented;}
    virtual log::code terminate();


    static application& app();
//    static desktop* screen_desktop();
    [[nodiscard]] std::string app_name() const;


protected:
    log::code setup();
    virtual log::code setup_ui(){ return log::code::reimplement; }
    virtual log::code install_signals();

    virtual size_t push_event(event&& ev);
    virtual event pop_event();

    //terminal::desktop*  _current_screen_{nullptr};

};



}
