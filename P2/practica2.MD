# PRACTICA 2 : INTERRUPCIONES 

El objetivo de la practica es comprender el funcionamiento de las interrupciones.

Para lo cual realizaremos una practica  donde controlaremos  2 leds  de una forma periódica  y una entrada ; de forma que el uso de la entrada provoque un cambio de frecuencia de las oscilaciones  pero solo en un led.


## Introducción teórica  

¿Qué es una interrupción hardware?

A un nivel básico, una interrupción es una señal que interrumpe la actividad normal de nuestro microprocesador y salta a atenderla. Hay tres eventos que pueden disparar una interrupción:

 
* Un evento hardware, previamente definido.
* Un evento programado, o Timer
* Una llamada por software.
 
Cuando un evento dispara una interrupción, la ejecución normal del micro se suspende (ordenadamente para poder volver) y salta a ejecutar una función especial que llamamos Interrupt Service Handler o ISH (Servicio de gestión de interrupción).

Cuando el ISH finaliza, el procesador vuelve tranquilamente al punto donde lo dejó y sigue con lo que estaba como si no hubiese pasado nada.

 
 El concepto de interrupción nace de la necesidad imperiosa de reaccionar de forma inmediata en respuesta a un acontecimiento electrónico fulgurante, que no admite demora. Bien sea por la urgencia del suceso o porque algo se podría perder de forma irrecuperable sino reaccionamos con suficiente presteza.
 

Pero ¿Qué hay tan urgente que no pueda esperar? ¿Es que nuestros procesadores  no son lo suficientemente rápidos para ver cada poco si hay una señal de alarma? ¿Por qué complicarnos la vida con una cosa tan extravagante?

La respuesta como siempre es… depende. Nuestro procesador puede estar liado y solo leerá la señal de un pin de tanto en tanto. Y si la señal que aparece se desvanece antes de que hayamos ido a ver, ni siquiera lo sabremos, porque aunque los procesadores son rápidos una señal electrónica lo es varios millones de veces más. Este es otro motivo por el que usar delays tiene mucho peligro.

 
 El nombre de verificar periodicamente el tema ( entrada , registro ,,,) , se le llama **Polling**.
 

Por otro lado las interrupciones nos ofrecen una ventaja enorme a la hora de organizar nuestro programa. Se define la función que se ejecutará al recibir una interrupción dada y se ejecuta limpiamente cuando ocurre, no hay que comprobar si se da o no una situación.

Simplemente te olvidas y se ejecutará única y exclusivamente cuando se alce la interrupción. No me digáis que no es elegante (SI, es una obsesión).

En realidad, nosotros funcionamos por interrupciones habitualmente, en respuesta a sucesos no previstos que nos sacan de la rutina habitual.

Imagínate que estás viendo tu serie favorit
    struct Button {
      const uint8_t PIN;
      uint32_t numberKeyPresses;
      bool pressed;
    };

    Button button1 = {18, 0, false};

    void IRAM_ATTR isr() {
      button1.numberKeyPresses += 1;
      button1.pressed = true;
    }

    void setup() {
      Serial.begin(115200);
      pinMode(button1.PIN, INPUT_PULLUP);
      attachInterrupt(button1.PIN, isr, FALLING);
    }

    void loop() {
      if (button1.pressed) {
          Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
          button1.pressed = false;
      }

      //Detach Interrupt after 1 Minute
      static uint32_t lastMillis = 0;
      if (millis() - lastMillis > 60000) {
        lastMillis = millis();
        detachInterrupt(button1.PIN);
         Serial.println("Interrupt Detached!");
      }
    }

### informe
  realizar el informe de funcionamiento  asi como las salidas que se obtienen a través de la impresión serie a en la tele y estas esperando a tu colega, amigo o novia.

Hay dos maneras de abrirle la puerta. Una es pasar a ver si ha llegada cada, digamos dos minutos, para ver si esta con cara de pánfilo/pánfila en la puerta esperando a que le abramos.

