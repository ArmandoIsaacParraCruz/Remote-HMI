#include "keyboard.h"

char Keyboard::get_valid_key(std::vector<char>& validKeys)
{
    char keyPressed = NO_KEY;
    // Wait for a key press
    while (keyPressed == NO_KEY) {
        keyPressed = keypad.getKey();
        for(char& validKey: validKeys) {
            if(keyPressed == validKey) {
                break;
            }
        }
    }
    return keyPressed;
}