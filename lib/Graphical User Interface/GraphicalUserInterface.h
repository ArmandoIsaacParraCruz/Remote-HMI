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
#include "StructureMessages.h"


class GraphicalUserInterface
{
    public:
        GraphicalUserInterface() = default;
        static void beginGraphicalUserInterface();
        static void displayUamLogo();
        static void displayMainMenuBackgroundElements();
        static void highlightCurrentOptionInMainMenu(const uint8_t &option);
        static void displaySelectPlacesMenuBackgroundElements(const bool selectedPlaces[], const uint8_t numPlaces);
        static void highlightCurrentPlaceInSelectPlacesMenu(const bool selectedPlaces[], const uint8_t &currentPlace, const uint8_t numPlaces);
        static void displayExitPromptForSelectPlacesMenu();
        static void displaySetUpSetpointsAndTimesMenuBackgroundElements(const bool selectedPlaces[], const uint8_t numPlaces, const uint8_t &currentProcess);
        static void clearMenuSpaceForSetUpSetpointsAndTimes();
        static void displayCurrentProcessTemperatureFunctionType(bool tempFunction);
        static void displaySetUpTemperatureFunctionTypeMenuBackgroundElements();
        static void positionPointerOnCurrentOptionInSetUpTemperatureFunctionTypeMenu(const uint8_t &currentOption);
        static void displayCurrentProcessTemperaturesSetpoints(const uint16_t &initTemp, const uint16_t &finalTemp);
        static void displayCurrentProcessStirringSetpoint(const uint16_t &stirringSetpoint);
        static void displayCurrentProcessDuration(const uint32_t &processDuration);
        static void positionPointerOnCurrentOptionInSetUpSetpointsAndTimesMenu(uint8_t &option);
        static void displaySetUpStirringSetpointsMenuBackgroundElements();
        static void displayRPMValueInSetUpStirringSetpointsMenu(const String &stirringSetpoint);
        static void displaySetUpConstantTemperatureMenuBackgroundElements();
        static void displayTemperatureValueInSetUpConstantTemperatureMenu(const String &temp);
        static void displaySetUpProcessDurationMenuBackgroundElements();
        static void displayDurationValueInSetUpProcessDurationMenu(const String &time);
        static void displaySetUpRampTemperatureMenuBackgroundElements();
        static void displayTemperaturesValuesInSetUpRampTemperatureMenu(const String &initTemp, const String &finalTemp);
        static void positionPointerOnCurrentOptionInSetUpRampTemperatureMenu(const uint8_t &currentOption);
        static void displayErrorInCurrentProcessSpecifications(const bool &stirringAndTemp, const bool &duration);
        static void displayPromptToAddOrSummarizeConfiguredProcesses();
        static void displaySummarizedExecutionSpecificationsMenuBackgroundElements(const bool selectedPlaces[], const uint8_t numPlaces);
        static void displayNumberOfCurrentProcess(const uint8_t &currentProcess, const uint8_t &configuredProcesses);
        static void displayConfirmAndTransmitConfiguredProcessesMenuBackgroundElements();
        static void displayTransmissionErrorMessage();
        static void displayTransmissionSuccessMessage();
        
        static void monitorMultiHeaterStirrerMenuBackgroundElements();
        static void displayTemperatureInMonitorMultiHeaterStirrerMenu(uint16_t& temperature, uint8_t& i);
        static void displayRPMInMonitorMultiHeaterStirrerMenu(uint16_t& RPM, uint8_t& i);
        static void displayTSIRInMonitorMultiHeaterStirrerMenu(float& temperatura);
        static void displayTimeInMonitorMultiHeaterStirrerMenu(uint32_t& time);
        static void displayManualUserAdjustmentMenuBackgroundElements();
        
    private:
        static TFT_eSPI lcd;
        static void displaySelectedPlaces(const bool selectedPlaces[], const uint8_t numPlaces);
};

