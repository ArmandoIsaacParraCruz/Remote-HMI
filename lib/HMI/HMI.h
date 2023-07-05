#pragma once
#include <Arduino.h>
#include <vector>
#include "GUI.h"
#include "RemoteCommunication.h"
#include "keyboard.h"

#define NUMBER_OF_PLACES 6
#define NUMBER_OF_PROCESS 20

enum TemperatureFunctionType{constant, ramp};
enum class MenuNavigationOptions{Forward, Backward, Exit};

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
    uint8_t configuredTask;
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
        bool validate_selected_places_array();
        MenuNavigationOptions set_up_processes();
        MenuNavigationOptions set_up_setpoints_and_times(const uint8_t &currentProcess);
        void update_specifications_current_process(const uint8_t &currentProcess);
        void  set_up_temperatura_function_type(const uint8_t &currentProcess);
        void  set_up_temperature_setpoints(const uint8_t &currentProcess);
        void  set_up_stirrering_setpoints(const uint8_t &currentProcess);
        void  set_up_process_duration(const uint8_t &currentProcess);
        MenuNavigationOptions summarize_the_defined_execution_specifications();
       //
};