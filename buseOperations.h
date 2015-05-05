/*
 * buseOperations.h
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */

#ifndef BUSEOPERATIONS_H_
#define BUSEOPERATIONS_H_

#include "commonIncludes.h"
#include <chrono>
#include <vector>
#include <inttypes.h>

namespace buse {
	class buseOperations {
		public:
			buseOperations();
			buseOperations(uint64_t size);
			virtual ~buseOperations();

			typedef struct {
					int fd;
					uint64_t diskSize;
					chrono::duration<double, std::micro> writeSpeed;
					chrono::duration<double, std::micro> readSpeed;
			} diskStats_t;

			virtual uint64_t getSize();

			virtual uint32_t read(void *buf, uint32_t len, uint64_t offset);
			virtual uint32_t write(const void *buf, uint32_t len, uint64_t offset);
			template <class Function>
			uint32_t handleTX(void *buf, uint32_t len, uint64_t offset, Function func);

			virtual void disc();
			virtual uint32_t flush();
			virtual uint32_t trim(uint64_t from, uint32_t len);
			void testDiskSpeed();
			inline uint8_t getNumDrives() { return disks.size(); }

		protected:
			std::vector<diskStats_t *> disks;
			uint64_t size; // size of the entire array
	};
}

#endif /* BUSEOPERATIONS_H_ */
