#ifndef WAVE_H
#define WAVE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define private static
#define public 

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;


typedef struct HEADER{
    // RIFF Header
	byte riff_header[4]; // Contains "RIFF"
    dword wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
    byte wave_header[4]; // Contains "WAVE"
    
    // Format Header
    byte fmt_header[4]; // Contains "fmt " (includes trailing space)
    dword fmt_chunk_size; // Should be 16 for PCM
    word audio_format; // Should be 1 for PCM. 3 for IEEE Float
    word num_channels;
    dword sample_rate;
    dword byte_rate; // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
    word sample_alignment; // num_channels * Bytes Per Sample
    word bit_depth; // Number of bits per sample
    
    // Data
    byte data_header[4]; // Contains "data"
    dword data_bytes; // Number of bytes in data. Number of samples * num_channels * sample byte size
    // uint8_t bytes[]; // Remainder of wave file is bytes
}__attribute__((packed))HEADER;


typedef struct WAV{
	HEADER *h;
    byte* data;
}WAV;


/**
 *  @brief chops a wav file given a starting second and a finishing
 *
 *  This function takes a char* as parameter which represents 
 *	the name of the .wav file, as well as the seconds of the 
 *	starting and finishing chops from the command line. Costructs 
 *	the .wav file out of it and calculates the start, finish and
 *	size of the new wav file that is yet to be created. After the
 *	creation of the new wav file, the bytes within the starting
 *	and finishig chops are transfered from the original in the new wav file.
 *
 *	@param *filename the name of the .wav file we want to be chopped
 *	@param s the starting second of the chop
 *  @param f the finishing second of the chop
 *  @return errorcode Returns 0 if there is no error, otherwise return the errorcode.
 */
public int ChopTrack(char* filename,int s,int f);

/** @brief This function is called from the main and performs all the instructions
*			in order to encrypt the message in the wav file.
*			
* Opens the two files and calls the function to create the permutation
* table. Changes the least significant bit of the bytes 
* according to the permutation table and stores them in the new wav file.
*
* @param *wavfile The wav file that we want to encode the message in.
* @param *filename The text file that we want to encode its contents.
* @return errorcode Returns 0 if there is no error, otherwise returns the errorcode.
*/

public int encodeText(char *wavfile,char *filename);


/** @brief This function is called from encodeText and from decodeText
*			in order to create the same table which holds in which byte	
*			a bit of the text file was stored in the wav file.
*			
* Creates a table which holds the numbers from 0 to N. 
* Using a given number and N, does N swappings between the contents 
* of the table using a pseudorandom number generator algorithm.
* 
*
* @param N The size of the array that we want to shuffle.
* @param systemkey The number that was used to create pseudorandom numbers.
* @return table Returns the table which contains in which byte a bit of the text file
*		was stored in the wav file.
*/
public int* createPermutationFunction(int N, unsigned int systemkey);



/** @brief This function is called to output the header of a given wav file.
*			
* The function gets as parameter an address of a struct wav and prints on the 
* screen each field of the header of the wav file.
* 
*
* @param *w The address of the struct wav that we want to print its header.
* @return errorcode Returns 1 if the file doesn't exists, otherwise returns 0.
*/
public int PrintList(WAV* w);


/** @brief This function is called from the main and mixes two wav files.
*			
* Gets as parameters two wav files. Creates a new wav file which contains
* the right side of the first file and the left side of the second file.
* 
*
* @param *filename1 The name of the first wav file.
* @param *filename2 The name of the second wav file.
* @return errorcode Returns 1 if there was an error, otherwise returns 0.
*/
public int MixChannels(char* filename1,char* filename2);


/** @brief This function is called to read a wav file.
*			
* Furthermore, it allocates memory and stores the header and 
* the data segment of the wav file in the heap.
* 
*
* @param *filename The name of the wav file.
* @param *w The address of the struct wav.
* @return errorcode Returns 1 if there was an error, otherwise returns 0.
*/
public int readFile(char *filename,WAV *w);

/**
 *  @brief This function is called to make a file sound backwards
 *
 *  This function takes a char* as parameter from the command
 *	line, which represents the name of the .wav file. Costructs 
 *	the .wav file out of it and transfers the last bytes (4 by
 *	4) from the end of the file at the start of a new .wav file 
 *	reversing the sound. 
 *
 *	@param *filename the name of the .wav file we want to be reversed
 *  @return errorcode Returns 0 if there is no error, otherwise return the errorcode.
 */
