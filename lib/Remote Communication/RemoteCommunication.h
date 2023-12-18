#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "GraphicalUserInterface.h"
#include "StructureMessages.h"



class RemoteCommunication
{
    public:
    RemoteCommunication() = default;
        static void beginRemoteCommunication();
        static bool testConnection();
        static bool sendProcessesConfigurated(ProcessesSpecificationsMessage& message);
        static void myDelay(unsigned long timeDuration); 
        static struct measurements measurements;
        static struct manualAdjustmentParameters manualAdjustmentParameters;
        static volatile bool receiveMeasurements;

    private:
        static bool messageReceived;
        static uint8_t mac_multiHeaterStirrer[6];
        static uint8_t mac_HMI[6];
        static esp_now_peer_info_t peerInfo;
        static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
        static void IRAM_ATTR OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);     
};