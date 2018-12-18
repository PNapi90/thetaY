#include <iostream>
#include <string>

#include "Threader.hpp"

void PrintFlags(int nThr,double Sigma);

void GetFlags(int argc, char **argv, double &Sigma, int &nThr);

int main(int argc,char** argv){

    int nThr = 1;
    double Sigma = 5;

    GetFlags(argc,argv,Sigma,nThr);
    PrintFlags(nThr,Sigma);

    Threader TT(nThr);
    TT.RunSimulation(Sigma);



    return 0;
}


void GetFlags(int argc,char** argv,double &Sigma,int &nThr){

    std::string Flag;
    bool threadFlag = false,SigFlag = false;

    for(int i = 0;i < argc;++i){
        Flag = std::string(argv[i]);

        if(Flag == "-t"){
            threadFlag = true;
            continue;
        }
        if(threadFlag){
            nThr = std::stoi(Flag);
            threadFlag = false;
            continue;
        }

        if(Flag == "-s"){
            SigFlag = true;
            continue;
        }
        if(SigFlag){
            Sigma = std::stod(Flag);
            SigFlag = false;
            continue;
        }
    }
}

void PrintFlags(int nThr, double Sigma){

    std::string threadS = (nThr > 1) ? "threads" : "thread";

    std::cout << "\n==========================================================="<< std::endl;
    std::cout << "Welcome to thetaY, a cos(\u03D1) uncertainty MC sampler" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "Using " << nThr << " " << threadS << std::endl;
    std::cout << "Position resolution: " << Sigma << " mm" << std::endl;
    std::cout << "===========================================================" << std::endl;
}