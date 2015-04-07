/*
 * buseRAMDevice.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */

#include "buseRAMDevice.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

namespace buse {
	buseRAMDevice::buseRAMDevice(uint64_t size) : buseOperations(size) {
		data = malloc(size);
	}

	buseRAMDevice::~buseRAMDevice() {
		DEBUGPRINTLN("Destroying buseRAMDevice.");
		free(data);
	}

	uint32_t buseRAMDevice::read(void* buf, uint32_t len, uint64_t offset) {
		buseOperations::read(buf, len, offset);
		if(len + offset > this->getSize()) return EFBIG;
		memcpy(buf, (char *) data + offset, len);
		return 0;
	}

	uint32_t buseRAMDevice::write(const void* buf, uint32_t len, uint64_t offset) {
		buseOperations::write(buf, len, offset);
		if(len + offset > this->getSize()) return EFBIG;
		memcpy((char *) data + offset, buf, len);
		return 0;
	}
}
