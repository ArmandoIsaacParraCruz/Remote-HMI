#include "RemoteCommunication.h"

/**Set up the parameters to stablish the remote communication
 * Configura los parámetros para establecer la comunicación remota
*/
RemoteCommunication::RemoteCommunication()
{
    WiFi.mode(WIFI_MODE_STA);
    ESPNow.set_mac(mac_HMI);
    WiFi.disconnect();
    ESPNow.init();
    ESPNow.reg_recv_cb(receiveData);
    ESPNow.add_peer(mac_multiHeaterStirrer);
}

void RemoteCommunication::receiveData(const uint8_t *mac_receiver, const uint8_t *data, int data_len)
{

}

/**Test the connection between the multi heater stirrer and the remote control device
 * Prueba la conexión entre la multiparrilla agitatora y el dispositivo remotor de control
*/
bool RemoteCommunication::testConnection()
{
    testConnection();
    myDelay(30);
    esp_now_register_send_cb([](const uint8_t* mac, esp_now_send_status_t status) {
        status == ESP_NOW_SEND_SUCCESS ? connected = true : connected = false;
        //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Entrega exitosa" : "Entrega fallida");
    });
    return connected;
}

bool RemoteCommunication::sendProcessesConfigurated()
{
    return false;
}

/**This function allows implement a non-blocking delay
 * Esta función permite implementar un retardo sin bloqueo
*/
void RemoteCommunication::myDelay(unsigned long timeDuration)
{
    unsigned long currentTime = millis();
    while(millis() - currentTime <= timeDuration){
        currentTime = millis();
    }
}

