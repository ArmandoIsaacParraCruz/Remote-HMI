#pragma once
#include <Arduino.h>
#include <vector>
#include "GUI.h"
#include "RemoteCommunication.h"
#include "keyboard.h"

#define NUMBER_OF_PLACES 6
#define TASK 20

enum TemperatureFunctionType{constant, ramp};
enum class MenuNavigationOptions{Forward, Backward, Exit};

struct TemperatureSetpoint {
            uint16_t temperature;
            TemperatureFunctionType tempFunction;
};

struct ExecutionSpecifications{
    bool selectedPlaces[NUMBER_OF_PLACES];
    TemperatureSetpoint temperatureSetpoint[TASK];
    uint16_t stirringSetpoints[TASK]; 
    uint32_t taskDuration[TASK];
    uint8_t configuredTask;
};

class HMI
{
    public:
        HMI();  
        void HMI_main_loop();
    private:
        ExecutionSpecifications executionSpecifications;
        void initialize_execution_specifications_struct();
        GUI gui{};
        Keyboard keyboard{};
        void main_menu();
        void define_execution_specifications();
       //Functions to set up the execution specifications
       //Funciones para configurar las especificaciones de ejecución
        MenuNavigationOptions select_places();
        bool validate_selected_places_array();
        MenuNavigationOptions set_up_setpoints_and_times();
        MenuNavigationOptions summarize_the_defined_execution_specifications();
       //
};