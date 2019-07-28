#ifndef OSKGADGET_H
#define OSKGADGET_H

#include <string>
#include <vector>

#include "oskdevice.h"

class OSKdevice;

class OSKgadget
{
public:
    OSKgadget();
private:
    std::string m_id;
    std::vector<OSKdevice*> m_device;
};

#endif // OSKGADGET_H
