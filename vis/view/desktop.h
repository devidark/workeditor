/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <stack>
#include "io/output.h"
#include "window.h"

namespace NVis {

/*!
 *  \brief  Рабочий стол.
 */
class Desktop
    : public View
{
    public:
        Desktop()
            : View(Rect(Screen::I().GetRect()), true)
        {}

        virtual ~Desktop() {}

        //! Нарисовать объект.
        virtual void OnDraw()
        {
            //
        }
};

}   // NVis
