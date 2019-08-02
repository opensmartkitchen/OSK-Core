#ifndef OSKLOADCELL_H
#define OSKLOADCELL_H

#include <stdio.h>
#include <string.h>
#include <iostream>

#include "oskdevice.h"

class OSKdevice;

class OSKloadcell : public OSKdevice
{
public:
    OSKloadcell(std::string id, int freq);
    ~OSKloadcell();
    static bool run(OSKloadcell *me);
    void start();
private:
    //Serial Communication Variables
    static FILE *m_serPort;
    static char m_readBuffer[1024];
    static int m_numBytesRead;

};

#endif // OSKLOADCELL_H
