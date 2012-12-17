#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vis/term/driver.h>

class Tests
{
    size_t line_;

    NVis::Point screen_size_;
    bool        has_colors_;
    bool        has_mouse_;

    void Wait()
    {
        NVis::ITerm::Driver().Print(0, ++line_, "... press any key to continue ...");
        NVis::ITerm::Driver().ScreenUpdate();
        NVis::ITerm::Driver().GetKeyboardStatus();
        NVis::ITerm::Driver().ClearScreen();
    }

public:
    Tests(): line_(0) {}

    void Init()
    {
        // Enable driver
        NVis::ITerm::Driver().Enable();

        // Check the screen and keyboard
        if (! NVis::ITerm::Driver().ScreenReady()) {
            throw std::runtime_error("Screen is not ready!");
        }
        if (! NVis::ITerm::Driver().KeyboardReady()) {
            throw std::runtime_error("Keyboard is not ready");
        }
    }

    void Test1_ScreenSize_HasColors_HasMouse()
    {
        line_ = 0;
        NVis::ITerm::Driver().Print(0, line_++, "=== Initial Test ===");

        // Get and show the screen size
        screen_size_ = NVis::ITerm::Driver().GetScreenSize();
        {
            std::stringstream ss;
            ss << "Screen size: " << screen_size_.y_ << " rows, " << screen_size_.x_ << " columns";
            NVis::ITerm::Driver().Print(0, line_++, ss.str());
        }

        // Check for colors
        has_colors_ = NVis::ITerm::Driver().HasColors();
        {
            std::stringstream ss;
            ss << "Has colors: " << (has_colors_ ? "YES" : "NO");
            NVis::ITerm::Driver().Print(0, line_++, ss.str());
        }

        Wait();
    }

    void Test2_Colors()
    {
        line_ = 0;
        NVis::ITerm::Driver().Print(0, line_++, "=== Colors Test ===");

        NVis::Color last_fore = NVis::ITerm::Driver().GetForeColor();
        NVis::Color last_back = NVis::ITerm::Driver().GetBackColor();

        // Try to print all colors for foreground
        size_t last = line_;
        NVis::ITerm::Driver().SetBackColor(NVis::clBlack);

        NVis::ITerm::Driver().SetForeColor(NVis::clBlack);          NVis::ITerm::Driver().Print(0, line_++, "  Black        ");
        NVis::ITerm::Driver().SetForeColor(NVis::clRed);            NVis::ITerm::Driver().Print(0, line_++, "  Red          ");
        NVis::ITerm::Driver().SetForeColor(NVis::clGreen);          NVis::ITerm::Driver().Print(0, line_++, "  Green        ");
        NVis::ITerm::Driver().SetForeColor(NVis::clBrown);          NVis::ITerm::Driver().Print(0, line_++, "  Brown        ");
        NVis::ITerm::Driver().SetForeColor(NVis::clBlue);           NVis::ITerm::Driver().Print(0, line_++, "  Blue         ");
        NVis::ITerm::Driver().SetForeColor(NVis::clMagenta);        NVis::ITerm::Driver().Print(0, line_++, "  Magenta      ");
        NVis::ITerm::Driver().SetForeColor(NVis::clCyan);           NVis::ITerm::Driver().Print(0, line_++, "  Cyan         ");
        NVis::ITerm::Driver().SetForeColor(NVis::clGrey);           NVis::ITerm::Driver().Print(0, line_++, "  Grey         ");
        NVis::ITerm::Driver().SetForeColor(NVis::clDarkGrey);       NVis::ITerm::Driver().Print(0, line_++, "  DarkGrey     ");
        NVis::ITerm::Driver().SetForeColor(NVis::clLightRed);       NVis::ITerm::Driver().Print(0, line_++, "  LightRed     ");
        NVis::ITerm::Driver().SetForeColor(NVis::clLightGreen);     NVis::ITerm::Driver().Print(0, line_++, "  LightGreen   ");
        NVis::ITerm::Driver().SetForeColor(NVis::clYellow);         NVis::ITerm::Driver().Print(0, line_++, "  Yellow       ");
        NVis::ITerm::Driver().SetForeColor(NVis::clLightBlue);      NVis::ITerm::Driver().Print(0, line_++, "  LightBlue    ");
        NVis::ITerm::Driver().SetForeColor(NVis::clLightMagenta);   NVis::ITerm::Driver().Print(0, line_++, "  LightMagenta ");
        NVis::ITerm::Driver().SetForeColor(NVis::clLightCyan);      NVis::ITerm::Driver().Print(0, line_++, "  LightCyan    ");
        NVis::ITerm::Driver().SetForeColor(NVis::clWhite);          NVis::ITerm::Driver().Print(0, line_++, "  White        ");

        // Try to print all colors for background
        line_ = last;
        NVis::ITerm::Driver().SetForeColor(NVis::clWhite);

        NVis::ITerm::Driver().SetBackColor(NVis::clBlack);          NVis::ITerm::Driver().Print(20, line_++, "  Black        ");
        NVis::ITerm::Driver().SetBackColor(NVis::clRed);            NVis::ITerm::Driver().Print(20, line_++, "  Red          ");
        NVis::ITerm::Driver().SetBackColor(NVis::clGreen);          NVis::ITerm::Driver().Print(20, line_++, "  Green        ");
        NVis::ITerm::Driver().SetBackColor(NVis::clBrown);          NVis::ITerm::Driver().Print(20, line_++, "  Brown        ");
        NVis::ITerm::Driver().SetBackColor(NVis::clBlue);           NVis::ITerm::Driver().Print(20, line_++, "  Blue         ");
        NVis::ITerm::Driver().SetBackColor(NVis::clMagenta);        NVis::ITerm::Driver().Print(20, line_++, "  Magenta      ");
        NVis::ITerm::Driver().SetBackColor(NVis::clCyan);           NVis::ITerm::Driver().Print(20, line_++, "  Cyan         ");
        NVis::ITerm::Driver().SetBackColor(NVis::clGrey);           NVis::ITerm::Driver().Print(20, line_++, "  Grey         ");
        NVis::ITerm::Driver().SetBackColor(NVis::clDarkGrey);       NVis::ITerm::Driver().Print(20, line_++, "  DarkGrey     ");
        NVis::ITerm::Driver().SetBackColor(NVis::clLightRed);       NVis::ITerm::Driver().Print(20, line_++, "  LightRed     ");
        NVis::ITerm::Driver().SetBackColor(NVis::clLightGreen);     NVis::ITerm::Driver().Print(20, line_++, "  LightGreen   ");
        NVis::ITerm::Driver().SetBackColor(NVis::clYellow);         NVis::ITerm::Driver().Print(20, line_++, "  Yellow       ");
        NVis::ITerm::Driver().SetBackColor(NVis::clLightBlue);      NVis::ITerm::Driver().Print(20, line_++, "  LightBlue    ");
        NVis::ITerm::Driver().SetBackColor(NVis::clLightMagenta);   NVis::ITerm::Driver().Print(20, line_++, "  LightMagenta ");
        NVis::ITerm::Driver().SetBackColor(NVis::clLightCyan);      NVis::ITerm::Driver().Print(20, line_++, "  LightCyan    ");
        NVis::ITerm::Driver().SetBackColor(NVis::clWhite);          NVis::ITerm::Driver().Print(20, line_++, "  White        ");

        NVis::ITerm::Driver().SetColor(last_fore, last_back);
        Wait();
    }

