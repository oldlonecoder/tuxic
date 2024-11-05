#include <tuxvision/ui/widget/uiscreen.h>






namespace tux::ui::terminal
{


desktop* desktop::the_screen{nullptr};


void desktop::refresh_zorder()
{
    int z = 0;
    for(auto wit = _windows_.begin(); wit != _windows_.end(); ++wit, z++) (*wit)->_tli_ = z;
}


desktop::desktop():widget(){}

desktop::desktop(const std::string &_id):widget(nullptr,_id)
{
    if(desktop::the_screen)
    {
        log::error() << log::fn::func << pretty_id() << " cannot create another screen widget  : use '" << desktop::the_screen->id() << "' instead and destroy this non-usable instance.";
        return ;
    }
    //...
    desktop::the_screen = this;
}

desktop::~desktop()
= default;


log::code desktop::update()
{

    return widget::update();
}


/*!
 * @brief Renders the dirtied desktop region.
 * @param rect re-validated rectangle.
 */
void desktop::render_dirty(const ui::rectangle& rect)
{

    for(int y = 0; y < rect.height(); y++)
    {
        peek_xy(rect.a + cxy{0,y});
        std::copy_n(_iterator_, *rect.width(), peek_sb(rect.a + cxy{0,y}));
    }

    for(auto w : _windows_)
    {
        auto r = w->_geometry_ & rect;
        if(!r) continue;
        for(int y = 0; y < r.height(); y++)
        {
            w->peek_xy(r.a-w->_geometry_.a);
            std::copy_n(w->_iterator_, *r.width(), peek_sb(r.a + cxy{0,y}));
        }
    }

    // flush to the terminal screen here:
    for(int y = 0; y < rect.height(); y++)
    {
        terminal::cursor(rect.a + cxy{0,y});
        auto i = peek_sb(rect.a + cxy{0,y});
        terminal::vchar::render_string(i, i + *rect.width<>());
    }
    std::cout << std::flush;
}


/*!
 * @brief Peek to the screen back buffer at the given coords...
 * @param xy
 * @return the (w-r) terminal::vchar::string::iterator.
 */
terminal::vchar::string::iterator desktop::peek_sb(ui::cxy xy)
{
    if(!_geometry_[xy]) return _screen_buffer_->end();
    return _screen_buffer_->begin() + xy.y * *_geometry_.width() + xy.x;
}


log::code desktop::dirty(const rectangle& _dirty_rect)
{
    auto area = _geometry_.tolocal() & _dirty_rect;
    if(!area)
        return log::code::rejected;

    _dirty_stack_.emplace_back(area); // So all rectangles in the dirty stack are pre-validated.
    return log::code::accepted;
}


}
