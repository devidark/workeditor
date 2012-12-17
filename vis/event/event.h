/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

namespace NVis {

//! Базовое событие
class Event
{
    public:
        virtual ~Event() {}

        virtual void Execute() = 0;

    protected:
        Event() {}

    private:
        Event(const Event&);
        Event& operator=(const Event&);
};

}   // NVis
