#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

template <class T>
class MessageQueue
{
public:
    void send(T &&) ;
    T receive() ;

private:
    std::deque<T> _queue ;
    std::condition_variable _condition;
    std::mutex _mutex;
};

enum TrafficLightPhase {
    red ,
    green
};


class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight() ;
    TrafficLight(std::shared_ptr<Terminate>) ;
    ~TrafficLight(){
        std::unique_lock<std::mutex> lck(_mtx);
        std::cout << "traffic light destructor " << std::endl ;
    } ;

    // getters / setters

    // typical behaviour methods
    void waitForGreen() ;
    TrafficLightPhase getCurrentPhase() ;
    void simulate() ;

private:
    // typical behaviour methods
    void cycleThroughPhases() ;

    TrafficLightPhase _currentPhase ;

    MessageQueue<TrafficLightPhase> _messageQueue ;

    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif