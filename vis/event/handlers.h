/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include "io/output.h"
#include "event/event.h"
#include "io/input.h"
#include "object.h"
#include "view/view.h"

namespace NVis {

//! Событие от клавиатуры
class EventKeyboard
    : public Event
{
    public:
        EventKeyboard(View* dst, KeyCode key_code)
            : dst_(dst)
            , key_code_(key_code)
        {}

        void Execute();

    private:
        View*   dst_;
        KeyCode key_code_;
};

//! Событие от мыши
class EventMouse
    : public Event
{
    public:
        EventMouse(View* dst, const Point& point, MouseState mouse_state)
            : dst_(dst)
            , point_(point)
            , mouse_state_(mouse_state)
        {}

        void Execute();

    private:
        View*       dst_;
        Point       point_;
        MouseState  mouse_state_;
};

//! Событие от таймера
class EventTimer
    : public Event
{
    public:
        EventTimer(Object* dst)
            : dst_(dst)
        {}

        void Execute();

    private:
        Object* dst_;
};

//! Событие "Сообщение от другого объекта"
class EventMessage
    : public Event
{
    public:
        EventMessage(Objcect* sender, Object* dst, unsigned message)
            : sender_(sender)
            , dst_(dst)
            , message_(message)
        {}

        void Execute();

    private:
        Object*  sender_;
        Object*  dst_;
        unsigned message_;
};


//--- Системные события ------------------------------------------------------------------------------------------------

//! Событие "Перерисовать объект"
class EventRedraw
    : public Event
{
    public:
        EventRedraw(View* dst)
            : dst_(dst)
        {}

        void Execute();

    private:
        View* dst_;
};

//! Событие "Установить фокус"
class EventSetFocus
    : public Event
{
    public:
        EventSetFocus(View* dst)
            : dst_(dst)
        {}

        void Execute();

    private:
        View* dst_;
};

//! Событие "Нарисовать всё" (полностью)
struct EventDrawAll
    : public Event
{
    void Execute();
};

//! Событие "Размер экрана изменился"
struct EventScreenResized
    : public Event
{
    void Execute();
};

//! \todo   ??? НУЖНА ЛИ - Реакция объектов на события ???
/*
enum EReaction {
    rctNothing = 0,
    rctClose,
    rctOk,
    rctCancel,
    rctMenu,
    rctZoom,
    rctResize
};
*/

}   // NVis
