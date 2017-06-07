#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <arm_neon.h>

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


    // Integer multiplication
    for(i=0; i<vectorSize; i++)
    {
        intVect1[i] = rand() % 100 + 1;
        intVect2[i] = rand() % 100 + 1;
        intVect3[i] = 0;
    }
    for(i=0; i<vectorSize; i+=4)
    {
        int32x4_t Vec1,Vec2,Vec3;
        Vec1 = vld1q_s32(intVect1 + i);
        Vec2 = vld1q_s32(intVect2 + i);
        Vec3 = vmulq_s32(Vec1,Vec2);
        vst1q_s32(intVect3 + i ,Vec3);
    }
    tStart = HiResTime();
    for(i=0; i<vectorSize; i+=4)
    {
        int32x4_t Vec1,Vec2,Vec3;
        Vec1 = vld1q_s32(intVect1 + i);
        Vec2 = vld1q_s32(intVect2 + i);
        Vec3 = vmulq_s32(Vec1,Vec2);
        vst1q_s32(intVect3 + i ,Vec3);
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
    for(i=0; i<vectorSize; i+=4)
    {
        int32x4_t Vec1,Vec3;
        float32x4_t Vecf1,Vecf2,Vecf3;

        Vec1 = vld1q_s32(intVect1 + i);
        Vecf1 = vcvtq_f32_s32(Vec1);

        Vecf2 = vrecpeq_f32(Vecf1);
        Vecf2 = vmulq_f32(vrecpsq_f32(Vecf1, Vecf2), Vecf2);
        Vecf2 = vmulq_f32(vrecpsq_f32(Vecf1, Vecf2), Vecf2);

        Vec1 = vld1q_s32(intVect1 + i);
        Vecf1 = vcvtq_f32_s32(Vec1);

        Vecf3 = vmulq_f32(Vecf1,Vecf2);

        Vec3 = vcvtq_s32_f32(Vecf3);
        vst1q_s32(intVect3 + i, Vec3);
    }
	tStart = HiResTime();
    for(i=0; i<vectorSize; i+=4)
    {
        int32x4_t Vec1,Vec3;
        float32x4_t Vecf1,Vecf2,Vecf3;

        Vec1 = vld1q_s32(intVect1 + i);
        Vecf1 = vcvtq_f32_s32(Vec1);

        Vecf2 = vrecpeq_f32(Vecf1);
        Vecf2 = vmulq_f32(vrecpsq_f32(Vecf1, Vecf2), Vecf2);
        Vecf2 = vmulq_f32(vrecpsq_f32(Vecf1, Vecf2), Vecf2);

        Vec1 = vld1q_s32(intVect1 + i);
        Vecf1 = vcvtq_f32_s32(Vec1);

        Vecf3 = vmulq_f32(Vecf1,Vecf2);

        Vec3 = vcvtq_s32_f32(Vecf3);
        vst1q_s32(intVect3 + i, Vec3);
    }
    tIntDiv = HiResTime() - tStart;
    for (i=0; i<vectorSize; i++)
    {
        fsum += floatVect3[i];
    }

    // Float multiplication
    for(i=0; i<vectorSize; i++)
    {
        floatVect1[i] = static_cast <float32_t> (rand()) / (static_cast <float32_t> (RAND_MAX/100)) + 1.0f; 
        floatVect2[i] = static_cast <float32_t> (rand()) / (static_cast <float32_t> (RAND_MAX/100)) + 1.0f;
        floatVect3[i] = 0;
    }
    for(i=0; i<vectorSize; i+=4)
    {
        float32x4_t Vec1,Vec2,Vec3;
        Vec1 = vld1q_f32(floatVect1 + i);
        Vec2 = vld1q_f32(floatVect2 + i);
        Vec3 = vmulq_f32(Vec1,Vec2);
        vst1q_f32(floatVect3 + i,Vec3);
    }
	tStart = HiResTime();
    for(i=0; i<vectorSize; i+=4)
    {
        float32x4_t Vec1,Vec2,Vec3;
        Vec1 = vld1q_f32(floatVect1 + i);
        Vec2 = vld1q_f32(floatVect2 + i);
        Vec3 = vmulq_f32(Vec1,Vec2);
        vst1q_f32(floatVect3 + i,Vec3);
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
        floatVect1[i] = static_cast <float32_t> (rand()) / (static_cast <float32_t> (RAND_MAX/100)) + 1.0f; 
        floatVect2[i] = static_cast <float32_t> (rand()) / (static_cast <float32_t> (RAND_MAX/100)) + 1.0f;
        floatVect3[i] = 0;
    }
    for(i=0; i<vectorSize; i+=4)
    {
        float32x4_t Vec1,Vec2,Vec3;

        Vec1 = vld1q_f32(floatVect2 + i);
        Vec2 = vrecpeq_f32(Vec1);
        Vec2 = vmulq_f32(vrecpsq_f32(Vec1, Vec2), Vec2);
        Vec2 = vmulq_f32(vrecpsq_f32(Vec1, Vec2), Vec2);

        Vec1 = vld1q_f32(floatVect1 + i);

        Vec3 = vmulq_f32(Vec1,Vec2);

        vst1q_f32(floatVect3 + i,Vec3);
    }
	tStart = HiResTime();
    for(i=0; i<vectorSize; i+=4)
    {
        float32x4_t Vec1,Vec2,Vec3;

        Vec1 = vld1q_f32(floatVect2 + i);
        Vec2 = vrecpeq_f32(Vec1);
        Vec2 = vmulq_f32(vrecpsq_f32(Vec1, Vec2), Vec2);
        Vec2 = vmulq_f32(vrecpsq_f32(Vec1, Vec2), Vec2);

        Vec1 = vld1q_f32(floatVect1 + i);

        Vec3 = vmulq_f32(Vec1,Vec2);

        vst1q_f32(floatVect3 + i,Vec3);
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

