// Created by oldlonecoder on 8/13/24.
//

//#ifndef INTUI_GLOBALS_H
//#define INTUI_GLOBALS_H
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







/*
Care must be taken when converting code from select(2) to poll() as they have slightly different semantics. The first semantic difference is that, unlike select(2), poll() has a way of indicating that one or more file descriptors is invalid by setting a flag in the revents field of corresponding entry of fds, whereas select(2) returns an error (-1) if any of the descriptors with bits set in the fd_set are invalid. The second difference is that on EOF there is no guarantee that POLLIN will be set in revents, the caller must also check for POLLHUP. This differs from select(2) where EOF is considered as a read event.

Consider the following usage of select(2) that implements a read from the standard input with a 60 second time out:

struct timeval timeout;
fd_set readfds;
char buf[BUFSIZ];
int nready;

timeout.tv_sec = 60;
timeout.tv_usec = 0;
FD_ZERO(&readfds);
FD_SET(STDIN_FILENO, &readfds);
nready = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
if (nready == -1)
	err(1, "select");
if (nready == 0)
	errx(1, "time out");
if (FD_ISSET(STDIN_FILENO, &readfds)) {
	if (read(STDIN_FILENO, buf, sizeof(buf)) == -1)
		err(1, "read");
}
This can be converted to poll() as follows:

struct pollfd pfd[1];
char buf[BUFSIZ];
int nready;

pfd[0].fd = STDIN_FILENO;
pfd[0].events = POLLIN;
nready = poll(pfd, 1, 60 * 1000);
if (nready == -1)
	err(1, "poll");
if (nready == 0)
	errx(1, "time out");
if (pfd[0].revents & (POLLERR|POLLNVAL))
	errx(1, "bad fd %d", pfd[0].fd);
if (pfd[0].revents & (POLLIN|POLLHUP)) {
	if (read(STDIN_FILENO, buf, sizeof(buf)) == -1)
		err(1, "read");
}
ERRORS
poll() and ppoll() will fail if:

[EAGAIN]
The kernel failed to allocate memory for temporary data structures; a later call may succeed.
[EFAULT]
fds points outside the process's allocated address space.
[EINTR]
A signal was caught before any polled events occurred and before the timeout elapsed.
[EINVAL]
nfds was greater than the number of available file descriptors.
[EINVAL]
The timeout passed was invalid.
SEE ALSO
clock_gettime(2), getrlimit(2), read(2), select(2), write(2)

STANDARDS
The poll() and ppoll() functions conform to.

HISTORY
A poll() system call appeared in AT&T System V Release 3 UNIX. The ppoll() function appeared in OpenBSD 5.4.

CAVEATS
The POLLWRBAND flag is accepted but ignored by the kernel.

Because OpenBSD does not implement STREAMS, there is no distinction between some of the fields in the events and revents bitmasks. As a result, the POLLIN, POLLNORM, and POLLRDNORM flags are equivalent. Similarly, the POLLPRI and POLLRDBAND flags are also equivalent.
*/




#include "tuxic/vision/events.h"
#include <sys/select.h>
#include <sys/ioctl.h>


