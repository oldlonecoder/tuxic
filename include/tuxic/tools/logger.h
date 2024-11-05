//
// Created by oldlonecoder on 8/21/24.
//

//#ifndef log_H
//#define log_H
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

#include <tuxic/tools/glyphes.h>
#include <tuxic/tools/string.h>
//#include "tuxic/journal/enums.h"
#include <source_location>

#include <functional>
#include <tuxic/tools/geometry.h>
#include <filesystem>
#include <fstream>



using tux::color;
using tux::glyph;
using tux::accent_fr;
using tux::ui::rectangle;
using tux::ui::cxy;
using tux::ui::size;


namespace tux
{
class object;

class TUXIC_FRM log
{
public:
    struct header_component
    {
         integers::U8 type  : 1;
         integers::U8 stamp : 1;
         integers::U8 fun  : 1;
         integers::U8 file  : 1;
         integers::U8 line  : 1;
         integers::U8 col   : 1;
       //...
    };


    enum class type : integers::U8{
        none, err, warning, fatal, except, message, output, debug, info, comment, syntax, status, test, interrupted, aborted, segfault, log
    };



    enum class code : integers::U8
    {
        ok  =0           , ///< Obviously;
        accepted         ,
        success          ,
        rejected         ,
        failed           ,
        empty            ,
        full             ,
        notempty         ,
        implemented      , ///< Like notimplemented or already implemented
        notimplemented   , ///< "Please, implement"
        untested         ,
        eof              , ///< End of file
        eos              , ///< End of stream or string or statement or Status ( machine Status )
        null_ptr         , ///< It will happen. Trust me :)
        notexist         , ///< does not exist
        exist            , ///< does already exist
        unexpected       , ///< unexpected
        expected         , ///< expected
        blocked          , ///< thread trying To lock A mutex has failed because the mutex is already locked IsIn another thread...
        locked           , ///< thread trying To lock A mutex has become the owner of the lock.
        overflow         , ///< buffer overflow
        oob              , ///< buffer overflow
        reimplement      ,
        done             ,
        complete         ,
        finish           ,
        undefined        ,
        ready            ,
        terminate        ,
        timeout          ,
        divbyzero        ,
        notvisible       ,
        cancel           ,
        object_ptr       ,
        object_id        ,

        //...

    };


    enum class fn : integers::U8
    {
        func             ,
        endl             , ///< End of line Code, input format
        file             ,
        line             ,
        stamp            , ///< fully detailed timestamp
        hour             ,
        minute           ,
        seconds          ,
        weekday          ,
        dayname          ,
        month            , ///< Par defaut month name
        day              ,
        monthnum         , ///< Maintenant explicite
        year
    };

    enum class action : integers::U8
    {
        enter            , ///< enter bloc or indent
        leave            , ///< End (logger: End of entry accumulators, so do commit); End of (sel)Section, Attribute ( auto-color::reset ) and unindent
        commit           , ///< Commit...
        begin            , ///< Begin (sel)Section or augment indent level
        end              , ///< End   Loop/Action or End selection or Unindent one level; or end inputs on the current logentry then flush to file.
        continu          , ///< Continue Loop or continue Signals::Action iteration.
    };


    static std::string TUXIC_FRM to_string(log::type enum_type);
    static std::string TUXIC_FRM to_string(log::code enum_code);
    static std::string TUXIC_FRM to_string(log::fn   enum_fn);
    static std::string TUXIC_FRM to_string(log::action enum_action);

    static std::pair<glyph::type, color::pair> TUXIC_FRM type_attributes         (log::type enum_type);
    static std::pair<glyph::type, color::pair> TUXIC_FRM return_code_attributes  (log::code enum_code);
    static std::pair<glyph::type, color::pair> TUXIC_FRM function_attributes     (log::fn enum_fn);
    static std::pair<glyph::type, color::pair> TUXIC_FRM action_attributes       (log::action enum_action);








private:
    log::type _type_{};
    log::code _code_{};
    std::source_location location{};
    // ---------------------------------
    tux::string  text{};
/*
    *        integers::U8 type  : 1;
             integers::U8 stamp : 1;
             integers::U8 fun  : 1;
             integers::U8 file  : 1;
             integers::U8 line  : 1;
             integers::U8 col   : 1;
 */
    header_component _headercomp_{1,1,1,1,1,1};
public:

