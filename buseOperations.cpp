/*
 * buseOperations.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: andras
 */
#include "buseOperations.h"
#include <chrono>
#include <iostream>
using namespace std;

namespace buse {
	buseOperations::buseOperations() { this->size = 0; }
	buseOperations::buseOperations(uint64_t size) { this->size = size; }

	buseOperations::~buseOperations() {
		DEBUGPRINTLN("Destroying buse object.");
		while(!disks.empty()) {
			close(disks.back()->fd);
			delete disks.back();
			disks.pop_back();
		}
	}

	uint64_t buseOperations::getSize() { return size; }

	uint32_t buseOperations::read(void *buf, uint32_t len, uint64_t offset) {
		UNUSED(buf); UNUSED(len); UNUSED(offset);
		DEBUGPRINTLN("R - " << offset << ", " << len);
		return buseOperations::handleTX(buf,len, offset,::read);
	}

	uint32_t buseOperations::write(const void *buf, uint32_t len, uint64_t offset) {
		UNUSED(buf); UNUSED(len); UNUSED(offset);
		DEBUGPRINTLN("W - " << offset << ", " << len);
		return buseOperations::handleTX((void*)buf,len, offset,::write);
	}

	template <class Function>
	uint32_t buseOperations::handleTX(void *buf, uint32_t len, uint64_t offset, Function func) {
		UNUSED(buf); UNUSED(len); UNUSED(offset); UNUSED(func);
		DEBUGPRINTLN("H - " << offset << ", " << len);
		return 0;
	}

	void buseOperations::disc() { DEBUGPRINTLN("Received a disconnect request."); }

	uint32_t buseOperations::flush() {
		DEBUGPRINTLN("Received a flush request.");
		for(uint i = 0; i < this->disks.size(); i++) ::syncfs(disks[i]->fd);
		return 0;
	}

	uint32_t buseOperations::trim(uint64_t from, uint32_t len) {
		UNUSED(from); UNUSED(len);
		DEBUGPRINTLN("T - " << from << ", " << len);
		return 0;
	}

#define READBYTESSIZE (128*1024*1024)
	void buseOperations::testDiskSpeed() {
		auto startTime = chrono::system_clock::now();
		char **buf = (char **) malloc(sizeof(char *) * 4);
		buf[0] = (char *) malloc(sizeof(char) * READBYTESIZE);
		buf[1] = (char *) malloc(sizeof(char) * READBYTESIZE);
		buf[2] = (char *) malloc(sizeof(char) * READBYTESIZE);
		buf[3] = (char *) malloc(sizeof(char) * READBYTESIZE);
		for(uint i = 0; i < READBYTESSIZE; i++) { buf[3][i] = 0xA5; }
		for(uint i = 0; i < disks.size(); i++) {
			if(disks[i]->diskSize < 2*READBYTESSIZE) {
				disks[i]->readSpeed = chrono::duration<double>().zero();
				disks[i]->writeSpeed = chrono::duration<double>().zero();
				continue;
			}
			startTime = chrono::system_clock::now();
			lseek64(disks[i]->fd, 0, SEEK_SET);
			::read(disks[i]->fd,&buf[0],READBYTESSIZE);
			lseek64(disks[i]->fd, disks[i]->diskSize / 2, SEEK_SET);
			::read(disks[i]->fd,&buf[1],READBYTESSIZE);
			lseek64(disks[i]->fd, disks[i]->diskSize - READBYTESSIZE, SEEK_SET);
			::read(disks[i]->fd,&buf[2],READBYTESSIZE);
			disks[i]->readSpeed = chrono::system_clock::now() - startTime;
			startTime = chrono::system_clock::now();
			lseek64(disks[i]->fd, 0, SEEK_SET);
			::write(disks[i]->fd,&buf[4],READBYTESSIZE);
			lseek64(disks[i]->fd, disks[i]->diskSize / 2, SEEK_SET);
			::write(disks[i]->fd,&buf[4],READBYTESSIZE);
			lseek64(disks[i]->fd, disks[i]->diskSize - READBYTESSIZE, SEEK_SET);
			::write(disks[i]->fd,&buf[4],READBYTESSIZE);
			disks[i]->writeSpeed = chrono::system_clock::now() - startTime;
			lseek64(disks[i]->fd, 0, SEEK_SET);
			::write(disks[i]->fd,&buf[0],READBYTESSIZE);
			lseek64(disks[i]->fd, disks[i]->diskSize / 2, SEEK_SET);
			::write(disks[i]->fd,&buf[1],READBYTESSIZE);
			lseek64(disks[i]->fd, disks[i]->diskSize - READBYTESSIZE, SEEK_SET);
			::write(disks[i]->fd,&buf[2],READBYTESSIZE);
		}
		free(buf[0]); free(buf[1]); free(buf[2]); free(buf[3]);
		free(buf);
	}
}
