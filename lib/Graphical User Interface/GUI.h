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
        void highlight_current_option_in_main_menu(const uint8_t &option);
        void show_select_places_menu_background_elements(const bool selectedPlaces[], const uint8_t numPlaces);
        void highlight_current_place_in_select_places_menu(const bool selectedPlaces[], const uint8_t &currentPlace, 
                                                                                            const uint8_t  numPlaces);
        void show_set_up_setpoints_and_times_menu_background_elements(const bool selectedPlaces[], const uint8_t numPlaces, const uint8_t &currentProcess);
        void clean_set_up_setpoints_and_times_menu_space();
        void update_function_temperature_type_current_process(bool tempFunction);
        void show_set_up_temperature_function_type_menu_background_elements();
        void show_current_option_set_up_temperature_function_type_menu(const uint8_t &currentOption);
        void update_temperatures_setpoints_current_process(const uint16_t &initTemp, const uint16_t &finalTemp);
        void update_stirring_setpoints_current_process(const uint16_t &stirringSetpoint);
        void update_duration_current_process(const uint32_t &processDuration);
        void show_current_option_set_up_setpoints_and_times_menu(uint8_t &option);
        
    private:
        TFT_eSPI lcd = TFT_eSPI();
        void show_selected_places(const bool selectedPlaces[], const uint8_t numPlaces);
};
