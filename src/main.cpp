#include "UTaste.hpp"

int main(int argc, char* argv[]) 
{
    UTaste utaste;
    utaste.GetDataFromDistrictsFile(argv[2]);
    utaste.GetDataFromResturantsFile(argv[1]);
    utaste.IoHandler();
}