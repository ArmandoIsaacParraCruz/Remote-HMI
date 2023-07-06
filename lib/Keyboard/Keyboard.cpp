#include "keyboard.h"

char Keyboard::get_valid_key(std::vector<char>& validKeys)
{
    char keyPressed = NO_KEY;
    bool invalid = true;
    // Wait for a key press
    while (keyPressed == NO_KEY) {
        keyPressed = keypad.getKey();
        for(char& validKey: validKeys) {
            invalid = invalid && (keyPressed != validKey);
        }

        if(invalid) {
            keyPressed == NO_KEY;
        } else {
            break;
        }
    }
    return keyPressed;
}