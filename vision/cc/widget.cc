#include <tuxvision/ui/widget.h>

//#include "tuxvision/ui/widget/uiscreen.h"

namespace tux::ui
{


#define CHECK_BLOC \
if(!_bloc_)\
    throw book::exception() [ book::except() <<  book::code::null_ptr << " undefined backbuffer on: "\
   << color::lightsteelblue << class_name()\
   << color::reset <<"::"\
   << color::yellow << id()\
];






widget::widget()
= default;


/*!
 * \brief widget::widget
 * Must be the only valid constructor used for instantiating any of the parent-children relational objects.
 * \param _parent_obj
 * \param _id    Identifier for this widget. (such as the variable name used when creating this widget )
 */
widget::widget(object *_parent_obj, const std::string& _id):object(_parent_obj, _id){}

widget::~widget()= default;



/*!
 * \brief widget::set_geometry
 * Define the widget's geometry.
 * \param r ui::rectangle : the requested geometry values.
 * \return
 */
book::code widget::set_geometry(const rectangle &r)
{
    book::info() << color::yellow << pretty_id() << " requested geometry:" << r << book::eol;

    if(!r)
    {
        book::error() <<  book::code::null_ptr << " - " << color::yellow << id() << " invalid rectangle!" << book::eol;
        return book::code::rejected;
    }
    _geometry_ = r;
    _geometry_.dwh.set_min_size(_size_limits_.min_size.x, _size_limits_.min_size.y);
    _geometry_.dwh.set_max_size(_size_limits_.max_size.x, _size_limits_.max_size.y);
    if((r.dwh.w < _size_limits_.min_size.x)
        || (r.dwh.h < _size_limits_.min_size.y)
        || (r.dwh.w > _size_limits_.max_size.x)
        || (r.dwh.h > _size_limits_.max_size.y))
    {
        book::error() << r << " does not respect the size requirements of " << pretty_id() << "." << book::fn::endl << "- request rejected. "  << book::eol;
        return book::code::rejected;
    }

    if(auto p = parent<widget>(); p)
    {
        book::out() << "parent [" << color::yellow << p->pretty_id() << "]::bloc is assigned to " << pretty_id() << "." << book::eol;
        if(_uistyle_ & ui::uistyle::Window)  goto TOPLVL;
        _bloc_ = p->_bloc_;
    }
    else
    {
TOPLVL:
        _bloc_ = std::make_shared<terminal::vchar::string>(_geometry_.dwh.area(), terminal::vchar(_colors_));
        _uistyle_ |= ui::uistyle::Window;
        book::out() << pretty_id() << " is a toplevel widget: Thus it owns the back_buffer" << book::eol;
    }

    _iterator_ = _bloc_.get()->begin();

    book::out() << pretty_id() << color::reset << " assigned geometry:" << _geometry_ << book::eol;
    return book::code::done;
}

/*!
 * \brief widget::set_theme
 * Query the theme id from the colors::attr_db.
 * Sets the internal _style_ and _colors_ from the query values.
 * \param theme_id
 * \return accepted or rejected if the theme name does not exist.
 */
book::code widget::set_theme(const std::string &theme_id)
{
    _theme_id_ = theme_id;
    auto const& comp = ui::colors::attr_db::theme().find(_theme_id_);
    if (comp == ui::colors::attr_db::theme().end())
    {
        book::error() <<  "Theme '" << color::orangered1 <<  _theme_id_ << color::reset << "' not found" << book::eol;
        return book::code::rejected;
    }

    _elements_ = ui::colors::attr_db::theme()[_theme_id_];
    _states_colors_ =  ui::colors::attr_db::theme()[_theme_id_]["Widget"];
    _colors_ = _states_colors_[ui::uistate::Active];

    book::log() << color::yellow << id() << color::reset << " theme set to '" << _states_colors_[_uistate_] << " " <<  _theme_id_ << " " << color::reset << "'.";
    return book::code::accepted;
}

/*!
 * \brief widget::position
 * Explicitly sets the internal iterator at the coordinates xy - _iterator_ is then ready for read/write operations.
 * \param xy
 * \return accepted or rejected if xy is pout of boundaries of local geometry.
 */
book::code widget::peek_xy(cxy xy)
{
    CHECK_BLOC

    if(!_geometry_.tolocal()[xy])
        throw book::exception()[
            book::except() << pretty_id() << ": " << book::code::oob << " -> " << color::red4 << xy << color::reset << " within rect:" << color::yellow << _geometry_.tolocal() << book::eol
        ];

    if(auto p = parent<widget>(); p)
    {
        auto pxy = xy + _geometry_.a;
        //book::debug() << book::fn::fun;
        // book::out()
        //     << color::yellow << id() <<  color::reset << "::" << color::lightsteelblue3 << "peek_xy" << color::reset << "(" << color::yellow << xy << color::reset << ")"
        //     << color::yellow3 << " peek offset in parent: " << color::lime << p->id() << color::reset << ":" << color::red4 << _geometry_.a << color::reset;
        auto r = p->peek_xy(pxy);
        //if(!!r)
        _iterator_ = p->_iterator_;
        return r;

    }
    else
    {
        // book::debug() << book::fn::fun << " Assign internal _iterator_ offset at [" << color::yellow << xy << "]:";
        _iterator_ = _bloc_->begin() + xy.y * *_geometry_.width() + xy.x;
        // book::out() << "_iterator_ offset (linear position): " << color::hotpink4 << _iterator_-_bloc_->begin() << color::reset;
    }
    //book::debug() << color::lime << id() << color::grey100 << "::" << color::lightsteelblue3 << "peek_xy" << color::grey100 << "(" << color::red4 << xy << color::grey100 << ").";
    return book::code::accepted;
}

/*!
 * \brief widget::position
 * Explicitly sets the internal iterator at the coordinates xy
 * \param xy
 * \return the value of _iterator_.
 */
terminal::vchar::string::iterator widget::at(cxy xy)
{
    //book::debug() << book::fn::fun << color::lime << id() << color::reset << "request at" << color::yellow << xy;
    auto& saved = _iterator_;
    peek_xy(xy);
    auto& request = _iterator_;
    _iterator_ = saved;

    return request;
}

terminal::vchar::string::iterator widget::operator[](cxy xy){ return at(xy); }




book::code widget::set_anchor(ui::anchor::value _ank)
{
    _anchor_ = _ank;
    // if(_bloc_ && _geometry_)
    //     auto_fit();
    //... We have to check conflicting and confusing bits.

    return book::code::accepted;
}




book::code widget::show(ui::uistate::Type st)
{
    _uistate_ |= st | ui::uistate::Visible;

    book::debug() << book::eol;
    book::out() << id() << " at [" << _geometry_ << "]";
    if(is_window())
        return render();

    return book::code::ok;
}


book::code widget::show()
{
    _uistate_ |= ui::uistate::Visible;
    if(is_window())
        return render();
    dirty(_geometry_.tolocal());
    return book::code::ok;
}


book::code widget::hide()
{
    _uistate_ &= ~ui::uistate::Visible;
    if(auto p = parent<widget>(); p)
    {
        auto dr = p->begin_draw(_geometry_);
        dr.clear();
        p->end_draw(dr);
    }
    return book::code::ok;
}




/*!
 * 
 * @return true if _state_ has the visible bit set
 */
bool widget::is_visible()
{
    return _uistate_ & ui::uistate::Visible;
}


/*!
 * @brief set Activate flag

 */
void widget::activate()
{
    _uistate_ = (_uistate_ & ~ui::uistate::Focus) | ui::uistate::Active;
    //...
}


/*!
 *
 * @return true if _state_ has the Active bit set
 */
bool widget::is_active() const
{
    return _uistate_ & ui::uistate::Active;
}


/*!
 * @brief set the focus flag...
 *
 */
void widget::set_focus()
{
    _uistate_ |= ui::uistate::Focus | ui::uistate::Active;
    //...

}


/*!
 * 
 * @return true if _state_ has the Focus bit set
 */
bool widget::is_focus() const
{
    return _uistate_ & ui::uistate::Focus;
}


bool widget::is_hidden() const
{
    return !(_uistate_ & ui::uistate::Visible);
}


/*!
 * \brief widget::draw
 * Self-draw or predefined draw() of the widget.
 * At this area, the base class only clears and or reset the back buffer _bloc_ with the current colors
 * \return
 */
book::code widget::draw()
{
    clear();
    _dirty_area_ = _geometry_.tolocal();
    if(_uicomponents_ & ui::components::Frame)
        draw_frame({});

    for(auto* o: m_children)
        if(auto* w = o->as<widget>(); w)
            w->draw();

    return book::code::done;
}


/*!
 * \brief widget::dirty
 * Invalidating the sub-area defined by the dirty_area rectangle. 'sub' area is applied using Union operation (ui::rectangle::operator | (ui::rectangle rhs))
 *  between _dirty_area_ member attribute and the given dirty_rect argument.
 * \param dirty_rect  mandatory valid rectangle.
 * \return accepted or rejected if dirty_rect is invalid ( nul/unset rectangle )
 */
book::code widget::dirty(const rectangle &dirty_rect)
{
    //book::debug() << book::fn::fun;
    // book::out() << color::lime << class_name() << "::" << id() << color::reset
    //             << " dirty_rect" << color::yellow  << dirty_rect;

    if(!dirty_rect)
    {
        _dirty_area_ = _geometry_.tolocal();
        book::info() <<  "invalidated entire geometry of " << color::lightsteelblue3 << class_name() << color::reset <<"::" << color::yellow << id() << book::eol;
        goto bad_cpp_jump;
    }

    if(!_dirty_area_)
        _dirty_area_ = dirty_rect;
    else
        _dirty_area_ |= dirty_rect; // merge/update this _dirty_area_ rectangle with our child 's _dirty_area_.

    if(_dirty_area_ = _dirty_area_ & _geometry_.tolocal(); !_dirty_area_)
        return book::code::rejected;


    //book::debug() << book::fn::fun << color::red4 << class_name() << "::" << id() << color::reset << " computed dirty area: " <<  color::yellow << _dirty_area_ << color::reset;
bad_cpp_jump:
    if(auto p = parent<widget>(); p != nullptr)
    {
        //book::out() << color::yellow << "signal parent widget '" << color::lime << p->id() << color::reset << "' :";
        return p->dirty(_dirty_area_+_geometry_.a);
    }

    return book::code::accepted;
}



/*!
 * \brief widget::update_child
 *      Updates merging child widget dirty area with this dirty area..
 * \param w
 * \return rejected if invalid computed rectangle ( requested area not visible within this geometry, or child widget has no current dirty area to update.).
 */
book::code widget::update_child(widget *w)
{
    if(!w->_dirty_area_) return book::code::rejected;
    return dirty(w->_dirty_area_);
}



/*!
 * \brief widget::render
 *          Temporary function to render this widget on the screen console.
 * \return
 */
book::code widget::render()
{
    if(!(_uistate_ & ui::uistate::Visible))
    {
        book::info() <<  id() << " is not visible.. - rendering request rejected" << book::eol;
        return book::code::rejected;
    }

    for(int y = 0; y < _geometry_.height(); y++)
    {
        peek_xy({0,y});
        terminal::cursor(_geometry_.a + cxy{0,y});
        terminal::vchar::render_string(_iterator_, _iterator_ + *_geometry_.width());
    }
    std::cout << std::flush;

    return book::code::done;
}


book::code widget::position_child(widget* w)
{
    if(!w->_anchor_)
        return book::code::rejected;

    auto off = ui::cxy{0,0};
    auto [a,b,wh] = _geometry_.tolocal().components();
    if(_uicomponents_ & ui::components::Frame)
        off = {1,1};


    // Right, Left, HCenter:
    ui::cxy xy = w->_anchor_ & ui::anchor::Left ? ui::cxy{off.x,w->_geometry_.a.y} :
        w->_anchor_ & ui::anchor::Right ? ui::cxy{_geometry_.dwh.w - (w->_geometry_.dwh.w + off.x),w->_geometry_.a.y} :
        w->_anchor_ & ui::anchor::HCenter ? ui::cxy{(_geometry_.dwh.w - w->_geometry_.dwh.w + off.x)/2 + off.x,w->_geometry_.a.y} : w->_geometry_.a;
    w->_geometry_.moveat(xy);


    // Width, Height:
    if(w->_anchor_ & ui::anchor::Width)
    {
        w->resize(ui::size{_geometry_.dwh.w-off.x*2, _geometry_.dwh.h});
        w->_geometry_.moveat(ui::cxy{off.x,w->_geometry_.a.y});
    }
    if(w->_anchor_ & ui::anchor::Height)
    {
        w->resize(ui::size{_geometry_.dwh.w, _geometry_.dwh.h-off.y*2});
        w->_geometry_.moveat(ui::cxy{w->_geometry_.a.x,off.y});
    }

    if(w->_anchor_ & ui::anchor::Top)
    {
        w->_geometry_.moveat(off);
    }
    else // Top, Bottom:
        if(w->_anchor_ & ui::anchor::Bottom)
        {
            w->_geometry_.moveat(ui::cxy{w->_geometry_.a.x, _geometry_.dwh.h-off.y});
        }


    //------------------------------------------------

    auto ank = w->_anchor_;

    return book::code::accepted;
}


book::code widget::setup_components()
{
    book::status() << " called the base widget class. " << book::code::reimplement << " - is this a derived class ? :" << pretty_id() << book::eol;
    return book::code::reimplement;
}


/*!
 * \brief widget::begin_draw
 *
 * Creates an instance of widget::painter_dc object for different 'drawing' capabilities on the widget's back buffer _bloc_,
 * drawing confined by the subarea.
 *
 * \param sub_area  confined rectangle within the back buffer geometry.
 * \return new instance of widget::painter_dc.
 */
widget::painter_dc widget::begin_draw(const rectangle& sub_area)
{
    return {this, sub_area };
}

/*!
 * \brief widget::end_draw
 * Triggers dirty call.
 * \param edc
 */
void widget::end_draw(painter_dc &edc)
{
    dirty(edc._geometry_);
}


/*!
 * \brief widget::clear
 * Just clears the widget's back buffer with the current colors
 */
void widget::clear()
{
    CHECK_BLOC

    book::debug() << color::grey100 << class_name() << color::lightcyan3 << '[' << color::lightsteelblue3 <<  id() << color::lightcyan3 << ']' << _colors_() << " >>colors<< ;" << color::yellow << _geometry_.tolocal() << book::eol;

    if(is_window())
        std::fill(_bloc_->begin(), _bloc_->end(), terminal::vchar(_colors_));
    else
    {
        if(auto p = parent<widget>(); p)
        {
            auto paint = begin_draw();
            paint.clear();
            end_draw(paint);
        }
    }
}


/*!
 * @brief Updates the widget.
 * @return ok
 */
book::code widget::update()
{
    auto p = parent<widget>();

    // no dirty rect = this widget has nothing to update.
    if(!_dirty_area_) return book::code::ok;

    if(p) return p->update_child(this);

    return book::code::done;
}


bool widget::has_frame() { return _uicomponents_ & ui::components::Frame; }


bool widget::has_caption() { return _uicomponents_ & ui::components::Caption; }


bool widget::has_glyph() { return _uicomponents_ & ui::components::Glyph; }


bool widget::has_status_bar() { return _uicomponents_ & ui::components::StatusBar; }


bool widget::has_horizontal_scroll_bar() { return _uicomponents_ & ui::components::HScrollBar; }


bool widget::has_vertical_scroll_bar(){ return _uicomponents_ & ui::components::VScrollBar; }


bool widget::has_menu_bar(){ return _uicomponents_ & ui::components::MenuBar; }


bool widget::has_component(ui::uistyle::Type b) { return _uicomponents_ & b; }


bool widget::has_style(ui::uistyle::Type b) { return _uistyle_ & b; }


bool widget::has_status(ui::uistate::Type b) { return _uistate_ & b; }


bool widget::has_class(ui::uiclass::Type b) { return _uiclass_ & b; }


/*!
 *
 * @param w
 * @return accepted or rejected;
 *
 * @note Just pretend for now. But using it for fitting children widgets:
 */
book::code widget::anchor_widget(widget* w)
{
    if(w->parent<widget>() != this)
    {
        book::error() <<  " widget " << w->pretty_id() << " is not a child widget of " << pretty_id() << ". - Request rejected." << book::eol;
        return book::code::rejected;
    }
    //...
    position_child(w);
    //...

    return book::code::accepted;
}


book::code widget::setup_ui()
{
    book::warning() <<  " widget " << pretty_id() << " has no manageable components in the base class. - " << book::fn::endl << book::code::reimplement  << book::eol;
    return book::code::reimplement;
}



void widget::set_components(ui::components::type c) { _uicomponents_ = c; }


void widget::set_uistyle(ui::uistyle::Type s) { _uistyle_ = s; }


void widget::set_uiclass(ui::uiclass::Type cls) { _uiclass_ = cls; }


/*!
 * \brief Protected instance widget::auto_fit
 * Auto fit this widget into the parent widget according to the anchor value.

 * \return  accepted or rejected.
 * \note As of Oct 2024, this method is not 100% usable. It is actually in development and experimentation.
 *       There is still a kind of bug regarding the local variable 'off' values relative to the rectangle::height value.
 */
book::code widget::auto_fit()
{

    book::debug() <<  '\'' << color::yellow << id() << color::reset << "' anchor:" << std::format("{:<04X}", _anchor_) << book::eol;
    cxy off{1,1};

    // need to separate and set simple access to the rectangle coordinates and its components:
    auto par = parent<widget>();
    rectangle area; // The geometry on which this element is positioning.
    if(par)
    {
        // if(par == desktop::instance())
        //     area = terminal::_geometry_;
        // else
        area = par->_geometry_.tolocal();
    }
    else
        area = terminal::geometry();

    if(par)
        if((par->has_frame()) && !(_anchor_ & anchor::Frame))
            off={1,1}; ///< Bug to be investigated, y should be '1' instead of '2'...

    book::out() << id() << " offset:" << off << book::eol;
    //
    book::debug() << "placement is within this area :" << color::yellow << area << color::reset << book::eol;

    auto [a,b,sz] = area.components();
    auto [ea,eb,esz] = _geometry_.components(); // this 'e'lement's geometry components

    if(_anchor_ & anchor::Width)
    {
        book::out() << " Resize this " << id() <<  " Geometry:" << color::blue4 << _geometry_ << book::eol;;
        resize(ui::size{sz.w - (off.x*2), *_geometry_.height()});
        _geometry_.moveat({off.x,_geometry_.a.y});
        book::out() << "fit width: " << color::yellow << id() << color::reset <<"::_geometry_: " << color::hotpink4 << _geometry_ << color::reset << book::eol;
    }
    else
    {
        if(_anchor_ & anchor::Right)
        {
            book::out() << color::yellow << id() << color::reset << " fit right:" << book::eol;
            _geometry_.moveat(cxy{sz.w - (esz.w-1 + off.x), eb.y});
            book::out() << _geometry_;
        }
        else
            if(_anchor_ & anchor::Left)
            {
                book::out() << color::yellow << id() << color::reset << " fit right:" << book::eol;
                _geometry_.moveat(cxy{0, eb.y});
                book::out() << _geometry_ << book::eol;
            }
        // else center....
    }

    if(_anchor_ & anchor::Height)
    {
        resize(ui::size{_geometry_.dwh.w,*area.height()});
        book::out() << "fit height: " << color::yellow << id() << color::reset <<"::_geometry_: " << color::hotpink4 << _geometry_ << color::reset << book::eol;
        _geometry_.moveat({a.x, off.y});
    }
    else
    {
        if(_anchor_ & anchor::Bottom)
        {

            _geometry_.moveat({_geometry_.a.x, *area.height()-off.y});
            book::out() << "fit bottom: " << color::yellow << id() << color::reset <<"::_geometry_: " << color::hotpink4 << _geometry_ << color::reset << book::eol;
        }
        else
        if(_anchor_ & anchor::Top)
        {
            _geometry_.moveat({_geometry_.a.x, 0/*off.y*/});
            book::out() << "fit bottom: " << color::yellow << id() << color::reset <<"::_geometry_: " << color::hotpink4 << _geometry_ << color::reset << book::eol;
        }
    }
    book::out() << "applied geometry : " << color::yellow << id() << ' '  << color::lime << _geometry_ << color::yellow << book::eol;

    //...

    return book::code::done;
}


/*!
 * \brief widget::resize
 * Resize the geometry of this widget.
 * \param new_sz
 * \return done.
 * \note As of Oct. 2024, there is no size checking! tuxvision is in early dev/experiments/learning and R&D.
 */
book::code widget::resize(size new_sz)
{
    CHECK_BLOC
    _geometry_.resize(new_sz);
    book::info() <<  "new geometry: " << color::yellow << _geometry_ << book::eol;
    if(is_window())
    {
        _bloc_->resize(new_sz.area(), terminal::vchar(_colors_));
        book::out() << " bloc reallocation done." << book::eol;
    }
    return book::code::done;
}



/*!
 * \brief widget::draw_frame
 *      Draw a rectangular frame given by the r argument.
 * \param r
 * \return rejected or accepted.
 * @note Provide independent iterator to multiple drawing at once ...
 */
book::code widget::draw_frame(const rectangle &r)
{
    auto area  = r;
    if(!r)
        area = _geometry_.tolocal();

    book::debug() <<  " area: " << color::yellow << area << book::eol;
    auto pos= _iterator_; // dummy assign.
    auto p = begin_draw(area);
    book::out() << pretty_id() << " les quattre coins :" << book::eol;
    p.home() << cadre::TopLeft
             << area.top_right() << cadre::TopRight
             << area.bottom_right() << cadre::BottomRight
             << area.bottom_left() << cadre::BottomLeft;

    book::out() << pretty_id() << " les hosizontaux :" << book::eol;
    pos = at(ui::cxy{1,0}); // Real assign from here.
    std::fill(pos, pos + area.dwh.w-2, terminal::vchar(_colors_) << cadre::Horizontal);
    pos = at(ui::cxy{1,area.b.y});
    std::fill(pos, pos + area.dwh.w-2, terminal::vchar(_colors_) << cadre::Horizontal);

    book::out() << pretty_id() << " la verticalité :" << book::eol;
    for(int y=1; y < area.dwh.h-1; y++)
        p << ui::cxy{0,y} << cadre::Vertical << ui::cxy{area.b.x,y} << cadre::Vertical;

    return book::code::done;
}



} // namespace tux::ui
