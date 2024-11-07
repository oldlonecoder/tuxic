

#include <tuxic/vision/application.h>
#include <tuxic/vision/terminal.h>
#include <csignal>
#include <utility>


//#include <memory>


namespace tux::ui
{

application* application::_app_{nullptr};



application::application(std::string  a_id, int argc, char** argv): _app_name_(std::move(a_id))
{
    if(argc && argv)
        _args_ = tux::string::string_view_list(argc,argv);

    if(application::_app_ == nullptr)
    {
        application::_app_ = this;
    }
    else
        abort();
    setup();
}


application::~application()
{
    //...
    _args_.clear();
    ///...
}


void application::sig_interrupted(int)
{
    log::interrupted() << log::eol;
    terminal::end();
    log::purge(nullptr);
    //application::app().terminate();
    exit(0);
}



void application::sig_aborted(int)
{
    log::aborted() << log::eol;
    terminal::end();
    log::purge(nullptr);
    //application::app().terminate();
    exit(0);
}

void application::sig_crash(int)
{
    log::segfault()  << log::eol;
    //terminal::end();
    //log::purge(nullptr);
    //application::app().terminate();
    exit(0);
}


void application::sig_winch(int)
{
    terminal::query_winch() ;
    //...
}



application& application::app()
{
    if(!application::_app_)
        throw log::exception() [log::except() << log::fn::func << log::fn::endl << " no instance of application!"];

    return *application::_app_;
}


std::string application::app_name() const
{
    tux::string text{};
    auto [gh,colors] = log::return_code_attributes(log::code::object_ptr);
    text
        | colors()
        | gh
        | class_name()
        | color::reset | "::";
    auto [gl, cc] = log::return_code_attributes(log::code::object_id);
    text
        | cc()
        | gl
        | _app_name_
        | color::reset | ' ';

    return text();
}


// desktop *application::screen_desktop()
// {
//     return desktop::instance();
// }

log::code application::install_signals()
{

    std::signal(SIGSEGV, &application::sig_crash);
    log::jnl() << "signal SIGSEV installed."  << log::eol;
    std::signal(SIGABRT, &application::sig_aborted);
    log::jnl() << "signal SIGABRT installed."  << log::eol;
    std::signal(SIGINT, &application::sig_interrupted);
    log::jnl() << "signal SIGINT installed."  << log::eol;
    std::signal(SIGWINCH, &application::sig_winch);
    log::jnl() << "signal SIGWINCH installed."  << log::eol;
    // std::signal(SIGHUP, &application::sig_winch);
    std::signal(SIGKILL, &application::sig_interrupted);
    log::jnl() << "signal SIGKILL installed." << log::eol;
    std::signal(SIGTERM, &application::sig_interrupted);
    log::jnl() << "signal SIGTERM installed." << log::eol;

    return log::code::done;
}

log::code application::setup()
{
    //...
    log::init();
    install_signals();
    terminal::begin();
    //_current_screen_ = &terminal::screen::create("1");
    return log::code::done;
}


log::code application::terminate()
{
    terminal::end();
    log::end();
    return log::code::reimplement;
}




size_t application::push_event(event&& ev)
{
    _events_stack_.push(ev);
    return _events_stack_.size();
}


event  application::pop_event()
{
    if(_events_stack_.empty())
    {
        log::error() << log::fn::func << log::code::empty << log::eol;
        return {};
    }

    auto ev = _events_stack_.top();
    _events_stack_.pop();
    return ev;
}


}
