#include "keyboard.h"

char Keyboard::get_valid_key(std::vector<char>& validKeys)
{
    char keyPressed = NO_KEY;
    // Wait for a key press
    while (true) {
        keyPressed = keypad.getKey();
        for(char& validKey: validKeys) {
            if(keyPressed == validKey) {
                goto exit;
            } 
        }
    }
    exit:
    return keyPressed;
}


char Keyboard::ignore_invalid_keys(std::vector<char> &invalidKeys) 
{ 
    char keyPressed = NO_KEY;
    bool keyPressedValid = false; 
    while(!keyPressedValid){  
        keyPressed = keypad.getKey();
        if(keyPressed != NO_KEY) {
            keyPressedValid = true;
            for(char& invalidKey: invalidKeys) { 
                keyPressedValid = keyPressedValid && (invalidKey != keyPressed); 
            }
        } 
    }
   return keyPressed; 
} 

