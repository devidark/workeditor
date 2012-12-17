/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <deque>
#include "event.h"

namespace NVis {

/*!
 *  \brief  Очередь событий.
 */
class EventsQueue
{
    public:
        //! Опубликовать событие
        static void Post(const Event* event)
        {
            queue_.push_back(event);
        }

        //! Просмотреть первое событие в очереди
        static const Event* Peek()
        {
            return queue_.front();
        }

        //! Удалить первое событие из очереди
        static void Next()
        {
            if (!queue_.empty()) {
                /// \todo   Переделать на auto_ptr?
                delete queue_.front();
                queue_.pop_front();
            }
        }

        //! True, если очередь пуста
        static bool Empty()
        {
            return queue_.empty();
        }

    private:
        static std::deque<Event*> queue_;
};

}   // NVis
