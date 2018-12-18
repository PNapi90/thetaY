#ifndef THREADER_H
#define THREADER_H

#include <thread>
#include <vector>
#include <memory>

#include "Handler.hpp"


class Threader{

    int nThr;

    std::vector<std::shared_ptr<Handler> > ThreadObjects; 

public:
    Threader(int _nThr);
    ~Threader();

    void RunSimulation(double deltaX);

};



#endif