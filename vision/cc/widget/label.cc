

#include <tuxvision/ui/widget/label.h>



namespace tux::ui
{

label::label(object* _parent_widget, const std::string _id): widget(_parent_widget,_id)
{
    _geometry_.dwh.set_min_size(1,1);
}

label::~label()
{
    _text_.clear();
}

book::code label::draw()
{

    //book::debug() << book::fn::fun << "[" << color::hotpink4 << id() << color::reset << "]" << "geometry: " << color::lime << _geometry_ << color::reset << book::fn::endl;
    clear();
    auto p = begin_draw();
    p.home();
    p << _text_;
    end_draw(p);

    return book::code::done;
}



book::code label::set_text(const std::string& _txt)
{
    book::log() << pretty_id() << book::eol;
    _text_ = _txt;
    book::out() << " text set to '" << _text_ << "';" << book::eol;
    dirty(_geometry_.tolocal());

    if(_justify_ & ui::justify::auto_size)
        return set_geometry(ui::rectangle{_geometry_.a.x,_geometry_.a.y, static_cast<int>(_text_.length()),1});

    ///@ Todo Apply (re-)size policies...

    return book::code::accepted;
}


book::code label::set_justify(ui::justify::Type j)
{
    _justify_ |= j;
    if(j&ui::justify::auto_size)
        return set_geometry(ui::rectangle{_geometry_.a.x,_geometry_.a.y, static_cast<int>(_text_.length()),_geometry_.dwh.h});
    // Handle the rest of justification flags that can be supported by labels...
    //...
    return book::code::accepted;
}


}
