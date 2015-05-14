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
		int fd;
		fd = open(fileName, O_RDWR | O_LARGEFILE);
		assert(fd != -1);

		/* Let's verify that this file is actually a block device. We could support
		 * regular files, too, but we don't need to right now. */
		fstat(fd, &buf);
		assert(S_ISBLK(buf.st_mode));

		disks.push_back(diskStats(fd));
		this->size = disks.back().getSize();
		DEBUGPRINTLN("The size of this device is " << this->size << " bytes.");
	}

	buseLODevice::~buseLODevice() { close(disks[0].getFD()); }

	int buseLODevice::handleTX(void *buf, size_t len, off64_t offset, ssize_t (*func)(int, void *, size_t)) {
		ssize_t bytes_processed;

		DEBUGPRINTLN("handleTX(" << len << ',' << offset << ')' << endl);
		lseek64(disks[0].getFD(), offset, SEEK_SET);
		while (len > 0) {
			bytes_processed = func(disks[0].getFD(), buf, len);
			assert(bytes_processed > 0);
			len -= bytes_processed;
			buf = (char *) buf + bytes_processed;
		}

		return 0;
	}

}
