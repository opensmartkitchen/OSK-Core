#ifndef OSKCAM_H
#define OSKCAM_H

#include "oskdevice.h"

class OSKdevice;

class OSKcam : public OSKdevice
{
public:
    OSKcam(std::string id, int freq);
};

#endif // OSKCAM_H
