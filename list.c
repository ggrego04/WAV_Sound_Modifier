/** @file  list.c
 *  @author Andreas Makris
 *	@date 21 Nov 2018
 *	@brief Contains a function that is responsible for
 *		displaying the header of the wav file on the screen.
 * 		
 * Specifically, it gets as parameter the address of a wav
 * struct and outputs each field of the header of the struct.
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


public int PrintList(WAV* w){
  if(w==NULL){
    printf("File doesn't exist\n");
    return 1;
  }
  printf("RIFF_CHUNK_HEADER\n");
	printf("=================\n");
	printf("chunkID:%c%c%c%c\n",w->h->riff_header[0],w->h->riff_header[1],w->h->riff_header[2],w->h->riff_header[3]);
	printf("chunkSize: %d\n",w->h->wav_size);
	printf("format: %c%c%c%c\n",w->h->wave_header[0],w->h->wave_header[1],w->h->wave_header[2],w->h->wave_header[3]);
	printf("\nFMT_SUBCHUNK_HEADER\n");
	printf("=====================\n");
	printf("subChunk1ID: %c%c%c%c\n",w->h->fmt_header[0],w->h->fmt_header[1],w->h->fmt_header[2],w->h->fmt_header[3]);
	printf("subChunk1Size: %d\n",w->h->fmt_chunk_size);
	printf("audioFormat: %u\n",w->h->audio_format);
	printf("numChannels: %u\n",w->h->num_channels);
	printf("sampleRate: %d\n",w->h->sample_rate);
	printf("byteRate: %d\n",w->h->byte_rate);
	printf("blockAlign: %u\n",w->h->sample_alignment);
	printf("bitsPerSample: %u\n",w->h->bit_depth);
	printf("\nDATA_SUBCHUNK_HEADER\n");
	printf("=====================\n");
	printf("subChunk2ID: %c%c%c%c\n",w->h->data_header[0],w->h->data_header[1],w->h->data_header[2],w->h->data_header[3]);
	printf("subChunk2Size: %d\n",w->h->data_bytes);
	printf("\n----------------------------------\n\n"); 
  return 0;
}
