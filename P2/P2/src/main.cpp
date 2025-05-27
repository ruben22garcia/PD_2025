#include <Arduino.h>


volatile int interruptCounter = 0;  // Se declara como volatile
int totalInterruptCounter = 0;      // No necesita ser volatile


hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


void IRAM_ATTR onTimer() {
 portENTER_CRITICAL_ISR(&timerMux);  // Entramos en el modo crítico en la ISR
 interruptCounter++;  // Incrementamos el contador de interrupciones
 portEXIT_CRITICAL_ISR(&timerMux);  // Salimos del modo crítico en la ISR
}


void setup() {
 Serial.begin(115200);


 // Inicialización del temporizador (1us = 80)
 timer = timerBegin(0, 80, true);  // Timer 0, prescaler 80 (para 1us)
 timerAttachInterrupt(timer, &onTimer, true);  // Adjuntamos la interrupción
 timerAlarmWrite(timer, 1000000, true);  // Alarma en 1 segundo (1000000 us)
 timerAlarmEnable(timer);  // Habilitamos la alarma
}


void loop() {
 if (interruptCounter > 0) {  // Si ha ocurrido una interrupción
   portENTER_CRITICAL(&timerMux);  // Entramos en el modo crítico
   interruptCounter--;  // Decrementamos el contador de interrupciones
   portEXIT_CRITICAL(&timerMux);  // Salimos del modo crítico


   totalInterruptCounter++;  // Contamos la interrupción total
   Serial.print("An interrupt has occurred. Total number: ");
   Serial.println(totalInterruptCounter);  // Imprimimos el total
 }
}