La otra es establecer una interrupción, para eso están los timbres. Cuando alguien llega, pulsa el timbre. Tu paras tu capitulo tranquilamente, dejas el refresco en la mesa y vas a abrirle.

Cuando vuelves con él, reanudas tu peli y recoges el refresco. ¿Qué tienen de raro las interrupciones? ¿Qué me decís del teléfono o de los Whatsapp? Es la misma idea. Y lo mismo pasa con tu Arduino.

¿Por qué voy a renunciar a las interrupciones y dedicarme a pasar por la puerta cada poco? Es absurdo. Las interrupciones no tienen nada de extraño ni de incognoscible. Dedícale un poco de tiempo y te encontrarás una herramienta magnifica que te resolverá limpiamente más de un problema.

## tipos de interrupciones 

De los tres  sucesos que pueden disparar una interrupción

 
* Un evento hardware,
* Un evento programado, o Timer
* Una llamada por software.
 
Nos encontramos con que Arduino no soporta las interrupciones por software y punto.

¿Y entonces porque hemos hablado de ellas? Pues, porque otros entornos de programación las aceptan y no será raro que en el futuro Arduino también.

Los eventos programados o Timers, y hoy los utilizaremos en la practica , también veremos hoy interrupciones disparadas por hardware.


## Interrupciones en ESP32

En el ESP32, podemos definir una función de rutina de servicio de interrupción que se llamará cuando un pin GPIO cambie el valor de su señal.

Con una placa ESP32, todos los pines GPIO pueden ser configurados para funcionar como entradas de solicitud de interrupción.

### Adjuntar la interrupción a un PIN GPIO

En el IDE de Arduino, usamos una función llamada attachInterrupt() para establecer una interrupción en base a un pin por pin. La sintaxis recomendada es la siguiente.

    attachInterrupt(GPIOPin, ISR, Mode);

Esta función toma tres parámetros:

* GPIOPin: Establece la clavija GPIO como una clavija de interrupción, que le dice al ESP32 qué clavija debe monitorear.
* ISR: Es el nombre de la función que se llamará cada vez que se dispare la interrupción.
* Mode: Define cuándo se debe disparar la interrupción. Cinco constantes están predefinidas como valores válidos:
    * LOW	Los disparadores interrumpen cuando el pin está LOW
    * HIGH	Los disparadores interrumpen cuando el pin es HIGH
    * CHANGE	Los disparadores interrumpen cuando el pin cambia de valor, de HIGH a LOW o LOW a HIGH
    * FALLING	Los disparadores interrumpen cuando el pin va de HIGH a LOW
    * RISING	Los disparadores interrumpen cuando el pin va de LOW a HIGH


### Desconectar la interrupcion de un GPIO 

Opcionalmente, puedes llamar a la función de separación de interrupciones cuando ya no quieras que el ESP32 monitorice un pin. La sintaxis a utilizar es la siguiente.

     detachInterrupt(GPIOPin);

### Rutina de servicio de interrupcion

Esta es la función que se llama cuando  ocurre el evento dela interrupción , dede de ser corta de tiempo de ejecución . Su sintaxis es como sigue.

     void IRAM_ATTR ISR() {
          Statements;
      }


## Temporizadores en ESP32

Un temporizador es un contador interno ; que al terminar un determinado numero de cuentas  produce una interrupción 

El ESP32 tiene dos grupos de temporizadores, cada uno con dos temporizadores de hardware de propósito general. Todos los temporizadores se basan en contadores de 64 bits y preescaladores de 16 bits.

El preescalador se utiliza para dividir la frecuencia de la señal de base (normalmente 80 MHz), que luego se utiliza para incrementar/disminuir el contador de tiempo. Dado que el prescalificador tiene 16 bits, puede dividir la frecuencia de la señal del reloj por un factor de 2 a 65536, lo que da mucha libertad de configuración.

Los contadores de tiempo pueden ser configurados para contar hacia arriba o hacia abajo y apoyar la recarga automática y la recarga de software. También pueden generar alarmas cuando alcanzan un valor específico, definido por el software [2]. El valor del contador puede ser leído por el programa de software.

