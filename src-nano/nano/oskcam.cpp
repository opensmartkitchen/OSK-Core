#include "oskcam.h"

OSKcam::OSKcam(std::string id, int freq) : OSKdevice(id, freq)
{
    m_initOK = initCam();
}

OSKcam::~OSKcam(){
    if(m_vidCap != NULL){
        m_vidCap->release();
    }
    cv::destroyAllWindows();
}

cv::VideoCapture* OSKcam::getVidCap(){ return m_vidCap; }

bool OSKcam::run(OSKcam *me){
    cv::namedWindow("CSI Camera", cv::WINDOW_AUTOSIZE);
    cv::Mat img;

    std::cout << "Hit ESC to exit" << "\n" ;
    while(true)
    {
        if (!me->getVidCap()->read(img)) {
            std::cout<<"Capture read error"<<std::endl;
            break;
        }

        if(me->getTakeSnapshot()){
            std::cout << "Saving Cam Snapshot" << std::endl;
            std::string fileName = me->getSaveDirPath()
                    + std::to_string(me->getTimeSnapshot())
                    + "_image.png";
            cv::imwrite(fileName,img);
            me->setTakeSnapshot(false,0);
        }

        if(!OSK_HEADLESS){
            cv::imshow("CSI Camera",img);
        }
        int keycode = cv::waitKey(30) & 0xff ;
        if (keycode == 27) break ;
    }
    return 0;
}

void OSKcam::start(){
    m_thread = new std::thread(run,this);
}

bool OSKcam::initCam(){
    std::string pipeline = makeGstreamerPipeline(
                m_captureWidth,
                m_captureHeight,
                m_displayWidth,
                m_displayHeight,
                m_framerate,
                m_flipMethod
                );
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";

    m_vidCap = new cv::VideoCapture(pipeline, cv::CAP_GSTREAMER);
    if(!m_vidCap->isOpened()) {
        std::cout<<"Failed to open camera."<<std::endl;
        return false;
    } else {
        return true;
    }
}

void OSKcam::setTakeSnapshot(bool toSet, long time){
    if(DEBUG_SNAPSHOT){
        std::cout << "setTakeSnapshot CALLED" << std::endl;
    }
    m_takeSnapshot = toSet;
    m_timeSnapshot = time;
}
bool OSKcam::getTakeSnapshot(){return m_takeSnapshot;}
long OSKcam::getTimeSnapshot(){return m_timeSnapshot;}
