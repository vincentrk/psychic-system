#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "Timer.h"
#include "HiResTimer.h"


int main(int argc, char ** argv)
{
	long tStart;
	long tIntMult, tIntDiv, tFloatMult, tFloatDiv;
	Timer_Init();

    int vectorSize = 65536;
    if (argc >= 2)
    {
        vectorSize = atoi(argv[1]);
    }

//    srand(time(NULL));

    int * __restrict intVect1 = (int *) malloc(vectorSize * sizeof(int));
    int * __restrict intVect2 = (int *) malloc(vectorSize * sizeof(int));
    int * __restrict intVect3 = (int *) malloc(vectorSize * sizeof(int));
    float * __restrict floatVect1 = (float *) malloc(vectorSize * sizeof(float));
    float * __restrict floatVect2 = (float *) malloc(vectorSize * sizeof(float));
    float * __restrict floatVect3 = (float *) malloc(vectorSize * sizeof(float));

    int i;
    unsigned int isum;
    float fsum;

    // Integer multiplication
    for(i=0; i<vectorSize; i++)
    {
        intVect1[i] = rand() % 100 + 1;
        intVect2[i] = rand() % 100 + 1;
        intVect3[i] = 0;
    }
    for (i=0; i<vectorSize; i++)
    {
        intVect3[i] = intVect1[i] * intVect2[i];
    }
    tStart = HiResTime();
    for (i=0; i<vectorSize; i++)
    {
        intVect3[i] = intVect1[i] * intVect2[i];
    }
    tIntMult = HiResTime() - tStart;
    isum = 0;
    for( i=0; i<vectorSize; i++)
    {
        isum += intVect3[i];
    }

    // Integer division
    for(i=0; i<vectorSize; i++)
    {
        intVect1[i] = rand() % 100 + 1;
        intVect2[i] = rand() % 100 + 1;
        intVect3[i] = 0;
    }
    for (i=0; i<vectorSize; i++)
    {
        intVect3[i] = intVect1[i] / intVect2[i];
    }
	tStart = HiResTime();
    for (i=0; i<vectorSize; i++)
    {
        intVect3[i] = intVect1[i] / intVect2[i];
    }
    tIntDiv = HiResTime() - tStart;
    for (i=0; i<vectorSize; i++)
    {
        isum += intVect3[i];
    }

    // Float multiplication
    for(i=0; i<vectorSize; i++)
    {
        floatVect1[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) + 1.0f; 
        floatVect2[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) + 1.0f;
        floatVect3[i] = 0;
    }
    for (i=0; i<vectorSize; i++)
    {
        floatVect3[i] = floatVect1[i] * floatVect2[i];
    }
	tStart = HiResTime();
    for (i=0; i<vectorSize; i++)
    {
        floatVect3[i] = floatVect1[i] * floatVect2[i];
    }
    tFloatMult = HiResTime() - tStart;
    fsum = 0.0f;
    for (i=0; i<vectorSize; i++)
    {
        fsum += floatVect3[i];
    }

    // Float division
    for(i=0; i<vectorSize; i++)
    {
        floatVect1[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) + 1.0f; 
        floatVect2[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) + 1.0f;
        floatVect3[i] = 0;
    }
    for (i=0; i<vectorSize; i++)
    {
        floatVect3[i] = floatVect1[i] / floatVect2[i];
    }
	tStart = HiResTime();
    for (i=0; i<vectorSize; i++)
    {
        floatVect3[i] = floatVect1[i] / floatVect2[i];
    }
    tFloatDiv = HiResTime() - tStart;
    for (i=0; i<vectorSize; i++)
    {
        fsum += floatVect3[i];
    }


    std::cerr << "Sum: " << isum << std::endl;
    std::cerr << "Sum: " << fsum << std::endl;

    // Clean up
    Timer_DeInit();
    free(intVect1);
    free(intVect2);
    free(intVect3);
    free(floatVect1);
    free(floatVect2);
    free(floatVect3);

    std::cout << vectorSize
            << "," << tIntMult
            << "," << tIntDiv
            << "," << tFloatMult
            << "," << tFloatDiv
            << "\n";

    return 0;
}

