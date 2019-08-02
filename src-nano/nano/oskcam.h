#ifndef OSKCAM_H
#define OSKCAM_H

#include <string>
#include <opencv2/opencv.hpp>

#include "oskdevice.h"

class OSKdevice;

class OSKcam : public OSKdevice
{
public:
    OSKcam(std::string id, int freq);
    ~OSKcam();
    static bool run(OSKcam *me);
    void start();
    cv::VideoCapture* getVidCap();
private:
    bool initCam();

    //Camera Parameters
    int m_captureWidth = 1280;
    int m_captureHeight = 720;
    int m_displayWidth = 1280;
    int m_displayHeight = 720;
    int m_framerate = 60;
    int m_flipMethod = 0;

    //Camera Capture Object
    cv::VideoCapture* m_vidCap = NULL;

    /**
     * @brief makeGstreamerPipeline Creates a Gstreamer Pipeline to intract with the camera
     * @param capture_width
     * @param capture_height
     * @param display_width
     * @param display_height
     * @param framerate
     * @param flip_method
     * @return The pipeline string
     */
    std::string makeGstreamerPipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
        return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
               std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
               "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
               std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
    }
};

#endif // OSKCAM_H
