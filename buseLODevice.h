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

	protected:
		virtual int handleTX(void *buf, size_t len, off64_t offset, ssize_t (*func)(int, void *, size_t)) override;
	};
}

#endif
