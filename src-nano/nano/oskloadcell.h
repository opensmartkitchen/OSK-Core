#ifndef OSKLOADCELL_H
#define OSKLOADCELL_H

#include <stdio.h>
#include <string.h>
#include <iostream>

#include "oskdevice.h"

#define DEBUG_DATALINE true
#define DATA_LENGTH 12

class OSKdevice;

class OSKloadcell : public OSKdevice
{
public:
    OSKloadcell(std::string id, int freq);
    ~OSKloadcell();
    static bool run(OSKloadcell *me);
    double getWeight();
    void start();
private:
    bool procDataLine();

    //Serial Communication Variables
    static FILE *m_serPort;
    static char m_readBuffer[1024];
    static int m_numBytesRead;
    static std::string m_dataline;

    //Data Variables
    double m_data[DATA_LENGTH]; //LAST POINT IS THE AVERAGE!
    double m_weight;
    double m_deltaWeight;

};

#endif // OSKLOADCELL_H
