#include "DataParser.hpp"

//--------------------------------------------------------------

DataParser::DataParser(std::vector<int> &dRange) : x0(dRange[0]), x1(dRange[1])
{
    
    exString = "[" + std::to_string(x0) + "," + std::to_string(x1) + "]";
    firstFile = true;
}

//--------------------------------------------------------------

DataParser::~DataParser(){

}

//--------------------------------------------------------------

std::string DataParser::GetFileName(){
    return Filename;
}

//--------------------------------------------------------------

std::ofstream* DataParser::GetDataStream(){
    return &File;
}

//--------------------------------------------------------------

void DataParser::OPEN(double d12){

    Filename = Filename_Folder + "d12_" + std::to_string((int) d12);
    File.open(Filename);

    if (File.fail())
    {
        throw ErrorCodes::FileNotFound;
        return;
    }
}

//--------------------------------------------------------------

void DataParser::LOAD(double d0Current){
    if (d0Current < x0 || d0Current > x1){
        ErrorCodes::Print(ErrorCodes::d0RangeExc, exString, d0Current);
        throw ErrorCodes::d0RangeExc;
        return;
    }

    Filename_Folder = "d0s_2s/d0_" + std::to_string(((int) d0Current)) + "/";
} 

//--------------------------------------------------------------

void DataParser::CLOSE(){
    File.close();
    File.clear();
}

//--------------------------------------------------------------
