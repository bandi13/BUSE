/*
 * buseRAMDevice.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */

#include "buseRAMDevice.h"
#include <stdlib.h>
#include <string.h>

namespace buse {
	buseRAMDevice::buseRAMDevice(uint64_t size) : buseOperations(size) {
		data = malloc(size);
	}

	buseRAMDevice::~buseRAMDevice() {
		free(data);
	}

	uint32_t buseRAMDevice::read(void* buf, uint32_t len, uint64_t offset, void* userdata) {
		buseOperations::read(buf, len, offset, userdata);
		memcpy(buf, (char *) data + offset, len);
		return 0;
	}

	uint32_t buseRAMDevice::write(const void* buf, uint32_t len, uint64_t offset, void* userdata) {
		buseOperations::write(buf, len, offset, userdata);
		memcpy((char *) data + offset, buf, len);
		return 0;
	}

	void buseRAMDevice::disc(void* userdata) {
		buseOperations::disc(userdata);
	}

	int buseRAMDevice::flush(void* userdata) {
		buseOperations::flush(userdata);
		return 0;
	}

	int buseRAMDevice::trim(uint64_t from, uint32_t len, void* userdata) {
		buseOperations::trim(from, len, userdata);
		return 0;
	}
}
