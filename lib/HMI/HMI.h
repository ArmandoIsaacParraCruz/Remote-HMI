#pragma once
#include <Arduino.h>
#include <vector>
#include "GUI.h"
#include "RemoteCommunication.h"
#include "keyboard.h"

#define NUMBER_OF_PLACES        6
#define NUMBER_OF_PROCESS       20
#define MAX_TEMPERATURE         300
#define MAX_TEMPERATURE_DIGIT   999
#define MAX_RPM                 1200
#define MAX_RPM_DIGITS          9999
#define MAX_TIME                180
#define MAX_TIME_DIGITS         999        

enum TemperatureFunctionType{constant, ramp};
enum class MenuNavigationOptions{Forward, Backward, Exit, Continue};

struct TemperatureSetpoint {
            uint16_t initialTemperature;
            uint16_t finalTemperature;
            TemperatureFunctionType tempFunction;
};

struct ProcessesSpecifications{
    bool selectedPlaces[NUMBER_OF_PLACES];
    TemperatureSetpoint temperatureSetpoints[NUMBER_OF_PROCESS];
    uint16_t stirringSetpoints[NUMBER_OF_PROCESS]; 
    uint32_t processDuration[NUMBER_OF_PROCESS];
    uint8_t configuredProcesses;
};

class HMI
{
    public:
        HMI();  
        void HMI_main_loop();
    private:
        ProcessesSpecifications processesSpecifications;
        void initialize_processes_specifications_struct();
        GUI gui{};
        Keyboard keyboard{};
        void main_menu();
        void define_execution_specifications();
       //Functions to set up the execution specifications
       //Funciones para configurar las especificaciones de ejecución
        MenuNavigationOptions select_places();
        MenuNavigationOptions confirm_exit_select_places();
        bool validate_selected_places_array();
        MenuNavigationOptions set_up_processes();
        MenuNavigationOptions set_up_setpoints_and_times(const uint8_t &currentProcess);
        void update_specifications_current_process(const uint8_t &currentProcess);
        void set_up_temperatura_function_type(const uint8_t &currentProcess);
        void set_up_temperature_setpoints(const uint8_t &currentProcess);
        void set_up_constant_temperature(const uint8_t &currentProcess);
        void set_up_ramp_temperature(const uint8_t &currentProcess);
        void set_up_stirring_setpoints(const uint8_t &currentProcess);
        void set_up_process_duration(const uint8_t &currentProcess);
        String process_value_string(const String &value, const char keyPressed, const uint16_t maxValue);
        bool verify_specifications_current_process(const uint8_t &currentProcess);
        void error_in_specifications_current_process(const bool &stirringAndTemp, const bool &duration);
        MenuNavigationOptions add_or_summarize_processes();
        MenuNavigationOptions summarize_the_defined_execution_specifications();
        MenuNavigationOptions confirmAndTransmitConfiguratedProcesses();
       //
};