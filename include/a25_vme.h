#ifndef A25_VME_H_CA737491
#define A25_VME_H_CA737491

#include <vector>

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <MEN/vme4l.h>
#include <MEN/vme4l_api.h> 



class VMEBus
{
	public:
		uint32_t readValue(uint32_t address);
		void setValue(uint32_t address, uint32_t value);
		void setSwapMode(int on);
		VMEBus(bool blt = false );
		~VMEBus( void );
	private:
		int bus_fd;
};

#endif /* end of include guard: A25_VME_H_CA737491 */

