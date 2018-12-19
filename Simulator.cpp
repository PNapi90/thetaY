#include "Simulator.hpp"

//--------------------------------------------------------------

Simulator::Simulator(unsigned int SEED,double DX) : generator(SEED) , deltaX(DX/2.355){
    x0 = std::vector<double>(3,0);
    x1 = std::vector<double>(3,0);
    x2 = std::vector<double>(3,0);

    mu0 = std::vector<double>(3,0);
    mu1 = std::vector<double>(3,0);
    mu2 = std::vector<double>(3,0);

    binsArr = std::vector<double>(nBins,0);
    Histogram = std::vector<double>(nBins,0);

    for(int i = 0;i < nBins;++i){
        binsArr[i] = -1. + i*2./((double) nBins);
    }

    cthArray = std::vector<double>(MAX_SIM,0);

    GaussX = std::normal_distribution<double>(0,deltaX);
}

Simulator::~Simulator(){}

//--------------------------------------------------------------

void Simulator::DoTheThing(std::vector<double> &values){

    d01 = values[0];
    d12 = values[1];
    theta = values[2];

    //set vectors x1 and x2 (x0 = 0)
    //x1
    x1[0] = d01;

    //x2
    x2[0] = d01 + d12*cos(theta);
    x2[1] = d12*sin(theta);

    double norm1 = 0;
    double norm2 = 0;
    double scalar = 0;

    int SimIter = 0;
    while(SimIter < MAX_SIM){

        norm1 = 0;
        norm2 = 0;
        scalar = 0;

        for(int i = 0;i < 3;++i){
            mu0[i] = x0[i] + GaussX(generator);
            mu1[i] = x1[i] + GaussX(generator);
            mu2[i] = x2[i] + GaussX(generator);

            norm1 += pow(mu0[i] - mu1[i],2);
            norm2 += pow(mu1[i] - mu2[i],2);
            scalar += (mu1[i] - mu0[i])*(mu2[i] - mu1[i]);
        }

        cthArray[SimIter] = scalar/std::sqrt(norm1*norm2);

        ++SimIter;
    }
    CreateHistogram();
}

//--------------------------------------------------------------

void Simulator::SaveRow(std::ofstream *data){
    for(int i = 0;i < nBins;++i) (*data) << Histogram[i] << " ";
    (*data) << std::endl;
}

//--------------------------------------------------------------

void Simulator::CreateHistogram(){
    double norm = 0;

    //reset histogram
    for(int i = 0;i < Histogram.size();++i) Histogram[i] = 0.;
    
    //fill histogram
    for(auto cth : cthArray){
        for(int i = 0;i < binsArr.size()-1;++i){
            if(cth >= binsArr[i] && cth < binsArr[i+1]){
                Histogram[i] += 1;
                norm += 1.;
                break;
            }
        }
    }
    
    double binWidth = 2./((double) nBins);

    //normalize histogram
    for(int i = 0;i < Histogram.size();++i) Histogram[i] /= norm*binWidth;

}

//--------------------------------------------------------------