    void Test3_PseudoGraphics()
    {
        line_ = 0;
        NVis::ITerm::Driver().Print(0, line_++, "=== PseudoGraphics Test ===");
        NVis::Color last_fore = NVis::ITerm::Driver().GetForeColor();
        NVis::Color last_back = NVis::ITerm::Driver().GetBackColor();

        NVis::ITerm::Driver().SetColor(NVis::clYellow, NVis::clBlue);

        const size_t vstep = 8, vsz = vstep * 2 + 1;
        const size_t hstep = 16, hsz = hstep * 2 + 1;
        const size_t top_margin = 2, left_margin = 2;

        // fill square
        for (size_t i = 0; i < hsz; ++i) {
            for (size_t j = 0; j < vsz; ++j) {
                NVis::ITerm::Driver().PrintChar(i + left_margin, j + top_margin, ' ');
            }
        }

        // draw 3 horizontal lines
        for (size_t i = 0; i < hsz; ++i) {
            NVis::ITerm::Driver().PrintGraph(i + left_margin, top_margin, NVis::PG_LINE_HORZ);
            NVis::ITerm::Driver().PrintGraph(i + left_margin, top_margin + vstep, NVis::PG_LINE_HORZ);
            NVis::ITerm::Driver().PrintGraph(i + left_margin, top_margin + vstep*2, NVis::PG_LINE_HORZ);
        }
        // draw 3 vertical lines
        for (size_t i = 0; i < vsz; ++i) {
            NVis::ITerm::Driver().PrintGraph(left_margin, top_margin + i, NVis::PG_LINE_VERT);
            NVis::ITerm::Driver().PrintGraph(left_margin + hstep, top_margin + i, NVis::PG_LINE_VERT);
            NVis::ITerm::Driver().PrintGraph(left_margin + hstep*2, top_margin + i, NVis::PG_LINE_VERT);
        }
        // draw corners and crossers
        NVis::ITerm::Driver().PrintGraph(left_margin, top_margin, NVis::PG_LINE_TL);
        NVis::ITerm::Driver().PrintGraph(left_margin + hstep, top_margin, NVis::PG_LINE_TM);
        NVis::ITerm::Driver().PrintGraph(left_margin + hstep*2, top_margin, NVis::PG_LINE_TR);

        NVis::ITerm::Driver().PrintGraph(left_margin, top_margin + vstep, NVis::PG_LINE_CL);
        NVis::ITerm::Driver().PrintGraph(left_margin + hstep, top_margin + vstep, NVis::PG_LINE_CM);
        NVis::ITerm::Driver().PrintGraph(left_margin + hstep*2, top_margin + vstep, NVis::PG_LINE_CR);

        NVis::ITerm::Driver().PrintGraph(left_margin, top_margin + vstep*2, NVis::PG_LINE_BL);
        NVis::ITerm::Driver().PrintGraph(left_margin + hstep, top_margin + vstep*2, NVis::PG_LINE_BM);
        NVis::ITerm::Driver().PrintGraph(left_margin + hstep*2, top_margin + vstep*2, NVis::PG_LINE_BR);

        NVis::ITerm::Driver().SetColor(last_fore, last_back);
        line_ = 20;
        Wait();
    }