para entender el funcionamiento de la practica (temporizador) se debe leer el siguiente tutorial 

https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/

## Practica A interrupción por GPIO 


#include <Arduino.h>


struct Button {
const uint8_t PIN;
uint32_t numberKeyPresses;
bool pressed;
};
Button button1 = {18, 0, false};
void IRAM_ATTR isr() {
button1.numberKeyPresses += 1;
button1.pressed = true;
}
void setup() {
Serial.begin(115200);
pinMode(button1.PIN, INPUT_PULLUP);
attachInterrupt(button1.PIN, isr, FALLING);
}
void loop() {
if (button1.pressed) {
Serial.printf("Button 1 has been pressed %u times\n",
button1.numberKeyPresses);
button1.pressed = false;
}
//Detach Interrupt after 1 Minute
static uint32_t lastMillis = 0;
if (millis() - lastMillis > 60000) {
lastMillis = millis();
detachInterrupt(button1.PIN);
Serial.println("Interrupt Detached!");
}
}

Este código configura un botón conectado al pin 18 del ESP32 y utiliza una interrupción para contar cuántas veces se ha presionado el botón.
Se define una estructura Button que contiene el pin del botón, el número de presiones y el estado del botón (pressed).
La función isr() se ejecuta cuando el botón se presiona, incrementando el contador numberKeyPresses y marcando que el botón fue presionado (pressed = true).
En el setup(), se configura el pin 18 como entrada con resistencia pull-up y se adjunta una interrupción al pin para detectar la caída de señal (cuando el botón se presiona).
En el loop(), si el botón ha sido presionado, el código imprime cuántas veces se ha presionado el botón en el Monitor Serie. Luego, la variable pressed se restablece a false.
Después de 1 minuto (60000 milisegundos), se desactiva la interrupción, y se imprime un mensaje indicando que la interrupción ha sido detenida.
El archivo de configuración en platformio.ini establece la plataforma y la velocidad del monitor serie.
El contador se desfasa debido a los rebotes que suceden
Hay veces que no cuenta todos los rebotes en el flanco. 
En resumen, el programa cuenta las veces que se presiona un botón, lo muestra por el Monitor Serie y desactiva la interrupción después de un minuto.




## Practica B interrupción por timer 

