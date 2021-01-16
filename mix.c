/** @file  mix.c
 *  @author Andreas Makris
 *	@date 21 Nov 2018
 *	@brief Contains a function that is responsible for
 *		mixing two wav files together.
 * 		
 * Specifically, it gets the sound from the right side of the
 * first file and merges it with the left side of the second
 * file.
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



public int MixChannels(char* filename1,char* filename2){

	WAV *f1=ConstructWav();
	int error = readFile(filename1,f1);
	if (error==1)
		return 1;
	
	WAV *f2=ConstructWav();
	error =readFile(filename2,f2);
	if(error==1)
		return 1;

	WAV *temp;
	int swap =0;
	if((f2->h->wav_size)<(f1->h->wav_size)){
		temp=f1;
		f1=f2;
		f2=temp;
		swap=1;
	}
    struct HEADER *h = (struct HEADER*)malloc(sizeof(struct HEADER));

    if((f1==NULL)||(f2==NULL)){
      printf("The files don't exist!");
      return 1;
    }
	
	strcpy((char *)h->riff_header,(const char *) f1->h->riff_header);
	strcpy((char *)h->wave_header, (const char *) f1->h->wave_header);
	strcpy((char *)h->fmt_header, (const char *) f1->h->fmt_header);
	h->fmt_chunk_size=(f1->h->fmt_chunk_size);
	h->audio_format = f1->h->audio_format;
	h->num_channels=f1->h->num_channels;
	h->sample_rate = f1->h->sample_rate;
	h->byte_rate=(f1->h->sample_rate)*(f1->h->num_channels)*(f1->h->bit_depth)/8;

	h->sample_alignment=(f1->h->num_channels)*(f1->h->bit_depth)/8;
	h->bit_depth = f1->h->bit_depth;
 
	strcpy((char *)h->data_header,  (const char *)f1->h->data_header);

	h->data_bytes=f1->h->data_bytes;

    h->wav_size=(f1->h->wav_size);  
   
	byte *data = (byte*)malloc(h->data_bytes);	

	struct WAV *w = (struct WAV*)malloc(sizeof(struct WAV));	
	w->h=h;  
	  
	if (swap==1){
		temp=f1;
		f1=f2;
		f2=temp;	
	}
	int i=0;
	for(i=0;i<(h->data_bytes);i+=4){

		data[i]=f2->data[i];
		data[i+1]=f2->data[i+1];
		data[i+2]=f1->data[i+2];
		data[i+3]=f1->data[i+3];
	}
           
	w->data=data;

	
//	PrintList(w);
	
	char newfile[512];
	strcpy(newfile,"mix-");
	printf("returned\n");
	strcat(newfile,filename1);
	char newfile2[512];
	strcpy(newfile2,"-");
	strcat(newfile2,filename2);
	strcat(newfile,newfile2);
	FILE* f=fopen(newfile,"wb");

	fwrite(w->h,sizeof(struct HEADER),1,f);
	fwrite(data,sizeof(w->h->data_bytes),w->h->data_bytes,f);
	
	fclose(f);
	free(f1->h);
	free(f1->data);
	free(f2->h);
	free(f2->data);
	free(h);
	free(data);
	free(w);
	free(f1);
	free(f2);

    return 0;
}
