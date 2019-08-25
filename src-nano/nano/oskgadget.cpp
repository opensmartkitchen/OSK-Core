#include "oskgadget.h"

OSKgadget::OSKgadget(std::string id, std::string logDirPath)
{
    m_id = id;
    m_logDirPath = logDirPath;
}

bool OSKgadget::init(){
    //Check if Log Path is Valid
    if(m_logDirPath ==  ""){
        return false;
    }

    //Initialize the Load Cell
    m_loadCell = new OSKloadcell("LoadCell",5);
    m_loadCell->setSaveDirPath(m_logDirPath);

    //Initialize the Camera
    m_cam = new OSKcam("Camera",30);
    m_cam->setSaveDirPath(m_logDirPath);
    m_loadCell->setCam(m_cam);

    return true;
}

void OSKgadget::run(){
    //Start Devices!
    m_cam->start();
    m_loadCell->start();
}

long OSKgadget::getScaleLastTimestamp(){
    return m_loadCell->getLastChangeTimestamp();
}
