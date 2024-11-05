//
// Created by oldlonecoder on 8/19/24.
//

//#ifndef EXPRESSION_H
//#define EXPRESSION_H
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

#include <tuxic/lexer/lexer.h>
#include "tuxic/est/bloc.h"


namespace tux::est 
{

class TUXIC_FRM expr : public bloc
{
    lexer       _lexer_;
    token_table _token_table_;
    
    std::string_view _src_{};

public:
    expr(const std::string& _id_);
    ~expr() override;

    expr& operator=(std::string_view expr_text);

    alu exec(std::string_view _text_="");
    log::code clear();
private:
    log::code compile();
    log::code lex();
    node* make_node(lex_token* a_token);

};

} // est

//#endif //EXPRESSION_H
