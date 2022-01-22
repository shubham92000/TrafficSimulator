#include<iostream>
#include "Terminate.h"

Terminate::Terminate () {
    kill = false ;
}

void Terminate::TerminateProcess () {
    std::unique_lock<std::mutex> lck(_mtx_terminate) ;
    kill = true ;
}

bool Terminate::isTerminated () {
    std::unique_lock<std::mutex> lck(_mtx_terminate) ;
    return kill == true ;
}