    // struct TUXIC_FRM logentry
    // {
    //     tux::string _text_{};
    //     using logs = std::vector<log::logentry>;
    //     explicit logentry(log::type, std::source_location src = std::source_location::current()){};
    //     logentry();
    //     ~logentry() { _text_.clear(); }
    //
    //     log::logentry& error       (std::source_location src = std::source_location::current());
    //     log::logentry& warning     (std::source_location src = std::source_location::current());
    //     log::logentry& fatal       (std::source_location src = std::source_location::current());
    //     log::logentry& except      (std::source_location src = std::source_location::current());
    //     log::logentry& message     (std::source_location src = std::source_location::current());
    //     log::logentry& out         (std::source_location src = std::source_location::current());
    //     log::logentry& debug       (std::source_location src = std::source_location::current());
    //     log::logentry& info        (std::source_location src = std::source_location::current());
    //     log::logentry& comment     (std::source_location src = std::source_location::current());
    //     log::logentry& syntax      (std::source_location src = std::source_location::current());
    //     log::logentry& status      (std::source_location src = std::source_location::current());
    //     log::logentry& test        (std::source_location src = std::source_location::current());
    //     log::logentry& interrupted (std::source_location src = std::source_location::current());
    //     log::logentry& aborted     (std::source_location src = std::source_location::current());
    //     log::logentry& segfault    (std::source_location src = std::source_location::current());
    //     log::logentry& jnl         (std::source_location src = std::source_location::current());
    //
    //     log::logentry& operator << (const std::string& txt);
    //     log::logentry& operator << (const char* txt);
    //     log::logentry& operator << (char ch);
    //     log::logentry& operator << (std::string_view txt);
    //     log::logentry& operator << (const rectangle& r);
    //     log::logentry& operator << (cxy pt);
    //     log::logentry& operator << (color::code col);
    //     log::logentry& operator << (color::pair fgbg);
    //     log::logentry& operator << (glyph::type gh);
    //     log::logentry& operator << (accent_fr::type ac);
    //     log::logentry& operator << (log::type ty);
    //     log::logentry& operator << (log::code cod);
    //     log::logentry& operator << (log::fn fn);
    //     log::logentry& operator << (log::action a_action);
    //     //log::logentry& operator << (tux::object*);
    //
    //     template<typename T> log::logentry& operator << (const T& v)
    //     {
    //         _text_ << v;
    //         return *this;
    //     }
    //     //...
    //
    // };
    enum oef : integers::u8 { eol };
    static log& error       (std::source_location src = std::source_location::current());
    static log& warning     (std::source_location src = std::source_location::current());
    static log& fatal       (std::source_location src = std::source_location::current());
    static log& except      (std::source_location src = std::source_location::current());
    static log& message     (std::source_location src = std::source_location::current());
    static log& out         (std::source_location src = std::source_location::current());
    static log& debug       (std::source_location src = std::source_location::current());
    static log& info        (std::source_location src = std::source_location::current());
    static log& comment     (std::source_location src = std::source_location::current());
    static log& syntax      (std::source_location src = std::source_location::current());
    static log& status      (std::source_location src = std::source_location::current());
    static log& test        (std::source_location src = std::source_location::current());
    static log& interrupted (std::source_location src = std::source_location::current());
    static log& aborted     (std::source_location src = std::source_location::current());
    static log& segfault    (std::source_location src = std::source_location::current());
    static log& jnl         (std::source_location src = std::source_location::current());

    log& operator << (const std::string& txt);
    log& operator << (const char* txt);
    log& operator << (char ch);
    log& operator << (std::string_view txt);
    log& operator << (const rectangle& r);
    log& operator << (cxy pt);
    log& operator << (color::code col);
    log& operator << (color::pair fgbg);
    log& operator << (glyph::type gh);
    log& operator << (accent_fr::type ac);
    log& operator << (log::type ty);
    log& operator << (log::code cod);
    log& operator << (log::fn fn);
    log& operator << (log::action a_action);
    log& operator << (log::oef e);
    template<typename T> log& operator << (const T& v)
    {
        text << v;
        return *this;
    }

    static std::vector<log> _mem_stream_;
    void init_header();
    static void purge(const std::function<void(log &)>& f);

    struct TUXIC_FRM section
    {
        std::string id;   ///< Section ID which is also the base name of the output file.
        std::ofstream ofs;
        std::ofstream* fout{nullptr}; ///< will see.
        std::vector<log> contents{}; ///< Actual contents. Will be transferred into the entries container when the transition is done.
       // std::vector<log::logentry> entries{}; ///< in transition.
        using list = std::vector<log::section>;
        log::section& operator *(); ///< Get the reference of this instance.
        log& operator << (log&& r); // move operator, will be removed and replaced with log::logentry object.
        void remove_last();
        void close();

    };


    static log::section::list sections;
    static log::section::list::iterator current_section;
public:
    static log::section& select(const std::string& section_id);
    static log::code init(std::function<log::code()> inifn = nullptr);
    static log::code append_section(const std::string& section_id);
    static log::code end();
    static log::code endl();

    class TUXIC_FRM exception :  public std::exception
    {
    public:

        explicit exception():std::exception() { _e_ = true; }
        explicit exception(const char *txt) { _msg_ = txt; _e_ = false; }
        explicit exception(const std::string &txt) { _msg_ = txt; _e_ = false; }

        ~exception() noexcept override {
            _msg_.clear();
        }

        const char* what() const noexcept override;

        log::exception operator[](log& el);
    private:
        bool _e_;
        mutable std::string _msg_;
        log *_log_instance_{nullptr};
    };

    log() = default;
    log(log::type message, log::code code, std::source_location src);
};

 bool operator !(log::code enum_code);
}

//#endif //log_H
