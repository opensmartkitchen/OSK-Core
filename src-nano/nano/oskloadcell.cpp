#include "oskloadcell.h"

FILE* OSKloadcell::m_serPort;
char  OSKloadcell::m_readBuffer[1024];
int OSKloadcell::m_numBytesRead;

OSKloadcell::OSKloadcell(std::string id, int freq) : OSKdevice(id, freq)
{
    char serialPortFilename[] = "/dev/ttyACM0";
    m_serPort = fopen(serialPortFilename, "r");

    if (m_serPort == NULL)
    {
        std::cout << getID()
                  << " ERROR connecting to Arduino on "
                  << serialPortFilename
                  << std::endl;
        m_initOK = false;
    } else {
        std::cout << getID()
                  << " Connected to Arduino on "
                  << serialPortFilename
                  << std::endl;
        m_initOK = true;
    }
}

void OSKloadcell::start(){
    m_thread = new std::thread(run,this);
}

bool OSKloadcell::run(OSKloadcell *me){

    while(1)
    {
        memset(m_readBuffer, 0, 1024);
        fread(m_readBuffer, sizeof(char),1024,m_serPort);
        if(sizeof(m_readBuffer) != 0 /*&& me->isTime()*/)
        {
            //TODO: Write a real communication protocol so we can implement some timing
            printf(m_readBuffer);
        }
    }
    return 0;
}
