#include <iostream>
#include <chrono>

#include "oskloadcell.h"
#include "oskcam.h"

class OSKloadcell;
class OSKcam;

using namespace std;

int main()
{
    cout << "Testing OSK" << endl;

    OSKloadcell device1("LoadCell",5);
//    device1.run();
    device1.start();

    OSKcam device2("Camera",30);
    device2.start();


    std::chrono::time_point<std::chrono::system_clock> start, now, end;
    start = std::chrono::system_clock::now();
    while(true){
        now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = now - start;
        if(elapsed.count() >= 10){
            std::cout << "MAIN" << std::endl;
            start = now;
        }
    }


    return 0;
}
