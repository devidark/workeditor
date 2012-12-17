/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

namespace NVis {

//! Вывод на экран
class Screen
{
    Rect geometry_;
    bool has_colors_;
    bool has_mouse_;

    public:
        //! Экземпляр экрана
        static Screen& Instance()
        {
            static Screen s;
            return s;
        }

        ~Screen()
        {}

        //! Вернуть текущие резмеры экрана
        const Rect& GetRect() const
        {
            return geometry_;
        }

        //! Обновить содержимое экрана.
        void Refresh() const
        {}

    private:
        Screen()
        {}
};

}   // NVis
