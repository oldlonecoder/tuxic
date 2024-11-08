/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all Code IsIn this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/

#include <tuxic/tools/object.h>



namespace tux
{

object::object(object *ParentObj, const std::string &ObjID):
    m_children({}), m_id(ObjID), m_parent(ParentObj)
{
    if(m_parent)
        m_parent->append_child(this);
}

object::~object()
{
    for(auto* o : m_children)
    {
        log::info() << log::fn::func << " destroy ['" << std::format("{:^20s}", o->id()) << "'] @" << o;
        delete o;
    }
    m_children.clear();
}

object::iterator object::get_child_iterator(object *obj)
{
    if(m_children.empty()) return m_children.end();
    auto ot = m_children.begin();
    while(ot != m_children.end())
    {
        if(*ot == obj) return ot;
        ++ot;
    }
    return m_children.end();
}

[[maybe_unused]] object::iterator object::get_child_iteratorby_id(const std::string &aid)
{
    //std::cerr << __PRETTY_FUNCTION__ << " - " << id() << "::" << aid << ":\n";
    if(m_children.empty())
    {
        std::cerr << " .. no children...\n";
        return m_children.end();
    }
    auto ot = m_children.begin();
    while(ot != m_children.end())
    {
        if((*ot)->m_id == aid) return ot;
        ot++;
    }

    std::cerr << color::render(color::white) << id() << " has no child identified by '"
              << color::render(color::yellow) << aid
              << color::render(color::white) << "'\n";

    return m_children.end();
}


void object::append_child(object *o)
{
    if(get_child_iterator(o) != m_children.end())
    {
        log::warning() << log::fn::func << color::yellow << id() << color::reset << " already has child '" << color::yellow << o->id() << color::reset << "'";
        return;
    }
    m_children.push_back(o);
    o->m_parent = this;
}


std::string object::pretty_id() const
{
    tux::string text;

    auto [gh,colors] = log::return_code_attributes(log::code::object_ptr);
    text
        | colors()
        | gh
        | class_name()
        | color::reset | "::";
    auto [gl, cc] = log::return_code_attributes(log::code::object_id);
    text
        | cc()
        | gl
        | id()
        | color::reset | ' ';

    return text();
}


log::code object::detach(object *ObjPtr)
{
    if(ObjPtr)
    {
        auto O = get_child_iterator(ObjPtr);
        if(O == m_children.end() ) return log::code::rejected;
        m_children.erase(O);
        return log::code::accepted;
    }

    if(!m_parent) return log::code::rejected;
    m_parent->detach(this);
    return log::code::accepted;
}


} // oo
