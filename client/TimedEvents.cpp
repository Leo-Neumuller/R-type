/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** TimedEvent.cpp
*/

#include "TimedEvents.hpp"

namespace client {

    TimedEvents::TimedEvents() : _time(0), _events(), _reocurringEvents()
    {
    }

    TimedEvents::~TimedEvents()
    {
    }

    void TimedEvents::addEvent(std::function<void()> func, float time)
    {
        _events.emplace_back(func, time + _time);
    }

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

    void TimedEvents::addReocurringEvent(std::function<void()> func, float time)
    {
        _reocurringEvents.emplace_back(func, std::make_pair(time, _time + time));
    }

} // server