//
// Created by oldlonecoder on 24-01-27.
//

#include <tuxic/lexer/token_data.h>
#include <tuxic/tools/sscan.h>
#include <tuxic/tools/geometry.h>
#include <format>

static std::string_view NullMsg { "No String" };


namespace tux
{



std::map<tux::sscan::numeric::details::size_type, lex::type::T> nummap =
{
    {tux::sscan::numeric::details::size_type::I8  , lex::type::I8  },
    {tux::sscan::numeric::details::size_type::I16 , lex::type::I16 },
    {tux::sscan::numeric::details::size_type::I32 , lex::type::I32 },
    {tux::sscan::numeric::details::size_type::I64 , lex::type::I64 },
    {tux::sscan::numeric::details::size_type::U8  , lex::type::U8  },
    {tux::sscan::numeric::details::size_type::U16 , lex::type::U16 },
    {tux::sscan::numeric::details::size_type::U32 , lex::type::U32 },
    {tux::sscan::numeric::details::size_type::U64 , lex::type::U64 },
    {tux::sscan::numeric::details::size_type::F32 , lex::type::F32 },
    {tux::sscan::numeric::details::size_type::F64 , lex::type::F64 },
    {tux::sscan::numeric::details::size_type::F128, lex::type::F128}
};

std::string_view lex_token::location_data::operator()()
{
    if(!begin) return NullMsg;
    log::debug() << " length: " << length;
    if(!end)
    {
        std::string_view sv(begin);
        length = sv.length();
        return sv;
    }
    return {begin,length ? length : length+1};
}




[[maybe_unused]] std::string lex_token::location_data::position() const
{
    tux::string Txt = "%d,%d";
    return { (Txt << line << column)() };
}

lex_token::location_data &lex_token::location_data::operator=(const tux::sscan::location_data &Data)
{
    line   = Data.line;
    column = Data.col;
    offset = Data.offset;
    return *this;
}


//lex_token::~lex_token(){}

std::string lex_token::semantic_names() const
{
    return tux::lexer_component::type_name(sem);
}


std::string lex_token::type_name() const
{
    return tux::lexer_component::type_name(prim);
}


std::string lex_token::details(bool Frame) const
{
    tux::string Out;
    auto T = text();
    Out | std::format("{:>4d},{:<4d}", token_location.column, token_location.line) |
        color::reset | "[" |
        color::yellow | std::format("{:<20s}",name) |
        color::reset | "] Primary Type:" |
        color::deepskyblue7 | std::format("{:<12s}", lexer_component::type_name(prim)) |
        color::reset | "{" |
        color::turquoise4 | std::format("{:<32s}",lexer_component::type_name(sem)) |
        color::reset | "}" | "text: " | color::yellow |  std::string(T.begin(), T.end()) | color::reset;

    return Out();
}


std::string lex_token::mark(bool a_colorize) const
{
    // 1 - Locate Beginning of the line:
    tux::string Str;
    // auto LBegin = token_location.begin;
    // auto LEnd   = token_location.end;
    // // Beginning of the line:
    // while((LBegin > token_location.begin) && (*LBegin != '\n') && (*LBegin != '\r')) --LBegin;
    // if(LBegin < token_location.begin) LBegin = token_location.begin;
    // // m_end of line:
    // while((LEnd < token_location.end) && (*LEnd != '\n') && (*LEnd != '\r')) ++LEnd;
    // if(LEnd > token_location.end) LEnd = token_location.end;
    // auto spc = std::string(token_location.column-1<=0? 0 : token_location.column-1, ' ');
    // //log::Debug() << ":---> nbspace: " << spc.length() << ":";
    // Str , '\n' , std::string(LBegin, LEnd+1) , '\n' , spc , tux::glyph::c_arrow_up;
    return Str();
}


void lex_token::numeric_tr()
{
    if(num_data.seq.empty())
        throw log::exception()[ log::error() << " Cannot call lex_token::numeric_tr on un-scanned or non-numeric token." ];
    sem = lex::type::Number | lex::type::Const | nummap[num_data.size] | lex::type::Leaf;
}


} // lex
