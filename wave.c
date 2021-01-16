/** @file  wave.c
 *  @author Gregory Gregoriades
 *	@date 21 Nov 2018
 *	@brief This .c file contains a function called ConstructWav
 *		   which is responsible to create an empty .wav file
 *  	   and return it.
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

public WAV * ConstructWav(){
   struct WAV *w = (struct WAV*)malloc(sizeof(struct WAV));
	 if(w==NULL){
	   printf("could not allocate memory for WAV\n");
	   exit(-1);
   }
   return w;
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


