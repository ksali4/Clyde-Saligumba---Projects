/*
 * music.h
 *
 * Created by Jeremy Venegas and Clyde Saligumba
 *
 * Fall 2025
 * ECE 266
 *

 */


#ifndef MUSIC_H_
#define MUSIC_H_
#include <stdint.h>
#define NUM_PITCH 4
#define NUM_VOLUME_LEVEL 3


// initialize the buzzer
void MusicInitBuzzer();

// set the buzzer volume and pitch
void MusicSetBuzzer(int pitch, int volume);

//turn off the buzzer
void MusicTurnOffBuzzer();

#endif /* MUSIC_H_ */
