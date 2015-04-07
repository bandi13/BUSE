/*
 * Copyright (C) 2015 Andras Fekete
 *
 * This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include "buseLODevice.h"
#include "buseRAMDevice.h"
#include "buse.h"

#include <iostream>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

using namespace buse;
using namespace std;

// Global variable containing the currently operating BUSE level
buseOperations *bop;

static void usage(char *progName) {
	cout << "Usage: " << progName << " <type> <physical device>* <virtual device>" << endl;
	cout << "type => (LO | RAM) <type options>*" << endl;
	cout << "RAM type options:" << endl;
	cout << "\t-s <size> => size of the array in bytes" << endl;
}

int main(int argc, char *argv[]) {
	int opt;

	bop = NULL; // Initialize to something benign

	if(argc < 3) { usage(argv[0]); return -1; }

	optind = 2; // ignore first two arguments
	if (strcmp(argv[1], "LO") == 0) {
		bop = new buseLODevice(argv[2]);
	} else if (strcmp(argv[1], "RAM") == 0) {
		int size = 128 * 1024 * 1024;
		while ((opt = getopt(argc, argv, "s:")) != -1) {
			switch (opt) {
				case 's':
					size = atol(optarg);
					break;
				default:
					cerr << "Unknown error." << endl;
					usage(argv[0]);
					return -1;
			}
		}
		bop = new buseRAMDevice(size);
	}

	DEBUGPRINTLN("Writing to: " << argv[argc - 1] << " diskSize=" << bop->getSize());
	return buse_main(argv[argc - 1], bop);
}
