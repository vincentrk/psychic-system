#include <iostream>
#include "Timer.h"
#include <math.h>


int main(int argc, char ** argv)
{
    Timer armIntMultTimer("ARM Integer Multiplicaiton");
    Timer armIntDivTimer("ARM Integer Division");
    Timer armFloatMultTimer("ARM Floating Point Multiplicaiton");
    Timer armFloatDivTimer("ARM Floating Point Division");

    

    int vectorSize = 65536;

    int intVect1[vectorSize];
    int intVect2[vectorSize];
    int intVect3[vectorSize];
    float floatVect1[vectorSize];
    float floatVect2[vectorSize];
    float floatVect3[vectorSize];

    int i;
    unsigned int isum;
    float fsum;
    for(i=0; i<vectorSize; i++)
    {
        intVect1[i] = rand() % 100 + 1;
        intVect2[i] = rand() % 100 + 1;
        floatVect1[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) + 1.0f; 
        floatVect2[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) + 1.0f;
    }

    armIntMultTimer.Start();
    for(i=0; i<vectorSize; i++)
    {
        intVect3[i] = intVect1[i] * intVect2[i];
    }
    armIntMultTimer.Pause();
    isum = 0;
    for(i=0; i<vectorSize; i++)
    {
        isum += intVect3[i];
    }
    std::cout << "Sum: " << isum << std::endl;

    armIntDivTimer.Start();
    for(i=0; i<vectorSize; i++)
    {
        intVect3[i] = intVect1[i] / intVect2[i];
    }
    armIntDivTimer.Pause();
    isum = 0;
    for(i=0; i<vectorSize; i++)
    {
        isum += intVect3[i];
    }
    std::cout << "Sum: " << isum << std::endl;

    armFloatMultTimer.Start();
    for(i=0; i<vectorSize; i++)
    {
        floatVect3[i] = floatVect1[i] * floatVect2[i];
    }
    armFloatMultTimer.Pause();
    fsum = 0.0f;
    for(i=0; i<vectorSize; i++)
    {
        fsum += floatVect3[i];
    }
    std::cout << "Sum: " << fsum << std::endl;

    armFloatDivTimer.Start();
    for(i=0; i<vectorSize; i++)
    {
        floatVect3[i] = floatVect1[i] / floatVect2[i];
    }
    armFloatDivTimer.Pause();
    fsum = 0.0f;
    for(i=0; i<vectorSize; i++)
    {
        fsum += floatVect3[i];
    }
    std::cout << "Sum: " << fsum << std::endl;


    armIntMultTimer.Print();
    armIntDivTimer.Print();
    armFloatMultTimer.Print();
    armFloatDivTimer.Print();

    return 0;
}

