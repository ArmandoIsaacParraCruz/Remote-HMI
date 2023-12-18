#include "RemoteCommunication.h"

uint8_t RemoteCommunication::mac_multiHeaterStirrer[6] = {0x34, 0x85, 0x18, 0xBD, 0x2B, 0x1C};
uint8_t RemoteCommunication::mac_HMI[6] = {0x40, 0x91, 0x51, 0xAB, 0x1B, 0xC0};


bool RemoteCommunication::messageReceived;

esp_now_peer_info_t peerInfo;

/**Set up the parameters to stablish the remote communication
 * Configura los parámetros para establecer la comunicación remota
*/
void RemoteCommunication::receiveData(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (status == ESP_NOW_SEND_SUCCESS) {
    	Serial.println("Delivery Success");
		messageReceived = true;
    } else {
    	Serial.println("Delivery Fail");
		messageReceived = false;
    }

}

/**Test the connection between the multi heater stirrer and the remote control device
 * Prueba la conexión entre la multiparrilla agitatora y el dispositivo remotor de control
*/
void RemoteCommunication::beginRemoteCommunication()
{
    WiFi.mode(WIFI_STA);
    
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
    }
    esp_now_register_send_cb(receiveData);

    

    memcpy(peerInfo.peer_addr, mac_multiHeaterStirrer, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
    }
	
}


bool RemoteCommunication::testConnection()
{
    return true;
}

bool RemoteCommunication::sendProcessesConfigurated(ProcessesSpecificationsMessage& message)
{
    esp_err_t internalProcessStatus = esp_now_send(mac_multiHeaterStirrer, (uint8_t*)&message, sizeof(message));
	
    if(internalProcessStatus == ESP_OK) {
        Serial.println("Internal Process to send data was succeed");
    } else {
		Serial.println("Internal Process to send data failed");
	}
	myDelay(50);
	Serial.print("received: "); Serial.println(messageReceived);
    return messageReceived;
}

/**This function allows implement a non-blocking delay
 * Esta función permite implementar un retardo sin bloqueo
*/
void RemoteCommunication::myDelay(unsigned long timeDuration)
{
    unsigned long currentTime = millis();
    while(millis() - currentTime <= timeDuration){
        //currentTime = millis();
    }
}


