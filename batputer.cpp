#include <iostream>
#include <fstream>




#if defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#define OSTYPE "UNIX"
#else
#define OSTYPE "OTHER"
#endif




#define PATH "/sys/class/power_supply/BAT0/"



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
    std::string filePathEnergyFullDesign = std::string(PATH) + "energy_full_design";
    std::string filePathEnergyFull = std::string(PATH) + "energy_full";

    //efd is short for enery full design
    std::ifstream fileEFD(filePathEnergyFullDesign);
    std::ifstream fileEF(filePathEnergyFull);

    std::string efd , ef;
    
    if (fileEFD.is_open() && fileEF.is_open())
    {
        std::getline(fileEFD , efd);
        std::getline(fileEF , ef);

        fileEFD.close();fileEF.close();
    }
    else 
    {
        return "ERROR";
    }

    int energyFullDesign = std::stoi(efd);
    int energyFull = std::stoi(ef);

    return std::to_string(
        static_cast<int>(
            (static_cast<float>(energyFull) / energyFullDesign) * 100)) + "%";
}











void showTypo()
{
    std::cout << R"(██▄ ▄▀▄ ▀█▀ █▀▄ █ █ ▀█▀ ██▀ █▀▄
█▄█ █▀█  █  █▀  ▀▄█  █  █▄▄ █▀▄
)";
}




int main()
{
    if(OSTYPE != "UNIX")
    {
        std::cout << "This tool is not developed for your OS. Run the tool on a Unix-like OS.";
        return 0;
    }


    showTypo();
    std::cout << std::endl;

    std::cout << "Battery stat : " << readItem("capacity") << std::endl;
    std::cout << "Battery level : " << readItem("capacity_level") << std::endl;
    std::cout << "Battery Status : " << readItem("status") << std::endl;
    std::cout << "Battery tech : " << readItem("technology") << std::endl;
    std::cout << "Battery Health : " << calculateBatteryHealth() << std::endl;
    std::cout << "Plug status : " << plugStatus() << std::endl;
    
}