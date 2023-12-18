#include "keyboard.h"

byte Keyboard::rowsPins[ROWS] = {4, 13, 14, 27};
byte Keyboard::columnsPins[COLUMNS] = {26, 25, 33, 32};

char Keyboard::keys[ROWS][COLUMNS] = {
            {'1','2','3','A'},
            {'4','5','6','B'},
            {'7','8','9','C'},
            {'*','0','#','D'}
        };

Keypad Keyboard::keypad{makeKeymap(keys), rowsPins, columnsPins, ROWS, COLUMNS};


/**
* Returns a valid key from the provided list of valid keys
* Devuelve una tecla válida de la lista de teclas válidas proporcionada
*/
char Keyboard::getValidKey(std::vector<char> &validKeys)
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

/**
* Returns a pressed key that is not in the list of invalid keys
* Devuelve una tecla presionada que no se encuentre dentro de la lista de teclas inválidas
*/
char Keyboard::ignoreIvalidKeys(std::vector<char> &invalidKeys) 
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

