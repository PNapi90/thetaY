#include "D0_Merger.hpp"

//-------------------------------

D0_Merger::D0_Merger(std::vector<int> &Range, std::string _d12, int _s) : Start(Range[0]), End(Range[1]), d12(_d12), sigmaX_s(std::to_string(_s))
{
    DataBlock = std::vector<std::vector<double> >(181,std::vector<double>(101,0));
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

    std::vector<std::vector<double>> Values(181, std::vector<double>(101, 0));

    for(int i = Start;i < End;++i)
    {
        fileName = "d0_tmp/d0_"+std::to_string(i) + "/d12_" + d12;

        DATA.open(fileName);//, std::ios::in | std::ios::binary);

        if (DATA.fail())
            FATAL_Exit(fileName);

        /*
        for (auto VBlock : Values)
        {
            DATA.read(reinterpret_cast<char *>(&VBlock[0]),
                      VBlock.size() * sizeof(VBlock[0]));
        }

        for (int j = 0; j < Values.size(); ++j)
        {
            for (int k = 0; k < Values[0].size(); ++k)
            {
                DataBlock[j][k] += Values[j][k];
                Norm[j] += Values[j][k];
            }
        }
        */

        
        
        
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
    std::string name = "d0_Folder/d0s_" + sigmaX_s +"_4/d0_"+ std::to_string(Start) + "/d12_" + d12;
    std::ofstream SAVER(name);//,std::ios::out | std::ios::binary);

    if(SAVER.fail())
    {
        std::cerr << "Could not open " << name << std::endl;
        exit(1);
    }

    for(auto DBlock : DataBlock)
    {
        
        //SAVER.write(reinterpret_cast<char *>(&DBlock[0]),
        //            DBlock.size() * sizeof(DBlock[0]));
        for(auto x : DBlock) SAVER << x << " ";
        SAVER << std::endl;
    }

    SAVER.close();

    std::cout << name << " done" << std::endl;
}

//---------------------------------------
