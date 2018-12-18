#ifndef ERRORCODES_H
#define ERRORCODES_H


#include <iostream>

namespace ErrorCodes{
    static const int FileNotFound = 1337;
    static const int d0RangeExc = 999;

    static void Print(int ErrC, std::string &str, double d0)
    {
        switch (ErrC)
        {
            case FileNotFound:
                std::cerr << "--------------------------------\n";
                std::cerr << "File " << str << " not found!" << std::endl;
                std::cerr << "--------------------------------" << std::endl;
                break;

            case d0RangeExc:
                std::cerr << "--------------------------------\n";
                std::cerr << "d0 " << d0 << " not in range ";
                std::cerr << str << " !" << std::endl;
                std::cerr << "--------------------------------" << std::endl;
                break;
            default:
                std::cerr << "Error Code " << ErrC << " not known" << std::endl;
        }
    }
};

#endif