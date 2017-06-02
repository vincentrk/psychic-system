#include <iostream>
#include "Timer.h"
#include <math.h>
#include <arm_neon.h>

int main(int argc, char ** argv)
{
    Timer armIntMultTimer("ARM Integer Multiplicaiton");
    Timer armIntDivTimer("ARM Integer Division");
    Timer armFloatMultTimer("ARM Floating Point Multiplicaiton");
    Timer armFloatDivTimer("ARM Floating Point Division");

    

    int vectorSize = 65536;

    int* __restrict intVect1;
    int* __restrict intVect2;
    int* __restrict intVect3;
    intVect1 = (int *) malloc(vectorSize*sizeof(int));
    intVect2 = (int *) malloc(vectorSize*sizeof(int));
    intVect3 = (int *) malloc(vectorSize*sizeof(int));
    float32_t* __restrict floatVect1;
    float32_t* __restrict floatVect2;
    float32_t* __restrict floatVect3;
    floatVect1 = (float32_t *) malloc(vectorSize*sizeof(float32_t));
    floatVect2 = (float32_t *) malloc(vectorSize*sizeof(float32_t));
    floatVect3 = (float32_t *) malloc(vectorSize*sizeof(float32_t));

    int i;
    unsigned int isum;
    float fsum;
    for(i=0; i<vectorSize; i++)
    {
        intVect1[i] = rand() % 100 + 1;
        intVect2[i] = rand() % 100 + 1;
        floatVect1[i] = static_cast <float32_t> (rand()) / (static_cast <float32_t> (RAND_MAX/100)) + 1.0f; 
        floatVect2[i] = static_cast <float32_t> (rand()) / (static_cast <float32_t> (RAND_MAX/100)) + 1.0f;
    }

    armIntMultTimer.Start();
    for(i=0; i<vectorSize; i+=4)
    { 
        int32x4_t Vec1,Vec2,Vec3;
        Vec1 = vld1q_s32(intVect1 + i);
        Vec2 = vld1q_s32(intVect2 + i);

        Vec3 = vmulq_s32(Vec1,Vec2);

        vst1q_s32(intVect3 + i ,Vec3);


        // intVect3[i] = intVect1[i] * intVect2[i];
    }
    armIntMultTimer.Pause();
    isum = 0;
    for(i=0; i<vectorSize; i++)
    {
        isum += intVect3[i];
    }
    std::cout << "Sum int mult: " << isum << std::endl;

    // armIntDivTimer.Start();
    // for(i=0; i<vectorSize; i++)
    // {
    //     // int32x4 Vec1,Vec2,Vec3;
    //     // Vec1 = vld_s32(intVect1);
    //     // Vec2 = vld_s32(intVect2);

    //     // Vec3 = vmul_s32(Vec1,Vec2);

    //     // vst1q_s32(intVect3,Vec3);

    //     intVect3[i] = intVect1[i] / intVect2[i];
    // }
    // armIntDivTimer.Pause();
    // isum = 0;
    // for(i=0; i<vectorSize; i++)
    // {
    //     isum += intVect3[i];
    // }
    // std::cout << "Sum int div: " << isum << std::endl;

    armFloatMultTimer.Start();
    for(i=0; i<vectorSize; i+=4)
    {
        float32x4_t Vec1,Vec2,Vec3;

        Vec1 = vld1q_f32(floatVect1 + i);
        Vec2 = vld1q_f32(floatVect2 + i);

        Vec3 = vmulq_f32(Vec1,Vec2);

        vst1q_f32(floatVect3 + i,Vec3);

        // floatVect3[i] = floatVect1[i] * floatVect2[i];
    }
    armFloatMultTimer.Pause();
    fsum = 0.0f;
    for(i=0; i<vectorSize; i++)
    {
        fsum += floatVect3[i];
    }
    std::cout << "Sum float mult: " << fsum << std::endl;

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
    std::cout << "Sum float div: " << fsum << std::endl;


    armIntMultTimer.Print();
    armIntDivTimer.Print();
    armFloatMultTimer.Print();
    armFloatDivTimer.Print();

    return 0;
}

