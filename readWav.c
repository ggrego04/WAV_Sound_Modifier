/** @file  readWav.c
 *  @author Andreas Makris
 *	@date 21 Nov 2018
 *	@brief Contains a function that is responsible for
 *		reading a wav file, and stores it in the heap.
 * 		
 * Specifically, it gets as parameter the address of a wav
 * struct allocates memory for the header and the data segment
 * of the wav file and stores the header and the data segment in
 * the heap.
 *   
 */

/*
Copyright (C) 2018 Andreas Makris Gregory Gregoriades
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
Υou should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/



#include "wave.h"

public int readFile(char *filename,WAV *w){
	
	printf("filename: %s\n",filename);
	FILE *fp = fopen(filename,"rb");
	if(fp==NULL){
		printf("Can't open file.\n");
		return 1;
	}
	

	struct HEADER *h = (struct HEADER*)malloc(sizeof(struct HEADER));
	fread(h,sizeof(HEADER),1,fp);

	byte *data = (byte*)malloc(h->data_bytes);
	fread(data,sizeof(byte),h->data_bytes,fp);
	w->h=h;
	w->data=data;
	
	fclose(fp);
	return 0;
}
