

#include <tuxic/vision/widgets/label.h>
#include <tuxic/vision/widgets/icon.h>


namespace tux::ui
{

label::label(object* _parent_widget, const std::string& _id): widget(_parent_widget,_id)
{
    _geometry_.dwh.set_min_size(1,1);
}

label::~label()
{
    _text_.clear();
}

log::code label::draw()
{

    //log::debug() << log::fn::fun << "[" << color::hotpink4 << id() << color::reset << "]" << "geometry: " << color::lime << _geometry_ << color::reset << log::fn::endl;
    clear();
    auto p = begin_draw();
    p.home();
    p << _text_;
    end_draw(p);

    return log::code::done;
}


log::code label::setup_ui()
{
    widget::setup_ui();

    if(has_component(ui::components::PrefixGlyph))
    {
        set_prefix_icon(glyph::alien);
    }
    if(has_component(ui::components::SuffixGlyph))
        set_suffix_icon(glyph::alien);

    return log::code::ok;
}


log::code label::set_prefix_icon(glyph::type ic_id)
{
    if(!_prefix_icon_)
    {
        _prefix_icon_ = new icon(this, "prefix_icon", ic_id);
        _prefix_icon_->set_geometry({{0,0},ui::size{2,1}});
        _prefix_icon_->set_theme(theme_name());
    }

    _prefix_icon_->set(ic_id);


    return log::code::accepted;
}


log::code label::set_suffix_icon(glyph::type ic_id)
{
    if(!_suffix_icon_)
    {
        _suffix_icon_ = new icon(this, "prefix_icon", ic_id);
        _suffix_icon_->set_geometry({{_geometry_.dwh.w-2,0},ui::size{2,1}});
        _suffix_icon_->set_theme(theme_name());
    }

    _suffix_icon_->set(ic_id);


    return log::code::accepted;
}


log::code label::set_text(const std::string& _txt)
{
    log::jnl() << pretty_id() << log::eol;
    _text_ = _txt;
    log::out() << " text set to '" << _text_ << "';" << log::eol;
    dirty(_geometry_.tolocal());

    if(_justify_ & ui::justify::auto_size)
        return set_geometry(ui::rectangle{_geometry_.a.x,_geometry_.a.y, static_cast<int>(_text_.length()),1});

    ///@ Todo Apply (re-)size policies...

    return log::code::accepted;
}


log::code label::set_justify(ui::justify::Type j)
{
    _justify_ |= j;
    if(j&ui::justify::auto_size)
        return set_geometry(ui::rectangle{_geometry_.a.x,_geometry_.a.y, static_cast<int>(_text_.length()),_geometry_.dwh.h});
    // Handle the rest of justification flags that can be supported by labels...
    //...
    return log::code::accepted;
}


}
