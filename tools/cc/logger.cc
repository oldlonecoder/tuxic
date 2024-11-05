//
// Created by oldlonecoder on 14/06/24.
//

#include <tuxic/tools/logger.h>


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
namespace Fs = std::filesystem;


namespace tux
{
//std::vector<log> log::logs{};
std::mutex log_guard{};

log::section::list log::sections{};
log::section::list::iterator log::current_section{};





bool operator !(log::code c)
{
    return (c != log::code::accepted)&&
           (c != log::code::ok)      &&
           (c != log::code::success) &&
           (c != log::code::done)    &&
           (c != log::code::ready)   &&
           (c != log::code::finish)  &&
           (c != log::code::complete);
}



std::map<log::type, const char*> enums_type_dictionary = {
    {log::type::none,        "none"},
    {log::type::err  ,       "err"},
    {log::type::warning,     "warning"},
    {log::type::fatal,       "fatal"},
    {log::type::except,      "exception"},
    {log::type::message,     "message"},
    {log::type::output,      ""},
    {log::type::debug,       "debug"},
    {log::type::info,        "info"},
    {log::type::comment,     "comment"},
    {log::type::syntax,      "syntax error"},
    {log::type::status,      "status"},
    {log::type::test,        "test"},
    {log::type::interrupted, "interrupted"},
    {log::type::aborted,     "aborted"},
    {log::type::segfault,    "segmentation fault"},
    {log::type::log,         "log"}
};


std::map<log::code, const char*> return_codes_dictionary = {
    {log::code::ok,             "ok"},
    {log::code::accepted,       "accepted"},
    {log::code::success,        "success "},
    {log::code::rejected,       "rejected"},
    {log::code::failed,         "failed"},
    {log::code::empty,          "empty"},
    {log::code::full,           "full"},
    {log::code::notempty,       "not empty"},
    {log::code::implemented,    "implemented"},
    {log::code::notimplemented, "not implemented"},
    {log::code::untested,       "untested"},
    {log::code::eof,            "end of file"},
    {log::code::eos,            "end of stream or string"},
    {log::code::null_ptr,       "null pointer"},
    {log::code::notexist,       "does not exist"},
    {log::code::exist,          "exist"},
    {log::code::unexpected,     "unexpected"},
    {log::code::expected,       "expected"},
    {log::code::blocked,        "blocked"},
    {log::code::locked,         "locked"},
    {log::code::overflow,       "buffer overflow"},
    {log::code::oob,            "out of boundaries"},
    {log::code::reimplement,    "need to be re-implemented in derived instances"},
    {log::code::done,           "done"},
    {log::code::complete,       "completed"},
    {log::code::finish,         "finished"},
    {log::code::undefined,      "undefined"},
    {log::code::ready,          "Ready"},
    {log::code::terminate,      "terminate"},
    {log::code::timeout,        "timeout"},
    {log::code::divbyzero,      "division by zero"},
    {log::code::notvisible,     "not visible"},
    {log::code::cancel,         "cancel"},
    {log::code::object_ptr,     "object"},
    {log::code::object_id,      "object id"},
};


std::map<log::action, const char*> actions_dictionary= {
    {log::action::enter,   "enter"},
    {log::action::leave,   "leave"},
    {log::action::begin,   "begin"},
    {log::action::end,     "end"},
    {log::action::commit,  "commit"},
    {log::action::continu, "continue"},

};


std::map<log::fn, const char*> functions_dictionary= {

    {log::fn::endl,           "end line"},
    {log::fn::func,            "function"},
    {log::fn::file,           "file"},
    {log::fn::line,           "line"},
    {log::fn::stamp,          "stamp"},
    {log::fn::hour,           "hour"},
    {log::fn::minute,         "minute"},
    {log::fn::seconds,        "seconds"},
    {log::fn::weekday,        "weekday"},
    {log::fn::month,          "month name"},
    {log::fn::dayname,        "day name"},
    {log::fn::day,            "day"},
    {log::fn::monthnum,       "month number"},
    {log::fn::year,           "year"}
};



std::map<log::type, std::pair<glyph::type, color::pair>> types_database={

    {log::type::none,        {glyph::computer,  {color::aquamarine1         , color::reset }}},
    {log::type::err,         {glyph::err1,      {color::red4                , color::reset }}},
    {log::type::warning,     {glyph::warning,   {color::yellow              , color::reset }}},
    {log::type::fatal,       {glyph::dead_head, {color::hotpink4            , color::reset }}},
    {log::type::except,      {glyph::bolt,      {color::skyblue3            , color::reset }}},
    {log::type::message,     {glyph::comment,   {color::green4              , color::reset }}},
    {log::type::output,      {glyph::notepad,   {color::grey39              , color::reset }}},
    {log::type::debug,       {glyph::bug,       {color::pink3               , color::reset }}},
    {log::type::info,        {glyph::info,      {color::lightskyblue4       , color::reset }}},
    {log::type::comment,     {glyph::comment,   {color::grey42              , color::reset }}},
    {log::type::syntax,      {glyph::handwrite, {color::lighcoreateblue     , color::reset }}},
    {log::type::status,      {glyph::admin,     {color::lightcyan3          , color::reset }}},
    {log::type::test,        {glyph::file,      {color::aquamarine3         , color::reset }}},
    {log::type::interrupted, {glyph::circle_x,  {color::khaki3              , color::reset }}},
    {log::type::aborted,     {glyph::stop,      {color::red4                , color::reset }}},
    {log::type::segfault,    {glyph::bomb,      {color::sandybrown          , color::reset }}},
    {log::type::log,         {glyph::log,       {color::orangered1          , color::reset }}}
    //...
};


std::map<log::action      , std::pair<glyph::type, color::pair>> actions_color_db = {
    {log::action::enter   , {glyph::enter        , {color::white               , color::reset}}},
    {log::action::leave   , {glyph::file         , {color::white               , color::reset}}},
    {log::action::begin   , {glyph::chronos      , {color::white               , color::reset}}},
    {log::action::end     , {glyph::dead_head    , {color::white               , color::reset}}},
    {log::action::commit  , {glyph::pencil_dr    , {color::white               , color::reset}}},
    {log::action::continu , {glyph::success      , {color::white               , color::reset}}},
};

std::map<log::code, std::pair<glyph::type, color::pair>> codes_database={
    {log::code::ok,              {glyph::thumb_up,        {color::lime              ,color::reset }}},
    {log::code::accepted,        {glyph::thumb_up,        {color::lime              ,color::reset }}},
    {log::code::success,         {glyph::success,         {color::darkgreen         ,color::reset }}},
    {log::code::rejected,        {glyph::thumb_down,      {color::hotpink4          ,color::reset }}},
    {log::code::failed,          {glyph::poop,            {color::darkgoldenrod     ,color::reset }}},
    {log::code::empty,           {glyph::arrowright,      {color::lighcoreategrey   ,color::reset }}},
    {log::code::full,            {glyph::small_dot,       {color::white             ,color::reset }}},
    {log::code::notempty,        {glyph::big_dot,         {color::white             ,color::reset }}},
    {log::code::implemented,     {glyph::arrow_head_right,{color::lime              ,color::reset }}},
    {log::code::notimplemented,  {glyph::err1,            {color::orange3           ,color::reset }}},
    {log::code::untested,        {glyph::flag,            {color::yellow            ,color::reset }}},
    {log::code::eof,             {glyph::baseline,        {color::white             ,color::reset }}},
    {log::code::eos,             {glyph::baseline,        {color::white             ,color::reset }}},
    {log::code::null_ptr,        {glyph::circle_x,        {color::hotpink4          ,color::reset }}},
    {log::code::notexist  ,      {glyph::circle_x ,       {color::white             ,color::reset }}},
    {log::code::exist     ,      {glyph::star5 ,          {color::white             ,color::reset }}},
    {log::code::unexpected,      {glyph::flag ,           {color::yellow            ,color::reset }}},
    {log::code::expected  ,      {glyph::cat ,            {color::white             ,color::reset }}},
    {log::code::blocked   ,      {glyph::unauth ,         {color::indianred3        ,color::reset }}},
    {log::code::locked    ,      {glyph::err3 ,           {color::white             ,color::reset }}},
    {log::code::overflow  ,      {glyph::dead_head,       {color::red4              ,color::reset }}},
    {log::code::oob       ,      {glyph::alien,           {color::red4              ,color::reset }}},
    {log::code::reimplement,     {glyph::log,             {color::yellow            ,color::reset }}},
    {log::code::done       ,     {glyph::ok,              {color::yellow            ,color::reset }}},
    {log::code::complete   ,     {glyph::ok,              {color::yellow            ,color::reset }}},
    {log::code::finish     ,     {glyph::ok,              {color::lime              ,color::reset }}},
    {log::code::undefined  ,     {glyph::err3,            {color::red               ,color::reset }}},
    {log::code::ready      ,     {glyph::ok,              {color::lime              ,color::reset }}},
    {log::code::terminate  ,     {glyph::flag,            {color::hotpink4          ,color::reset }}},
    {log::code::timeout    ,     {glyph::chronos,         {color::lime              ,color::reset }}},
    {log::code::divbyzero  ,     {glyph::circle_x,        {color::red4              ,color::reset }}},
    {log::code::notvisible ,     {glyph::circle_x,        {color::yellow            ,color::reset }}},
    {log::code::cancel     ,     {glyph::circle_x,        {color::red4              ,color::reset }}},
    {log::code::object_ptr ,     {glyph::log,             {color::lightsteelblue3   ,color::reset }}},
    {log::code::object_id ,      {glyph::arrowright,      {color::yellow            ,color::reset }}},

};


std::map<log::fn, std::pair<glyph::type, color::pair>> functions_database={

    {log::fn::stamp     ,      {glyph::chronos  ,   {color::skyblue3          ,color::reset }}},
    {log::fn::func      ,      {glyph::function ,   {color::skyblue3          ,color::reset }}},
    {log::fn::file      ,      {glyph::file     ,   {color::lightcyan3        ,color::reset }}},
    {log::fn::line      ,      {glyph::baseline ,   {color::lime              ,color::reset }}},
    {log::fn::stamp     ,      {glyph::chronos  ,   {color::yellow            ,color::reset }}},
    {log::fn::hour      ,      {glyph::chronos  ,   {color::white             ,color::reset }}},
    {log::fn::minute    ,      {glyph::chronos  ,   {color::white             ,color::reset }}},
    {log::fn::seconds   ,      {glyph::chronos  ,   {color::white             ,color::reset }}},
    {log::fn::weekday   ,      {glyph::fabric   ,   {color::yellow            ,color::reset }}},
    {log::fn::month     ,      {glyph::chronos  ,   {color::white             ,color::reset }}},
    {log::fn::dayname   ,      {glyph::star5    ,   {color::white             ,color::reset }}},
    {log::fn::day       ,      {glyph::star5    ,   {color::white             ,color::reset }}},
    {log::fn::monthnum  ,      {glyph::star5    ,   {color::white             ,color::reset }}},
    {log::fn::year      ,      {glyph::star5    ,   {color::white             ,color::reset }}}

};


std::string log::to_string(log::type ty)
{
    return enums_type_dictionary[ty];
}

std::string log::to_string(log::code cod)
{
    return return_codes_dictionary[cod];
}


std::pair<glyph::type, color::pair> log::type_attributes(log::type ty)
{
    return types_database[ty];
}

std::pair<glyph::type, color::pair> log::return_code_attributes(log::code cod)
{
    return codes_database[cod];
}

std::pair<glyph::type, color::pair> log::function_attributes(log::fn fn)
{
    return functions_database[fn];
}

std::pair<glyph::type, color::pair> log::action_attributes(log::action a)
{
    return actions_color_db[a];
}

std::string log::to_string(log::fn fn)
{
    return functions_dictionary[fn];
}

std::string log::to_string(log::action ac)
{
    return actions_dictionary[ac];
}




log &log::error(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::err, log::code::failed, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::warning(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::warning, log::code::ok, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::fatal(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::fatal, log::code::failed, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::except(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::except, log::code::rejected, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::message(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::message, log::code::implemented, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::out(std::source_location src)
{

    log_guard.lock();
    auto& r = **log::current_section << log{};
    r.text | "\r\n";
    log_guard.unlock();
    return r;
    // log_guard.lock();
    // if(log::sections.empty())
    // {
    //     abort();
    //     auto& r = **log::current_section << log{log::type::warning, log::code::empty, src};
    //     r << " using uninitialized log storage -  Initializing with default: 'globals'";
    //     r << "\r\n";
    //     log_guard.unlock();
    //     return r;
    // }
    //
    // if(!log::current_section->contents.empty())
    // {
    //     //@todo apply encoded newline : either ascii or html
    //     auto& le = log::current_section->contents.back();
    //     le.text | "\r\n"; // this way we make sure that we set new line for all oses.
    //     log_guard.unlock();
    //     return le;
    // }
    // auto& r = **log::current_section << log{log::type::output, log::code::empty, src};
    // log_guard.unlock();
    // return r;
}

log &log::debug(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::debug, log::code::ok, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::info(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::info, log::code::implemented, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::comment(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::comment, log::code::implemented, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::syntax(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::syntax, log::code::rejected, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::status(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::status, log::code::implemented, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::test(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::test, log::code::implemented, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::interrupted(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::interrupted, log::code::rejected, src};
    r.init_header();
    log_guard.unlock();
    return r;
}

log &log::aborted(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::aborted, log::code::rejected, src};
    r.init_header();
    log_guard.unlock();
    return r;
}


log &log::segfault(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::segfault, log::code::blocked, src};
    r.init_header();
    log_guard.unlock();
    return r;
}


log& log::jnl(std::source_location src)
{
    log_guard.lock();
    auto& r = **log::current_section << log{log::type::log, log::code::blocked, src};
    r.init_header();
    log_guard.unlock();
    return r;

}


log &log::operator<<(const std::string &txt)
{
    text << txt;
    return *this;
}

log &log::operator<<(const char *txt)
{
    text << txt;
    return *this;
}

log &log::operator<<(std::string_view txt)
{
    text << txt;
    return *this;
}

log &log::operator<<(const rectangle &r)
{
    text << r.tostring();
    return *this;
}

log &log::operator<<(cxy pt)
{
    text | std::format("{},{}", pt.x, pt.y);
    return *this;
}

log &log::operator<<(color::code col)
{
    text | col;
    return *this;
}

log &log::operator<<(color::pair fgbg)
{
    text | fgbg();
    return *this;
}

log &log::operator<<(glyph::type gh)
{
    text | gh;
    return *this;
}

log &log::operator<<(log::type ty)
{
    auto [gh,colors] = log::type_attributes(ty);
    text | colors | gh  | log::to_string(ty) | color::reset;
    return *this;
}


log &log::operator<<(accent_fr::type ac)
{
    text | accent_fr::data[ac];
    return *this;
}

void log::init_header()
{
    if(_headercomp_.stamp)
    {
        auto txt{tux::string::now("%H:%M:%S")};
        auto [ic, a] = log::function_attributes(log::fn::stamp);
        tux::string acc;
        acc | a.fg | glyph::data[ic]  | txt;
        text | acc() | " ";
    }
    if(_headercomp_.type)
    {
        auto [gh,colors] = log::type_attributes(_type_);
        text | colors | gh  | ' ' | log::to_string(_type_) | color::reset | ' ';
    }

    if(_headercomp_.file)
    {
        auto [gh, colors] = log::function_attributes(log::fn::file);
        tux::string txt = location.file_name();
        tux::string::word::list words;
        if(auto count = txt.words(words, false, "/"); !count) return ;
        text | color::reset | " in " | colors | gh;
        if(words.size() > 1)
        {
            auto i = words.end();
            i--; // filename
            auto filename = *i;
            i--; // parent dir
            text | **i;
            ++i;
            text | '/' | **i | ' ';
        }
        words.clear();
    }
    // disable uncontrollable and potentially insane length of function signature given by std::source_location.
    // instead, using it explicitly into a distinct log input
    //------------------------------------------------------------------------------------------------------------
    //    if(headercomp.fun)
    //    {
    //        auto [gh, colors] = log::functionattributes(log::fn::fun);
    //        text << colors << gh << ' ' << location.function_name() << color::reset;
    //    }
    //------------------------------------------------------------------------------------------------------------
    if(_headercomp_.line)
    {
        auto [gh, colors] = log::function_attributes(log::fn::line);
        text | colors | "line: " | std::format("{}", location.line()) | color::reset;
    }
    if(_headercomp_.fun)
        (*this) << log::fn::endl << log::fn::func;

    //text | " \r\n";
}


log &log::operator<<(char ch)
{
    text | ch;
    return *this;
}

void log::purge(const std::function<void(log &)>& f)
{
    std::cout << " Purge log::sections->contents:\n\r";
    for(auto& sec: log::sections)
    {
        std::cout << " Section: [" << sec.id << "]:\n\r--------------------------------------------------------\n\r";
        for(auto& r : sec.contents)
        {
            if (f)
                f(r);
            else
                std::cout << r.text() << "\r\n";

            r.text.clear();
        }
        sec.contents.clear();
    }
}


log &log::operator<<(log::action a_action)
{
    auto [gh,colors] = log::action_attributes(a_action);
    switch(a_action)
    {
        case log::action::commit :
        {
            if(!log::current_section->fout)
                return *this;

            *(log::current_section->fout) << text() << std::flush;
            log::current_section->remove_last();
            return *this;

        }
        break;
        default:
            text | colors() | gh | log::to_string(a_action);
        break;
    }

    return *this;
}


log& log::operator<<(log::oef e)
{
    log::current_section->contents.back() << color::reset << log::action::commit;
    return *this;
}


log &log::operator<<(log::code cod)
{
    auto [gh,colors] = log::return_code_attributes(cod);
    text
        | colors()
        | gh
        | log::to_string(cod)
        | color::reset | ' ';
    return *this;
}

log &log::operator<<(log::fn fn)
{
    switch (fn) {
        case log::fn::endl:
            text | '\n';
//            switch (applog::format()) ///@todo create log::format(); directly instead.
//            {
//                case color::format::ansi256:
//                    input("\n");
//                    break;
//                case color::format::html:
//                    input("<br />");
//                    break;
//            }
            break;
        case log::fn::stamp: {
            /*
                 * %d %f ou %d %m %y
                 * %r %t %h %m %s
                 * %a {monday} %a {mon}
                 * %b {june}   %b {jun}
            */


            //std::chrono::zoned_time date{"america/toronto", std::chrono::system_clock::now()};
            //const auto tp{std::chrono::system_clock::now()};
            //auto txt{tux::string::now("{:%h:%m:%s}", tp)};
            auto [ic, a] = log::function_attributes(log::fn::stamp);
            tux::string acc;
            acc | a.fg | glyph::data[ic] | color::reset | tux::string::now("%t");
            text | acc();
            return *this;
        }

        case log::fn::file:
            text | location.file_name();
            return *this;
        case log::fn::weekday: {
            auto [ic, a] = log::function_attributes(log::fn::weekday);
            //auto today{std::chrono::system_clock::now()};
            tux::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | tux::string::now("%a");
            text | acc();
            return *this;
        }

        case log::fn::day : {
            auto [ic, a] = log::function_attributes(log::fn::day);
            //auto today{std::chrono::system_clock::now()};
            tux::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | tux::string::now("%d");
            text | acc();
            return *this;
        }

        case log::fn::month: {
            auto [ic, a] = log::function_attributes(log::fn::month);
            //auto today{std::chrono::system_clock::now()};
            tux::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | tux::string::now("%m");
            text | acc();
            return *this;
        }
        case log::fn::monthnum: {
            auto [ic, a] = log::function_attributes(log::fn::month);
            //auto today{std::chrono::system_clock::now()};
            tux::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | tux::string::now("%b");
            text | acc();
            return *this;
        }
        case log::fn::year: {
            auto [ic, a] = log::function_attributes(log::fn::year);
            //auto today{std::chrono::system_clock::now()};
            tux::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | tux::string::now("%y");
            text | acc();
            return *this;
        }
        case log::fn::func:
            auto [gh, colors] = log::function_attributes(log::fn::func);
            text | "From [" | colors | location.function_name() | color::reset | "]\n";
            break;

        //default: break;
    }
    return *this;
}


log::exception log::exception::operator[](log& el)
{
    _log_instance_ = &el;
    return *this;
}


log::log(log::type in_type, log::code code, std::source_location src):_type_(in_type), _code_(code), location(std::move(src)){text | "\r\n"; }


const char* log::exception::what() const noexcept
{
    if(_log_instance_)
    {
        _msg_ = _log_instance_->text();
        return _msg_.c_str();
    }
    return std::exception::what();
}


log::section &log::select(const std::string& section_id)
{
    if(log::sections.empty())
    {
        log::init();
        log::current_section = log::sections.begin();
        return log::sections[0];
    }
    int count=0;
    for(auto& s : log::sections)
    {
        if(s.id == section_id)
        {
            log::current_section = log::sections.begin() + count;
            return s;
        }
        ++count;
    }
    log::current_section = log::sections.begin();
    return *log::current_section;
}


log::code log::init(std::function<log::code()> inifn)
{
    log::sections.emplace_back(log::section{.id="globals"});
    log::current_section = log::sections.begin();
    log::current_section->ofs.open("global.log", std::ios_base::trunc|std::ios_base::out);
    if(!log::current_section->ofs.is_open())
        throw "Could not open log.";

    log::current_section->fout = &log::current_section->ofs;
    if(inifn)
        return inifn();
    return log::code::done;
}

log::code log::append_section(const std::string &section_id)
{
    if(log::select(section_id).id == section_id)
    {
        log::current_section = log::sections.begin();
        log::error() << " section identified by '" << section_id << "' already exists. - request rejected";
        return log::code::rejected;
    }
    log::sections.emplace_back(log::section{.id=section_id});
    log::current_section = --log::sections.end();
    std::string filename{};
    filename = section_id + ".log";
    log::current_section->ofs.open(filename.c_str(), std::ios_base::trunc|std::ios_base::out);
    log::current_section->fout = &log::current_section->ofs;

    //--log::current_section;
    return log::code::accepted;
}


log::code log::end()
{
    ///@todo Iterate sections and close their output file.
    for(auto& sec : log::sections)
    {
        sec.ofs.close();
        sec.contents.clear();
    }

    ///...
    //log::current_section->close();
    return log::code::done;
}


log::code log::endl()
{
    log::current_section->contents.back() << log::action::commit;
    return log::code::accepted;
}


log::section &log::section::operator*()
{
    return *this;
}

log &log::section::operator<<(log &&r)
{
    contents.emplace_back(r);
    return contents.back();
}


void log::section::remove_last()
{
    if(!contents.empty()) contents.pop_back();
    //log::debug() << "section size: " << contents.size() << log::eol;
}


void log::section::close()
{
    log::info() << log::fn::func << " " << log::fn::month << "," << log::fn::year << " " << log::fn::hour << ":"  << log::fn::minute << ":" << log::fn::seconds << log::action::end;
    if(ofs.is_open()) ofs.close();
}
} // namespace tux
