#include <vector>
#include <memory>
#include <string>
#include <iostream>


#include "D0_Merger.hpp"


int main(int argc,char** argv)
{

    int d12 = 0;
    bool d12Flag = false;
    bool sigXFlag = false;
    int sigX = 5;


    for(int i = 0;i < argc;++i){
        if(std::string(argv[i]) == "-d"){
            d12Flag = true;
            continue;
        }
        if(d12Flag){
            d12 = std::stoi(std::string(argv[i]));
            d12Flag = false;
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

    std::cout << "Merging groups of 4 d0s in for d12_" << d12 << std::endl; 
    
    std::string d12_String = std::to_string(d12);

    int d0Range = 600;
    int d12Range = 600;

    int d0_Merge = 4;
    int iter = 0;

    std::vector<int> Range(2,0);
    std::vector<std::shared_ptr<D0_Merger> > Q;
    
    Q.reserve(d0Range/d0_Merge);
    while(iter < d0Range)
    {
        Range[0] = iter;
        Range[1] = iter + d0_Merge;

        Q.push_back(std::make_shared<D0_Merger>(Range,d12_String,sigX));

        iter += d0_Merge;
    }

    for(int i = 0;i < Q.size();++i) Q[i]->LOAD();
    

    std::cout << "d12_" << d12 << " done" << std::endl;

    return 0;

}