public int ReverseTrack(char* filename);

/**  
 *  @brief This function is called to calculate the Euclidean distance
 *         between 2 wav files
 *
 *  This function calculates the Euclidean distance given two wav files.
 *	At first it calculates the smallest size of the two wav files. Then
 *  it starts a loop and performs the following equation for each of the
 *  bytes: sum=sum + |A[i]-B[i]|^2 .After the loop the square root of this
 *  number is calculated and printed out.
 *
 *	@param *f1 the first wav file
 *	@param *f2 the second wav file
 *  @return errorcode Returns 0 if there is no error, otherwise return the errorcode.
 */
public int EuclideanDistance(WAV* f1,WAV* f2);

/**
 *  @brief This function is called to calculate the Least Common SubSequence
 *         distance between 2 wav files
 *
 *  This function calculates the LCSS distance given two wav files.
 *	At first it creates two dwords with the size of the second file
 *  increased by one. Then, two loops check byte by byte the two files
 *  (the first byte of the first file with all the other bytes of the
 *  second, then the second byte of the first file with all the other
 *  bytes of the second etc.).If the two bytes are the same, the value
 *  of the first dword is equal with the value of the second dword in 
 *  the previous place increased by one (counter).If not, then the first
 *  dword is equal with the maximum between the current counter of the
 *  second dword and the previous of the first dword. Before the byte 
 *  of the first file changes, we swap the first dword with the second.
 *  In the end we take the final result of the first dword, we divide
 *  it with the smallest of the two wav files sizes and we substract it
 *  from number 1. FInally we print it out.
 *   
 *  @param *f1 The first wav file
 *  @param *f2 The second wav file
 *  @return errorcode Returns 0 if there is no error, otherwise return the errorcode.
 *
 */
public int LCSS( WAV *f1,WAV *f2);



/** @brief This function is called from the main and converts a stereo
*			wav file to mono.
*			
* Gets as parameters the stereo wav files and creates a new wav file with only
* the right side of the first file.
* 
*
* @param *filename The name of the first wav file.
* @return errorcode Returns 1 if there was an error, otherwise returns 0.
*/
public int ToMono(char* filename);


/** @brief This function is called from the main and performs all the instructions
*			in order to decrypt the message from the wav file.
*			
* Opens the wav file and calls the function to create the permutation
* table. According to the permutation table creates a new table that holds 
* the bits of the hidden message in correct order. In the end, converts 
* the bits to characters and writes the characters in a text file
*
* @param *wavfile The wav file that we want to decode the message from.
* @param msglength The number of the characters of the text file that we previoulsy encoded.
* @param *filename The name of the text file that we want to store the decoded message.
* @return errorcode Returns 0 if there is no error, otherwise returns the errorcode.
*/
public int decodeText(char *wavfile,int msglength,char *filename);

/**
 *  @brief This function is responsible of the construction of a wav file
 *
 *  @returns an empty wav file
 */
public WAV * ConstructWav();

/**
 *  @brief This function is called in order to make a wav file sound slower
 *
 *  This function takes a char* as parameter from the command
 *	line, which represents the name of the .wav file. Costructs 
 *	the .wav file out of it and divides the sample rate and
 *  byte rate by 2 so that it will become 2 times slower. It transfers
 *  the bytes from the original wav into a new one and saves it.
 *
 *  @param *filename the name of the wav file we want to slow down
 *  @return errorcode Returns 0 if there is no error, otherwise return the errorcode.
 */
public int SlowMotion(char *filename);

/**
 *  @brief This function is called in order to make a wav file sound faster
 *
 *  This function takes a char* as parameter from the command
 *	line, which represents the name of the .wav file. Costructs 
 *	the .wav file out of it and multiplies the sample rate and
 *  byte rate by 2 so that it will become 2 times faster. It transfers
 *  the bytes from the original wav into a new one and saves it.
 *
 *  @param *filename the name of the wav file we want to fast forward
 *  @return errorcode Returns 0 if there is no error, otherwise return the errorcode.
 */
public int FastForward(char *filename);


#endif
