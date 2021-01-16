/**
*@file wavengine.c
*@author Andreas Makris Gregory Gregoriades
*@date 21 Nov 2018
*@brief Contains the main function that calls other functions 
*		to create or modify wav files.
*
*To compile the program you have to make sure that the  
*Makefile is in the same folder with the .c files. Then
*you hit make and the program is compiled and the executable 
*name is as4.
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

/** @brief The main function of the program*
*
* This function is only called when the executable file executes.
* Provides the user interface and according to the optrions of the user
* calls the right functions to complete the requested tasks.
*
* @param argc The number of the arguments that the user has entered.
* @param *argv[] An array which holds the arguments that the user has entered.
* @return errorcode Returns 1 if there was a problem, otherwise 0.
*/
int main(int argc,char* argv[]){
    
	printf("\as4 Copyright (C) 2018 Andreas Makris Gregory Gregoriades\n");
	printf("This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n");
	printf("This is free software, and you are welcome to redistribute it\n");
	printf("under certain conditions; type `show c' for details.\n\n\n");
	

    int starting_chop;
    int finishing_chop;
    int i;
    struct WAV *w;
	struct WAV *x;
	
	if (argc<2){
		printf("Wrong input! Use one of the following options:\n");
		printf("<-list>\n");
		printf("<-mono>\n");
		printf("<-mix>\n");
		printf("<-chop>\n");
		printf("<-reverse>\n");
		printf("<-similarity>\n");
		printf("<-encodeText>\n");
		printf("<-decodeText>\n");
		printf("<-slow>\n");
		printf("<-fastForward>\n");
		exit(-1);
	}

    if(strcmp(argv[1],"-list")==0){
        if(argc<3){
        	printf("TYPE: ./<executable> <-list> <filename>\n");
		    return 1;
        }
        for(i=2;i<argc;i++){
          w=ConstructWav();
          int error = readFile(argv[i],w);
          if (error==1)
			  return 1;
		  PrintList(w);
		  free(w->h);
		  free(w->data);
		  free(w);
        } 
		
                
    }else if(strcmp(argv[1],"-mono")==0){
        if(argc<3){
        	printf("TYPE: ./<executable> <-mono> <filename>\n");
		    return 1;
        }
        
        for(i=2;i<argc;i++){          
          ToMono(argv[i]);
        }       
    }else if(strcmp(argv[1],"-mix")==0){
        if(argc!=4){
          printf("Wrong input!\nTYPE: ./<executable> <-mix> <filename1> <filename2>\n\n");
          return 1;
        }
        MixChannels(argv[2],argv[3]);
                
    }else if(strcmp(argv[1],"-chop")==0){
        if(argc!=5){
          printf("Wrong input!\nTYPE: ./<executable> <-chop> <filename> <starting chop> <finishing chop>\nStarting chop number must be lower than finishing and within audio input bounds!\n");
          return 1;
        } 
        starting_chop=atoi(argv[3]);
        finishing_chop=atoi(argv[4]);
        ChopTrack(argv[2],starting_chop,finishing_chop); 
                
    }else if(strcmp(argv[1],"-reverse")==0){
        if(argc<3){
        	printf("TYPE: ./<executable> <-reverse> <filename>\n");
		    return 1;
        }
        for(i=2;i<argc;i++){
          ReverseTrack(argv[i]);
        } 
                
                
    }else if(strcmp(argv[1],"-similarity")==0){
        if(argc<4){
        	printf("TYPE: ./<executable> <-similarity> <filename1> <filename2>\n");
		    return 1;
        }
		w=ConstructWav();
		readFile(argv[2],w);
        for(i=3;i<argc;i++){
			x=ConstructWav();
			readFile(argv[i],x);
        	EuclideanDistance(w,x); 
			LCSS(w,x);		
        }
		
		free(w->h);
		free(w->data);
		free(w);
 
		free(x->h);
		free(x->data);
		free(x);
		
    }else if(strcmp(argv[1],"-encodeText")==0){
        if(argc!=4){
          printf("TYPE: ./<executable> <-encodeText> <Wavfile> <Textfile>\n");
          return 1;
        }
        encodeText(argv[2],argv[3]);
		
    }else if(strcmp(argv[1],"-decodeText")==0){
        if(argc!=5){
          printf("TYPE: ./<executable> <-decodeText> <Wavfile> <MessageLength> <Textfile>\n");
          return 1;
        } 
		int length = atoi(argv[3]);
		
		decodeText(argv[2],length,argv[4]);        
    }else if(strcmp(argv[1],"-slow")==0){
        if(argc<3){
            printf("TYPE: ./<executable> <-slow> <filename>\n");
		    return 1;
        }
        for(i=2;i<argc;i++){
          SlowMotion(argv[i]);

        } 
                
    }else if(strcmp(argv[1],"-fastForward")==0){
        if(argc<3){
            printf("TYPE: ./<executable> <-fastForward> <filename>\n");
			return 1;
        }
        for(i=2;i<argc;i++){
          FastForward(argv[i]);
        }
    }else{
      printf("Option not available! Use one of the following options:\n");
		printf("<-list>\n");
		printf("<-mono>\n");
		printf("<-mix>\n");
		printf("<-chop>\n");
		printf("<-reverse>\n");
		printf("<-similarity>\n");
		printf("<-encodeText>\n");
		printf("<-decodeText>\n");
		printf("<-slow>\n");
		printf("<-fastForward>\n");
		return 1;
    }     

    return 0;   
}               
