#include<iostream>
#include "Terminate.h"

Terminate::Terminate () {
    kill = false ;
}

void Terminate::TerminateProcess () {
    std::unique_lock<std::mutex> lck(_mtx) ;
    kill = true ;
}

bool Terminate::isTerminated () {
    std::unique_lock<std::mutex> lck(_mtx) ;
    return kill == true ;
}