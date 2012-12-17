/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include "view.h"

namespace NVis {

//! Нарисовать объект и все его дочерние.
void View::FullDraw() const
{
    FullDrawImpl(this);
}

void View::FullDrawImpl(const View* view) const
{
    OnDraw();
    for (Object* obj = view->FirstChildObject(); obj; obj = obj->NextObject()) {
        if (obj->IsView()) {
            const View* v = dynamic_cast<const View*>(obj);
            if (v->IsVisible()) {
                v->OnDraw();
                FullDraw(v);
            }
        }
    }
}

//! Добавить дочерний визуальный элемент.
View& View::AddChildView(View* view)
{
    Object::AddChildObject(view);
    return *this;
}


//! Получить корневой визуальный объект (у него нет предков).
View* View::GetRootView() const
{
    Object* root = this;
    Object* obj = ParentObject();
    while (obj) {
        if (obj->IsView()) {
            root = obj;
        }
        obj = obj->ParentObject();
    }
    return dynamic_cast<View*>(root);
}

//! Получить текущий (выбранный) визуальный объект.
View* View::GetCurrentFocused()
{
    GetCurrentFocusedImpl(this);
}

View* View::GetCurrentFocusedImpl(View* view)
{
    return ToFocusable(view);
}

//! Сбросить текущий визуальный объект на первый.
View* View::ResetCurrentFocused()
{
    return ResetCurrentFocusedImpl(this);
}

View* View::ResetCurrentFocusedImpl(View* view)
{
    ResetFirstTreeObject();
    return GetCurrentFocusedImpl(this);
}

//! Переместить указатель текущего визуального объекта на следующий; NULL, если больше нет.
View* View::NextFocusable(View* view = NULL)
{
    return NextFocusableImpl(this);
}

View* View::NextFocusableImpl(View* view)
{
    view->NextTreeObject();
    return GetCurrentFocusedImpl(view);
}

}   // NVis
