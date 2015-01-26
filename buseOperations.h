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

			virtual uint32_t read(void *buf, uint32_t len, uint64_t offset);
			virtual uint32_t write(const void *buf, uint32_t len, uint64_t offset);
			virtual void disc();
			virtual int flush();
			virtual int trim(uint64_t from, uint32_t len);

		protected:
			uint64_t size; // size of the entire array
	};
}

#endif /* BUSEOPERATIONS_H_ */
