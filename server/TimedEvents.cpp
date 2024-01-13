/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** TimedEvent.cpp
*/

#include "TimedEvents.hpp"

namespace server {

    /*
     * TimedEvents
     * Constructor of TimedEvents
     */
    TimedEvents::TimedEvents() : _time(0), _events(), _reocurringEvents()
    {
    }

    /*
     * ~TimedEvents
     * Destructor of TimedEvents
     */
    TimedEvents::~TimedEvents()
    {
    }

    /*
     * addEvent
     * Add an event
     * @param func: the function
     * @param time: the time
     */
    void TimedEvents::addEvent(std::function<void()> func, float time)
    {
        _events.emplace_back(func, time + _time);
    }

    /*
     * runEvents
     * Run the events
     * @param deltaTime: the delta time
     */
    void TimedEvents::runEvents(float &deltaTime)
    {
        _time += deltaTime;
        for (auto &event : _events) {
            if (_time >= event.second) {
                event.first();
                _events.erase(_events.begin());
            }
        }
        for (auto &event : _reocurringEvents) {
            if (_time >= event.second.second) {
                event.first();
                event.second.second = _time + event.second.first;
            }
        }
    }

    /*
     * addReocurringEvent
     * Add a reocurring event
     * @param func: the function
     * @param time: the time
     */
    void TimedEvents::addReocurringEvent(std::function<void()> func, float time)
    {
        _reocurringEvents.emplace_back(func, std::make_pair(time, _time + time));
    }

} // server