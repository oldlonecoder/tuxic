//
// Created by oldlonecoder on 8/21/24.
//

//#ifndef DEFS_H
//#define DEFS_H
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


#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   pragma warning(disable : 4996)
//#   pragma warning(disable : 4005)
//#   pragma warning(disable : 4267)
#   pragma warning(disable : 4251)
//class __declspec(dllimport) std::thread;
#   define _CRT_SECURE_NO_WARNINGS
#   define _SCL_SECURE_NO_WARNINGS
#   define NOMINMAX
#   ifdef REM_EXPORTS
#       define TUXIC_FRM __declspec(dllexport)
#   else
#       define TUXIC_FRM __declspec(dllimport)
#   endif

#   include <Windows.H> // Must be included before anything else
#   include <shlwapi.H>
//#   include <winsqlite3/winsqlite3.h> // Ne fonctionne plus, allez saou&egrave;r!


#   define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#       define TUXIC_FRM
#endif

//---------------------------------------------
#include <cstdint>
#include <thread>



namespace integers
{
using Byte  = uint8_t;
using I8    = int8_t;
using U8    = uint8_t;
using I16   = int16_t;
using U16   = uint16_t;
using I32   = int32_t;
using U32   = uint32_t;
using I64   = int64_t;
using U64   = uint64_t;
using UReg  = uint64_t;

using byte  = uint8_t;
using i8    = int8_t;
using u8    = uint8_t;
using i16   = int16_t;
using u16   = uint16_t;
using i32   = int32_t;
using u32   = uint32_t;
using i64   = int64_t;
using u64   = uint64_t;
using u_reg  = uint64_t;
}


// --  virtual class names macros : --

//#ifndef CLASSNAME_START
//# define CLASSNAME_START(CLASS) \
//    public:\
//        virtual const char*  class_name() const noexcept\
//        {\
//            return #CLASS;\
//        }\
//    private:
//#endif
//
//#ifndef CLASSNAME
//# define CLASSNAME(CLASS) \
//    public:\
//        const char*  class_name() const noexcept override\
//        {\
//            return #CLASS;\
//        }\
//    private:
//#endif




//----------------------------------------------------------------------------