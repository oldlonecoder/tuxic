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


#include <tuxic/vision/terminal.h>


namespace tux::ui::terminal
{

struct TUXIC_FRM vchar final
{
    u32 d{0x8003A020};

    using string = std::vector<vchar>;
    using iterator = string::iterator;

    using back_buffer = std::shared_ptr<terminal::vchar::string>;


    struct TUXIC_FRM bloc final
    {
        ui::size                geometry{};
        terminal::vchar::string  buffer{};
    };

    static constexpr u32 CharMask  = 0x800000FF;
    static constexpr u32 FGMask    = 0x0000FF00;
    static constexpr u32 BGMask    = 0x00FF0000;
    static constexpr u32 CMask     = 0x00FFFF00;
    static constexpr u32 ColorsMask= 0x00FFFF00;
    static constexpr u32 AttrMask  = 0xFF000000;
    static constexpr u32 UtfMask   = 0xB10000FF;
    static constexpr u32 StyleMask = 0x0E000000;
    // ==============u===attributes==========================
    static constexpr u32 UGlyph    = 0x01000000;
    static constexpr u32 Underline = 0x02000000;
    static constexpr u32 Stroke    = 0x04000000;
    static constexpr u32 Blink     = 0x08000000;
    static constexpr u32 Accent    = 0x10000000;
    static constexpr u32 Frame     = 0x20000000;
    static constexpr u32 TRGB      = 0x40000000;
    /// This will maku use of true-color RGB command instead of the re-routed terminal GUI colors profile
    static constexpr u32 ASCII     = 0x80000000;
    static constexpr u32 UTFBITS   = Accent | Frame | UGlyph;
    // ==============Bit Shift ============================
    static constexpr int FGShift = 0x08;
    static constexpr int BGShift = 0x10;
    static constexpr int ATShift = 0x18;



    vchar() = default;

    explicit vchar(U32 Ch);
    explicit vchar(vchar* C);
    vchar(vchar& C){d = C.d;}
    vchar(const vchar& C){d = C.d;}
    vchar(color::pair cc);
    ~vchar() = default;

    vchar& set_fg(color::code fg_);
    vchar& set_bg(color::code bg_);

    vchar& set_attributes(U32 Ch);
    //vchar& set_colors(color::pair&&Ch);
    // vchar& ResetAttributes(vchar::Type bits_);

    vchar& set_colors(const color::pair&CP);

    vchar& operator=(U32 Ch);
    vchar& operator=(const vchar& Ch) = default;
    vchar& operator=(const U32* Ch);
    vchar& operator=(char Ch);
    vchar& operator=(int Ch)
    {
        d = Ch;
        return *this;
    };

    [[nodiscard]] std::string get_utf_string() const;

    [[nodiscard]] color::code     foreground() const;
    [[nodiscard]] color::code     background() const;
    [[nodiscard]] color::pair     colors() const;
    [[nodiscard]] glyph::type     icon_id() const;
    [[nodiscard]] accent_fr::type accent_id() const;
    [[nodiscard]] cadre::index    frame_id() const;
    [[nodiscard]] char     ascii() const;
    vchar&  operator*() { return *this; }
    [[nodiscard]] uint16_t attributes() const;
    vchar& operator <<(glyph::type gl);
    vchar& operator <<(accent_fr::type ac);
    vchar& operator << (cadre::index fr);
    vchar& operator <<(color::pair cp);


    vchar& operator <<(vchar Ch)
    {
        d = Ch.d;
        return *this;
    }

    static std::string render(const vchar::string& _string);
    static std::string render(const vchar* _blk, int _width);
    static log::code render_string(vchar::string::iterator start, vchar::string::iterator end);



    vchar&     operator <<(char Ch);
    [[nodiscard]] std::string render_colors() const;
    explicit    operator std::string() const;
    [[nodiscard]] std::string details() const;



};
}
