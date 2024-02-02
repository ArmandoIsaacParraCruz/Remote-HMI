#pragma once
#include <Arduino.h>
#include <vector>
#include "GraphicalUserInterface.h"
#include "RemoteCommunication.h"
#include "keyboard.h"
#include "StructureMessages.h"

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
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        void defineProcessSpecificationsMenu();
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
        void monitorConfiguredProcessesMenu();
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        void monitorManualAdjustmentMenu();
};