El codigo de la practica es el siguiente 
```
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


Este código configura un temporizador hardware en el ESP32 que genera una interrupción cada 1 segundo. La interrupción se maneja en la función onTimer(), que es una rutina de interrupción (ISR) donde se incrementa el contador interruptCounter cada vez que el temporizador se activa.
En el setup(), se inicializa el temporizador con un prescaler de 80 (para que cuente en microsegundos) y se configura para generar una interrupción cada 1 segundo. Además, se habilita la interrupción y se adjunta la función onTimer() como la rutina a ejecutar cuando ocurra la interrupción.
En el loop(), el programa verifica si el contador interruptCounter ha sido incrementado por la ISR. Si es así, el contador se decrementa de forma segura dentro de una sección crítica (portENTER_CRITICAL y portEXIT_CRITICAL), y el contador total de interrupciones (totalInterruptCounter) se incrementa. Luego, el número total de interrupciones se imprime en el Monitor Serie.
El uso de las secciones críticas asegura que el acceso a las variables compartidas entre la ISR y el código principal esté sincronizado correctamente, evitando condiciones de carrera. Este proceso se repite continuamente, y el monitor serie muestra el número total de interrupciones ocurridas.


## ejercicio extra 


#include <Arduino.h>


const int ledPin = 2;      // Pin donde se conecta el LED
const int buttonPin1 = 4;  // Pin del primer pulsador
const int buttonPin2 = 5;  // Pin del segundo pulsador


volatile int blinkDelay = 1000;  // Frecuencia inicial de parpadeo (en milisegundos)
volatile bool ledState = LOW;    // Estado del LED
volatile unsigned long lastDebounceTime1 = 0;  // Tiempo para debouncing del pulsador 1
volatile unsigned long lastDebounceTime2 = 0;  // Tiempo para debouncing del pulsador 2
unsigned long debounceDelay = 50;  // Tiempo de espera para evitar rebotes (en milisegundos)


hw_timer_t *timer = NULL;         // Temporizador
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


void IRAM_ATTR onTimer() {
 // Cambiar el estado del LED solo cuando el tiempo de parpadeo haya pasado
 portENTER_CRITICAL_ISR(&timerMux);
 static unsigned long previousMillis = 0; // Variable para llevar el control del tiempo
 unsigned long currentMillis = millis();
  // Solo alternamos el LED si ha pasado el tiempo configurado en blinkDelay
 if (currentMillis - previousMillis >= blinkDelay) {
   ledState = !ledState;  // Alternar el estado del LED
   digitalWrite(ledPin, ledState);  // Aplicamos el cambio de estado al LED
   previousMillis = currentMillis;  // Actualizamos el tiempo del último cambio
 }
 portEXIT_CRITICAL_ISR(&timerMux);
}


void IRAM_ATTR buttonInterrupt1() {
 if (millis() - lastDebounceTime1 > debounceDelay) {
   portENTER_CRITICAL_ISR(&timerMux);
   blinkDelay = max(100, blinkDelay - 100);  // Aumenta la frecuencia (reduce el delay)
   portEXIT_CRITICAL_ISR(&timerMux);
   lastDebounceTime1 = millis();
 }
}


void IRAM_ATTR buttonInterrupt2() {
 if (millis() - lastDebounceTime2 > debounceDelay) {
   portENTER_CRITICAL_ISR(&timerMux);
   blinkDelay += 100;  // Disminuye la frecuencia (aumenta el delay)
   portEXIT_CRITICAL_ISR(&timerMux);
   lastDebounceTime2 = millis();
 }
}


void setup() {
 Serial.begin(115200);


 pinMode(ledPin, OUTPUT);
 pinMode(buttonPin1, INPUT_PULLUP);
 pinMode(buttonPin2, INPUT_PULLUP);


 // Configurar interrupciones para los pulsadores
 attachInterrupt(buttonPin1, buttonInterrupt1, FALLING);
 attachInterrupt(buttonPin2, buttonInterrupt2, FALLING);


 // Configuración del temporizador para generar interrupciones a intervalos
 timer = timerBegin(0, 80, true);  // Timer 0, prescaler 80 para generar interrupciones a 1ms
 timerAttachInterrupt(timer, &onTimer, true);  // Asociamos la interrupción
 timerAlarmWrite(timer, blinkDelay, true);  // Configuramos el temporizador con el delay inicial
 timerAlarmEnable(timer);  // Habilitamos la alarma
}


void loop() {
 // El código en el loop es muy simple ya que todo está manejado por las interrupciones
}


Informe Breve – Ejercicio Extra: Control de Parpadeo con Pulsadores e Interrupciones

Objetivo

Controlar la frecuencia de parpadeo de un LED en un ESP32 usando dos pulsadores: uno para aumentar y otro para disminuir la frecuencia. Todo se gestiona con interrupciones por hardware, sin usar el bucle loop().

Funcionamiento

El LED parpadea con una frecuencia ajustable.

Pulsador 1 incrementa la frecuencia (reduce el tiempo de parpadeo).

Pulsador 2 disminuye la frecuencia (aumenta el tiempo de parpadeo).

Se usa un temporizador por hardware para controlar el parpadeo.

El código evita rebotes mediante un pequeño retardo (debounce).

Características técnicas

Se utilizan interrupciones para el temporizador y los pulsadores, permitiendo una respuesta inmediata sin ocupar el procesador con esperas activas.

El tiempo de parpadeo se actualiza en tiempo real y se protege el acceso compartido a variables mediante secciones críticas.

Ventajas

Alta eficiencia del procesador (tiempo libre alto).

Control preciso de la frecuencia.

Escalable para otros sistemas de control de tiempo o eventos.

Aplicaciones

Este sistema puede servir como base para temporizadores, controladores PWM, sistemas de señales visuales, o como práctica avanzada de gestión de interrupciones en sistemas embebidos.





