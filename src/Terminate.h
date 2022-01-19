#ifndef TERMINATE_H
#define TERMINATE_H

#include<mutex>

class Terminate {
public :
    Terminate() ;
    void TerminateProcess() ;
    bool isTerminated() ;

private :
    bool kill ;
    std::mutex _mtx ;
};

#endif