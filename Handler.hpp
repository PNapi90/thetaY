#ifndef HANDLER_H
#define HANDLER_H

#include <vector>
#include <thread>

#include "DataParser.hpp"

class Handler{

private:

    double Min_Range,Max_Range;

    DataParser DATA;

    void Simulate();


public:
    Handler(std::vector<int> &dRange);
    ~Handler();

    std::thread threading(){


};



#endif