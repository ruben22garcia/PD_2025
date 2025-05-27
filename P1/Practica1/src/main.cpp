



#include <Arduino.h>


#define LED_BUILTIN 2   // Pin donde está conectado el LED
#define DELAY_TIME 1000  // Tiempo de espera (500 milisegundos)


void setup() {
 // Inicializar el pin del LED como salida
 pinMode(LED_BUILTIN, OUTPUT);


 // Iniciar la comunicación serie a 115200 baudios
 Serial.begin(115200);
}


void loop() {
 // Encender el LED
 digitalWrite(LED_BUILTIN, HIGH);


 // Enviar mensaje "ON" por el puerto serie
 Serial.println("1");


 // Esperar 500 milisegundos
 delay(DELAY_TIME);


 // Apagar el LED
 digitalWrite(LED_BUILTIN, LOW);


 // Enviar mensaje "OFF" por el puerto serie
 Serial.println("O");


 // Esperar otros 500 milisegundos
 delay(DELAY_TIME);
}
