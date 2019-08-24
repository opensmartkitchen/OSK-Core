#include "oskdevice.h"

OSKdevice::OSKdevice(std::string id, int freq)
{
    m_initOK = false; //Assume [F] until [T] in inhereted classes
    m_id = id;
    m_freq = freq;
    m_dt = 1.0 / m_freq;
    m_start = std::chrono::system_clock::now();
}

OSKdevice::~OSKdevice(){}

std::string OSKdevice::getID(){ return m_id; }

std::string OSKdevice::getTimestamp(){
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);
    char timeCstr[70];
    std::strftime(timeCstr,sizeof timeCstr,"%F_%H-%M_%S",&now_tm);

    return std::string(timeCstr);
}


bool OSKdevice::isTime(){
    m_now = std::chrono::system_clock::now();
    m_elapsed = m_now - m_start;
    if(m_elapsed.count() >= m_dt){
        m_start = m_now;
        return true;
    } else {
        return false;
    }
}

bool OSKdevice::setSaveDirPath(std::string path){
    m_saveDir = path;
    return true;
}

std::string OSKdevice::getSaveDirPath(){
    return m_saveDir;
}
