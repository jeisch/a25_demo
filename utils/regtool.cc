#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include "a25_vme.h"

int main(int argc, char **argv) {
	std::string command, extra;
	uint32_t addr, value;
	uint32_t base;
	if (argc != 2) {
		std::cout << "usage: " << argv[0] << " base_address" << std::endl;
		return -1;
	}
	VMEBus *bus;
	bus = new VMEBus();
	std::istringstream argss(argv[1]);
	argss.unsetf(std::ios::basefield);
	argss >> base;
	std::cout << std::hex << "Base Address: 0x" << base << std::endl;
	std::cout << "'q' to exit" << std::endl;
	std::cout << "'r offset' to read, 'w offset data' to write" << std::endl;
	while(1) {
		std::cout << "vme 0x" << std::setfill('0') << std::setw(8) << std::hex << base << " => ";
		if (!getline(std::cin,command)) {
			std::cout << std::endl;
			return 0;
		}
		if (command[0] == 'q') {
			std::cout << "bye!" << std::endl;
			return 0;
		}else if(command[0] == 'r') {
			std::stringstream ss;
			ss.unsetf(std::ios::basefield);
			ss << command.substr(1);
			ss >> addr;
			std::cout << std::setfill('0') << std::setw(8) << std::hex << base+addr << " " << std::setfill('0') << std::setw(8) << std::hex << bus->readValue(base+addr) << std::endl;
		}else if(command[0] == 'w') {
			std::stringstream ss;
			ss.unsetf(std::ios::basefield);
			ss << command.substr(1);
			ss >> addr >> value;
			std::cout << std::hex << base+addr << " " << value << std::endl;
			bus->setValue(base+addr,value);
		}else if(command[0] == 's') {
			int swapmode;
			std::stringstream ss;
			ss.unsetf(std::ios::basefield);
			ss << command.substr(1);
			ss >> swapmode;
			bus->setSwapMode(swapmode);
			std::cout << "Swapmode set to " << swapmode << std::endl;
		}else{
			std::cout << "unknown command: " << command << std::endl;
		}
	}
	std::cout << std::endl;
	return 0;
}
