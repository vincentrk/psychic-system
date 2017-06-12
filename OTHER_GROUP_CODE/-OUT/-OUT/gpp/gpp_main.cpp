#include "meanshift.h"
#include "Timer.h"
#include <iostream>

/* DSP related headers */
#include "dsplink.h"

extern "C" {
#include "pool_notify.h"

}

#define DSP_BUFFER_SIZE "2048"

#define RECT_TO_PROC_HEIGHT 640
#define RECT_TO_PROC_WIDTH 480

Timer partialTimer("Partial Time");
Timer partialTimer2("Partial Time2");

int main(int argc, char ** argv)
{
    Timer totalTimer("Total Time");
    Timer trackTimer("Partial Time");

    uchar Preallocated[RECT_TO_PROC_HEIGHT*RECT_TO_PROC_WIDTH*3];
    cv::Mat frame_for_tracking = cv::Mat(640,480,CV_8U,Preallocated);


    cv::VideoCapture frame_capture;
    char *video = NULL;

    char *dspExecutable = NULL;
    DSP_STATUS status;

    if(argc<3)
    {
        std::cout <<"specifiy an input video file to track and a DSP executable" << std::endl;
        std::cout <<"Usage:  ./" << argv[0] << " path/to/dps_exacutable" << " car.avi" << std::endl;
        return -1;
    }

    dspExecutable = argv[1];
    video = argv[2];

    std::cout << "Using DSP executabel: " << dspExecutable << std::endl;
    std::cout << "Using video file: " << video << std::endl;

    /* Setup DSP communication */
    status = pool_notify_Init(dspExecutable, DSP_BUFFER_SIZE);
    if (!DSP_SUCCEEDED(status))
    {
        std::cout << "Initializing DSP failed" << std::endl;
        return -1;
    }

    frame_capture = cv::VideoCapture(video);

    // this is used for testing the car video
    // instead of selection of object of interest using mouse
    cv::Rect rect(228,367,58,58);
    //cv::Mat frame;
    cv::Mat frame;

    frame_capture.read(frame);
    MeanShift ms; // creat meanshift obj

    std::cout << "data pointer frame: " << static_cast<void*>(frame.data) << std::endl;
    //frame_for_tracking = frame.clone();
    std::cout << "data pointer frame: " << static_cast<void*>(frame.data) << std::endl;

    ms.Init_target_frame(frame,rect); // init the meanshift

    int codec = CV_FOURCC('F', 'L', 'V', '1');
    cv::VideoWriter writer("tracking_result.avi", codec, 20, cv::Size(frame.cols,frame.rows));


    totalTimer.Start();

    int TotalFrames = 32;
    int fcount;
    for(fcount=0; fcount<TotalFrames; ++fcount)
    {
        // read a frame
        int status = frame_capture.read(frame);
        if( 0 == status ) break;
        //frame_for_tracking = frame.clone();

        // track object
        trackTimer.Start();
        cv::Rect ms_rect =  ms.track(frame);
        trackTimer.Pause();

        // mark the tracked object in frame
        cv::rectangle(frame,ms_rect,cv::Scalar(0,0,255),3);

        // write the frame
        writer << frame;
    }
    totalTimer.Pause();

    pool_notify_Delete (0) ;

    //partialTimer.Print();
    //totalTimer.Print();
    std::cout << "\nTotal Time:                   " << totalTimer.GetTime() << std::endl;
    std::cout << "ms.track Time:                " << trackTimer.GetTime() << std::endl;
    std::cout << "partial:                      " << partialTimer.GetTime() << std::endl;
    std::cout << "partial2:                     " << partialTimer2.GetTime() << std::endl;
    std::cout << "speed-up:                     " << 9.81/trackTimer.GetTime() << "x" << std::endl;
    std::cout << "\nPercentage track/total:       " << 100*trackTimer.GetTime()/totalTimer.GetTime() << "%" << std::endl;
    std::cout << "Percentage partial/track:     " << 100*partialTimer.GetTime()/trackTimer.GetTime() << "%" << std::endl;
    std::cout << "Percentage partial2/track:    " << 100*partialTimer2.GetTime()/trackTimer.GetTime() << "%" << std::endl;
    std::cout << "Percentage partial2/partial:  " << 100*partialTimer2.GetTime()/partialTimer.GetTime() << "%" << std::endl;
    //std::cout << "Processed " << fcount << " frames" << std::endl;
    std::cout << "\nFPS:                          " << fcount/totalTimer.GetTime() << "\n" << std::endl;


    return 0;
}

