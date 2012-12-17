/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <list>
#include <common/intrusive.h>
#include "event/event.h"

namespace NVis {

/*!
 *  \brief  Объект.
 */
class Object
    : public IntrusivePtrBase
{
    public:
        typedef IntrusivePtr<Object>    PObject;
        //! \todo Что-то придyмать со списком, чтобы из него yдобно было yдалять. Видимо нyжно сделать свой intrusive_list.
        typedef std::list<PObject>      ObjectsList;

        //! Список дочерних объектов.
        const ObjectsList& GetChildObjects() const { return owning_objects_; }

        //! True, если объект визуальный.
        bool IsView() const { return is_view_; }

        //! Обработчик события "сообщение".
        virtual void OnMessage(Object* sender, unsigned message) {}

        //! Обработчик события таймера.
        virtual void OnTimer() {}

        Object* ParentObject() const { return parent_; }
        Object* FirstChildObject() const { return first_child_; }
        Object* NextObject() const { return next_; }
        Object* PrevObject() const { return prev_; }

        virtual ~Object() {}

    protected:
        Object(bool is_view = false)
            : is_view_(is_view)
            , parent_(NULL)
            , prev_(NULL)
            , next_(NULL)
            , first_child_(NULL)
            , last_child_(NULL)
            , current_(NULL)
        {}

        //! Добавить объект во владение в качестве дочернего.
        void AddChildObject(Object* obj)
        {
            ASSERT(obj);
            owning_objects_.push_back(PObject(obj));
            LinkChildTreeItem(obj);
        }

        //! Удалить и уничтожить дочерний объект.
        void DelChildObject(Object* obj)
        {
            ASSERT(obj);
            UnlinkChildTreeItem(obj);
            ObjectsList::iterator i = FindInList(obj);
            if (i != owning_objects_.end()) {
                owning_objects_.erase(i);
            }
        }

        //! Вернуть текущий элемент дерева объектов.
        Object* GetCurrentTreeObject() const { return current_; }

        //! Найти первый текущий элемент в дереве в порядке обхода "вглубину" (т.е. рекурсивно).
        Object* ResetFirstTreeObject()
        {
            // если есть дочерние, тогда идём вглубину, иначе возвращаем самого себя
            return (current_ = first_child_ ? first_child_->ResetFirstTreeObject() : this);
        }

        //! Переместить указатель на следующий элемент в порядке обхода "вглубину"
        Object* NextTreeObject()
        {
            ASSERT(current_);
            Object* n = NULL;
            // если есть дочерние, идем в глубину
            if (first_child_) {
                n = NextTreeObject();
            }
            // если нет дочерних или в глубине больше нет элементов, переходим на следующего брата
            if (!n && current_) {
                n = current_->next_;
            }
            return (current_ = n);
        }

    private:
        bool        is_view_;                   //!< Визуальный объект.
        ObjectsList owning_objects_;            //!< Дочерние объекты, находящиеся во владении текущего.
        // указатели, образующие дерево
        Object*     parent_;
        Object*     prev_;
        Object*     next_;
        Object*     first_child_;
        Object*     last_child_;
        Object*     current_;

        //! Вернуть предка данного объекта в дереве.
        Object* GetParentTreeItem() const { return parent_; }

        //! Присоединить дочерний элемент в дерево к данному.
        void LinkChildTreeItem(Object* obj)
        {
            ASSERT(obj);
            ASSERT(!obj->prev_ && !obj->next_);
            obj->parent_ = this;
            // первый дочерний
            if (!last_child_) {
                ASSERT(!last_child_ && !first_child_);
                first_child_ = obj;
                last_child_ = obj;
                return;
            }
            // очередной
            last_child_->next_ = obj;
            obj->prev_ = last_child_;
            last_child_ = obj;
            // если текyщий не задан
            if (!current_) {
                current_ = obj;
            }
        }

        //! Отсоединить дочерний элемент (всё дочернее поддерево остается целым).
        void UnlinkChildTreeItem(Object* obj)
        {
            ASSERT(obj);
            // если отсоединяют текущий
            if (obj == current_) {
                current_ = current_->next_ ? current_->next_ : current_->parent_;
            }
            // отсединение из цепочки братьев
            if (obj->prev_) {
                obj->prev_->next_ = obj->next_;
            }
            if (obj->next_) {
                obj->next_->prev_ = obj->prev_;
            }
            // отсоединяемся от предка
            if (first_child_ == obj) {
                first_child_ = obj->next_;
            }
            if (last_child_ == obj) {
                last_child_ = obj->prev_;
            }
            // затираем предысторию
            obj->parent_ = NULL;
            obj->prev_ = NULL;
            obj->next_ = NULL;
            obj->current_ = NULL;
        }

        // Найти элемент в списке
        ObjectsList::iterator FindInList(Object* obj)
        {
            ObjectsList::iterator i = owning_objects_.begin(), e = owning_objects_.end();
            while (i != e && *i != obj) {
                ++i;
            }
            return i;
        }
};

}   // NVis
