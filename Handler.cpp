#include "Handler.hpp"

//--------------------------------------------------------------

Handler::Handler(std::vector<int> &dRange) : DATA(dRange){
    Min_Range = dRange[0];
    Max_Range = dRange[1];
}

//--------------------------------------------------------------

Handler::~Handler(){

}

//--------------------------------------------------------------

void Handler::Simulate(){

}

//--------------------------------------------------------------

std::thread Handler::threading(){
    return std::thread([=]{Simulate();});
}

//--------------------------------------------------------------