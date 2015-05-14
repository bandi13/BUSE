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
			virtual int read(void *buf, size_t len, off64_t offset) override;
			virtual int write(const void *buf, size_t len, off64_t offset) override;
		private:
			void *data;
	};
}

#endif /* BUSERAMDEVICE_H_ */
