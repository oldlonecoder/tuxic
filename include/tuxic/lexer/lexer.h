//
// Created by oldlonecoder on 24-03-08.
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

#include <tuxic/lexer/tokens_table.h>
#include <tuxic/tools/sscan.h>

//#ifndef LEXER_LEXER_H
//#define LEXER_LEXER_H

namespace tux
{

class TUXIC_FRM lexer
{
public:

    struct TUXIC_FRM config_data
    {
        std::string_view text{};
        token_table*      production{nullptr};
    };
    config_data& config() { return m_config; }

    lexer() = default;
    virtual ~lexer() = default;

    virtual log::code exec();




protected:
    tux::sscan scanner{};
    virtual log::code loop();
    log::code state{log::code::ok};
    void push_token(lex_token&);


    void update_token_location(lex_token&);
    log::code tokenize(lex_token);

    config_data m_config;

    virtual log::code tokenize_identifier    (lex_token &);
    virtual log::code tokenize_binary_operator(lex_token&);
    virtual log::code tokenize_default       (lex_token&);
    virtual log::code tokenize_unary_operator (lex_token&);
    virtual log::code tokenize_punctuation   (lex_token&);
    virtual log::code tokenize_keyword       (lex_token&);
    virtual log::code tokenize_string        (lex_token&);
    virtual log::code tokenize_sign_prefix    (lex_token&);
    virtual log::code tokenize_prefix        (lex_token&);
    virtual log::code tokenize_postfix       (lex_token&);
    virtual log::code tokenize_cpp_comment    (lex_token&);
    virtual log::code tokenize_comment_bloc   (lex_token&);
    virtual log::code tokenize_numeric       (lex_token&);

    lex_token::list& production();


};

} // lex

//#endif //LEXER_LEXER_H
