#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "ESPNowW.h"
#define NUMBER_OF_PLACES        6
#define NUMBER_OF_PROCESS       15
#define MAX_TEMPERATURE         300
#define MAX_TEMPERATURE_DIGIT   999
#define MAX_RPM                 1200
#define MAX_RPM_DIGITS          9999
#define MAX_TIME                180
#define MAX_TIME_DIGITS         999  

enum TemperatureFunctionType{constant, ramp};

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
};

class RemoteCommunication
{
    public:
    RemoteCommunication() = default;
        static void beginRemoteCommunication();
        static bool testConnection();
        static bool sendProcessesConfigurated(ProcessesSpecificationsMessage& message);
    private:
        static bool messageReceived;
        static uint8_t mac_multiHeaterStirrer[6];
        static uint8_t mac_HMI[6];
        static void receiveData(const uint8_t *mac_addr, esp_now_send_status_t status);
        static void myDelay(unsigned long timeDuration); 
};