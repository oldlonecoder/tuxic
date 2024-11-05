//
// Created by oldlonecoder on 24-11-05.
//

#include "tddv.h"

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




namespace tux
{


tddv::~tddv() = default;
//{
//}


tddv::tddv(std::string app_name, int argc, char** argv): ui::application(std::move(app_name), argc, argv)
{
    // Init is RAII :
    application::setup();
    // setup() -> setup_ui().
}



log::code tddv::setup()
{
    application::setup();
    //...

    return setup_ui();
}


log::code tddv::setup_ui()
{
    return log::code::notimplemented;
}



log::code tddv::run()
{
    try
    {
        log::jnl() << log::fn::stamp << app_name() << log::eol;
        ui::event ev{};
        auto c = log::code::ok;
        while(!!(c = ui::event::get_stdin_event(ev,{65000,0})) && c != log::code::cancel)
        {
            if(ev.event_type == ui::event::type::MOUSE)
                log::info() << ev.data.mev.to_string() << log::eol;
        }

    }
    catch(log::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    terminate();
    return log::code::notimplemented;
}


log::code tddv::terminate()
{
    //...

    return application::terminate();
}



} // namespace tux


auto main(int argc, char** argv) -> int
{
    tux::tddv tddv{"tuxic_vision:tddv application!", argc,argv};
    return static_cast<int>(tddv.run());
}
