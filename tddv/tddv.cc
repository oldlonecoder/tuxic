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
// {
//     // Can't delete test widget here because the logger is already closed.
// }


tddv::tddv(std::string app_name, int argc, char** argv): ui::application(std::move(app_name), argc, argv){}


/*!
 * 
 * @return 
 */
log::code tddv::tddv_setup()
{
    //application::setup();
    log::debug() << log::eol;
    //...

    return setup_ui();
}


/*!
 * 
 * @return 
 */
log::code tddv::setup_ui()
{

    _test_widget_ = new ui::widget(nullptr, "_test_widget_");
    log::test() << _test_widget_->pretty_id() << "has been created..." << log::eol;
    _test_widget_->set_geometry({{2,5},ui::size{40,5}});
    _test_widget_->set_theme("C64");
    _test_widget_->set_components(ui::components::Frame);
    _test_widget_->draw();
    auto p = _test_widget_->begin_draw();
    p.home() << ui::cxy{2,2} << color::lightsteelblue3 <<  glyph::pi << "  widget::" << _test_widget_->id();
    _test_widget_->end_draw(p);
    _test_widget_->show();
    log::jnl() << app_name() << " ui..." << log::code::done << log::eol;
    return log::code::done;
}


/*!
 * 
 * @return 
 */
log::code tddv::run()
{
    try
    {
        tddv_setup();
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
    delete _test_widget_;
    return application::terminate();
}



} // namespace tux


auto main(int argc, char** argv) -> int
{
    tux::tddv tddv{"tuxic_vision:tddv application!", argc,argv};
    return static_cast<int>(tddv.run());
}
