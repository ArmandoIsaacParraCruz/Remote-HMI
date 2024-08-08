#include "keyboard.h"

byte Keyboard::rowPins[ROWS] = {4, 13, 14, 27};
byte Keyboard::colPins[COLS] = {26, 25, 33, 32};

char Keyboard::keys[ROWS][COLS] = {
            {'1','2','3','A'},
            {'4','5','6','B'},
            {'7','8','9','C'},
            {'*','0','#','D'}
        };

void Keyboard::begin() 
{
    // Set up the row pins as outputs
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW); // Keep rows LOW
  }

  // Set up the column pins as inputs
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT);
  }

}


/**
* Returns a valid key from the provided list of valid keys
* Devuelve una tecla válida de la lista de teclas válidas proporcionada
*/
char Keyboard::getValidKey(std::vector<char> &validKeys)
{
    char keyPressed = NO_KEY;
    // Wait for a key press
    while (true) {
        keyPressed = getKey();
        
        for(char& validKey: validKeys) {
            if(keyPressed == validKey) {
                Serial.println(keyPressed);
                return keyPressed;
            } 
        }
    }
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
        keyPressed = getKey();
        
        if(keyPressed != NO_KEY) {
            keyPressedValid = true;
            for(char& invalidKey: invalidKeys) { 
                keyPressedValid = keyPressedValid && (invalidKey != keyPressed); 
            }
        } 
    }
    Serial.println(keyPressed);
   return keyPressed; 
}

char Keyboard::getKey()
{
  char key;
  for (int row = 0; row < ROWS; row++) {
    // Set the current row to HIGH
    digitalWrite(rowPins[row], HIGH);

    // Read the columns
    for (int col = 0; col < COLS; col++) {
      if (digitalRead(colPins[col]) == HIGH) {
        //Serial.print("Key pressed: ");
        //Serial.println(keys[row][col]);
        key = keys[row][col];
        // Wait until the key is released
        while (digitalRead(colPins[col]) == HIGH);
      }
    }

    // Restore the row to LOW
    digitalWrite(rowPins[row], LOW);
  }

  return key;
}
