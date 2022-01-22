#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::receive()
{
    std::unique_lock<std::mutex> lck(_mutex) ;
    _condition.wait(lck , [this](){ return !_queue.empty() ;} ) ;

    T msg = std::move(_queue.back()) ;
    _queue.pop_back() ;
    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    
    std::lock_guard<std::mutex> lck(_mutex);
    _queue.emplace_back(std::move(msg)) ;
    _condition.notify_one() ;

}

/* Implementation of class "TrafficLight" */

 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
    this->terminate = nullptr ;
}


TrafficLight::TrafficLight(std::shared_ptr<Terminate> terminate)
{
    _currentPhase = TrafficLightPhase::red;
    this->terminate = terminate ;
}

void TrafficLight::waitForGreen()
{
    while(1){
        TrafficLightPhase tlp = _messageQueue.receive() ;
        if(tlp == TrafficLightPhase::green){
            return ;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{   
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases,this)) ;
}

void TrafficLight::cycleThroughPhases()
{

    std::unique_lock<std::mutex> lck(_mtx);
    std::cout << "TrafficLight #" << _id << "::simulate: thread id = " << std::this_thread::get_id() << std::endl;
    lck.unlock();
    
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;  

    lastUpdate = std::chrono::system_clock::now();
    auto val = rand() % 2 + 4 ;

    while(1){

        std::this_thread::sleep_for(std::chrono::milliseconds(1)) ;

        if(terminate->isTerminated()){
            return ;
        }

        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - lastUpdate).count();
        // todo change to float last update
        

        if(timeSinceLastUpdate > val){
            if(_currentPhase == TrafficLightPhase::green){
                _currentPhase = TrafficLightPhase::red ;
            }else {
                _currentPhase = TrafficLightPhase::green;
            }
            _messageQueue.send(std::move(_currentPhase));
            lastUpdate = std::chrono::system_clock::now();
            val = rand() % 2 + 4 ;
        }

    }
}