    void Test4_Cursor()
    {
        line_ = 0;
        NVis::ITerm::Driver().Print(0, line_++, "=== System Cursor Test ===");

        NVis::ITerm::Driver().ShowCursor();
        NVis::ITerm::Driver().Print(0, line_++, "Now you can see the system cursor here->");
        NVis::ITerm::Driver().ScreenUpdate();
        NVis::ITerm::Driver().GetKeyboardStatus();

        NVis::ITerm::Driver().HideCursor();
        NVis::ITerm::Driver().Print(0, line_++, "And now there is NO system cursor on screen!");

        Wait();
    }

    void Test5_Keyboard()
    {
        line_ = 0;
        NVis::ITerm::Driver().Print(0, line_++, "=== Keyboard Test; Space - interrupt testing ===");

        NVis::Point scr_size = NVis::ITerm::Driver().GetScreenSize();
        const size_t top = ++line_;
        const size_t bottom = scr_size.y_ - 1;
        const size_t wide = 10;
        const size_t right = scr_size.x_ - wide;
        size_t y = top, x = 0;
        unsigned key = 0;
        do {
            NVis::ITerm::Driver().Print(x, y, "->      ");
            key = NVis::ITerm::Driver().GetKeyboardStatus();
            NVis::ITerm::Driver().Print(x, y, "  ");
            NVis::ITerm::Driver().PrintInt(x+2, y, key);
            NVis::ITerm::Driver().ScreenUpdate();
            ++y;
            if (y > bottom) {
                y = top;
                x += wide;
                if (x > right) {
                    x = 0;
                }
            }
        }
        while (key != ' ');

        line_ = scr_size.y_-2;
        Wait();
    }

    void Test6_Mouse()
    {
        line_ = 0;
        NVis::ITerm::Driver().Print(0, line_++, "=== Mouse Test ===");
        NVis::ITerm::Driver().SetKeyboardWaiting(200);

        size_t spos = line_;
        NVis::ITerm::Driver().Print(0, line_++, "X:");
        NVis::ITerm::Driver().Print(0, line_++, "Y:");
        NVis::ITerm::Driver().Print(0, line_++, "-- Left button");
        NVis::ITerm::Driver().Print(0, line_++, "pressed    : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "released   : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "clicked    : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "dbl-clicked: [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "-- Right button");
        NVis::ITerm::Driver().Print(0, line_++, "pressed    : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "released   : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "clicked    : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "dbl-clicked: [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "-- Middle button");
        NVis::ITerm::Driver().Print(0, line_++, "pressed    : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "released   : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "clicked    : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "dbl-clicked: [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "-- Scroller");
        NVis::ITerm::Driver().Print(0, line_++, "up         : [ ]");
        NVis::ITerm::Driver().Print(0, line_++, "down       : [ ]");

        NVis::ITerm::Driver().Print(0, ++line_, "== Push mouse buttons! Press Enter to finish test. ==");

        NVis::Point ms_pos;
        unsigned ms_stat = 0;
        unsigned key = 0;
        const NVis::Char checked = 'X';
        const size_t margin_left = 14;

        do {
            ms_stat = NVis::ITerm::Driver().GetMouseStatus(ms_pos);
            size_t p = spos;
            NVis::ITerm::Driver().PrintInt(3, p++, ms_pos.x_);
            NVis::ITerm::Driver().PrintInt(3, p++, ms_pos.y_);
            p++;
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msLeftPressed) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msLeftReleased) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msLeftClicked) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msLeftDblClicked) ? checked : ' ');
            p++;
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msRightPressed) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msRightReleased) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msRightClicked) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msRightDblClicked) ? checked : ' ');
            p++;
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msMiddlePressed) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msMiddleReleased) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msMiddleClicked) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msMiddleDblClicked) ? checked : ' ');
            p++;
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msScrollUp) ? checked : ' ');
            NVis::ITerm::Driver().PrintChar(margin_left, p++, (ms_stat & NVis::msScrollDown) ? checked : ' ');
        }
        while ((key = NVis::ITerm::Driver().GetKeyboardStatus()) != '\r');

        NVis::ITerm::Driver().ResetKeyboardWaiting();
        Wait();
    }

    void Test10_ScreenResizeDetection()
    {
        // Wait();
    }

    ~Tests()
    {
        NVis::ITerm::Driver().Disable();
    }
};

