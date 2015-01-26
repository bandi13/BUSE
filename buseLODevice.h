/*
 * buseLODevice.h
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */

#ifndef BUSELODEVICE_H_
#define BUSELODEVICE_H_

#include "buseOperations.h"

namespace buse {
	class buseLODevice : public buseOperations {
		public:
			buseLODevice(char *fileName);
			~buseLODevice();
			uint32_t read(void *buf, uint32_t len, uint64_t offset);
			uint32_t write(const void *buf, uint32_t len, uint64_t offset);

		private:
			int fd;
	};
}

#endif
