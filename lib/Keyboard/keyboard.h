#pragma once
#include <Keypad.h>
#include <Arduino.h>
#include <vector>
#define ROWS  4 
#define COLUMNS 4

class Keyboard
{
    public:
        Keyboard() = default;
        char get_valid_key(std::vector<char>& validKeys);
        char ignore_invalid_keys(std::vector<char> &invalidKeys);
    private:
        byte rowsPins[ROWS] = {4, 13, 14, 27}; 
        byte columnsPins[COLUMNS] = {26, 25, 33, 32}; 
        Keypad keypad = Keypad( makeKeymap(keys), rowsPins, columnsPins, ROWS, COLUMNS); 

        char keys[ROWS][COLUMNS] = {
            {'1','2','3','A'},
            {'4','5','6','B'},
            {'7','8','9','C'},
            {'*','0','#','D'}
        };
};


