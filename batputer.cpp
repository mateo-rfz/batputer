#include "tinyArgs/include/tinyArgs.hpp"


#include <iostream>
#include <fstream>





#if defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#define OSTYPE "UNIX"
#else
#define OSTYPE "OTHER"
#endif




#define PATH "/sys/class/power_supply/BAT0/"
#define VERSION "0.0.2"



std::string readItem(std::string itemName)
{
    std::string filePath = std::string(PATH) + itemName;
    std::ifstream file(filePath);
    std::string c;
    
    if (file.is_open())
    {
        std::getline(file , c);
        file.close();
    }
    else 
    {
        c = "ERROR";
    }

    return c;
}




std::string plugStatus()
{

    std::string filePath = std::string(PATH) + "present";
    std::ifstream file(filePath);
    std::string c;
    
    if (file.is_open())
    {
        std::getline(file , c);
        file.close();
    }
    else 
    {
        return "ERROR";
    }

    if(c == "0")
    {
        return "Battery Unplugged";
    }
    else 
    {
        return "Battery Plugged";
    }
    
}





std::string calculateBatteryHealth()
{
    std::string names[2] = {"energy", "charge"};
    int energyFullDesign = 0, energyFull = 0;

    for (std::string name : names)
    {
        std::string filePathEnergyFullDesign = std::string(PATH) + name + "_full_design";
        std::string filePathEnergyFull = std::string(PATH) + name + "_full";

        // Open files
        std::ifstream fileEFD(filePathEnergyFullDesign);
        std::ifstream fileEF(filePathEnergyFull);

        if (fileEFD.is_open() && fileEF.is_open())
        {
            //efd is short for energy full design
            std::string efd, ef;
            std::getline(fileEFD, efd);
            std::getline(fileEF, ef);

            fileEFD.close();
            fileEF.close();

            energyFullDesign = std::stoi(efd);
            energyFull = std::stoi(ef);

            return std::to_string(
                static_cast<int>((static_cast<float>(energyFull) / energyFullDesign) * 100)) + "%";
        }
    }

    return "ERROR";
}












void showTypo()
{
    std::cout << R"(██▄ ▄▀▄ ▀█▀ █▀▄ █ █ ▀█▀ ██▀ █▀▄
█▄█ █▀█  █  █▀  ▀▄█  █  █▄▄ █▀▄
)";
}




int main(int argc , char * argv[])
{
    if(OSTYPE != std::string("UNIX"))
    {
        std::cout << "This tool is not developed for your OS. Run the tool on a Unix-like OS.";
        return 0;
    }


    targs::TinyArgs ta(argc , argv);


    bool helpFlag = ta.getLongFlag("--help" , "show help msg") || ta.getShortFlag("-h" , "show help msg");
    bool verbose = ta.getLongFlag("--verbose" , "verbose mode") || ta.getShortFlag("-vv" , "verbose mode");
    bool versionN = ta.getLongFlag("--version" , "show version") || ta.getShortFlag("-v" , "show version");

    
    if(helpFlag)
    {
        showTypo();
        std::cout << std::endl;

        std::cout << ta.help();
    }


    if(verbose)
    {
        showTypo();
        std::cout << std::endl;

        std::cout << "Battery stat : " << readItem("capacity") << std::endl;
        std::cout << "Battery level : " << readItem("capacity_level") << std::endl;
        std::cout << "Battery Status : " << readItem("status") << std::endl;
        std::cout << "Battery tech : " << readItem("technology") << std::endl;
        std::cout << "Battery Health : " << calculateBatteryHealth() << std::endl;
        std::cout << "Plug status : " << plugStatus() << std::endl;
    }


    if(versionN)
    {
        showTypo();
        std::cout << std::endl;

        std::cout << "Version : " << VERSION << std::endl;
    }


    std::vector<std::string> falgs = ta.getAllFlags();
    if(falgs.empty())
    {
        showTypo();
        std::cout << std::endl;

        std::cout << "Battery stat : " << readItem("capacity") << std::endl;
        std::cout << "Battery Status : " << readItem("status") << std::endl;
        std::cout << "Battery Health : " << calculateBatteryHealth() << std::endl;
    }
}