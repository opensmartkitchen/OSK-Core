#ifndef OSKLOADCELL_H
#define OSKLOADCELL_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "oskdevice.h"
#include "oskcam.h"

#define DEBUG_DATALINE false
#define DATA_LENGTH 12

class OSKdevice;
class OSKcam;

class OSKloadcell : public OSKdevice
{
public:
    OSKloadcell(std::string id, int freq);
    ~OSKloadcell();
    static bool run(OSKloadcell *me);
    double getWeight();
    void start();
    void setCam(OSKcam* cam);
    long getLastChangeTimestamp();
protected:
    OSKcam* getCam();
    void setLastChangeTimestamp(long toSet);
private:
    bool procDataLine();

    //Serial Communication Variables
    static FILE *m_serPort;
    static char m_readBuffer[1024];
    static int m_numBytesRead;
    static std::string m_dataline;

    //Data Variables
    double m_data[DATA_LENGTH]; //LAST POINT IS THE AVERAGE!
    double m_weight = 0.0;
    double m_deltaWeight = 0.0;
    std::atomic<long> m_lastChangeTimestamp{0};

    //Pointer to a Camera
    OSKcam* m_cam = NULL;
};

#endif // OSKLOADCELL_H
