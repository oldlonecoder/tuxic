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

#include <tuxvision/ui/terminal.h>
#include <tuxvision/tools/actions.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

//#include <thread>
//#include <mutex>
#include <csignal>
#include <tuxvision/ui/vchar.h>

namespace tux::ui::terminal
{

static termios  saved_st{}, new_term{};
signals::action<rectangle> _winch{};
rectangle _geometry_{};




signals::action<rectangle>& term_resize_signal()
{
    return _winch;
}


terminal::caret_shapes _shape_{caret_shapes::def};


book::code query_winch()
{
    winsize win{};
    ioctl(fileno(stdout), TIOCGWINSZ, &win);
    if((!win.ws_col)||(!win.ws_row))
        return book::code::notexist;

    _geometry_ = ui::rectangle{{0,0}, ui::size{static_cast<int>(win.ws_col), static_cast<int>(win.ws_row)}};
    book::info() << book::fn::func << " terminal resize to:" << color::yellow << std::format("{:>3d}x{:<3d}",_geometry_.dwh.w,_geometry_.dwh.h);
    return book::code::done;
}


rectangle geometry() { return _geometry_; }


void resize_signal(int )
{
    query_winch();
}

book::code begin()
{
    if(auto c = terminal::query_winch(); !c)
        book::error() << book::code::failed << " to get the screen geometry - there will be no boudaries checks. ";


    tcgetattr(STDIN_FILENO, &saved_st);
    new_term = saved_st;

    new_term.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | IGNCR | IXON );
    new_term.c_oflag &= ~OPOST;
    new_term.c_cflag |= (CS8);
    new_term.c_cflag &= ~PARENB;
    new_term.c_lflag &= ~(ICANON | ECHO | IEXTEN | TOSTOP | ECHONL);
    new_term.c_cc[VMIN] = 0;
    new_term.c_cc[VTIME] = 1;
    new_term.c_cc[VSTART] = 0;
    new_term.c_cc[VSTOP] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);

    switch_alternate();

    book::out() << " console set to raw mode...";

    ::signal(SIGWINCH, &terminal::resize_signal);
    terminal::cursor_off();
    terminal::start_mouse();
    return book::code::done;
}

book::code end()
{
    switch_back();
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_st);
    cursor_on();
    terminal::stop_mouse();
    return book::code::done;
}

void switch_alternate()
{
    std::cout << "\x1b[0m\x1b[?1049h" << std::flush;
}

void switch_back()
{
    std::cout << "\x1b[0m\x1b[?1049l" << std::flush;
}


/**
 * @brief Set terminal to report the mouse events.

    @note Execute CSI on each parameters because I realized that "\x1b[?1000;1002;...h" is not working.
 *
 */
void start_mouse()
{
    std::cout << CSI << "?1000h";
    std::cout << CSI << "?1002h";
    std::cout << CSI << "?1003h";
    std::cout << CSI << "?1006h";
    std::cout << CSI << "?1015h" << std::flush;
}

void stop_mouse()
{
    std::cout << CSI << "?1000l";
    std::cout << CSI << "?1002l";
    std::cout << CSI << "?1003l";
    std::cout << CSI << "?1006l";
    std::cout << CSI << "?1015l" << std::flush;
}


void clear()
{
    std::cout << "\x1b[2J";
}


/*!
 * @brief Activate the screen cursor.
 *
 */
void cursor_on()
{
    std::cout << "\x1b[?25h" << std::flush;
}


/**
 * @brief Deactivate the screen cursor
 *
 */
void cursor_off()
{
    std::cout << "\x1b[?25l" << std::flush;
}



void cursor(ui::cxy xy)
{
    std::cout << std::format("\x1b[{:d};{:d}H", xy.y+1,xy.x+1);
}

void mv(ui::direction::type dir, int d)
{
    char ch =dir == ui::direction::right ? 'C': dir==ui::direction::left  ? 'D' : dir==ui::direction::up    ? 'A' : 'B';
    std::cout << "\x1b[" << d << ch;
}



}
