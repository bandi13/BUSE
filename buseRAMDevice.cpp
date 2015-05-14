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

	int buseRAMDevice::read(void* buf, size_t len, off64_t offset) {
		buseOperations::read(buf, len, offset);
		if(len + (uint64_t)offset > this->getSize()) return EFBIG;
		memcpy(buf, (char *) data + offset, len);
		return 0;
	}

	int buseRAMDevice::write(const void* buf, size_t len, off64_t offset) {
		buseOperations::write(buf, len, offset);
		if(len + (uint64_t)offset > this->getSize()) return EFBIG;
		memcpy((char *) data + offset, buf, len);
		return 0;
	}
}
