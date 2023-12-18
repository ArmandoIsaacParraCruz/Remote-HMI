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
        static char getValidKey(std::vector<char>& validKeys);
        static char ignoreIvalidKeys(std::vector<char> &invalidKeys);
        static char getKey();
    private:
        static byte rowsPins[ROWS]; 
        static byte columnsPins[COLUMNS]; 
        static Keypad keypad; 
        static char keys[ROWS][COLUMNS];
};


