#include <iostream>
#include "header.h"

using namespace std;

int main(int argc, char* argv[])
{

    /*------Validating argument count--------------------------*/

    if(argc != 4){
        Error("Please provide 4 valid arguments.");
    }


    loadMechanics(argv[2]);

    claimEvaluation(argv[1], argv[3]);


    return 0;
}
