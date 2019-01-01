#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <random>
#include <iostream>
#include <vector>
#include <fstream>


class Simulator{

private:

    const int MAX_SIM = 100000;
    const int nBins = 101;

    double deltaX;

    std::vector<double> x0,x1,x2;
    std::vector<double> mu0,mu1,mu2;
    std::vector<double> cthArray;
    std::vector<double> binsArr,Histogram;
    

    std::normal_distribution<double> GaussX;
    std::default_random_engine generator;


    double d01,d12,theta;

    void CreateHistogram();   


public:
    Simulator(unsigned int SEED,double DX);
    ~Simulator();

    void DoTheThing(std::vector<double> &Values);

    void SaveRow(std::ofstream *data);
};


#endif