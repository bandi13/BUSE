/*
 * buseOperations.h
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */

#ifndef BUSEOPERATIONS_H_
#define BUSEOPERATIONS_H_

#include "commonIncludes.h"
#include <inttypes.h>

namespace buse {
	class buseOperations {
		public:
			buseOperations();
			buseOperations(uint64_t size);

			virtual uint64_t getSize();

			virtual uint32_t read(void *buf, uint32_t len, uint64_t offset, void *userdata);
			virtual uint32_t write(const void *buf, uint32_t len, uint64_t offset, void *userdata);
			virtual void disc(void *userdata);
			virtual int flush(void *userdata);
			virtual int trim(uint64_t from, uint32_t len, void *userdata);

		protected:
			uint64_t size;
	};
}

#endif /* BUSEOPERATIONS_H_ */