namespace tux::ui
{

key_event key_event::nokey{};
mouse event::mouse_data{};
u64 event::prev_mouse_state{event::noevent}; ///< Record previous bitmap of move event flags for the next mouse event.


// This is the permanent stdin input flags for the duration of the intui application:
//-----------------------------------------------------------------------------------




key_event::key_group key_event::command_keys_db =
    {
        {0x00000000001b5b41,"Arrow UP",     {},  key_event::ArrowUP    },
        {0x00000000001b5b42,"Arrow Down",   {},  key_event::ArrowDown  },
        {0x00000000001b5b44,"Arrow Left",   {},  key_event::ArrowLeft  },
        {0x00000000001b5b43,"Arrow Right",  {},  key_event::ArrowRight },
        {0x000000000000000A,"Enter",        {},  key_event::Enter      },
        {0x000000000000001b,"ESC",          {},  key_event::ESC        },
        {0x000000000000007F,"Back Space",   {},  key_event::BS         },
        {0x00000000001b5b48,"HOME",         {},  key_event::Home       },
        {0x00000000001b5b46,"End",          {},  key_event::End        },
        {0x000000001b5b357e,"Page UP",      {},  key_event::PgUp       },
        {0x000000001b5b367e,"Page Down",   {}, key_event::PgDown     },
        {0x000000001b5b327e,"Insert",      {}, key_event::INS        },
        {0x000000001b5b337e,"Delete",      {}, key_event::DEL        },
        {0x00000000001b4f50,"F1",          {}, key_event::F1         },
        {0x00000000001b4f51,"F2",          {}, key_event::F2         },
        {0x00000000001b4f52,"F3",          {}, key_event::F3         },
        {0x00000000001b4f53,"F4",          {}, key_event::F4         },
        {0x0000001b5b31357e,"F5",          {}, key_event::F5         },
        {0x0000001b5b31377e,"F6",          {}, key_event::F6         },
        {0x0000001b5b31387e,"F7",          {}, key_event::F7         },
        {0x0000001b5b31397e,"F8",          {}, key_event::F8         },
        {0x0000001b5b32307e,"F9",          {}, key_event::F9         },
        {0x0000001b5b32317e,"F10",         {}, key_event::F10        },
        {0x0000001b5b32337e,"F11",         {}, key_event::F11        },
        {0x0000001b5b32347e,"F12",         {}, key_event::F12        },
        {0x0000000000000009,"TAB",         {}, key_event::TAB        }
};


key_event::key_group key_event::shifted_command_keys_db=
    {
        {0x000000001b4f3251,"Shift+F2",              {},key_event::ShiftF2            },
        {0x00001b5b313b3241,"Shift+ArrowUp",         {},key_event::ShiftArrowUp   },
        {0x00001b5b313b3242,"Shift+ArrowDown",       {},key_event::ShiftArrowDown },
        {0x00001b5b313b3244,"Shift+ArrowLeft",       {},key_event::ShiftArrowLeft },
        {0x00001b5b313b3243,"Shift+ArrowRight",      {},key_event::ShiftArrowRight},
        {0x00001b5b313b3246,"Shift+End",             {},key_event::ShiftEnd},
        {0x00001b5b313b3248,"Shift+Home",            {},key_event::ShiftHome},
        {0x000000001b4f3252,"Shift+F3",              {},key_event::ShiftF3},
        {0x000000001b4f3253,"Shift+F4",              {},key_event::ShiftF4},
        {0x001b5b31353b327e,"Shift+F5",              {},key_event::ShiftF5},
        {0x001b5b31373b327e,"Shift+F6",             {},key_event::ShiftF6},
        {0x001b5b31383b327e,"Shift+F7",             {},key_event::ShiftF7},
        {0x001b5b31393b327e,"Shift+F8",             {},key_event::ShiftF8},
        {0x001b5b32303b327e,"Shift+F9",             {},key_event::ShiftF9},
        {0x001b5b32313b327e,"Shift+F10",            {},key_event::ShiftF10},
        {0x001b5b32333b327e,"Shift+F11",            {},key_event::ShiftF11},
        {0x001b5b32343b327e,"Shift+F12",            {},key_event::ShiftF12},
        {0x00000000001b5b5a,"Shift+Tab",            {},key_event::ShiftTab},//...
        {0x00000000001b4f4d,"Shift+Enter",          {},key_event::ShiftEnter},
        {0x00001b5b313b3644,"Shift+Ctrl+ArrowLeft", {},key_event::ShiftCtrlArrowLeft},
        {0x00001b5b313b3643,"Shift+Ctrl+ArrowRight",{},key_event::ShiftCtrlArrowRight},
        {0x00001b5b313b3641,"Shift+Ctrl+ArrowUp",   {},key_event::ShiftCtrlArrowUp},
        {0x00001b5b313b3642,"Shift+Ctrl+ArrowDown", {},key_event::ShiftCtrlArrowDown},
        {0x00001b5b313b3646,"Shift+Ctrl+Del",       {},key_event::ShiftCtrlDel},
        {0x00001b5b313b3648,"Shift+Ctrl+Home",      {},key_event::ShiftCtrlHome},
        {0x00001b5b313b3444,"Shift+Alt+ArrowLeft",  {},key_event::ShiftAltArrowLeft},
        {0x00001b5b313b3443,"Shift+Alt+ArrowRight", {},key_event::ShiftAltArrowRight},
        {0x00001b5b313b3441,"Shift+Alt+ArrowUp",    {},key_event::ShiftAltArrowUp   },
        {0x00001b5b313b3442,"Shift+Alt+ArrowDown",  {},key_event::ShiftAltArrowDown },
        {0x00001b5b313b3446,"Shift+Alt+End",        {},key_event::ShiftAltEnd },
        {0x00001b5b313b3448,"Shift+Alt+Home",       {},key_event::ShiftAltHome },
        {0x00001b5b353b347e,"Shift+Alt+PagegUp",    {},key_event::ShiftAltPgUp },
        {0x00001b5b363b347e,"Shift+Alt+PageDown",   {},key_event::ShiftAltPgDown },
        {0x00001b5b353b327e,"Shift+PageUp",         {},key_event::ShiftPageUp },
        {0x00001b5b363b327e,"Shift+PageDown",       {},key_event::ShiftPageDown },
        {0x00001b5b353b357e,"Ctrl+PageUp",          {},key_event::CtrlPageUp },
        {0x00001b5b363b357e,"Ctrl+PageDown",        {},key_event::CtrlPageDown },
        {0x00001b5b333b357e,"Ctrl+Delete",          {},key_event::CtrlDelete},
        {0x00001b5b313b3546,"Ctrl+End",             {},key_event::CtrlEnd},
        {0x00001b5b313b3344,"Alt+LeftArrow",        {},key_event::AltLeftArrow},
        {0x00001b5b313b3343,"Alt+RightArrow",       {},key_event::AltRightArrow},
        {0x00001b5b313b3341,"Alt+UpArrow",          {},key_event::AltUpArrow},
        {0x00001b5b313b3342,"Alt+DownArrow",        {},key_event::AltDownArrow},
        {0x00001b5b313b3744,"Ctrl+Alt+LeftArrow",   {},key_event::CtrlAltLeftArrow},
        {0x00001b5b313b3743,"Ctrl+Alt+RightArrow",  {},key_event::CtrlAltRightArrow},
        {0x00001b5b313b3741,"Ctrl+Alt+UpArrow",     {},key_event::CtrlAltUpArrow},
        {0x00001b5b313b3742,"Ctrl+Alt+DownArrow",   {},key_event::CtrlAltDownArrow},

        };


//0x1b,0x5b,0x31,0x3b,0x36,0x44,0x00
key_event::key_group key_event::ctrl_command_keys_db=
    {
        {0x00001b5b313b3544,"Ctrl+ArrowLeft",  {}, key_event::CtrlArrowLeft},
        {0x00001b5b313b3543,"Ctrl+ArrowRight", {}, key_event::CtrlArrowRight},
        {0x00001b5b313b3541,"Ctrl+ArrowUp"   , {}, key_event::CtrlArrowUp},
        {0x00001b5b313b3542,"Ctrl+ArrowDown" , {}, key_event::CtrlArrowDown},
        {0x00001b5b313b3548,"Ctrl+Home",       {}, key_event::CtrlHome},
        {0x00001b5b323b357e,"Ctrl+Insert",     {}, key_event::CtrlInsert},
        {0x0000000000000011,"Ctrl+Q",          {}, key_event::CtrlQ},
        {0x0000000000000013,"Ctrl+S",          {}, key_event::CtrlS},
        {0x0000000000000016,"Ctrl+V",          {}, key_event::CtrlV},
        {0x0000000000000008,"Ctrl+Back-Space", {}, key_event::CtrlBS},
        {0x001b5b31393b357e,"Ctrl+F8",        {}, key_event::CtrlF8},
        //...
};


const key_event &key_event::query(key_event::key_group &k_db, U64 key_code)
{
    for(const auto& k : k_db)
        if(key_code == k.code) return k;

    return key_event::nokey;
}

const key_event& key_event::query(U64 key_code)
{

    if(const key_event& Ky = query(key_event::ctrl_command_keys_db, key_code); Ky.mnemonic != key_event::None)
        return Ky;
    if(auto const &SK = query(key_event::shifted_command_keys_db, key_code); SK.mnemonic != key_event::None)
        return SK;
    if(auto const& InK = query(key_event::command_keys_db, key_code); InK.mnemonic != key_event::None)
        return InK;

    return key_event::nokey;
}



std::string_view key_event::sequence()
{
    return ansi_seq;
}


event::operator bool()
{
    return event_type != type::noop;
}


// Far from being ready to multitask
// void event::shutdown_listeners()
// {
//     ;
// }





log::code event::get_stdin_event(event &_event_, timeval tv)
{
    log::jnl() << "Enter:" << log::eol;

    fd_set fds;
    FD_ZERO(&fds);                                          // NOLINT
    FD_SET(STDIN_FILENO, &fds);                             // NOLINT
    select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv);  // NOLINT

