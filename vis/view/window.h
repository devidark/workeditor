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
 *  \brief  Окно.
 */
class Window
    : public View
{
    public:
        Window(const Rect& rect,
               bool modal = false,
               bool visible = true)
            : View(rect, visible, modal)
        {}

        virtual ~Window() {}

        //! Нарисовать.
        void OnDraw() const
        {
            //! \todo
        }
};

}   // NVis
