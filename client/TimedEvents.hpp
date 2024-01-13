/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** TimedEvent.hpp
*/

#ifndef R_TYPE_SERVER_TIMEDEVENTS_HPP
#define R_TYPE_SERVER_TIMEDEVENTS_HPP

#include <iostream>
#include <functional>
#include <chrono>

namespace client {

    /*
     * TimedEvents
     * Class of the timed events
     */
    class TimedEvents {
        public:
            TimedEvents();
            ~TimedEvents();

            void addEvent(std::function<void()> func, float time);
            void addReocurringEvent(std::function<void()> func, float time);

            void runEvents(float &deltaTime);
        protected:

        private:
            std::vector<std::pair<std::function<void()>, float>> _events;
            std::vector<std::pair<std::function<void()>, std::pair<float, float>>> _reocurringEvents;
            float _time;



    };

} // server

#endif //R_TYPE_SERVER_TIMEDEVENTS_HPP
