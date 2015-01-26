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
	buseOperations::buseOperations() {
		this->size = 0;
	}
	buseOperations::buseOperations(uint64_t size) {
		this->size = size;
	}

	uint64_t buseOperations::getSize() {
		return size;
	}

	uint32_t buseOperations::read(void *buf, uint32_t len, uint64_t offset) {
		UNUSED(buf); UNUSED(len); UNUSED(offset);
		DEBUGCODE(cerr << "R - " << offset << ", " << len << endl);
		return 0;
	}
	uint32_t buseOperations::write(const void *buf, uint32_t len, uint64_t offset) {
		UNUSED(buf); UNUSED(len); UNUSED(offset);
		DEBUGCODE(cerr << "W - " << offset << ", " << len << endl);
		return 0;
	}
	void buseOperations::disc() {
		DEBUGCODE(cerr << "Received a disconnect request." << endl);
	}
	int buseOperations::flush() {
		DEBUGCODE(cerr << "Received a flush request." << endl);
		return 0;
	}
	int buseOperations::trim(uint64_t from, uint32_t len) {
		UNUSED(from); UNUSED(len);
		DEBUGCODE(cerr << "T - " << from << ", " << len << endl);
		return 0;
	}
}
