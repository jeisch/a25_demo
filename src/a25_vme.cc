#include <exception>
#include <stdexcept>
#include <string.h>
#include <time.h>

#include <endian.h>
#include <vector>

#include "a25_vme.h"

VMEBus::VMEBus(bool blt) {
	if (blt==true) {
		bus_fd = VME4L_Open( VME4L_SPC_A32_D32 );
	}else{
		bus_fd = VME4L_Open( VME4L_SPC_A32_D32_BLT );
	}
	if (bus_fd == -1) throw std::runtime_error("Error initializing the VMEBus");
	// Turn on hardware byteswapping by default
	// Byte swapping doesn't seem to be supported by the hardware...
	if (VME4L_SwapModeSet( bus_fd, VME4L_HW_SWAP1 )) throw std::runtime_error("error setting swap mode");
	// Set requestor mode, mode 0 is "release on request", mode 1 is "release when done"	
	if (VME4L_RequesterModeSet(bus_fd, 0)) throw std::runtime_error("Error setting bus aribitration mode");
}


VMEBus::~VMEBus( void ) {
	VME4L_Close(bus_fd);
}




void VMEBus::setValue(uint32_t address, uint32_t value) {
	value = htobe32(value);
	VME4L_Write(bus_fd,address, 4, 4, &value, VME4L_RW_NOFLAGS);
}

uint32_t VMEBus::readValue(uint32_t address) {
	uint32_t value;
	VME4L_Read(bus_fd,address, 4,4,&value,VME4L_RW_NOFLAGS);
	return be32toh(value);
}

