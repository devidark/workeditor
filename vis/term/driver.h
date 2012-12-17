/*!
 *  \brief  Интерфейс драйвера терминала.
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include "common.h"
#include "geometry.h"
#include "colors.h"
#include "keyboard.h"
#include "mouse.h"

namespace NVis {

//! Pseudo-graphics symbols' ids
enum EPseudoGraph {
    PG_LINE_TL,         // top-left
    PG_LINE_TM,         // top-middle
    PG_LINE_TR,         // top-right
    PG_LINE_CL,         // center-left
    PG_LINE_CM,         // center-middle, eqivalent of PG_LINE_CROSS
    PG_LINE_CR,         // center-right
    PG_LINE_BL,         // bottom-left
    PG_LINE_BM,         // bottom-middle
    PG_LINE_BR,         // bottom-right
    PG_LINE_CROSS,      // cross-liner, eqivalent of PG_LINE_CM
    PG_LINE_VERT,       // vertical line
    PG_LINE_HORZ        // horizontal line
};

/*!
 *  \brief  Интерфейс драйвера терминала.
 *
 *  \note   Аксиомы и гарантии.
 *          Настройки по-умолчанию:
 *            - цвета: текущие цвета консоли.
 *            - системный курсор: виден.
 *            - клавиатура: блокирующее получение значений с клавиатуры (ждем нажатия клавиатуры);
 *            - мышь: работа инициализируется, курсор мыши скрыт.
 *          Координаты:
 *            - координаты символов считаются из левого верхнего угла, начиная с (0,0),
 *              где в данном случае первый "0" - это номер строки, второй - номер столбца.
 *          Цвета:
 *            - поддержка цветности зависит от терминала и реализации контроллера;
 *            - максимальное количество цветов для фона и тона - 16 (от черного до белого).
 *          Клавиатура и мышь:
 *            - клавиатура: гарантирована работа в блокирующем (по-умолчанию) и неблокирующем режиме.
 *            - мышь: нет гарантий работы - всё зависит от терминала и реализации контроллера.
 *            - спектр возвращаемых значений для клавиатуры и мыши зависит от возможностей
 *              терминала и реализации контроллера.
 *          Звук:
 *            - возможность издать звуковой сигнал зависит от терминала и реализации контроллера.
 *          Ошибки и исключения:
 *            - в случае ошибок драйвер бросает исключение std::runtime_error.
 */
class ITerm
{
public:
    //! Instance of singleton; тело метода в реализации драйвера
    static ITerm& Driver();

    // Работа драйвера в целом
    virtual bool IsEnabled() const = 0;
    virtual bool Enable() = 0;
    virtual void Disable() = 0;

    // *** Screen Refreshing ***
    //! Перерисовать экран из буфера
    virtual void ScreenUpdate() = 0;

    //! \todo TODO
    virtual void SetScreenResizeHandler() {}

    // *** Screen specific ***

    //! True, если инициализация экрана прошла успешно; экранные функции можно использовать
    virtual bool ScreenReady() const = 0;

    //! Очистить экран
    virtual void ClearScreen() = 0;

    //! Проддержка цветности
    virtual bool HasColors() const = 0;

    //! Размер экрана; y - кол-во строк; x - количество столбцов;
    virtual Point GetScreenSize() const = 0;

    //! Видимость системного курсора
    virtual bool IsCursorVisible() const = 0;
    virtual void ShowCursor() = 0;
    virtual void HideCursor() = 0;

    //! Получить/Установить текущую позицию курсора.
    virtual Point GetCursorPos() const = 0;
    virtual void SetCursorPos(unsigned x, unsigned y) = 0;

    //! Установить цвета
    virtual void SetColor(Color foreground, Color background) = 0;
    virtual void SetForeColor(Color color) = 0;
    virtual void SetBackColor(Color color) = 0;

    //! Получить цвета
    virtual Color GetForeColor() const = 0;
    virtual Color GetBackColor() const = 0;

    //! Вывод
    virtual void PrintChar(unsigned x, unsigned y, Char c) = 0;
    virtual void Print(unsigned x, unsigned y, String s) = 0;
    virtual void PrintInt(unsigned x, unsigned y, long n) = 0;
    virtual void PrintReal(unsigned x, unsigned y, double n) = 0;
    virtual void PrintGraph(unsigned x, unsigned y, EPseudoGraph c) = 0;


    // *** Keyboard specific ***

    //! True, если клавиатурные функции можно использовать
    virtual bool KeyboardReady() const = 0;

    //! 0 - неблокирующий ввод через GetKeyboardStatus() ("пролетает"); иначе ждет соотв. кол-во миллисекунд.
    virtual void SetKeyboardWaiting(unsigned timeout_msec = 0) = 0;

    //! Включить "неблокирующий" режим
    virtual void ResetKeyboardWaiting() = 0;

    //! Получить состояние клавиатуры (нажатые клавиши).
    virtual KbStatus GetKeyboardStatus() const = 0;

    // *** Mouse specific ***
    virtual MouseStatus GetMouseStatus(Point& pos) const = 0;

    // *** Speaker specific ***
    virtual void Beep() = 0;

protected:
    ITerm() {}
    virtual ~ITerm() {}

private:
    ITerm(const ITerm&);
    ITerm& operator=(const ITerm&);
};

}   // NVis
