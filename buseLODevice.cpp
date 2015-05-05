/*
 * buseLODevice.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */
#include "buseLODevice.h"
#include "buseOperations.h"

#include <assert.h>
#include <fcntl.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>

#include <iostream>
using namespace std;

namespace buse {
	buseLODevice::buseLODevice(char *fileName) {
		struct stat buf;
		int err;
		int64_t size;
		diskStats_t curDisk;
		curDisk.fd = open(fileName, O_RDWR | O_LARGEFILE);
		assert(curDisk.fd != -1);

		/* Let's verify that this file is actually a block device. We could support
		 * regular files, too, but we don't need to right now. */
		fstat(curDisk.fd, &buf);
		assert(S_ISBLK(buf.st_mode));

		/* Figure out the size of the underlying block device. */
		err = ioctl(curDisk.fd, BLKGETSIZE64, &size);
		assert(err != -1);
		DEBUGPRINTLN("The size of this device is " << size << " bytes.");
		this->size = size;
	}

	buseLODevice::~buseLODevice() { close(disks[0].fd); }

	template <class Function>
	uint32_t buseLODevice::handleTX(void *buf, uint32_t len, uint64_t offset, Function func) {
		int bytes_processed;

		lseek64(disks[0].fd, offset, SEEK_SET);
		while (len > 0) {
			bytes_processed = func(disks[0].fd, buf, len);
			assert(bytes_processed > 0);
			len -= bytes_processed;
			buf = (char *) buf + bytes_processed;
		}

		return 0;
	}

}
