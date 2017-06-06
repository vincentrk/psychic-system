#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "Timer.h"
#include "HiResTimer.h"


int main(int argc, char ** argv)
{
    Timer armIntMultTimer("ARM Integer Multiplicaiton");
    Timer armIntDivTimer("ARM Integer Division");
    Timer armFloatMultTimer("ARM Floating Point Multiplicaiton");
    Timer armFloatDivTimer("ARM Floating Point Division");

	long tStart, tEnd;
	long tIntMult, tIntDiv, tFloatMult, tFloatDiv;
	Timer_Init();

    int vectorSize = 65536;
    bool csv = false;
    if (argc >= 2)
    {
        vectorSize = atoi(argv[1]);
        csv = true;
    }

    int * intVect1 = (int *) malloc(vectorSize * sizeof(int));
    int * intVect2 = (int *) malloc(vectorSize * sizeof(int));
    int * intVect3 = (int *) malloc(vectorSize * sizeof(int));
    float * floatVect1 = (float *) malloc(vectorSize * sizeof(float));
    float * floatVect2 = (float *) malloc(vectorSize * sizeof(float));
    float * floatVect3 = (float *) malloc(vectorSize * sizeof(float));

    int i, n;
    unsigned int isum;
    float fsum;
    for(i=0; i<vectorSize; i++)
    {
        intVect1[i] = rand() % 100 + 1;
        intVect2[i] = rand() % 100 + 1;
        floatVect1[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) + 1.0f; 
        floatVect2[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) + 1.0f;
    }

    // Integer multiplication
    armIntMultTimer.Start();
    tStart = HiResTime();
    for (i=0; i<vectorSize; i++)
    {
        intVect3[i] = intVect1[i] * intVect2[i];
    }
    tIntMult = HiResTime() - tStart;
    armIntMultTimer.Pause();
    isum = 0;
    for( i=0; i<vectorSize; i++)
    {
        isum += intVect3[i];
    }
    std::cerr << "Sum: " << isum << std::endl;

    // Integer division
    armIntDivTimer.Start();
	tStart = HiResTime();
    for (i=0; i<vectorSize; i++)
    {
        intVect3[i] = intVect1[i] / intVect2[i];
    }
    tIntDiv = HiResTime() - tStart;
    armIntDivTimer.Pause();
    isum = 0;
    for (i=0; i<vectorSize; i++)
    {
        isum += intVect3[i];
    }
    std::cerr << "Sum: " << isum << std::endl;

    // Float multiplication
    armFloatMultTimer.Start();
	tStart = HiResTime();
    for (i=0; i<vectorSize; i++)
    {
        floatVect3[i] = floatVect1[i] * floatVect2[i];
    }
    tFloatMult = HiResTime() - tStart;
    armFloatMultTimer.Pause();
    fsum = 0.0f;
    for (i=0; i<vectorSize; i++)
    {
        fsum += floatVect3[i];
    }
    std::cerr << "Sum: " << fsum << std::endl;

    // Float division
    armFloatDivTimer.Start();
	tStart = HiResTime();
    for (i=0; i<vectorSize; i++)
    {
        floatVect3[i] = floatVect1[i] / floatVect2[i];
    }
    tFloatDiv = HiResTime() - tStart;
    armFloatDivTimer.Pause();
    fsum = 0.0f;
    for (i=0; i<vectorSize; i++)
    {
        fsum += floatVect3[i];
    }
    std::cerr << "Sum: " << fsum << std::endl;

    // Clean up
    Timer_DeInit();
    free(intVect1);
    free(intVect2);
    free(intVect3);
    free(floatVect1);
    free(floatVect2);
    free(floatVect3);

    if (csv)
    {
        std::cout.precision(3);
        std::cout << std::scientific;
        std::cout << vectorSize
/*            << "," << armIntMultTimer.GetTime()
            << "," << armIntDivTimer.GetTime()
            << "," << armFloatMultTimer.GetTime()
            << "," << armFloatDivTimer.GetTime() */
            << "," << tIntMult
            << "," << tIntDiv
            << "," << tFloatMult
            << "," << tFloatDiv
            << "\n";
    }
    else
    {
        armIntMultTimer.Print();
        armIntDivTimer.Print();
        armFloatMultTimer.Print();
        armFloatDivTimer.Print();
    }

    return 0;
}

