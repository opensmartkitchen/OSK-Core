#ifndef OSKLOADCELL_H
#define OSKLOADCELL_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <thread>

#include "oskdevice.h"

class OSKdevice;

class OSKloadcell : public OSKdevice
{
public:
    OSKloadcell();
    static bool run();
    void start();
private:
    //Serial Communication Variables
    static FILE *m_serPort;
    static char m_readBuffer[1024];
    static int m_numBytesRead;

    //Threading Variables
    std::thread* m_thread;
};

#endif // OSKLOADCELL_H
