#ifndef OSKDEVICE_H
#define OSKDEVICE_H

#include <string>
#include <chrono>
#include <thread>
#include <atomic>

class OSKdevice
{
public:
    OSKdevice(std::string id, int freq);
    ~OSKdevice();
    void getData();
    std::string getID();
    /**
     * @brief isTime Can be used to check whether or
     * not the device is ready to perform it's reoccurring
     * operation
     * @return [T] if the tick frequency has occured
     */
    bool isTime();
    /**
     * @brief setSaveDirPath
     * @param path Path to Save DIRECTORY
     * @return True if set OK
     */
    bool setSaveDirPath(std::string path);
    /**
     * @brief getSaveDirPath
     * @return
     */
    std::string getSaveDirPath();

    virtual void start() = 0;
protected:

    std::string getTimestamp();

    bool m_initOK;
    std::string m_saveDir; //Logging Data Directory

    //Threading Variables
    std::thread* m_thread;
private:
    std::string m_id; //ID Caller

    //Timing Variables
    int m_freq; //Device tick
    double m_dt; //Device Period [1/freq]
    std::chrono::time_point<std::chrono::system_clock> m_start, m_now;
    std::chrono::duration<double> m_elapsed;
};

#endif // OSKDEVICE_H
