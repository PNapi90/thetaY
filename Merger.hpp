#ifndef MERGER_H
#define MERGER_H

#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iterator>

class Merger
{

private:

    int Start,End,sigX;

    std::string FOLDER;

    std::vector<std::vector<double> > DataBlock;
    std::vector<double> Norm;

    void SaveBlock();
    
    void FATAL_Exit(std::string fileName);


public:
    Merger(std::vector<int> &Range,
           std::string Folder,
           int _sigX);
    ~Merger();

    void LOAD();



};



#endif