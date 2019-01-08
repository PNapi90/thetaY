#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "ErrorCodes.hpp"

class DataParser{

  private:

    int x0,x1,sigX;

    bool firstFile;
   

    std::ofstream File;

    std::string Filename,Filename_Folder;
    std::string exString;

  public:
    DataParser(std::vector<int> &dRange,int _sigX);
    ~DataParser();

    void OpenFile();
    std::string GetFileName();
    std::ofstream* GetDataStream();

    void OPEN(double d12);
    void CLOSE();
    void LOAD(double d0Current);
};

#endif