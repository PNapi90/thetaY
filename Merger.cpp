#include "Merger.hpp"

//---------------------------------------

Merger::Merger(std::vector<int> &Range,
               std::string Folder,
               int _sigX) 
    : Start(Range[0]) ,
      End(Range[1]) ,
      FOLDER(Folder) ,
      sigX(_sigX)
{
    DataBlock = std::vector<std::vector<double> >(181,std::vector<double>(101,0));
    Norm = std::vector<double>(181,0);
}

//---------------------------------------

Merger::~Merger()
{}

//---------------------------------------

void Merger::LOAD(int iterator)
{
    std::ifstream DATA;
    std::string fileName,line;

    int fileIter = 0;
    double Value = 0;

    std::vector<std::vector<double>> Values(181,std::vector<double>(101,0));

    for(int i = Start;i < End;++i)
    {
        fileName = "d0_Raw/d0s_"+std::to_string(sigX) +"/d0_"+FOLDER + "/d12_" + std::to_string(i);
        
        DATA.open(fileName,std::ios::in | std::ios::binary);
        
        if(DATA.fail())
            FATAL_Exit(fileName);

        fileIter = 0;

        for(auto VBlock : Values)
        {
            DATA.read(reinterpret_cast<char *>(&VBlock[0]), 
                      VBlock.size() * sizeof(VBlock[0]));
        }

        for(int j = 0;j < Values.size();++j)
        {
            for(int k = 0;k < Values[0].size();++k)
            {
                DataBlock[j][k] += Values[j][k];
                Norm[j] += Values[j][k];
            }
        }

        
        /*
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
        */
        DATA.close();
        DATA.clear();
    }

    for(int i = 0;i < 181;++i){
        for(int j = 0;j < 101;++j) DataBlock[i][j] /= Norm[i];
    }

    SaveBlock(iterator);
}

//---------------------------------------

void Merger::FATAL_Exit(std::string fileName)
{
    std::cerr << "Could not find " << fileName << std::endl;
    exit(1);
}

//---------------------------------------

void Merger::SaveBlock(int iterator)
{
    std::string name = "d0_tmp/d0_"+FOLDER + "/d12_" + std::to_string(Start);
    std::ofstream SAVER(name,std::ios::out | std::ios::binary);

    for(auto DBlock : DataBlock)
    {
        SAVER.write(reinterpret_cast<char*>(&DBlock[0]),
                    DBlock.size() * sizeof(DBlock[0]));
        //for(auto x : DBlock) SAVER << x << " ";
        //SAVER << std::endl;
    }

    SAVER.close();

    //if(iterator % 100 == 0) std::cout << name << " done" << std::endl;
}

//---------------------------------------
