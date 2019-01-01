#ifndef D0_MERGER_H
#define D0_MERGER_H

#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iterator>

class D0_Merger
{

private:
    
    int Start,End;

    std::string d12;

    std::vector<std::vector<double> > DataBlock;
    std::vector<double> Norm;

    void SaveBlock();
    
    void FATAL_Exit(std::string fileName);


public:
    D0_Merger(std::vector<int> &Range,std::string _d12);
    ~D0_Merger();

    void LOAD();

};

#endif