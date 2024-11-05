//
// Created by oldlonecoder on 24-01-27.
//

/******************************************************************************************
 *   Copyright (C) /.../2024 by Serge Lussier                                             *
 *   lussier.serge@gmail.com                                                              *
 *                                                                                        *
 *   Unless otherwise specified, all code in this project is written                      *
 *   by the author (Serge Lussier)                                                        *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply to the code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 *****************************************************************************************/

#pragma once


#include <tuxic/lexer/lexer_types.h>
#include <tuxic/tools/sscan.h>

namespace tux
{
struct TUXIC_FRM lex_token
{
    using list      = std::vector<lex_token>;
    using iterator  = lex_token::list::iterator;
    using citerator = lex_token::list::const_iterator;


    lex::type::T          prim = lex::type::Null;
    lex::type::T          sem  = lex::type::Null;
    lex::mnemonic::T      m    = lex::mnemonic::Noop;
    std::string_view name{"mnemonic::Undefined"}; // Pas vraiment le choix d'ajouter ça ici...
    lex::operand::Index   d = lex::operand::Identifier;

    ~lex_token() = default;

    // From tux::StrScanner :
    tux::sscan::numeric::details num_data{};
    void                         numeric_tr();
    // ------------------------------------------------

    struct TUXIC_FRM location_data
    {
        [[maybe_unused]] size_t                    line{0};
        [[maybe_unused]] size_t                    column{0};
        [[maybe_unused]] size_t                    offset{0};
        [[maybe_unused]] size_t                    length{0};
        const char*                                begin{};
        const char*                                end{};
        std::string_view                           operator()();
        [[maybe_unused]] [[nodiscard]] std::string position() const;
        lex_token::location_data&                  operator =(tux::sscan::location_data const&ldata);
    } token_location;


    struct TUXIC_FRM token_flags
    {
        uint8_t V: 1; // This token is a usable value into expression.
        uint8_t S: 1; // Post semantic parser: Left-Assignable Object
        uint8_t M: 1; // Virtual multiply operator. ( ex.: "4ac" => 4*a*c )
        //                                             ^<...
        uint8_t U: 1; // This token is a single utf-8 symbol { ex.:π,➪, ... }
    } flags{0};

    explicit operator bool() const { return token_location.begin != nullptr; }
    bool     operator||(lex::type::T Sem_) const { return sem || Sem_; }

    std::string  semantic_names() const;
    std::string  type_name() const;
    [[nodiscard]] std::string_view text() const
    {
        if ((flags.M) && (m == lex::mnemonic::Mul))
            return lex::lexem::Multiply;
        /* Overwrite source location. */
        if (!token_location.length)
            return token_location.begin; // This token is a ref token.
        return {token_location.begin, token_location.length};
    }


    [[nodiscard]] bool is_operator() const { return sem & lex::type::Operator; }
    [[nodiscard]] bool is_leaf() const { return sem & lex::type::Leaf; }
    [[nodiscard]] bool is_number() const { return sem & lex::type::Number; }


    [[nodiscard]] bool        has_type(lex::type::T ty) const { return sem & ty; }
    [[nodiscard]] std::string details(bool Frame = false) const;
    std::string               mark(bool a_colorize = false) const;
};
}
