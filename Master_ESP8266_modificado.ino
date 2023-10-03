#include <ESP8266WiFi.h>
#include <espnow.h>
#include <iostream>

using namespace std;

string encryptDecrypt(string toEncrypt) {
    char key = 'K'; //Any char will work
    string output = toEncrypt;
    
    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;

    
    return output;
}


// Reemplazar con la MAC Address del ESP que recibe
uint8_t broadcastAddress[] = { 0xe0, 0x5a, 0x1b, 0xa1, 0x0c, 0xd8 };

// LMK and PMK keys
static const char *PMK_KEY_STR = "PrivateKey";
static const char *LMK_KEY_STR = "PublicKey";

int cuenta = 0;
// Creo una estructura para enviar los datos
// esta debe estar replicada en el receptor
typedef struct struct_message {
  char palabra[6];
  int numero;
} struct_message;

// Creo la estructura para enviar los datos
struct_message myData;

// Funcion que se ejecuta para enviar el dato
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print(cuenta);
  Serial.print(" Mensaje enviado: ");
  if (sendStatus == 0) {
    Serial.println("Ok ");
  } else {
    Serial.println("Fallo ");
  }
  cuenta++;
}

void setup() {

  Serial.begin(115200);
  
  // Defino el funcionamiento del ESP01 como Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error inicializando ESP-NOW");
    return;
  }


  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Registro el receptor
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  // Valores a enviar
  string encrypted = encryptDecrypt("HolaYisus");
  strcpy(myData.palabra, encrypted.c_str());
  myData.numero = 5;

  // envio el mensaje via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
}

void loop() {
}
