/*
 * project_main.c


 *
 * Created by Jeremy Venegas and Clyde Saligumba
 *
 * Fall 2025
 * ECE 266
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include "launchpad.h"
#include "seg7.h"
#include "pushbutton.h"
#include "music.h"

// Game limit
#define MAX_SEQUENCE 20

// game setting
typedef struct
{
    int sequence[MAX_SEQUENCE];
    int length;
    int player_index;
    bool playing_sequence;
} GameState;

GameState game;
Seg7Display display = { {0, 0, 0, 0}, false }; // prep seg7

/***********************************************************************
 * starting setting for the game
 *
 **********************************************************************/
void init_game()
{
    game.length = 1;
    game.player_index = 0;
    game.playing_sequence = false;
    int i;
    // use the rand function to generate random sequence
    for (i = 0; i < MAX_SEQUENCE; i++)
    {
        game.sequence[i] = rand() % 4;
    }
}

/***********************************************************************
 * increment seg 7 for every played turn
 *
 * this defines what level the player is on
 *
 **********************************************************************/
void update_display()
{
    display.digit[0] = game.length % 10;
    display.digit[1] = game.length / 10;
    display.digit[2] = 0;
    display.digit[3] = 0;
    Seg7Update(&display);
}


/***********************************************************************
 * to ensure the buzzer timing works, play one note at a time.
 *
 * plays when game is playing the sequence and when the player presses
 * a button
 *
 **********************************************************************/
void play_note(int note)
{
    MusicSetBuzzer(note, 1);  // This will play and return automatically
}



/***********************************************************************
 * game response for the player
 *
 * generates the turn value and next note in the
 * sequence for player input
 *
 **********************************************************************/

void play_sequence()
{
    //ready to play
    game.playing_sequence = true;
    int i;

    //start loop for tone sequence
    for ( i = 0; i < game.length; i++)
    {
        // Show which number in the sequence
        display.digit[0] = (i + 1) % 10;
        display.digit[1] = (i + 1) / 10;
        Seg7Update(&display);

        // Play the note
        play_note(game.sequence[i]);

        // Brief pause between notes for player to memorize
        if (i < game.length - 1)
        {
            SysCtlDelay(SysCtlClockGet() / 10); // Short pause from internal clock
        }
    }

    // Reset display to show level
    update_display();
    game.playing_sequence = false;
}


/***********************************************************************
 * user inputs
 *
 *
 **********************************************************************/
void handle_button(Button button)
{
    if (game.playing_sequence)
        {
        return;
        }

    int note = -1;
    switch (button) {

        case BUTTON_UP:
            note = 0;
            break;

        case BUTTON_DOWN:
            note = 1;
            break;

        case BUTTON_LEFT:
            note = 2;
            break;

        case BUTTON_RIGHT:
            note = 3;
            break;

        default: return;
    }

    // Play button tone for player
    play_note(note);

    // Check if correct
    if (note == game.sequence[game.player_index])
    {
        game.player_index++;

        if (game.player_index >= game.length)
        {

            // Level complete - increase difficulty
            if (game.length < MAX_SEQUENCE)
            {
                game.length++;
            }
            game.player_index = 0;
            update_display();

            // Play next sequence after delay
            SysCtlDelay(SysCtlClockGet() / 4);
            play_sequence();
        }
    }
    else
    {
        // Wrong note - game over and restart
        init_game();
        update_display();
        SysCtlDelay(SysCtlClockGet() / 4);
        play_sequence();
    }
}


/***********************************************************************
 * Main function
 *
 * includes initializations and game function call loops
 *
 *
 **********************************************************************/
int main()
{
    // Initialize everything
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    LaunchPadInit();
    Seg7Init();
    PushButtonsInit();
    MusicInitBuzzer();

    srand(SysCtlClockGet());
    init_game();
    update_display();

    // Start the first sequence after a brief delay for player prep
    SysCtlDelay(SysCtlClockGet() / 2);
    play_sequence();


    // Infinite loop to never stop playing unless power is removed LOL

    while (1)
    {
        //check if player started
        Button pressed = PushButtonsGetPressed();
        if (pressed != BUTTON_NONE)
        {
            handle_button(pressed); //check if they lose!!

            // wait for button release to not mix signals
            while (PushButtonsGetPressed() != BUTTON_NONE)
            {
                SysCtlDelay(SysCtlClockGet() / 1000);
            }
            SysCtlDelay(SysCtlClockGet() / 100);
        }

        // fix to ensure correct timing
        SysCtlDelay(SysCtlClockGet() / 1000);
    }
}
