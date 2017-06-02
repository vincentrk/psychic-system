#include "meanshift.h"
#include "Timer.h"
#include "pool_notify.h"
#include <iostream>

#ifndef ARMCC
#include "markers.h"
#endif

#define pool_notify_IPS_ID                0
#define pool_notify_IPS_EVENTNO           5

int main(int argc, char ** argv)
{
    Timer intmult("int mult");
    Timer floatmult("float mult");
    Timer intdiv("int div");
    Timer floatdiv("float div");

    cv::VideoCapture frame_capture;
    if(argc<2)
    {
        std::cout <<"specifiy dsp file" << std::endl;
        std::cout <<"Usage:  " << argv[0] << " meanshift.dsp" << std::endl;
        return -1;
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

pool_notify_Execute();

pool_notify_Result();
intmult.Start();

pool_notify_Result();
intmult.Stop();
floatmult.Start();

pool_notify_Result();
floatmult.Stop();
intdiv.Start();

pool_notify_Result();
intdiv.Stop();
floatdiv.Start();

pool_notify_Result();
floatdiv.Stop();

#ifdef USE_DSP
    // Stop DSP
    Uint8 processorId = 0;
    pool_notify_Delete (processorId);
#endif

    intmult.Print();
    floatmult.Print();
    intdiv.Print();
    floatdiv.Print();

    return 0;
}

