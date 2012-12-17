/*!
 *  \brief  Геометрия терминала.
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

namespace NVis {

//! Точка
struct Point {
    Point(): x_(0), y_(0) {}
    Point(unsigned x, unsigned y)
        : x_(x)
        , y_(y)
    {}

    unsigned x_, y_;
};

//! Прямоугольная область
struct Rect {
    Rect() {}
    Rect(unsigned x, unsigned y, unsigned w, unsigned h)
        : begin_(x, y)
        , sizes_(w, h)
    {}

    Point begin_;
    Point sizes_;
};

}   // NVis
