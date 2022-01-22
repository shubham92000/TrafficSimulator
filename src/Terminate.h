#ifndef TERMINATE_H
#define TERMINATE_H

#include<mutex>

class Terminate {
public :
    Terminate() ;
    ~Terminate() {
        // std::unique_lock<std::mutex> lck(TrafficObject::_mtx);
        std::cout << "terminate destructor" << std::endl;
    };
    void TerminateProcess() ;
    bool isTerminated() ;

private :
    bool kill ;
    std::mutex _mtx_terminate ;
};

#endif