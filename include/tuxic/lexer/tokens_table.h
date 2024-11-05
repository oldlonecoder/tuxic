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
#include <tuxic/lexer/token_data.h>

namespace tux
{

class TUXIC_FRM  token_table
{
    
protected:
    lex_token::list ref_table;
    lex_token::list prod_table;
    friend class lexer;
    std::string m_name{"Default Common token_table"};

public:

    token_table()= default;

    ~token_table();

    lex_token scan( const char* C);

    [[maybe_unused]] virtual size_t set_reference_table();
    lex_token::list&                reference_table() { return ref_table; }
    lex_token::list&                production_table() { return  prod_table; }
    token_table&                    operator << (lex_token&);
    std::size_t                     count() { return prod_table.size(); }
    bool                            empty() { return prod_table.empty(); }
    void                            dump_reference_table() const;
    void                            dump_production_table();
    lex_token const&                get(std::string_view);
    lex_token const&                get(lex::mnemonic::T);
    std::string&                    name() { return m_name; }
protected:
//    static size_t AddMnemonicsComponentFromThisTable(const lex_token::Array & Table);
//    static size_t AddMnemonicComponent(std::string_view Lexeme, Mnemonic::T Num);
};








// class LEXER_API ArithmeticLexemes : public token_table
// {
// public:

//     [[maybe_unused]] virtual size_t set_reference_table();
// };








} // ULexer
