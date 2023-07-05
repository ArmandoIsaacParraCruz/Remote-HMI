#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "ESPNowW.h"


class RemoteCommunication
{
    public:
    RemoteCommunication();
    static bool testConnection();
    private:
        uint8_t mac_multiHeaterStirrer[6] = {0x40, 0x91, 0x51, 0xAB , 0x1B, 0xC0};
        uint8_t mac_HMI[6] = {0x0C, 0xB8, 0x15, 0xC1, 0x9A, 0xD4};
        static void receiveData(const uint8_t *mac_receiver, const uint8_t *data, int data_len);
        static bool connected;
        static void myDelay(unsigned long timeDuration); 
};