    if(auto e = FD_ISSET(STDIN_FILENO, &fds); !e)
    {
        log::out() << "TIMEOUT" << log::eol;
        _event_.event_type = event::type::noop;
        return log::code::timeout;
    }
    int pksize{0};
    ioctl(0,FIONREAD,&pksize);
    if(!pksize)
    {
        log::out() << color::reset << "stdin triggered with 0 bytes ( likely terminal resize event )..." << log::eol;
        return log::code::empty;
    }
    //log::out() << " STD INPUT EVENT  : " << color::yellow << pksize << color::reset << " bytes";
    char buffer[100];

    size_t r = ::read(STDIN_FILENO, buffer, 100);
    buffer[r] = 0;
    //log::out() << "{" << color::yellow << tuxin::string::bytes(buffer) << color::reset << "}";

    ansi_parser cparser;
    _event_.event_type = cparser.parse(_event_, buffer);

    if(_event_.event_type == event::type::DROP)
        return log::code::rejected;

    //if(_event_.event_type == event::type::MOUSE)
    //    log::out() << event::mouse_data.to_string() << color::reset;

    else if(_event_.event_type == event::type::key_command)
    {
        log::out() << "KEY COMMAND: {" << color::lime << _event_.data.kev.description << color::reset << '}' << log::eol;
        if(_event_.data.kev.mnemonic == key_event::ESC)
            return log::code::cancel;
    }
    return log::code::accepted;
}




