/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#ifndef NDEBUG
#include <iostream>
#include <sstream>
// #include <common/assert.h>
#endif  // NDEBUG

#include <stdexcept>
#include <locale.h>
#include <curses.h>

#include "ncurs.h"

#define VIS_ASSERT(FOO)    \
    if (! (FOO)) {                              \
        std::stringstream msg;                  \
        msg << "Method: " << __PRETTY_FUNCTION__ << ", line: " << __LINE__ << ", -> " << #FOO; \
        throw std::runtime_error(msg.str());    \
    }

#define VIS_ASSERT_OK(FOO)  VIS_ASSERT(FOO == OK)


namespace NVis {

// Инстанция драйвера.
ITerm& ITerm::Driver()
{
    static NcursesTermDriver d;
    return d;
}

NcursesTermDriver::NcursesTermDriver()
    : enabled_(false)
    , cursor_visible_(true)
    , has_colors_(false)
    , color_foreground_(clWhite)
    , color_background_(clBlack)
{}

NcursesTermDriver::~NcursesTermDriver()
{
    Disable();
}

bool NcursesTermDriver::IsEnabled() const
{
    return enabled_;
}

bool NcursesTermDriver::Enable()
{
    if (enabled_) {
        return true;
    }
    // такую локаль рекомендуют устанавливать те, кто кодит под ncurses
    VIS_ASSERT(setlocale(LC_ALL, "") != NULL);
    // включаем режим curses
    VIS_ASSERT(initscr() != NULL);
    // отключаем прерывание работы программы по Ctrl+Break (Ctrl+C) - эти сочетания будут доступны нам через getch() и
    // мы их cможем обрабатывать, как обычные нажатия клавиш
    VIS_ASSERT_OK(cbreak());
    // отключаем вывод на консоль того, что вводим с клавиатуры
    VIS_ASSERT_OK(noecho());
    // обрабатывать нажатие на Enter внутри программы; стандартно консоль переводит курсор на новую строку и не "отдает" программе код этой клавиши
    VIS_ASSERT_OK(nonl());
    // отключаем flushing клавиатурного буфера при нажатии Ctrl+C.
    VIS_ASSERT_OK(intrflush(stdscr, FALSE));
    // включить режим функциональных клавиш. В этом режиме, такие кнопки как F1-12, Left/Right etc. будут возвращаться
    // через wgetch() в виде одного символа - например, KEY_LEFT, а не в виде двух, как обычно.
    VIS_ASSERT_OK(keypad(stdscr, TRUE));
    // уменьшаем задержку после нажатия Esc
    VIS_ASSERT_OK(set_escdelay(50));
    // инициализируем цвета, если они поддерживаются текущей консолью
    has_colors_ = ::has_colors();
    if (has_colors_) {
        VIS_ASSERT_OK(start_color());
        InitColors();
    }
    // получаем текущие цвета консоли
    short cl_pair;
    attr_t a = 0;
    VIS_ASSERT_OK(attr_get(&a, &cl_pair, NULL));
    VIS_ASSERT_OK(pair_content(cl_pair, &color_foreground_, &color_background_));
    // по-умолчанию системный курсор виден
    ShowCursor();
    // указываем какие события хотим получать от мыши
    mmask_t mask = BUTTON1_PRESSED | BUTTON1_RELEASED | BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED |
                   BUTTON2_PRESSED | BUTTON2_RELEASED | BUTTON2_CLICKED | BUTTON2_DOUBLE_CLICKED |
                   BUTTON3_PRESSED | BUTTON3_RELEASED | BUTTON3_CLICKED | BUTTON3_DOUBLE_CLICKED |
                   //! \todo ??? BUTTON_SHIFT | BUTTON_CTRL | BUTTON_ALT |
                   REPORT_MOUSE_POSITION;
    mousemask(mask, NULL);
    // по-умолчанию - блокирующее получение значений с клавиатуры (ждем нажатия клавиатуры)
    SetKeyboardWaiting(0);

    enabled_ = true;
    return true;
}

void NcursesTermDriver::Disable()
{
    if (! enabled_) {
        return;
    }

    // обрабатываем нажатие на Enter как и раньше
    nl();
    // выключить режим функциональных клавиш
    keypad(stdscr, FALSE);
    // выключаем режим curses
    endwin();

    cursor_visible_ = true;
    has_colors_ = false;
}

bool NcursesTermDriver::ScreenReady() const
{
    return enabled_;
}

bool  NcursesTermDriver::HasColors() const
{
    return has_colors_;
}

Point NcursesTermDriver::GetScreenSize() const
{
    return Point(getmaxx(::stdscr), getmaxy(::stdscr));
}

void NcursesTermDriver::ScreenUpdate()
{
    VIS_ASSERT_OK(refresh());
}

void NcursesTermDriver::ClearScreen()
{
    VIS_ASSERT_OK(erase());
}

bool NcursesTermDriver::IsCursorVisible() const
{
    return cursor_visible_;
}

void NcursesTermDriver::HideCursor()
{
    VIS_ASSERT(curs_set(0) != ERR);
    cursor_visible_ = false;
}

void NcursesTermDriver::ShowCursor()
{
    VIS_ASSERT(curs_set(1) != ERR);
    cursor_visible_ = true;
}

Point NcursesTermDriver::GetCursorPos() const
{
    return Point(getcurx(::stdscr), getcury(::stdscr));
}

void  NcursesTermDriver::SetCursorPos(unsigned x, unsigned y)
{
    VIS_ASSERT_OK(move(y, x));
}

void NcursesTermDriver::SetColor(Color foreground, Color background)
{
    if (foreground & 0x08) {
        VIS_ASSERT_OK(attron(A_BOLD));
    } else {
        VIS_ASSERT_OK(attroff(A_BOLD));
    }
    color_foreground_ = foreground;
    color_background_ = background;
    VIS_ASSERT_OK(color_set(CalcColorPair(foreground, background), NULL));
}

void NcursesTermDriver::SetForeColor(Color color)
{
    SetColor(color, color_background_);
}

void NcursesTermDriver::SetBackColor(Color color)
{
    SetColor(color_foreground_, color);
}

Color NcursesTermDriver::GetForeColor() const
{
    return color_foreground_;
}

Color NcursesTermDriver::GetBackColor() const
{
    return color_background_;
}

void NcursesTermDriver::PrintChar(unsigned x, unsigned y, Char c)
{
    /// \todo
    VIS_ASSERT_OK(mvaddch(y, x, c));
}

void NcursesTermDriver::Print(unsigned x, unsigned y, String s)
{
    /// \todo
    VIS_ASSERT_OK(mvaddnstr(y, x, s.data(), s.size()));
}

void NcursesTermDriver::PrintInt(unsigned x, unsigned y, long n)
{
    StringStream s;
    s << n;
    Print(x, y, s.str());
}

void NcursesTermDriver::PrintReal(unsigned x, unsigned y, double n)
{
    StringStream s;
    s << n;
    Print(x, y, s.str());
}

void NcursesTermDriver::PrintGraph(unsigned x, unsigned y, EPseudoGraph c)
{
    chtype r = 0;
    switch (c) {
        case PG_LINE_TL     : r = ACS_ULCORNER; break;
        case PG_LINE_TM     : r = ACS_TTEE; break;
        case PG_LINE_TR     : r = ACS_URCORNER; break;
        case PG_LINE_CL     : r = ACS_LTEE; break;
        case PG_LINE_CM     : r = ACS_PLUS; break;
        case PG_LINE_CR     : r = ACS_RTEE; break;
        case PG_LINE_BL     : r = ACS_LLCORNER; break;
        case PG_LINE_BM     : r = ACS_BTEE; break;
        case PG_LINE_BR     : r = ACS_LRCORNER; break;
        case PG_LINE_CROSS  : r = ACS_PLUS; break;
        case PG_LINE_VERT   : r = ACS_VLINE; break;
        case PG_LINE_HORZ   : r = ACS_HLINE; break;
    }
    if (r) {
        VIS_ASSERT_OK(mvaddch(y, x, r));
    }
}

bool NcursesTermDriver::KeyboardReady() const
{
    return enabled_;
}

void NcursesTermDriver::SetKeyboardWaiting(unsigned timeout_msec)
{
    if (0 == timeout_msec) {
        VIS_ASSERT_OK(::nodelay(stdscr, false));
    } else {
        ::timeout(timeout_msec);
    }
}

void NcursesTermDriver::ResetKeyboardWaiting()
{
    ::nodelay(stdscr, true);
}

KbStatus NcursesTermDriver::GetKeyboardStatus() const
{
    /// \todo
    return getch();
}

MouseStatus NcursesTermDriver::GetMouseStatus(Point& pos) const
{
    MEVENT mev;
    if (getmouse(&mev) != OK) {
        return msNothing;
    }

    pos.x_ = mev.x;
    pos.y_ = mev.y;

    // translate ncurses status to controller's status flags
    MouseStatus s = 0;

    s |= (mev.bstate & BUTTON1_PRESSED)        ? msLeftPressed : 0;
    s |= (mev.bstate & BUTTON1_RELEASED)       ? msLeftReleased : 0;
    s |= (mev.bstate & BUTTON1_CLICKED)        ? msLeftClicked : 0;
    s |= (mev.bstate & BUTTON1_DOUBLE_CLICKED) ? msLeftDblClicked : 0;

    s |= (mev.bstate & BUTTON2_PRESSED)        ? msMiddlePressed : 0;
    s |= (mev.bstate & BUTTON2_RELEASED)       ? msMiddleReleased : 0;
    s |= (mev.bstate & BUTTON2_CLICKED)        ? msMiddleClicked : 0;
    s |= (mev.bstate & BUTTON2_DOUBLE_CLICKED) ? msMiddleDblClicked : 0;

    s |= (mev.bstate & BUTTON3_PRESSED)        ? msRightPressed : 0;
    s |= (mev.bstate & BUTTON3_RELEASED)       ? msRightReleased : 0;
    s |= (mev.bstate & BUTTON3_CLICKED)        ? msRightClicked : 0;
    s |= (mev.bstate & BUTTON3_DOUBLE_CLICKED) ? msRightDblClicked : 0;

    s |= (mev.bstate & BUTTON4_PRESSED)        ? msScrollUp : 0;
    s |= (mev.bstate & BUTTON4_RELEASED)       ? msScrollDown : 0;
    // s |= (mev.bstate & BUTTON4_CLICKED)        ? msScrollUp : 0;
    // s |= (mev.bstate & BUTTON4_DOUBLE_CLICKED) ? msScrollDown : 0;

    /*! \todo ???
    s |= (mev.bstate & BUTTON_SHIFT)           ? msShiftPressed : 0;
    s |= (mev.bstate & BUTTON_CTRL)            ? msCtrlPressed : 0;
    s |= (mev.bstate & BUTTON_ALT)             ? msAltPressed : 0;
    */

    s |= (mev.bstate & REPORT_MOUSE_POSITION)  ? msMove : 0;

    return s;
}

void NcursesTermDriver::Beep()
{
    VIS_ASSERT_OK(::beep());
}


//--- private ----------------------------------------------------------------------------------------------------------

short NcursesTermDriver::CalcColorPair(Color foreground, Color background) const
{
    return ((foreground & 0x07) | ((background & 0x07) << 3)) + 1;
}

void NcursesTermDriver::InitColors()
{
    for (Color f = 0; f < 8; ++f) {
        for (Color b = 0; b < 8; ++b) {
            VIS_ASSERT_OK(init_pair(CalcColorPair(f, b), f, b));
        }
    }
}

}   // NVis
