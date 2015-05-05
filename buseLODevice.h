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
			template <class Function>
			uint32_t handleTX(void *buf, uint32_t len, uint64_t offset,Function func);
	};
}

#endif
