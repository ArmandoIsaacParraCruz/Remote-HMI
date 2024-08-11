#pragma once
#include <Arduino.h>
#include <vector>
#define ROWS  4 
#define COLS 4

const char NO_KEY = '\0';

class Keyboard
{
    public:
        Keyboard() = default;
        static void begin();
        static char getValidKey(std::vector<char>& validKeys);
        static char ignoreIvalidKeys(std::vector<char> &invalidKeys);
        static char getKey();
    private:
        static byte rowPins[ROWS]; 
        static byte colPins[COLS]; 
        static char keys[ROWS][COLS];
};


