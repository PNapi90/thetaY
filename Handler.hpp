#ifndef HANDLER_H
#define HANDLER_H

#include <vector>
#include <thread>
#include <cstdlib>

#include "ErrorCodes.hpp"
#include "DataParser.hpp"
#include "Simulator.hpp"



class Handler{

private:

    const int nBinsD12 = 300;
    const int nBinsTheta = 90;

    const double d12MAX = 600;
    const double THETA_MAX = 180;
    const double THETA_MIN = 0;

    int Min_Range, Max_Range, nBinsd01;
    int binSized12, binSizeTheta;

    int thrNum;

    std::vector<double> d12s,thetas;

    DataParser DATA;
    Simulator SIM;

    void Simulate();


public:
    Handler(std::vector<int> &dRange,
            std::vector<int> &binSize,
            unsigned int SEED,int _thrNum,
            double DX);
    ~Handler();

    std::thread threading();


};



#endif