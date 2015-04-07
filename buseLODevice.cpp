/*
 * buseLODevice.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */
#include "buseLODevice.h"

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
		fd = open(fileName, O_RDWR | O_LARGEFILE);
		assert(fd != -1);

		/* Let's verify that this file is actually a block device. We could support
		 * regular files, too, but we don't need to right now. */
		fstat(fd, &buf);
		assert(S_ISBLK(buf.st_mode));

		/* Figure out the size of the underlying block device. */
		err = ioctl(fd, BLKGETSIZE64, &size);
		assert(err != -1);
		DEBUGPRINTLN("The size of this device is " << size << " bytes.");
		this->size = size;
	}

	buseLODevice::~buseLODevice() { close(fd); }

	uint32_t buseLODevice::read(void* buf, uint32_t len, uint64_t offset) {
		int bytes_read;
		buseOperations::read(buf, len, offset);

		lseek64(fd, offset, SEEK_SET);
		while (len > 0) {
			bytes_read = ::read(fd, buf, len);
			assert(bytes_read > 0);
			len -= bytes_read;
			buf = (char *) buf + bytes_read;
		}

		return 0;
	}

	uint32_t buseLODevice::write(const void* buf, uint32_t len, uint64_t offset) {
		int bytes_written;
		buseOperations::write(buf, len, offset);

		lseek64(fd, offset, SEEK_SET);
		while (len > 0) {
			bytes_written = ::write(fd, buf, len);
			assert(bytes_written > 0);
			len -= bytes_written;
			buf = (char *) buf + bytes_written;
		}

		return 0;
	}
}
