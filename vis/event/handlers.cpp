/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include "handlers.h"
#include <vis.h>

namespace NVis {

//! Обработчик события от клавиатуры
void EventKeyboard::Execute()
{
    dst_->OnKey(key_code);
}

//! Обработчик события от мыши
void EventMouse::Execute()
{
    /// \todo   В зависимости от того, что мышь сделала, нужно дёрнуть OnClick/OnDblClick/OnDrag/OnDrop
    dst_->OnMouseClick(point_);
}

//! Обработчик события от таймера
void EventTimer::Execute()
{
    dst_->OnTimer();
}

//! Обработчик события "Сообщение от другого объекта"
void EventMessage::Execute()
{
    dst_->OnMessage(sender_, message_);
}

//! Обработчик события "Перерисовать объект"
void EventRedraw::Execute()
{
    /// \todo Возможно, здесь нужны доработки
    dst_->FullDraw();
}

//! Обработчик события "Установить фокус"
void EventSetFocus::Execute()
{
    ASSERT(dst_);

    // получаем корневой объект (обычно окно)
    View* pview = dst_->GetRootView();

    // Если фокусируемое окно не действует в рамках текущего модального, выходим
    if (!modal_stack_.back().IsHere(pview)) {
        return false;
    }

    // Окно
    if (!pview) {
        // Не фокусируемое окно
        if (!(dst_->is_focusable_ && dst_->is_visible_)) {
            return false;
        }
        // Не модальное - меняем z-order окна.
        if (!dst_->IsModal()) {
            modal_stack_.back().MoveToTop(win);
        }
        // Берём текущий элемент окна, фокусируемся на него.
        dst_ = win->GetCurrentChildView();
        if (!dst_) {
            return false;
        }
    // Обычный визуальный элемент
    } else if (!dst_->IsFocusable()) {
        // если элемент не фокyсирyемый, делаем фокyс на родительское окно
        SetFocus(pview);
        return false;
    }

    // Переключаем
    if (focused_) {
        focused_->State().Reset(ViewState::stFocused);
    }
    focused_ = dst_;
    dst_->State().Set(ViewState::stFocused);
    return true;
}

//! Обработчик события "Нарисовать всё (полностью)"
void EventDrawAll::Execute()
{
    Vis::ModalStack::const_iterator mwi = Vis::Instance().modal_stack_.begin(), mwe = Vis::Instance().modal_stack_.end();
    for (; mwi != mwe; ++mwi) {
        const Vis::ModalEnv& modal_env = *mwi;
        modal_env.main_->FullDraw();
        // окна, действующие в рамках данного модального
        const Vis::ViewList& zord = modal_env.zorder_;
        Vis::ViewList::const_iterator wi = zord.begin(), we = zord.end();
        for (; wi != we; ++wi) {
            wi->get()->FullDraw();
        }
    }
}

//! Обработчик события "Размер экрана изменился"
void EventScreenResized::Execute()
{
    /// \todo Здесь нужно написать алгоритм.
}

}   // NVis
