#pragma once
#include <Arduino.h>
#include <string>
#include <iostream>
#include <TFT_eSPI.h>   
#include <SPI.h>        
#include "Free_Fonts.h" 
#include "Logo_UAM.h"   
#include "My_Colors.h"  
#include "multiHeaterStirrerImage.h"


class GUI
{
    public:
        GUI();
        void show_UAM_logo();
        void show_main_menu_background_elements();
        void highlight_current_option_in_main_menu(uint8_t option);
    private:
        TFT_eSPI lcd = TFT_eSPI();
};