int main(int argc, char* argv[])
{
    size_t line = 0;

    try {
        Tests tt;

        tt.Init();
        tt.Test1_ScreenSize_HasColors_HasMouse();
        tt.Test2_Colors();
        tt.Test3_PseudoGraphics();
        tt.Test4_Cursor();
        tt.Test5_Keyboard();
        tt.Test6_Mouse();
        tt.Test10_ScreenResizeDetection();
    }
    catch (const std::exception& exc) {
        std::cerr << " (!) Error: " << exc.what() << std::endl;
        return 1;
    }

    std::cout << "DONE" << std::endl;

    /*
    NVis::Point p = ctl.ScreenSize();

    // Check colors
    if (!ctl.ScreenHasColors()) {
        ctl.Print(0, 0, "Screen has NO colors!");
    } else {
        ctl.Print(0, 0, "Check all colors (16 foreground and 8 background colors total):");
        unsigned i = 0;
        for (NVis::Color f = 0; f < 16; ++f) {
            for (NVis::Color b = 0; b < 8; ++b) {
                ctl.SetColor(f, b);
                ctl.Print(f, b+1, "0");
            }
        }
    }

    ctl.ScreenRefresh();

    if (!ctl.MouseReady()) {
        ctl.Print(0, 20, "We have NO mouse! :(");
    } else {
        ctl.Print(0, 25, "Press SPACE for next test");
        NVis::Point p;
        ctl.EnableKeyboardDelayMode(10);
        do {
            NVis::MouseStatus ms = ctl.GetMouseStatus(p);
            std::stringstream s;
            s << "Mouse coords: " << p.x_ << ',' << p.y_ << "     ";
            ctl.Print(0, 20, s.str());
            if (ms & NVis::msButton1Pressed) {
                ctl.Print(0, 21, "BUTTON 1 PRESSED    ");
            }
            if (ms & NVis::msButton1Released) {
                ctl.Print(0, 22, "BUTTON 1 RELEASED   ");
            }
            if (ms & NVis::msButton1Clicked) {
                ctl.Print(0, 23, "BUTTON 1 CLICKED    ");
            }
            if (ms & NVis::msButton1DblClicked) {
                ctl.Print(0, 24, "BUTTON 1 DBL_CLICKED");
            }
            if (ms & NVis::msButton2Pressed) {
                ctl.Print(0, 21, "BUTTON 2 PRESSED    ");
            } else if (ms & NVis::msButton2Released) {
                ctl.Print(0, 21, "BUTTON 2 RELEASED   ");
            } else if (ms & NVis::msButton2Clicked) {
                ctl.Print(0, 21, "BUTTON 2 CLICKED    ");
            } else if (ms & NVis::msButton2DblClicked) {
                ctl.Print(0, 21, "BUTTON 2 DBL_CLICKED");
            } else if (ms & NVis::msButton2Pressed) {
                ctl.Print(0, 21, "BUTTON 3 PRESSED    ");
            } else if (ms & NVis::msButton3Released) {
                ctl.Print(0, 21, "BUTTON 3 RELEASED   ");
            } else if (ms & NVis::msButton3Clicked) {
                ctl.Print(0, 21, "BUTTON 3 CLICKED    ");
            } else if (ms & NVis::msButton3DblClicked) {
                ctl.Print(0, 21, "BUTTON 3 DBL_CLICKED");
            } else {
                // ctl.Print(0, 21, "                           ");
            }

            ctl.ScreenRefresh();
        } while (ctl.GetKeyboardStatus() != ' ');
        ctl.EnableKeyboardDelayMode();
    }

    NVis::KbStatus kb = 0;
    while ((kb = ctl.GetKeyboardStatus()) != ' ') {
        std::stringstream s;
        s << "Keycode: " << kb << "                          ";
        ctl.Print(0, 20, s.str());
        ctl.ScreenRefresh();
    }

    ctl.GetKeyboardStatus();
    */

    return 0;
}
