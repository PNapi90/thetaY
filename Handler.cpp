#include "Handler.hpp"

//--------------------------------------------------------------

Handler::Handler(std::vector<int> &dRange,std::vector<int> &binSize,
                 unsigned int SEED,int _thrNum,double DX) 
                 : DATA(dRange) , SIM(SEED,DX) , thrNum(_thrNum)
{
    Min_Range = dRange[0];
    Max_Range = dRange[1];
    nBinsd01 = dRange[2];

    binSized12 = binSize[0];
    binSizeTheta = binSize[1];

    d12s = std::vector<double>(nBinsD12,0);
    thetas = std::vector<double>(nBinsTheta,0);

    std::cout << "Created Handler object for d0 range " << Min_Range << " " << Max_Range;
    std::cout << " -> thr # " << thrNum << std::endl;
}

//--------------------------------------------------------------

Handler::~Handler(){

}

//--------------------------------------------------------------

void Handler::Simulate(){
    //loop over d0 range

    std::vector<double> d0s(nBinsd01,0);

    double binDiff = (double)(Max_Range - Min_Range)/((double) nBinsd01);

    for(int i = 0;i < nBinsd01;++i){
        d0s[i] = (double) (i*binDiff + Min_Range); 
    }

    //binning of d12 and theta
    for(int i = 0;i < nBinsD12;++i){
        d12s[i] = (double)(i*d12MAX/((double) nBinsD12));
    }
    for(int i = 0;i < nBinsTheta;++i){
        thetas[i] = (double)(i*(THETA_MAX-THETA_MIN)/((double) nBinsTheta));
    }

    //temporary vector for data transport
    std::vector<double> TmpVec(3,0);

    //loop over d0s for simulation
    for(auto d0 : d0s){
        try{
            DATA.LOAD(d0);
        }
        catch(int err){
            exit(1);
        }

        for(auto d12 : d12s){
            try{
                DATA.OPEN(d12);
            }
            catch(int Err){
                std::string FileName = DATA.GetFileName();
                ErrorCodes::Print(Err, FileName, 0);
                exit(1);
            }
            for(auto theta : thetas){
                TmpVec[0] = d0;
                TmpVec[1] = d12;
                TmpVec[2] = theta;

                //simulate data for set d0,d12,theta
                SIM.DoTheThing(TmpVec);
                //Save Row in File
                SIM.SaveRow(DATA.GetDataStream());
            }

            if(thrNum == 0){
                std::cout << "\r";
                std::cout << "Distance d12 " << d12 << " in thread 0 done\t\t\t\t";
                std::cout.flush();
            }
            //close file again
            DATA.CLOSE();
        }
        if(thrNum == 0){
            std::cout << std::endl;
            std::cout << "Distance d0 " << d0 << " in thread 0 done" << std::endl;
        }
    }
}

//--------------------------------------------------------------

std::thread Handler::threading(){
    return std::thread([=]{Simulate();});
}

//--------------------------------------------------------------