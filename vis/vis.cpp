/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include "vis.h"
#include "event/queue.h"
#include "event/handlers.h"

namespace NVis {

//! Добавить визуальный объект во владение системы.
void Vis::AddView(View* view)
{
    ASSERT(view);
    if (view->IsModal()) {
        modal_stack_.push_back(ModalEnv(view));
    } else {
        TopModalEnv().Add(view);
    }
}

//! Получить текущую группу.
View* Vis::TopView()
{
    ASSERT(!modal_stack_.empty());
    if (TopModalEnv().zorder_.empty()) {
        return NULL;
    }
    return TopModalEnv().zorder_.back().get();
}

//! Получить текущую модальную группу.
View* Vis::TopModalView()
{
    ASSERT(!modal_stack_.empty());
    return modal_stack_.back().win_.get();
}

//! Установить пользовательскую функцию "бездействия".
void Vis::SetIdleMethod(IdleMethod idle_method)
{
    idle_method_ = idle_method;
}

//! Запуск системы.
void Vis::Run()
{
    // если фокус никуда не установлен, устанавливаем его на рабочий стол
    if (!focused_) {
        SetFocus(desktop_->GetCurrentFocused());     //! \todo Лучше брать "активный на вершине".
    }

    // нарисовать все видимые элементы
    DrawAll();

    // работаем
    while (!modal_stack_.empty()) {
        // полyчаем события и обрабатываем их
        if (PollEvents()) {
            HandleEvents();
        } else {
            if (idle_method_) {
                idle_method_();
            }
        }
    }
}

//! Останов системы.
void Vis::Stop()
{
    stop_ = true;
}

//! Получаем и постим события; true - очередь событий не пуста.
bool Vis::PollEvents()
{
    // - от мыши
    // - от клавы
    // - от таймера
    return !EventsQueue::Empty();
}

//! Обрабатываем события
void Vis::HandleEvents()
{
    while (!EventsQueue::Empty()) {
        EventsQueue::Peek()->Execute();
        EventsQueue::Next();
    }
}

}   // NVis
