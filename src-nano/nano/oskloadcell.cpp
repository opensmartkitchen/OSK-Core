#include "oskloadcell.h"

FILE* OSKloadcell::m_serPort;
char  OSKloadcell::m_readBuffer[1024];
int OSKloadcell::m_numBytesRead;
std::string OSKloadcell::m_dataline="";

OSKloadcell::OSKloadcell(std::string id, int freq) : OSKdevice(id, freq)
{
    char serialPortFilename[] = "/dev/ttyACM0";
    m_serPort = fopen(serialPortFilename, "r");

    if (m_serPort == NULL)
    {
        std::cout << getID()
                  << " ERROR connecting to Arduino on "
                  << serialPortFilename
                  << std::endl;
        m_initOK = false;
    } else {
        std::cout << getID()
                  << " Connected to Arduino on "
                  << serialPortFilename
                  << std::endl;
        m_initOK = true;
    }
}

OSKloadcell::~OSKloadcell(){}

void OSKloadcell::start(){
    m_thread = new std::thread(run,this);
}

bool OSKloadcell::run(OSKloadcell *me){

    while(1)
    {
        memset(m_readBuffer, 0, 1024);
        fread(m_readBuffer, sizeof(char),1024,m_serPort);
        if(sizeof(m_readBuffer) != 0 /*&& me->isTime()*/)
        {
            if(m_dataline.find("EOL") == std::string::npos){
                m_dataline += std::string(m_readBuffer);
            } else{ //After getting a FULL line, write to file
                std::string time = me->getTimestamp();
                std::cout << time << ":" << m_dataline << std::endl;

                //TODO: Send trigger to camera to save a frame!!!
                if(me->getCam() != NULL){
                    std::cout << "Sending Cam Snapshot Request" << std::endl;
                    me->getCam()->setTakeSnapshot(true,std::stol(time));
                }

                //Write to CSV File
                static int fileNum = 0;
                std::ofstream file;
                std::string fileName = me->getSaveDirPath() + time + "_weight.csv";
                file.open(fileName);
                file << m_dataline << std::endl;

                //Wipe & Reset
                file.close();
                m_dataline = "";
                fileNum++;
            }
        }
    }
    return 0;
}

double OSKloadcell::getWeight(){
    procDataLine();
    return m_weight;
}

void OSKloadcell::setCam(OSKcam *cam){
    m_cam = cam;
}

OSKcam* OSKloadcell::getCam(){return m_cam;}

bool OSKloadcell::procDataLine(){
#if (DEBUG_DATALINE == true)
    m_dataline = "0.059,-0.075,-0.943,-3.092,-4.321,-4.410,-3.974,-1.874,-0.586,-0.105,-1.932,1.94";
#else
    static std::string lastDataline = "";
    if(m_dataline == ""){
        return false;
    } else if(m_dataline == lastDataline){
        return false;
    } else {
        lastDataline = m_dataline;
    }
#endif

    std::string temp = m_dataline;
    std::string data = "";
    for(int i = 0; i < DATA_LENGTH; ++i){
        std::size_t pos = temp.find_first_of(',');
        data = temp.substr(0,pos);
        temp = temp.substr(pos+1);
        m_data[i] = std::stod(data); //Convert string to double
        std::cout << temp << "\nDATAPT: " << data << "\n";
    }

    if(DEBUG_DATALINE){
        for(int i = 0; i < DATA_LENGTH; ++i){
            std::cout << m_data[i] << ",";
        }
        std::cout << std::endl;
    }


    return true;
}
