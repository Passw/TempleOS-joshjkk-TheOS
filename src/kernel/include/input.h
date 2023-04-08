#ifndef INPUT_H
#define INPUT_H

#define INPUT_DELAY 120 // ms

#define INPUT_BUF_TICKS 1 /* Stop the buffer filling up straight away, 
						   * if the same key is pressed twice, 
						   * wait an amount of ticks (INPUT_DELAY * TICKS)ms to decide 
						   * if the user actually wanted to press that key */

char getchar();

#endif /* INPUT_H */
