/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <deque>
#include <list>
#include <set>
#include "view/desktop.h"
#include "event/handlers.h"

namespace NVis {

//! Метод, который будет вызываться во время "бездействия".
typedef void (*IdleMethod)();

/*!
 *  \brief  Visual System
 */
class Vis
{
    public:
        static Vis& Instance()
        {
            static Vis v;
            return v;
        }

        Vis()
            : desktop_(NULL)
            , idle_method_(NULL)
            , focused_(NULL)
            , stop_(false)
        {
            // создаём рабочий стол
            desktop_ = new Desktop();
            AddWindow(desktop_);
        }

        virtual ~Vis() {}

        Desktop* GetDesktop() { return desktop_; }

        //! Добавить группу визуальных объектов во владение системы.
        void AddView(View *view);

        //! Получить текущую группу.
        View* TopView();

        //! Получить текущую модальную группу.
        View* TopModalView();

        //! Установить пользовательскую функцию "бездействия".
        void SetIdleMethod(IdleMethod idle_method);

        //! Запуск системы.
        void Run();

        //! Останов системы.
        void Stop();

    private:
        friend class EventDrawAll;
        friend class EventScreenResized;

        Desktop*    desktop_;
        IdleMethod  idle_method_;
        View*       focused_;
        bool        stop_;

        //! Получаем и постим события; true - очередь событий не пуста.
        bool PollEvents();

        //! Обрабатываем события
        void HandleEvents();

        typedef IntrusivePtr<View>  PView;
        typedef std::list<PView>    ViewList;

        /*!
         *  \brief  Окрyжение модальной вьюхи.
         *          В рамках одной модальной группы может действовать несколько дочерних немодальных.
         *          Например, в рамках одного модального окна - несколько немодальных; более частный пример:
         *          рабочий стол - модальное окно, в его рамках может быть несколько немодальных окон.
         *          В данный момент может быть активно только верхнее по стеку модальное окно.
         *          Это значит, что все дочерние модальных, которые лежат по стеку ниже являются недоступными.
         *          Они видны, в них может что-то меняться (например, по таймеру), просто ими нельзя управлять
         *          клавой и мышью.
         */
        struct ModalEnv
        {
            public:
                PView    main_;                     //!< Модальная вьюха.
                ViewList zorder_;                   //!< Список дочерних вьюх, он же Z-Order; back() - верхняя вьюха.

                ModalEnv(View* view)
                    : main_(PView(view))
                {}

                //! Добавить дочерний объект во владение.
                void Add(View* view)
                {
                    zorder_.push_back(PView(view));
                }

                //! Уничтожить дочерний объект.
                void Del(View* view)
                {
                    zorder_.erase(Find(view));
                }

                //! Поместить объект сверху.
                void MoveToTop(View* view)
                {
                    ViewList::iterator i = Find(view);
                    ASSERT(i != zorder_.end());
                    PView pw = *i;
                    zorder_.erase(i);
                    zorder_.push_back(pw);
                }

                //! true, если win действует в рамках данного модального
                bool IsHere(View* view) const
                {
                    return (view == main_.get() || Find(view) != zorder_.end());
                }

            private:
                ViewList::iterator Find(View* view) const
                {
                    ViewList::iterator i = zorder_.begin(), e = zorder_.end();
                    for (; i != e; ++i) {
                        if (i->get() == view) {
                            break;
                        }
                    }
                    return i;
                }
        };

        typedef std::deque<ModalEnv> ModalStack;
        ModalStack modal_stack_;

        //! Текyщее модальное окрyжение
        ModalEnv& TopModalEnv() const
        {
            return modal_stack_.back();
        }
};

}   // NVis
