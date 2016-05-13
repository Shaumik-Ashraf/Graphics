//mks_png.h

//allow DIRECT creation of png files
//No more imagyck required

#ifndef _MKS_PNG_H_
#define _MKS_PNG_H_

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

#include"ml6.h"
#include"draw.h"

/* png data is stored in chunks,
 * similar to packets in networking
 */

//there are different types of chunks
#define CHUNK_HDR 0
#define CHUNK_IDAT 1
#define CHUNK_END 2

struct png_chunk {
	int type;
	unsigned int len;  //size of data
	void* data;
	unsigned int crc;  //checksum
}

const char** CHUNK_NAMES {
	{'I', 'H', 'D', 'R'},
	{'I', 'D', 'A', 'T'},
	{'I', 'E', 'N', 'D'}
}

extern struct png_chunk* new_chunk(int chunk_type, screen s);
extern void save_png(char* filename, screen s);

#endif
