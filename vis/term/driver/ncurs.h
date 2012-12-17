/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <vis/term/driver.h>

namespace NVis {

//! Вывод на экран
class NcursesTermDriver
    : public ITerm
{
    public:
        // Работа драйвера в целом
        bool IsEnabled() const;
        bool Enable();
        void Disable();

        // *** Screen specific ***

        //! True, если инициализация экрана прошла успешно; экранные функции можно использовать
        bool ScreenReady() const;

        //! Проддержка цветности
        bool HasColors() const;

        //! Размер экрана; y - кол-во строк; x - количество столбцов;
        Point GetScreenSize() const;

        //! Перерисовать экран из буфера
        void ScreenUpdate();

        //! Очистить экран
        virtual void ClearScreen();

        //! Видимость системного курсора
        bool IsCursorVisible() const;
        void ShowCursor();
        void HideCursor();

        //! Получить/Установить текущую позицию курсора.
        Point GetCursorPos() const;
        void SetCursorPos(unsigned x, unsigned y);

        //! Установить цвета
        void SetColor(Color foreground, Color background);
        void SetForeColor(Color color);
        void SetBackColor(Color color);

        //! Получить цвета
        Color GetForeColor() const;
        Color GetBackColor() const;

        //! Вывод
        void PrintChar(unsigned x, unsigned y, Char c);
        void Print(unsigned x, unsigned y, String s);
        void PrintInt(unsigned x, unsigned y, long n);
        void PrintReal(unsigned x, unsigned y, double n);
        void PrintGraph(unsigned x, unsigned y, EPseudoGraph c);


        // *** Keyboard specific ***

        //! True, если клавиатурные функции можно использовать
        bool KeyboardReady() const;

        //! Включить блокирующий ввод; 0 - ждать вечно до нажатия клавиши.
        void SetKeyboardWaiting(unsigned timeout_msec);

        //! Включить "неблокирующий" режим
        void ResetKeyboardWaiting();

        //! Получить состояние клавиатуры (нажатые клавиши).
        KbStatus GetKeyboardStatus() const;

        // *** Mouse specific ***

        MouseStatus GetMouseStatus(Point& pos) const;


        // *** Speaker specific ***
        void Beep();

    private:
        bool  enabled_;
        bool  cursor_visible_;
        bool  has_colors_;
        Color color_foreground_;
        Color color_background_;

        inline short CalcColorPair(Color foreground, Color background) const;
        void InitColors();

        NcursesTermDriver();
        ~NcursesTermDriver();

        friend ITerm& ITerm::Driver();
};

}   // NVis
