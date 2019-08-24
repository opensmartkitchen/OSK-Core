#include <iostream>
#include <chrono>

#include "oskloadcell.h"
#include "oskcam.h"
#include "oskgadget.h"

class OSKloadcell;
class OSKcam;
class OSKgadget;

using namespace std;

#define DEBUG false

int main()
{
    std::cout << "Testing OSK" << std::endl;
//    std::string filePath = "/home/mepix/Workspace/OSK-Core/src-nano/testoutputdata/";
    std::string filePath = "/home/mc/workspace/OSK-Core/src-nano/testoutputdata/";


//    //Initialize the Load Cell
//    OSKloadcell device1("LoadCell",5);
//    device1.setSaveDirPath(filePath);

//    //Initialize the Camera
//    OSKcam device2("Camera",30);
//    device2.setSaveDirPath(filePath);
//    device1.setCam(&device2);

//    //Start Devices!
//    device1.start();
//    device2.start();

    OSKgadget gadget("Hackday2019",filePath);
    gadget.init();
    gadget.run();



    std::chrono::time_point<std::chrono::system_clock> start, now, end;
    start = std::chrono::system_clock::now();
#if (DEBUG == true)
    device1.getWeight();
#else
    while(true){
        now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = now - start;
        if(elapsed.count() >= 10){
            std::cout << "MAIN" << std::endl;
            start = now;
        }
//        device1.getWeight();
    }
#endif

    return 0;
}
