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
    Char8 * strBufferSize = "4096";
    if (argc >= 3)
    {
        strBufferSize = argv[2];
    }
    int vectorSize = atoi(strBufferSize) / sizeof(int);

#ifdef USE_DSP
    // Set up DSP
    Char8 * dspExecutable = argv[1];
    if (!pool_notify_Main(dspExecutable, strBufferSize)) {
        std::cout << "Error setting up DSP" << std::endl;
        return -1;
    }
#endif


    long tStart;
    long tCopy, tWriteback, tNotify, tRead;
	Timer_Init();

    int * buf = pool_notify_GetBuf();
    int * data = (int *) malloc(vectorSize * sizeof(int));

    // Generate data
    for(int i=0; i<vectorSize; i++)
    {
        data[i] = rand();
    }

    // Read back stuff, to ensure cache voodoo
    // This simulates the pool being in the cache already
    memcpy(buf + 1, data, (vectorSize - 1) * sizeof(int));

    // Copy to shared memory
    tStart = HiResTime();
    memcpy(buf, data, vectorSize * sizeof(int));
    tCopy = HiResTime() - tStart;

    // Flush cache
    tStart = HiResTime();
    pool_notify_Writeback();
    tWriteback = HiResTime() - tStart;

    // Send notification
    tStart = HiResTime();
    pool_notify_Execute();
    pool_notify_Result();
    tNotify = HiResTime() - tStart;

    // Read back
    tStart = HiResTime();
    pool_notify_Invalidate();
    memcpy(data, buf, vectorSize * sizeof(int));
    tRead = HiResTime() - tStart;



    Timer_DeInit();

    std::cout << buf[0]
            << "," << tCopy
            << "," << tWriteback
            << "," << tNotify
            << "," << tRead
            << "\n";

#ifdef USE_DSP
    // Stop DSP
    Uint8 processorId = 0;
    pool_notify_Delete (processorId);
#endif

    return 0;
}

