#ifndef TERMINATE_H
#define TERMINATE_H

#include<mutex>

class Terminate {
public :
    Terminate() ;
    ~Terminate() {
        std::cout << "terminate destructor" << std::endl;
    };
    void TerminateProcess() ;
    bool isTerminated() ;

private :
    bool kill ;
    std::mutex _mtx ;
};

#endif