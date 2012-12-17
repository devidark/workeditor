/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <stdint.h>
#include "io/output.h"
#include "io/input.h"
#include "vis/object.h"
#include "event/event.h"
#include "event/handlers.h"
#include "event/queue.h"
#include "state.h"

namespace NVis {

/*!
 *  \brief  Визуальный объект
 */
class View
    : public Object
{
    public:
        // Атрибуты.
        bool is_visible_;
        bool is_focusable_;

        // На объект сейчас можно установить фокус
        bool CanBeFocused() const { return is_visible_ && is_focusable_; }

        //! Признак модальности группы объектов.
        bool IsModal() const { return is_modal_; }

        // Позиционирование объекта относительно предка.
        enum EPositioning {
            posCenterX       = 0x001,
            posCenterY       = 0x002,
            posCenter        = (posCenterX | posCenterY),
            posStickLeft     = 0x010,
            posStickRight    = 0x020,
            posStickTop      = 0x040,
            posStickBottom   = 0x080,
            posStick         = (posStickLeft | posStickRight | posStickTop | posStickBottom),
            posExpandLeft    = 0x100,
            posExpandRight   = 0x200,
            posExpandTop     = 0x400,
            posExpandBottom  = 0x800,
            posExpand        = (posExpandLeft | posExpandRight | posExpandTop | posExpandBottom)
        };
        uint16_t positioning_;

        // Положение и размеры объекта
        void SetRect(const Rect& rect) { rect_ = rect; Redraw(); }
        const Rect& GetRect() const { return rect_; }

        //! Drawing of this object.
        virtual void OnDraw() const = 0;

        ViewState&       State()        { return state_; }
        const ViewState& State() const  { return state_; }

        //! Ask the system to accurately redrawing of this object
        void Redraw() { EventsQueue::Post(new EventRedraw(this)); }

        //! Ask the system to set focus to this object
        void SetFocus() { EventsQueue::Post(new EventSetFocus(this)); }

        //! Add the view as a child to owning
        View& AddChildView(View* view);

        //! Get the root parent (that hasn't parent) of this view
        View* GetRootView() const;

        //! Drawing of this object and its children
        void FullDraw() const;

        //! Handling the focus of the child views
        View* GetCurrentFocused();
        View* ResetCurrentFocused();
        View* NextFocusable();

        //! Реакции пользователя на те или иные события
        virtual Event::EReaction OnMouseClick(const Point& point)   { return Event::rctNothing; }
        virtual Event::EReaction OnMouseDblClick(const Point& point){ return Event::rctNothing; }
        virtual Event::EReaction OnMouseDrag(const Point& point)    { return Event::rctNothing; }
        virtual Event::EReaction OnMouseDrop(const Point& point)    { return Event::rctNothing; }
        virtual Event::EReaction OnClose()                          { return Event::rctNothing; }
        virtual Event::EReaction OnKey(KeyCode key_code)            { return Event::rctNothing; }

    protected:
        Rect     rect_;             //!< Положение относительно предка и размеры объекта.
        ViewAttr attr_;

        bool is_movable_;
        bool is_sizeable_;

        View(const Rect& rect, bool is_visible = true, bool is_modal = false)
            : Object(true)
            , rect_(rect)
            , is_visible_(is_visible)
            , is_focusable_(true)
            , positioning_(0)
            , is_movable_(false)
            , is_sizeable_(false)
            , is_modal_(is_modal)
        {}

        virtual ~View() {}

    private:
        bool      is_modal_;
        ViewState state_;

        void  FullDrawImpl(const View* view) const;
        View* GetCurrentFocusedImpl(View* view);
        View* ResetCurrentFocusedImpl(View* view);
        View* NextFocusableImpl(View* view);

        // Сместить курсор на текущий объект на фокусируемый объект (если только он сам не таковой).
        View* ToFocusable(View* view) const
        {
            Object* c = view->GetCurrentTreeObject();
            while (c && (!c->IsView() || !static_cast<View*>(c)->CanBeFocused())) {
                c = view->NextTreeObject();
            }
            return static_cast<View*>(c);
        }
};

}   // NVis
