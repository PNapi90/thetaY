#include "Threader.hpp"

//--------------------------------------------------------------

Threader::Threader(int _nThr) : nThr(_nThr) {
    
    //reduce amount of threads to even number
    if(nThr > 1 && nThr % 2) --nThr;

    ThreadObjects.reserve(nThr);
}

//--------------------------------------------------------------

Threader::~Threader(){

}

//--------------------------------------------------------------

void Threader::RunSimulation(double deltaX){

    //d0 range
    std::vector<int> dRange(3,0);
    std::vector<int> binSize(2,0);

    int delim = 600/nThr;
    delim = 1;

    for(int i = 0;i < nThr;++i){
        dRange[0] = 200;//dRange[1];
        dRange[1] = 201;//dRange[0] + delim;
        dRange[2] = delim;
        ThreadObjects.push_back(std::make_shared<Handler>(dRange,binSize,
                                                          (unsigned int) i ,
                                                          i,deltaX));
    }
    std::thread t[nThr];
    for(int i = 0;i < nThr;++i) t[i] = ThreadObjects[i]->threading();
    for (int i = 0; i < nThr; ++i) t[i].join();
    
}

//--------------------------------------------------------------