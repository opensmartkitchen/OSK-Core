#ifndef OSKDEVICE_H
#define OSKDEVICE_H

#include <string>

class OSKdevice
{
public:
    OSKdevice();
    void getData();
    std::string getID();
protected:

    bool m_initOK;
private:
    std::string m_id; //ID Caller
    int m_freq; //Device tick
};

#endif // OSKDEVICE_H
