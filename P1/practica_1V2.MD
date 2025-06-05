# Práctica 1: Blink con ESP32

---

## 🎯 Objetivo

El objetivo de esta práctica es generar el parpadeo periódico de un LED utilizando un ESP32. Además, se emplea la salida serie para depuración y se comparan distintas técnicas: funciones estándar de Arduino, acceso directo a registros, y distintas formas de temporización. Finalmente, se analiza el rendimiento del microcontrolador.

---

## ⚙️ Microcontrolador: ESP32

### Imagen del ESP32

![ESP32](https://ae04.alicdn.com/kf/S8dee2f4cafc344e1b57ebc21ad5c11a4P.jpg?fit=600%2C600&ssl=1)

### Distribución de pines

![Pines ESP32](https://ae04.alicdn.com/kf/S61a9f7eb6ad3487ca95acc2f410157a35.jpg?resize=966%2C574&ssl=1)

---

## 🔧 Descripción de la funcionalidad

- Iniciar pin de LED como salida
- Bucle infinito:
  - Encender LED
  - Enviar mensaje "ON" por el puerto serie
  - Esperar 500 o 1000 ms
  - Apagar LED
  - Enviar mensaje "OFF" por el puerto serie
  - Esperar 500 o 1000 ms# PRACTICA 1  :  BLINK

El objeticvo de la practica es producir el parpadeo periodico de un led. 
Se utilizara la salida serie  para depurar  el programa 

El microcontrolador que utilizaremos es el ya comentado en la introducción  **ESP32**


---

## 🧪 Implementaciones

### 🟢 1. Código básico

```cpp
#define LED_BUILTIN 2
#define DELAY 500

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(DELAY);
  digitalWrite(LED_BUILTIN, LOW);
  delay(DELAY);
}


### 🟢 2 Codigo con salida serie

#define LED_BUILTIN 2
#define DELAY_TIME 1000

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("ON");
  delay(DELAY_TIME);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("OFF");
  delay(DELAY_TIME);
}

#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  GPIO.out_w1ts = (1 << LED_PIN);
  Serial.println("ON");

  unsigned long startMillis = millis();
  while (millis() - startMillis < 500);

  GPIO.out_w1tc = (1 << LED_PIN);
  Serial.println("OFF");

  startMillis = millis();
  while (millis() - startMillis < 500);
}

### 🟢 3. Acceso directo a registros + espera activa

#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  GPIO.out_w1ts = (1 << LED_PIN);
  Serial.println("ON");

  unsigned long startMillis = millis();
  while (millis() - startMillis < 500);

  GPIO.out_w1tc = (1 << LED_PIN);
  Serial.println("OFF");

  startMillis = millis();
  while (millis() - startMillis < 500);
}


### 🟢 4. Alternativas para medir frecuencia


#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("ON");

  while(millis() % 2 == 0);

  digitalWrite(LED_PIN, LOW);
  Serial.println("OFF");

  while(millis() % 2 == 1);
}

## 🟢 Diagrama de flujo

┌──────────────┐
│    setup()   │
│ - pinMode    │
│ - Serial.begin │
└──────┬───────┘
       │
 ┌─────▼─────┐
 │   loop()  │
 └─────┬─────┘
       │
┌──────▼──────┐
│ Encender LED│
│ Serial "ON" │
└──────┬──────┘
       │
┌──────▼──────┐
│ Esperar     │
└──────┬──────┘
       │
┌──────▼──────┐
│ Apagar LED  │
│ Serial "OFF"│
└──────┬──────┘
       │
┌──────▼──────┐
│ Esperar     │
└──────┬──────┘
       │
      (loop)



🧠 Tiempo libre del procesador

Durante las esperas activas (delay() o while()), el procesador no ejecuta otras tareas, pero tampoco realiza trabajo útil (bloqueo activo). Esto significa que:

    Ocupado útil: solo unos pocos microsegundos por ciclo.

    Tiempo "libre" (esperando): ~99.9% del tiempo.

✅ Conclusiones

    El uso de registros es más eficiente y permite alcanzar frecuencias más altas.

    El uso de funciones Arduino es más legible, pero introduce latencias y es menos preciso.

    La espera activa con millis() permite mantener el control sin usar delay(), pero consume CPU.

    El puerto serie reduce significativamente la frecuencia máxima de parpadeo.

    El ESP32 tiene una alta capacidad de respuesta cuando no se bloquea con delay() o Serial.
