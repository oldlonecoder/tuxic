//
// Created by oldlonecoder on 8/18/24.
//



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

#include "tuxic/est/bloc.h"




namespace tux::est
{

bloc::bloc(bloc* a_parent_bloc, const std::string a_bloc_id, lex_token* a_token, alu* a_alu):node(a_parent_bloc,a_token,a_alu)
{
    set_id(a_bloc_id);
}


bloc::~bloc()
{
    // log::log() << log::fn::fun;
    // for(auto* o : m_children)
    // {
    //     node* n = o->as<node>();
    //     if(n)
    //     {    if(!n->mem.ref && n->mem.acc)
    //         {
    //             log::out() << color::reset << " destroy '" << color::yellow << n->attribute() << color::reset << "'.";
    //             delete n;
    //         }
    //     }
    // }
    delete _instructions_;
    delete _variables_;
    //delete _root_;
}


alu bloc::JSR()
{
    if(!_instructions_) return *_a_;
    for(auto* o : *_instructions_)
    {
        if(auto n = o->as<node>())
        {
            *_a_ = n->JSR();
            if(n->mem.leave)
                return *_a_;
        }
    }
    return *_a_;
}

variable::list void_variables{};

const variable::list &bloc::variables()
{
    if(!_variables_) return void_variables;
    return *_variables_;
}

node *tux::est::bloc::append_instruction(node *_i_)
{
    if(!_instructions_)
        _instructions_ = new node::list{};
    _instructions_->push_back(_i_);

    return nullptr;
}


variable *bloc::query_variable(lex_token *a_token)
{

    if(_variables_)
    {
        for(auto* v : *_variables_) if(v->id() == a_token->text()) return v->as<est::variable>();
    }

    if(auto* p = parent<est::bloc>())
        return p->query_variable(a_token);

    return nullptr;
}


void bloc::add_local_variable(variable *v)
{
    if(!_variables_)
        _variables_ = new variable::list{};

    _variables_->push_back(v);
}

} // est

