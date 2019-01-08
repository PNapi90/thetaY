#include "D0_Merger.hpp"

//-------------------------------

D0_Merger::D0_Merger(std::vector<int> &Range,std::string _d12) : Start(Range[0]) , End(Range[1]) , d12(_d12)
{
    DataBlock = std::vector<std::vector<double> >(181,std::vector<double>(100,0));
    Norm = std::vector<double>(181,0);
}

//-------------------------------

D0_Merger::~D0_Merger()
{}

//-------------------------------


void D0_Merger::LOAD()
{
    std::ifstream DATA;
    std::string fileName,line;

    int fileIter = 0;
    double Value = 0;

    for(int i = Start;i < End;++i)
    {
        fileName = "d0s/d0_tmp/d0_"+std::to_string(i) + "/d12_" + d12;
        
        DATA.open(fileName);
        if(DATA.fail()) FATAL_Exit(fileName);

        fileIter = 0;

        while(std::getline(DATA,line))
        {
            std::istringstream Buffer(line);
            std::vector<std::string> Words(std::istream_iterator<std::string>{Buffer},
                                           std::istream_iterator<std::string>());
            for(int k = 0;k < Words.size();++k)
            {
                Value = std::stod(Words[k]);
                DataBlock[fileIter][k] += Value;
                Norm[fileIter] += Value;
            }
            ++fileIter;
        }
        DATA.close();
        DATA.clear();
    }

    for(int i = 0;i < 181;++i){
        for(int j = 0;j < 101;++j) DataBlock[i][j] /= Norm[i];
    }

    SaveBlock();
}

//---------------------------------------

void D0_Merger::FATAL_Exit(std::string fileName)
{
    std::cerr << "Could not find " << fileName << std::endl;
    exit(1);
}

//---------------------------------------

void D0_Merger::SaveBlock()
{
    std::string name = "d0s_4/d0_"+ std::to_string(Start) + "/d12_" + d12;
    std::ofstream SAVER(name);

    for(int i = 0;i < 181;++i)
    {
        for(auto x : DataBlock[i]) SAVER << x << " ";
        SAVER << std::endl;
    }

    SAVER.close();

    std::cout << name << " done" << std::endl;
}

//---------------------------------------
