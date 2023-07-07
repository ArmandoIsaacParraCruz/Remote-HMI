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
        void ask_to_exit_select_places();
        void show_set_up_setpoints_and_times_menu_background_elements(const bool selectedPlaces[], const uint8_t numPlaces, const uint8_t &currentProcess);
        void clean_set_up_setpoints_and_times_menu_space();
        void update_function_temperature_type_current_process(bool tempFunction);
        void show_set_up_temperature_function_type_menu_background_elements();
        void show_current_option_set_up_temperature_function_type_menu(const uint8_t &currentOption);
        void update_temperatures_setpoints_current_process(const uint16_t &initTemp, const uint16_t &finalTemp);
        void update_stirring_setpoints_current_process(const uint16_t &stirringSetpoint);
        void update_duration_current_process(const uint32_t &processDuration);
        void show_current_option_set_up_setpoints_and_times_menu(uint8_t &option);
        void show_set_up_stirring_setpoints_menu_background_elements();
        void show_rmp_value_set_up_stirring_setpoints_menu(const String &stirringSetpoint);
        void show_set_up_constant_temperature_menu_background_elements();
        void show_temp_value_set_up_constant_temperature_menu(const String &temp);
        void show_set_up_process_duration_menu_background_elements();
        void show_duration_value_set_up_process_duration_menu(const String &time);
        void show_set_up_ramp_temperature_menu_background_elements();
        void show_rmp_value_set_up_ramp_temperature_menu(const String &initTemp, const String &finalTemp);
        void show_current_option_set_up_ramp_temperature_menu(const uint8_t &currentOption);
        void show_the_error_in_specifications_current_process(const bool &stirringAndTemp, const bool &duration);
        void ask_add_or_summarize_processes();
        void show_summarize_the_defined_execution_specifications_background_elements(const bool selectedPlaces[], const uint8_t numPlaces);
        void update_number_of_current_process(const uint8_t &currentProcess, const uint8_t &configuratedProcesses);
    private:
        TFT_eSPI lcd = TFT_eSPI();
        void show_selected_places(const bool selectedPlaces[], const uint8_t numPlaces);
};
