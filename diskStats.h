//
// Created by andras on 5/6/15.
//

#ifndef DISKSTATS_H
#define DISKSTATS_H

#include "commonIncludes.h"
#include <chrono>
#include <aio.h>

class diskStats {
public:
	diskStats(int fd);
	diskStats(int fd, std::chrono::duration<double, std::micro> writeSpeed, std::chrono::duration<double, std::micro> readSpeed);

	int getFD() { return aiocb.aio_fildes; }
	uint64_t getSize() { return diskSize; }

	void testSpeed();
	// The buffers all have to be of size bufSiz.
	void testSpeed(char *buf0, char *buf1, char *buf2, const char *buf3, const uint64_t bufSiz);
	std::chrono::duration<double, std::micro> getWriteSpeed() { return writeSpeed; }
	std::chrono::duration<double, std::micro> getReadSpeed() { return readSpeed; }

	int aio_read(void *buf, uint32_t len, off64_t offset);
	int aio_write(const void *buf, uint32_t len, off64_t offset);
	ssize_t aio_return();
	int aio_error();
	ssize_t read(void *buf, uint32_t len, off64_t offset);
	ssize_t write(const void *buf, uint32_t len, off64_t offset);

private:

	uint64_t diskSize;
	std::chrono::duration<double, std::micro> writeSpeed;
	std::chrono::duration<double, std::micro> readSpeed;
	::aiocb64 aiocb;
};

#endif //DISKSTATS_H
