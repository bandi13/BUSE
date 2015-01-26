/*
 * loopback - example loopback device using BUSE
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
#include <iostream>
#include <unistd.h>

#include "buseLODevice.h"
#include "buse.h"
using namespace buse;
using namespace std;

static void usage(void) {
	cerr << "Usage: loopback <phyical device> <virtual device>" << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		usage();
		return -1;
	}

	buseLODevice bop(argv[1]);

	buse_main(argv[2], &bop, NULL);

	return 0;
}
