#pragma once
#include <Arduino.h>
#include <vector>
#include "GraphicalUserInterface.h"
#include "RemoteCommunication.h"
#include "keyboard.h"

/*
NUMBER_OF_PLACES = 6
NUMBER_OF_PROCESS = 20
MAX_TEMPERATURE = 300
MAX_TEMPERATURE_DIGIT = 999
MAX_RPM = 1200
MAX_RPM_DIGITS = 9999
MAX_TIME = 180
MAX_TIME_DIGITS = 999  
*/      

/*enum TemperatureFunctionType{constant, ramp};
struct TemperatureSetpoint {
            uint16_t initialTemperature;
            uint16_t finalTemperature;
            TemperatureFunctionType tempFunction;
};

struct ProcessesSpecificationsMessage{
    bool selectedPlaces[NUMBER_OF_PLACES];
    TemperatureSetpoint temperatureSetpoints[NUMBER_OF_PROCESS];
    uint16_t stirringSetpoints[NUMBER_OF_PROCESS]; 
    uint32_t processDuration[NUMBER_OF_PROCESS];
    uint8_t configuredProcesses;
};*/

enum class MenuNavigationOptions{Forward, Backward, Exit, Continue};

class HMI
{
    public:
        HMI();  
        void runHMI();
    private:
        ProcessesSpecificationsMessage processesSpecifications;
        void initializeProcessesSpecificationsStruct();
        void mainMenu();
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        void defineExecutionSpecifications();
        MenuNavigationOptions selectPlacesMenu();
        MenuNavigationOptions confirmExitSelectPlaces();
        bool validateSelectedPlacesArray();
        MenuNavigationOptions setUpProcessesMenus();
        MenuNavigationOptions setUpSetpointsAndTimesMenu(const uint8_t &currentProcess);
        void updateSpecificationsCurrentProcess(const uint8_t &currentProcess);
        void setUpTemperatureFunctionTypeMenu(const uint8_t &currentProcess);
        void setUpTemperatureSetpointsMenus(const uint8_t &currentProcess);
        void setUpConstantTemperatureMenu(const uint8_t &currentProcess);
        void setUpRampTemperatureMenu(const uint8_t &currentProcess);
        void setUpStirringSetpointsMenu(const uint8_t &currentProcess);
        void setUpProcessDurationMenu(const uint8_t &currentProcess);
        String processValueString(const String &value, const char keyPressed, const uint16_t maxValue);
        bool verifySpecificationsCurrentProcess(const uint8_t &currentProcess);
        void handleSpecificationErrors(const bool &stirringAndTemp, const bool &duration);
        MenuNavigationOptions addOrSummarizeProcessesMenu();
        MenuNavigationOptions summarizeDefinedExecutionSpecificationsMenu();
        MenuNavigationOptions confirmAndTransmitConfiguredProcessesMenu();
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        void manualUserAdjustment();
};