/**
 * @brief Will be used when tui subproject goes to multithreads.
 *
 */
void shutdown_listeners(){}

/*!
 * \brief event::init
 * \return [log::code::]done when finished or throws log::exception if errors during the execution of init.
 */
log::code event::init()
{
    log::message() << " As os nov. 2024, there is nothing to init yet..." << log::eol;
    //...

    return log::code::reimplement;
}



bool event::ansi_parser::next_byte()
{
    it++;
    return it < _seq_.end();
}

event::ansi_parser::~ansi_parser()
{

}



event::type event::ansi_parser::parse(event &_ev_, const char *a_seq_)
{
    //log::log() << log::fn::fun;
    _seq_ = a_seq_; ///@todo handle MSVC craps that forbid "const char*" to be used to construct their string_view !!!
    //log::debug() << log::fn::fun << "{" << color::yellow << tuxin::string::bytes(_seq_) << color::reset << "}:";
    it = _seq_.begin();

    // L'on s'occupe des CSI (Control Sequence Introducer) avant tout:
    if((*it==27) && (_seq_.size()>1)) return parse_esc(_ev_);
    if(*it == 27)
    {
        // systematic/explicitely ESC pressed:
        _ev_.data.kev = key_event::query(27l);
        log::out() << _ev_.data.kev.description << log::eol;
        _ev_.event_type = event::type::key_command;
        return _ev_.event_type;
    }

    //---------------------------------------------------------------
    // Not ESC seq.
    // Check CTRL hit ( *it < ascii(32) ) + ENTER,TAB, BACKSP ...
    // One Byte key. All extra keys are ignored/discarded.

    if((*it < 32) || (*it == 127))
    {

        _ev_.event_type = event::type::key_command;
        log::out() << "KEY_COMMAND: " << color::yellow << (int)*it << color::reset << "';" << log::eol;
        if(key_event tmpkev = key_event::query(*it); tmpkev.mnemonic != key_event::None)
        {
            _ev_.data.kev=tmpkev;
            return _ev_.event_type;
        }
        _ev_.data.kev.code = *it;
        return _ev_.event_type;
    }
    // -- key input.
    log::out() << "CHARACTER:'" << color::yellow << *it << color::reset << "';"  << log::eol;
    _ev_.data.kev = key_event::nokey;
    _ev_.event_type = event::type::CHARACTER; // Extra bytes are all ignored.
    _ev_.data.kev.code = *it;
    return _ev_.event_type;
}


