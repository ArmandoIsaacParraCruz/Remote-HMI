#include "keyboard.h"

char Keyboard::get_valid_key(std::vector<char>& validKeys)
{
    char keyPressed = NO_KEY;
    bool valid = true;
    // Wait for a key press
    while (keyPressed == NO_KEY) {
        keyPressed = keypad.getKey();
        for(char& validKey: validKeys) {
            valid = valid && (keyPressed == validKey);
        }

        if(valid) {
            break;
        } else {
            keyPressed == NO_KEY;
        }
    }
    return keyPressed;
}