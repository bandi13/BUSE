/*
 * buseRAMDevice.h
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */

#ifndef BUSERAMDEVICE_H_
#define BUSERAMDEVICE_H_

#include "buseOperations.h"

namespace buse {
	class buseRAMDevice: public buseOperations {
		public:
			buseRAMDevice(uint64_t size);
			~buseRAMDevice();
			uint32_t read(void *buf, uint32_t len, uint64_t offset, void *userdata);
			uint32_t write(const void *buf, uint32_t len, uint64_t offset, void *userdata);
			void disc(void *userdata);
			int flush(void *userdata);
			int trim(uint64_t from, uint32_t len, void *userdata);

		private:
			void *data;
	};
}

#endif /* BUSERAMDEVICE_H_ */
