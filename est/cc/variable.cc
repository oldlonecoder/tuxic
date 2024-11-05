//
// Created by oldlonecoder on 8/19/24.
//

#include "tuxic/est/variable.h"

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




namespace tux::est {
variable::variable(node* a_parent_node, lex_token* a_token, alu* a_alu):node(a_parent_node, a_token, a_alu)
{
    _token_->sem |= lex::type::Var;
    set_id(std::string(_token_->text()));
}


alu tux::est::variable::pop()
{
    if(_stack_.empty()) 
    {
        log::warning() << log::fn::func << log::code::rejected << "-> stack is empty; using current alu::value.";
        return *_a_;
    }
    *_a_ = _stack_.top();
    _stack_.pop();
    return *_a_;
}

void tux::est::variable::push()
{
    _stack_.push(*_a_);
}

} // est
