/* Test program created by: Fekete, Andras
	 This program writes a set of random byte sequences in random locations on
	 the nbd disk and then reads them back to make sure they're correctly written.
	 */
#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

using namespace std;

#define MYBUFSIZ 2000
#define LOCCNT 1000
int doPass(int fd, char c, uint64_t maxLoc) {
	char buf[MYBUFSIZ];
	uint64_t locs[LOCCNT];

	for(int i = 0; i < MYBUFSIZ; i++) buf[i] = i+c;
	cout << "Starting test of char=" << c<< " with filesize=" << maxLoc << endl;
	maxLoc -= MYBUFSIZ; // make sure we don't accidentally try to write off the end of the file
	locs[0] = 0; // make sure we get the beginning
	locs[LOCCNT - 1] = maxLoc; // make sure we get the end
	for(int i = 1; i < LOCCNT - 1; i++) {
		locs[i] = (((float)rand() / RAND_MAX) * (maxLoc - locs[i-1] - MYBUFSIZ)) / ((LOCCNT - 2)/4) + locs[i-1] + MYBUFSIZ; // set up the location to be written relative to the last one
	}
	for(int i = 0; i < LOCCNT; i++) {
//		cout << i << ": Writing to " << locs[i] << endl;
		lseek64(fd,locs[i],SEEK_SET);
		if(write(fd,buf,MYBUFSIZ) != MYBUFSIZ) { cerr << "Didn't complete a write of " << MYBUFSIZ << " * '" << c << "' at " << locs[i] << " because " << strerror(errno) << endl; return -1; }
	}
	for(int i = 0; i < LOCCNT; i++) {
//		cout << i << ": Reading from " << locs[i] << endl;
		lseek64(fd,locs[i],SEEK_SET);
		if(read(fd,buf,MYBUFSIZ) != MYBUFSIZ) { cerr << "Didn't complete a read of " << MYBUFSIZ << " * '" << c << "' at " << locs[i] << " because " << strerror(errno) << endl; return -2; }
		for(int j = 0; j < MYBUFSIZ; j++)
			if(buf[j] != (char)(j+c)) {
				cerr << "Verification of write/read failed at location " << locs[i] << ", offset=" << j << endl;
				cerr << "  expected=";
				for(int k = 0; k < MYBUFSIZ; k++) cerr << (int)(char)(k+c) << ',';
				cerr << endl;
				cerr << "       got=";
				for(int k = 0; k < MYBUFSIZ; k++) cerr << (int)buf[k] << ',';
				cerr << endl;
				return -3;
			}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	int fd;
	uint64_t diskSize = 0;
	fd = open("/dev/nbd0",O_RDWR|O_LARGEFILE);
	if(fd == -1) {
		cerr << "Error opening file" << endl;
		return 0;
	}
	if(argc == 2) { diskSize = atol(argv[1]); cout << "Setting DiskSize=" << diskSize << endl; }
  if(diskSize == 0) {
		struct stat fd_stat;
		if(fstat(fd,&fd_stat)) { cerr << "Error getting the stats on the file: " << strerror(errno) << endl; return -1; }
    if(S_ISBLK(fd_stat.st_mode)) {
      ioctl(fd,BLKGETSIZE64, &diskSize);
    } else {
      cout << "File stats: blksize=" << fd_stat.st_blksize << " blkcnt=" << fd_stat.st_blocks << endl;
      diskSize = fd_stat.st_blksize * fd_stat.st_blocks;
    }
  }

	if(diskSize == 0) { cerr << "DiskSize==0, we can't deal with that." << endl; return -1; }
  cout << "Running test with diskSize=" << diskSize << endl;
	if(doPass(fd,'a',diskSize)) { cerr << "Failed a test" << endl; return -1; }
	if(doPass(fd,'b',diskSize)) { cerr << "Failed a test" << endl; return -1; }
	if(doPass(fd,'c',diskSize)) { cerr << "Failed a test" << endl; return -1; }
	cout << "Test completed" << endl;
	return 0;
}