event::type event::ansi_parser::parse_esc(event& evd)
{
    //log::log() << log::fn::fun;

    if (!next_byte()) return event::type::UNCOMPLETED;
    switch (*it)
    {
        case 'P':
            return parse_dcs();
        case '[':
            return parse_csi(evd); ///@note Le focus est ici [ clefs de commandes et autres ], mouse...
        case ']':
            return parse_osc(evd);

            // Expecting 2 characters.
        case ' ':
        case '#':
        case '%':
        case '(':
        case ')':
        case '*':
        case '+':
        case 'O':
        case 'N': {
            if (!next_byte()) return event::type::UNCOMPLETED;
            return parse_ss_1_2(evd);
        }
        // Expecting 1 character:
        default:
            return event::type::SPECIAL;
    }
}

event::type event::ansi_parser::parse_ss_1_2(event &evd)
{
        // 8 bytes max which include the beginning of the buffer (ESC;O | [)

    // Consume the buffer. key_event::ansi_seq is now the final location.
    //log::debug() << log::fn::fun;
    //log::out() << "copy seq into event kev ansi_seq: ";
    std::strncpy(evd.data.kev.ansi_seq, _seq_.data(), 19);

    auto& code = evd.data.kev.code;
    code = 0;
    auto ln = std::min(size_t(8),std::strlen(evd.data.kev.ansi_seq));
    //log::out() << " Check: ansi_seq to parse: {" << color::yellow << tuxin::string::bytes(evd.data.kev.ansi_seq) << color::reset << "}:";

    U8 _b_ = evd.data.kev.ansi_seq[0]; // start with ESC byte
    code = (code << 8) | _b_;
    _b_ = evd.data.kev.ansi_seq[1]; // no matter '[' or 'O' :
    code = (code << 8) | _b_;
    // Now push the rest towards ln or until  hit or miss:
    for(int x=2;x < ln; x++)
    {
        _b_ = evd.data.kev.ansi_seq[x];
        code = (code << 8) | _b_;
        log::out() << std::format("{:04x}",code) << log::eol;
        if(key_event tmp_kev = key_event::query(code); tmp_kev.mnemonic != key_event::None)
        {
            log::out() << "Match:" << color::lime << tmp_kev.description << log::eol;
            evd.data.kev = tmp_kev;
            evd.event_type = event::type::key_command;
            return evd.event_type;
        }
    }

    return event::type::noop;
}


event::type event::ansi_parser::parse_dcs()
{
    return event::type::UNCOMPLETED;
}

