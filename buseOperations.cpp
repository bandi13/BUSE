/*
 * buseOperations.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */
#include "buseOperations.h"
#include <iostream>
using namespace std;

namespace buse {
	buseOperations::buseOperations() { this->size = 0; }
	buseOperations::buseOperations(uint64_t size) { this->size = size; }

	buseOperations::~buseOperations() { DEBUGPRINTLN("Destroying buse object."); }

	uint64_t buseOperations::getSize() { return size; }

	uint32_t buseOperations::read(void *buf, uint32_t len, uint64_t offset) {
		UNUSED(buf); UNUSED(len); UNUSED(offset);
		DEBUGPRINTLN("R - " << offset << ", " << len);
		return 0;
	}

	uint32_t buseOperations::write(const void *buf, uint32_t len, uint64_t offset) {
		UNUSED(buf); UNUSED(len); UNUSED(offset);
		DEBUGPRINTLN("W - " << offset << ", " << len);
		return 0;
	}

	void buseOperations::disc() { DEBUGPRINTLN("Received a disconnect request."); }

	uint32_t buseOperations::flush() { DEBUGPRINTLN("Received a flush request."); return 0; }

	uint32_t buseOperations::trim(uint64_t from, uint32_t len) {
		UNUSED(from); UNUSED(len);
		DEBUGPRINTLN("T - " << from << ", " << len);
		return 0;
	}
}
