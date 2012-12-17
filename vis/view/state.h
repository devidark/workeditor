/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include "view.h"

namespace NVis {

/*!
 *  \brief  Состояние визуального объекта.
 */
class ViewState
{
    public:
        //! Флаги состояния визуального объекта.
        enum EState {
            stResizing  = 0x01,             //!< Элемент в процессе изменения размера.
            stMoving    = 0x02              //!< Элемент в процессе изменения положения.
        };

        ViewState(uint16_t state = 0)
            : state_(state)
        {}

        //! Установить флаги состояния.
        void Set(uint16_t flags) { state_ |= flags; }

        //! Сбросить флаги состояния.
        void Reset(uint16_t flags) { state_ &= ~flags; }

        ViewState& operator+=(uint16_t flags)       { Set(flags); return *this; }
        ViewState& operator-=(uint16_t flags)       { Reset(flags); return *this; }
        ViewState  operator+(uint16_t flags) const  { ViewState st(*this); st.Set(flags); return st; }
        ViewState  operator-(uint16_t flags) const  { ViewState st(*this); st.Reset(flags); return st; }

        //! Получить флаги текущего состояния объекта.
        unsigned Get() const { return state_; }

        //! Проверить наличие флагов (true == _все_ флаги установлены).
        bool Check(uint16_t flags) const { return (state_ & flags == flags); }

    protected:
        uint16_t state_;
};

}   // NVis
