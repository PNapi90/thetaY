#include <vector>
#include <memory>
#include <string>
#include <iostream>


#include "Merger.hpp"


int main(int argc,char** argv)
{

    int d0 = 0;
    bool d0Flag = false;

    int sigX = 5;
    bool sigXFlag = false;

    for(int i = 0;i < argc;++i){
        if(std::string(argv[i]) == "-d"){
            d0Flag = true;
            continue;
        }
        if(d0Flag){
            d0 = std::stoi(std::string(argv[i]));
            d0Flag = false;
            continue;
        }
        if (std::string(argv[i]) == "-s")
        {
            sigXFlag = true;
            continue;
        }
        if (sigXFlag)
        {
            sigX = std::stoi(std::string(argv[i]));
            sigXFlag = false;
            continue;
        }
    }

    std::cout << "Merging groups of 4 d12s in folder d0_" << d0 << std::endl; 
    
    std::string d0_String = std::to_string(d0);

    int d0Range = 600;
    int d12Range = 600;

    int d12_Merge = 4;
    int iter = 0;

    std::vector<int> Range(2,0);
    std::vector<std::shared_ptr<Merger> > Q;
    
    Q.reserve(d12Range/d12_Merge);

    while(iter < d12Range)
    {
        Range[0] = iter;
        Range[1] = iter + d12_Merge;

        Q.push_back(std::make_shared<Merger>(Range,d0_String,sigX));

        iter += d12_Merge;
    }

    for(int i = 0;i < Q.size();++i) Q[i]->LOAD();
    

    std::cout << "d0_" << d0 << " done" << std::endl;

    return 0;

}