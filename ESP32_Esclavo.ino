// ESCLAVO (recibe datos del maestro)


#include <esp_now.h>
#include <WiFi.h>
// Estructura de datos que va a contener el mensaje recibido
// requerido, debe ser igual al del maestro

const int Rojo = 32;
const int Verde = 33;
const int Azul = 21;
const int Amarillo = 18;

std::string myKeys[] = {"18079","395523"};


struct aRecibir {
  char palabra[6];
  int numero;
};
// crea una estructura para recibir los datos
aRecibir Datos;


// Funcion que se ejecuta cuando se recibe un mensaje
void OnRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&Datos, incomingData, sizeof(Datos));
  Serial.print("Bytes recibidos: ");
  Serial.println(len);
  Serial.print("Datos recibidos : ");
  Serial.println(Datos.palabra);
  Serial.println(Datos.numero);

  std::string key = "395525";

  std::string a = Datos.palabra;

  bool check = false;

  for (int i = 0; i < 2; ++i) {
    std::string b = myKeys[i];
    if (b == a) {
      check = true;
    }
  }  

  if (check) {
    digitalWrite(Rojo, HIGH);
    delay(250);
    digitalWrite(Rojo, LOW);
    digitalWrite(Verde, HIGH);
    delay(250);
    digitalWrite(Verde, LOW);
    digitalWrite(Amarillo, HIGH);
    delay(250);
    digitalWrite(Amarillo, LOW);
    digitalWrite(Azul, HIGH);
    delay(250);
    digitalWrite(Azul, LOW);
  } 
  
}
void setup() {
  // inicializo Serial Monitor
  Serial.begin(115200);
  // Seteo placa como estacion Wi-Fi
  WiFi.mode(WIFI_STA);
  // Inicializo ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error inicializando ESP-NOW");
    return;
  }

  pinMode(Rojo, OUTPUT);
  pinMode(Verde, OUTPUT);
  pinMode(Azul, OUTPUT);
  pinMode(Amarillo, OUTPUT);

  // Despues de inicializar el protocolo ESP-Now registro la funcion que recibe los mensajes
  // para poder ejecutarla cuando llega un mensaje.
  esp_now_register_recv_cb(OnRecv);
}

void loop() {
}