event::type event::ansi_parser::parse_csi(event& evd)
{

    //log::debug() << log::fn::fun;

    bool altered = false;
    int argument = 0;
    std::vector<int> arguments;
    while (true) {
        if (!next_byte()) {
            //log::out() << " End of the sequence ";
            return event::type::UNCOMPLETED;
        }

        if (*it == '<') {
            //log::out() << " altered mode";
            altered = true; // Just bypass ...for now...
            continue;
        }

        if (*it >= '0' && *it <= '9') {
            //log::out() << "cursor on digit: '" << color::yellow << (*it-'0') << color::reset << "'";
            argument *= 10;  // NOLINT
            argument += *it - '0';
            continue;
        }

        if (*it == ';') {
            //log::out() << "arg separator: arg value: '" << color::yellow << argument << color::reset << "' ";
            arguments.push_back(argument);
            argument = 0;
            continue;
        }

        // CSI is terminated by a character in the range 0x40–0x7E
        // (ASCII @A–Z[\]^_`a–z{|}~),
        // Note: I don't remember why we exclude '<'
        // To handle F1-F4, we exclude '['.
        if (*it >= '@' && *it <= '~' && *it != '<' && *it != '[')
        {
            //log::out() << "CSI completed: last arg : '" << color::yellow << argument << color::reset << "' ";
            arguments.push_back(argument);
            argument = 0;  // NOLINT
            int c=1;
            //for(auto n : arguments) log::out() << c++ << " > " << std::format("0x{:02x}",n);
            switch (*it) {
                case 'M':
                    return parse_mouse(evd,altered, true, std::move(arguments));
                case 'm':
                    return parse_mouse(evd,altered, false, std::move(arguments));
                case 'R':
                    return parse_caret_report(std::move(arguments));
                default:
                    log::out() << " Switching to parse_ss_1_2():";
                    return parse_ss_1_2(evd);
            }
        }
        log::out() << " Unterminated CSI: switchting to parse_ss_1_2" << log::eol;
        return parse_ss_1_2(evd);

        // // Invalid ESC in CSI.
        // if (*it == '\x1B') {
        //     return event::type::SPECIAL;
        // }
    }
}


event::type event::ansi_parser::parse_osc(event& ev)
{
    tux::string str = tux::string::bytes(_seq_);
    log::debug() << log::fn::func << "rec seq: {" << color::yellow << str << color::reset << "} - not implemented yet" << log::eol;
    return event::type::DROP;
}


/*!
   \brief event::conio_parser::parse_mouse
       Code and functionnality from the Arthur Sonzogni's FTXUI project:
       https://github.com/ArthurSonzogni/FTXUI. Adapted by me for this events build.

    Modfied by ...me (oldlonecoder).

   \param ref to the ed event data instance
   \param altered key
   \param pressed buttons state
   \param arguments state, position
   \return event::type::MOUSE
 */
event::type event::ansi_parser::parse_mouse(event& evnt, bool /*altered - not using, not needed altered report mode... for now*/, bool /*pressed*/, std::vector<int> arguments)
{
    // pressed 'flag' ignored. Relying on the XTerm Button and meta state byte which reports buttons on the lasts two bits:

    if (arguments.size() != 3) return parse_ss_1_2(evnt);
    evnt.event_type = event::type::MOUSE;

    event::mouse_data.button = {0,0,0};
    event::mouse_data.button.left   = (arguments[0] & 3) == 0 ? 1 :0;
    event::mouse_data.button.middle = (arguments[0] & 3) == 1 ? 1 :0;
    event::mouse_data.button.right  = (arguments[0] & 3) == 2 ? 1 :0;
    ///@todo Handle the other buttons...
    /// ...

    event::mouse_data.shift     = arguments[0] & 4;
    event::mouse_data.meta      = arguments[0] & 8;
    event::mouse_data.control   = arguments[0] & 0x10;
    if(event::mouse_data.meta)
        log::info() << log::fn::func << color::pair({.fg=color::grey100, .bg=color::red4}) << "meta" << log::eol;
    // Subtract 1 from the coords. Because the terminal starts at 1,1 and our ui system starts 0,0
    event::mouse_data.xy.x = arguments[1]-1;
    event::mouse_data.xy.y = arguments[2]-1;
    event::mouse_data.move = event::mouse_data.oldxy != event::mouse_data.xy;
    event::mouse_data.dxy = {event::mouse_data.xy.x-event::mouse_data.oldxy.x, event::mouse_data.xy.y-event::mouse_data.oldxy.y};
    event::mouse_data.oldxy = event::mouse_data.xy;
    evnt.data.mev = event::mouse_data; ///< copy mouse state to the event data.
    return evnt.event_type;
}

