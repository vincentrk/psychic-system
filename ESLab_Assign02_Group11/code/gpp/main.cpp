#include <iostream>

#include "meanshift.h"
#include "pool_notify.h"
#include "HiResTimer.h"
#include "Timer.h"


#ifndef ARMCC
#include "markers.h"
#endif

#define pool_notify_IPS_ID                0
#define pool_notify_IPS_EVENTNO           5

int main(int argc, char ** argv)
{
    cv::VideoCapture frame_capture;
    if(argc<2)
    {
        std::cout <<"specifiy dsp file" << std::endl;
        std::cout <<"Usage:  " << argv[0] << " meanshift.dsp" << std::endl;
        return -1;
    }
    int vectorSize = 65536;
    if (argc >= 3)
    {
        vectorSize = atoi(argv[2]);
    }

#ifdef USE_DSP
    // Set up DSP
    Char8 * dspExecutable = argv[1];
    Char8 * strBufferSize = "128";
    if (!pool_notify_Main(dspExecutable, strBufferSize)) {
        std::cout << "Error setting up DSP" << std::endl;
        return -1;
    }
#endif

    Timer intmult("int mult");
    Timer floatmult("float mult");
    Timer intdiv("int div");
    Timer floatdiv("float div");

    long tStart;
    long tIntMult, tIntDiv, tFloatMult, tFloatDiv;
	Timer_Init();

    int * buf = pool_notify_GetBuf();
    buf[0] = vectorSize;
    pool_notify_Execute();
    pool_notify_Result();

    pool_notify_Result();
    tStart = HiResTime();
//    intmult.Start();
    pool_notify_Result();
    tIntMult = HiResTime() - tStart;
    intmult.Stop();

    pool_notify_Result();
    tStart = HiResTime();
//    intdiv.Start();
    pool_notify_Result();
    tIntDiv = HiResTime() - tStart;
    intdiv.Stop();

    pool_notify_Result();
    tStart = HiResTime();
//    floatmult.Start();
    pool_notify_Result();
    tFloatMult = HiResTime() - tStart;
    floatmult.Stop();

    pool_notify_Result();
    tStart = HiResTime();
//    floatdiv.Start();
    pool_notify_Result();
    tFloatDiv = HiResTime() - tStart;
    floatdiv.Stop();


    Timer_DeInit();

/*    std::cout.precision(3);
    std::cout << std::scientific;
    std::cout << buf[1]
            << "," << intmult.GetTime()
            << "," << intdiv.GetTime()
            << "," << floatmult.GetTime()
            << "," << floatdiv.GetTime()
            << "\n";*/
    std::cout << buf[1]
            << "," << tIntMult
            << "," << tIntDiv
            << "," << tFloatMult
            << "," << tFloatDiv
            << "\n";

#ifdef USE_DSP
    // Stop DSP
    Uint8 processorId = 0;
    pool_notify_Delete (processorId);
#endif

    return 0;
}

