#include "cpp-utils/mac.hpp"
#include "cpp-utils/stringutils.hpp"

#include <map>
#include <filesystem>

#include <unistd.h>

namespace cu
{

std::string getMacAddressAsString()
{
    std::map<std::string, std::string> m_macWired;
    std::map<std::string, std::string> m_macWireless;
    std::map<std::string, std::string> m_macModem;

    for(auto& entry : std::filesystem::directory_iterator("/sys/class/net"))
    {
        std::filesystem::file_status deviceDirectoryStatus = std::filesystem::status(entry.path() / "device");
        if(!std::filesystem::is_directory(deviceDirectoryStatus))
            continue; // filter out all virtual devices like "lo", "sit0", etc.

        std::string deviceName = entry.path().stem().string();

        std::string type = fileToString(entry.path() / "type");
        if(type.empty())
            continue;

        // Linux kernel: include/uapi/linux/if_arp.h => #define ARPHRD_ETHER 	1
        if(std::stol(type) != 1)
            continue;

        std::string assignType = fileToString(entry.path() / "addr_assign_type");
        if(!assignType.empty())
        {
            // https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-class-net
            if(std::stol(assignType) == 1) // randomly generated
                continue;
        }

        std::string mac = fileToString(entry.path() / "address");
        if(!mac.empty())
        {
            mac.erase(std::remove(mac.begin(), mac.end(), ':'), mac.end());
            std::transform(mac.begin(), mac.end(), mac.begin(), ::toupper);

            if(mac.rfind("00000000", 0) == 0) // starts with
                continue;
        }

        if(deviceName.rfind("wwan", 0) == 0) // starts with
            m_macModem[deviceName] = mac;
        else
        {
            std::filesystem::file_status wirelessDirectoryStatus = std::filesystem::status(entry.path() / "wireless");
            if(std::filesystem::is_directory(wirelessDirectoryStatus))
            {
                m_macWireless[deviceName] = mac;
            }
            else
                m_macWired[deviceName] = mac;
        }
    }

    std::string macAddress;
    if(!m_macWired.empty())
        macAddress = m_macWired.begin()->second;

    if((!m_macWireless.empty() && (macAddress.empty())))
        macAddress = m_macWireless.begin()->second;

    if((!m_macModem.empty() && (macAddress.empty())))
        macAddress = m_macModem.begin()->second;

    if(macAddress.empty())
    {
        int i, randomValue;
        srand(time(NULL) + getpid());
        for (i = 0; i < 6; i++)
        {
            randomValue = rand() % 256;
            macAddress.append((std::stringstream{} << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << randomValue).str());
        }
    }

    return macAddress;
}

std::vector<unsigned char> getMacAddressAsVector()
{
    std::string macAddress = getMacAddressAsString();
    std::vector<unsigned char> macAddressBytes;

    for(unsigned int i = 0; i < macAddress.length(); i += 2)
    {
        std::string byteString = macAddress.substr(i, 2);
        char byte = (char) strtol(byteString.c_str(), NULL, 16);
        macAddressBytes.push_back(byte);
    }

    return macAddressBytes;
}

}