/**
 * @brief Not used. Don't think I will need it. But I still need to acknowledge it, even only to DROP it.
 *
 * @param _args
 * @return event::type
 */
event::type event::ansi_parser::parse_caret_report(std::vector<int>/* _args*/) { return event::type::DROP; }


/**
 * @brief Quick render to report the actual mouse state in a std::string
 *
 * @return std::string
 */
std::string mouse::to_string()
{
    tux::string output{};
    output | color::grey100 | "[" | color::yellow | xy | color::grey100 | "] ";
    output | color::grey100 | (button.left   ? color::render(color::lime) : color::render(color::grey66)) | "left ";
    output | color::grey100 | (button.middle ? color::render(color::lime) : color::render(color::grey66)) | "middle ";
    output | color::grey100 | (button.right  ? color::render(color::lime) : color::render(color::grey66)) | "right";
    output | color::grey100 | " move[" | color::yellow | (move ? "yes" : "no") | color::grey100 | "] ";
    output | color::grey100 | " delta[" | color::yellow | dxy | color::grey100 | "] ";
    return output;
}


/**
 * @brief

 * @note Not used or usable yet. Code and functionnality from the Arthur Sonzogni's FTXUI project:
 *       https://github.com/ArthurSonzogni/FTXUI
 *
 * @param ev
 * @return event::type
 */
event::type event::ansi_parser::parse_utf8(event& ev)
{
    auto head = *it;
    unsigned char selector = 0b1000'0000;  // NOLINT

    // The non code-point part of the first byte.
    unsigned char mask = selector;

    // Find the first zero in the first byte.
    unsigned int first_zero = 8;            // NOLINT
    for (unsigned int i = 0; i < 8; ++i) {  // NOLINT
        mask |= selector;
        if (!(head & selector)) {
            first_zero = i;
            break;
        }
        selector >>= 1U;
    }

    // Accumulate the value of the first byte.
    auto value = uint32_t(head & ~mask);  // NOLINT

    // Invalid UTF8, with more than 5 bytes.
    const unsigned int max_utf8_bytes = 5;
    if (first_zero == 1 || first_zero >= max_utf8_bytes) {
        ev.event_type = event::type::DROP;
        return event::type::DROP;
    }

    // Multi byte UTF-8.
    for (unsigned int i = 2; i <= first_zero; ++i) {
        if (!next_byte()) {
            ev.event_type = event::type::UNCOMPLETED;
            return event::type::UNCOMPLETED;
        }

        // Invalid continuation byte.
        head = *it;
        if ((head & 0b1100'0000) != 0b1000'0000) {  // NOLINT
            ev.event_type = event::type::DROP;
            return event::type::DROP;
        }
        value <<= 6;                  // NOLINT
        value += head & 0b0011'1111;  // NOLINT
    }

    // Check for overlong UTF8 encoding.
    int extra_byte = 0;
    if (value <= 0b000'0000'0111'1111) {                 // NOLINT
        extra_byte = 0;                                    // NOLINT
    } else if (value <= 0b000'0111'1111'1111) {          // NOLINT
        extra_byte = 1;                                    // NOLINT
    } else if (value <= 0b1111'1111'1111'1111) {         // NOLINT
        extra_byte = 2;                                    // NOLINT
    } else if (value <= 0b1'0000'1111'1111'1111'1111) {  // NOLINT
        extra_byte = 3;                                    // NOLINT
    } else {
        ev.event_type = event::type::DROP;                                             // NOLINT
        return event::type::DROP;
    }

    if (extra_byte != (it - _seq_.begin())) {
        ev.event_type = event::type::DROP;
        return event::type::DROP;
    }
    ev.event_type = event::type::CHARACTER;
    return event::type::CHARACTER;
}




}// namespace tuxin::ui
