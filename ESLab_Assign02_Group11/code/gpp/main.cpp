#include "meanshift.h"
#include "Timer.h"
#include "pool_notify.h"
#include <iostream>

#ifndef ARMCC
#include "markers.h"
#endif

int main(int argc, char ** argv)
{
    Timer totalTimer("Total Time");
    Timer readTimer("Reading Time");
    Timer writeTimer("Writing Time");
    Timer trackTimer("Tracking Time");

    cv::VideoCapture frame_capture;
    if(argc<4)
    {
        std::cout <<"specifiy an input video file to track" << std::endl;
        std::cout <<"Usage:  " << argv[0] << " car.avi meanshift.dsp buffersize" << std::endl;
        return -1;
    }
    else
    {
        frame_capture = cv::VideoCapture( argv[1] );
    }

#ifdef DSP
    // Set up DSP
    Char8 * dspExecutable = argv[2];
    Char8 * strBufferSize = argv[3];
    if (!pool_notify_Main(dspExecutable, strBufferSize)) {
        std::cout << "Error setting up DSP" << std::endl;
        return -1;
    }
#endif

    // this is used for testing the car video
    // instead of selection of object of interest using mouse
    cv::Rect rect(228,367,86,58);
    cv::Mat frame;
    frame_capture.read(frame);
    
    MeanShift ms; // creat meanshift obj
    ms.Init_target_frame(frame,rect); // init the meanshift

    {
    int codec = CV_FOURCC('F', 'L', 'V', '1');
    cv::VideoWriter writer("tracking_result.avi", codec, 20, cv::Size(frame.cols,frame.rows));

    totalTimer.Start();
    #ifndef ARMCC
    MCPROF_START();
    #endif
    int TotalFrames = 32;
    int fcount;
    for(fcount=0; fcount<TotalFrames; ++fcount)
    {
        // read a frame
        readTimer.Start();
        int status = frame_capture.read(frame);
        if( 0 == status ) break;
        readTimer.Pause();

        // track object
        #ifndef ARMCC
        // MCPROF_START();
        #endif
        trackTimer.Start();
        cv::Rect ms_rect =  ms.track(frame);
        trackTimer.Pause();
        #ifndef ARMCC
        // MCPROF_STOP();
        #endif
        
        // mark the tracked object in frame
        writeTimer.Start();
        cv::rectangle(frame,ms_rect,cv::Scalar(0,0,255),3);

        // write the frame
        writer << frame;
        writeTimer.Pause();
    }
    #ifndef ARMCC
    MCPROF_STOP();
    #endif
    totalTimer.Pause();

#ifdef DSP
    // Stop DSP
    Uint8 processorId = 0;
    pool_notify_Delete (processorId);
#endif

    totalTimer.Print();
    readTimer.Print();
    writeTimer.Print();
    trackTimer.Print();

    std::cout << "Processed " << fcount << " frames" << std::endl;
    std::cout << "Time: " << totalTimer.GetTime() <<" sec\nFPS : " << fcount/totalTimer.GetTime() << std::endl;

    } // Destroy writer to flush output to file
    #ifdef ARMCC
    std::cout << "4bf41e5572f56bfedb3182781e24d4ac  is expected...\n";
    #else
    std::cout << "051a524f68785b2f9c7fbb0754facb35  is expected...\n";
    #endif
    system("md5sum tracking_result.avi");

    return 0;
}

