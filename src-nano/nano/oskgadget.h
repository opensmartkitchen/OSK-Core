#ifndef OSKGADGET_H
#define OSKGADGET_H

#include <string>
#include <vector>

#include "oskdevice.h"
#include "oskloadcell.h"
#include "oskcam.h"
#include "oskflags.h"

class OSKdevice;
class OSKloadcell;
class OSKcam;

class OSKgadget
{
public:
    OSKgadget(std::string id, std::string logDirPath);
    bool init();
    void run();
    long getScaleLastTimestamp();

private:
    std::string m_logDirPath;
    std::string m_id;
    std::vector<OSKdevice*> m_device;
    OSKloadcell* m_loadCell = NULL;
    OSKcam* m_cam = NULL;
};

#endif // OSKGADGET_H
