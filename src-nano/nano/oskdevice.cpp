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
