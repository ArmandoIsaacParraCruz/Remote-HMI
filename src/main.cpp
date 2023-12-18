#include <Arduino.h>
#include "HMI.h"

//40:91:51:AB:1B:C0

HMI hmi{};

void setup() {
  Serial.begin(115200);
}

void loop() {
  hmi.runHMI();
}



/*
#include <esp_now.h>
#include <WiFi.h>

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

typedef struct ProcessesSpecificationsMessage{
    bool selectedPlaces[NUMBER_OF_PLACES];
    TemperatureSetpoint temperatureSetpoints[NUMBER_OF_PROCESS];
    uint16_t stirringSetpoints[NUMBER_OF_PROCESS]; 
    uint32_t processDuration[NUMBER_OF_PROCESS];
    uint8_t configuredProcesses;
} ProcessesSpecificationsMessage;


ProcessesSpecificationsMessage processesSpecifications;

void initializeProcessesSpecificationsStruct()
{
    // Initialize the array of selected places as false for all places
    // Inicizaliza el arreglo de plazas seleccionadas como falso
    for (uint8_t i = 0; i < NUMBER_OF_PLACES; ++i) {
        processesSpecifications.selectedPlaces[i] = false;
    }

    // Initialize the temperature setpoints and stirring setpoints
    // Inicializa los setpoints de temeperatura y agitación en 0
    for (uint8_t i = 0; i < NUMBER_OF_PROCESS; ++i) {
        processesSpecifications.temperatureSetpoints[i].initialTemperature = 0;
        processesSpecifications.temperatureSetpoints[i].finalTemperature = 0;
        processesSpecifications.temperatureSetpoints[i].tempFunction = TemperatureFunctionType::constant;
        processesSpecifications.stirringSetpoints[i] = 0;
        processesSpecifications.processDuration[i] = 0;
    }

    // Set the configured task to zero
    // Asigna cero a las tareas configuradas
    processesSpecifications.configuredProcesses = 0;
}

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x34, 0x85, 0x18, 0xBD, 0x2B, 0x1C};


esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Transmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  initializeProcessesSpecificationsStruct();
}
 
void loop() {

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &processesSpecifications, sizeof(processesSpecifications));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}


*/