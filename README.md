# WAV Sound Modifier

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Demonstration](#demonstration)
* [Use](#use)

## General info
A standalone platform capable of hosting Quantum Computing experiments of different levels using Qiskit resources.

## Technologies
Technologies and Frameworks used for this project:
* C

## Demonstration
This program can modify wav files

## Use
File wavengine.c :

This is the main function of the program. It's where the necessary methods are called in order to read, construct and edit a .wav file. We are able to edit a file by typing in the command line ./as4 <-option> <filename.wav> , where <-option> can be one of the following:
<-list>
<-mono>
<-mix>
<-chop>
<-reverse>
<-similarity>
<-encodeText>
<-decodeText>
<-slow>
<-fastForward>


File wave.c :

This is the function responsible for the construction of an empty wav file. It is called inside almost every function.

File reverse.c :

This function takes a string as parameter from the command line, which represents the name of the .wav file. It costructs the .wav file out of it and transfers the last bytes (4 by 4) from the end of the file at the start of a new .wav file reversing the sound.  We can enter more than one files here.
In order to call this function we type :
./as4 -reverse <filename.wav>

File chop.c :

This function takes a string as parameter which represents the name of the .wav file, as well as the seconds of the starting and finishing chops from the command line. Costructs the .wav file out of it and calculates the start, finish and size of the new wav file that is yet to be created. After the creation of the new wav file, the bytes within the starting and finishig chops are transfered from the original in the new wav file.
We can't enter more than one files here.
In order to call this function we type :
./as4 -chop <filename.wav> <starting second (ex.2)> <finishiing second (ex.4)> 


File ff.c :

This function takes a string as parameter from the command line, which represents the name of the .wav file. Costructs the .wav file out of it and multiplies the sample rate and byte rate by 2 so that it will become 2 times faster. It transfers the bytes from the original wav into a new one and saves it. We can enter more than one files here.
In order to call this function we type:
./as4 -fastForward <filename.wav>


File slow.c :

This function takes a string as parameter from the command line, which represents the name of the .wav file. Costructs the .wav file out of it and divides the sample rate and byte rate by 2 so that it will become 2 times slower. It transfers the bytes from the original wav into a new one and saves it. We can enter more than one files here.
In order to call this function we type:
./as4 -slow <filename.wav>


File similarity.c :

This function calculates the Euclidean Distance and the Least Common SubSequence (LCSS) distance.
To calculate the Euclidean distance first we give two wav files. Then it calculates the smallest size of the two wav files. Then it starts a loop and performs the following equation for each of the bytes: 
sum=sum + |A[i]-B[i]|^2 .After the loop the square root of this number is calculated and printed out.
To calculate the LCSS distance first it takes the same files as the Euclidean distance.Then it creates two dwords with the size of the second file increased by one. Then, two loops check byte by byte the two files (the first byte of the first file with all the other bytes of the second, then the second byte of the first file with all the other bytes of the second etc.).If the two bytes are the same, the value of the first dword is equal to the value of the second dword in the previous place increased by one (counter).If not then the first dword is equal with the maximum between the current counter of the second dword and the previous place of the first dword. Before the byte of the first file changes, we swap the first dword with the second. In the end we take the final result of the first dword, we divide it with the smallest of the two wav files sizes and we substract it from number 1. FInally we print it out. We can enter more than one files here but each distance is calculated given the first file with each of the rest.
In order to call this function we type:
./as4 -similarity <filename1.wav> <filename2.wav>

File list.c:

Contains a function that is responsible for displaying the header of the wav 
file on the screen. Specifically, it gets as parameter the address of a wav
struct and outputs each field of the header of the struct.
In order to call this function we type:
./as4 -list <filename1.wav> 

File StereoToMono.c:

Contains a function that is responsible for	converting a stereo wav file to a mono wav file.
Specifically, it gets as parameter the address of a wav struct and creates a new wav file 
without the right samples of the first wav file.
In order to call this function we type:
./as4 -mono <filename1.wav> 

File mix.c:

Contains a function that is responsible for mixing two wav files together.
Specifically, it gets the sound from the right side of the first file and 
merges it with the left side of the second file.
In order to call this function we type:
./as4 -mix <filename1.wav> <filename2.wav>

File readWav.c:

Contains a function that is responsible for reading a wav file, and stores it in the heap.
Specifically, it gets as parameter the address of a wavstruct allocates memory for the 
header and the data segment of the wav file and stores the header and the data segment in
the heap.
This function is only called by other functions.

File encryption.c:

Contains the functions that are responsible for the encryption of a text messages in a wav file.
Includes 3 functions: encodeText, getBit and createPermutationFunction.
In order to call this function we type:
./as4 -encodeText <Wavfile> <Textfile>

File decryption.c:

Contains the function that is responsible for the decryption of a text message from a wav file.
Includes the function decodeText which is responsible open the wav file, create the 
permutation table, decode the text message, and create a text file
which contains the hidden message.
In order to call this function we type:
./<executable> <-decodeText> <Wavfile> <MessageLength> <Textfile>
