# Práctica 3: WiFi y Bluetooth con ESP32  
**Autor:** Martí Fontseca  
**Fecha:** Junio 2025  
**Plataforma:** ESP32-S3 DevKitM-1  
**Entorno de desarrollo:** PlatformIO + Arduino Framework

---

## 📋 Descripción

Esta práctica tiene como objetivo comprender el uso de las tecnologías **WiFi** y **Bluetooth** en microcontroladores, mediante el uso de un ESP32. Se divide en dos partes principales:

- **Parte A:** Creación de un servidor web con ESP32 usando WiFi.
- **Parte B:** Comunicación Bluetooth clásica entre ESP32 y un dispositivo móvil.

---

## 🧪 Parte A: Servidor Web con WiFi (Modo STA)

### A1 – Página Web Básica

Se genera una página web simple utilizando HTML embebido en el código del ESP32.  
**URL local:** Dirección IP asignada por el router (p. ej., `192.168.1.X`).

### A2 – Página Web con HTML/CSS

Se mejora la interfaz web incluyendo CSS y tarjetas con información de jugadores de fútbol, haciendo uso de imágenes y diseño responsivo.

> Ambas versiones del servidor están disponibles en sus respectivos archivos `.ino`.

---

## 📱 Parte B: Comunicación Bluetooth

Se establece una conexión Bluetooth clásica (SPP) entre la ESP32 y una aplicación de móvil (`Serial Bluetooth Terminal`). El sistema actúa como puente entre el puerto serie del ordenador y el móvil, permitiendo intercambio de datos.

---

## 🧰 Requisitos

- Placa ESP32 (ESP32-S3 DevKitM-1)
- Entorno PlatformIO o Arduino IDE
- Red WiFi local
- App móvil para Bluetooth (como **Serial Bluetooth Terminal** en Android)

---

## ⚙️ Configuración PlatformIO

```ini
[env:esp32-s3-devkitm-1]
platform = espressif32
board = esp32-s3-devkitm-1
framework = arduino
monitor_speed = 115200


# 🛰️ Práctica 3: WiFi y Bluetooth con ESP32

**Autor:** Martí Fontseca  
**Fecha:** Junio 2025  
**Plataforma:** ESP32-S3 DevKitM-1  
**Entorno de desarrollo:** PlatformIO + Arduino Framework  

---

## 📋 Descripción

Esta práctica se centra en el uso del ESP32 con conectividad **WiFi**, desarrollando páginas web alojadas en el propio microcontrolador. Se divide en dos partes:

- **A1:** Servidor web básico que muestra una página HTML sencilla.
- **A2:** Servidor web con una interfaz gráfica mejorada usando HTML y CSS.

---

## 🧪 Parte A – Servidor Web WiFi (Modo Estación)

---

### 🔹 A1 – Servidor Web Básico

Página simple servida desde el ESP32, conectándose a una red WiFi como cliente (modo estación).

**Código:**

```cpp
#include <WiFi.h>
#include <WebServer.h>

// Credenciales de la WiFi
const char* ssid = "Nautilus";  
const char* password = "20000Leguas";  

// Creación del objeto servidor
WebServer server(80);

// Función para gestionar la página principal
void handle_root() {
    String HTML = "<!DOCTYPE html>\
    <html>\
    <head>\
        <meta charset='UTF-8'>\
        <title>Pàgina ESP32</title>\
    </head>\
    <body>\
        <h1>My Primera Pagina con ESP32 - Station Mode 😊 by Marti Fontseca</h1>\
    </body>\
    </html>";
    server.send(200, "text/html", HTML);
}

void setup() {
    Serial.begin(115200);
    delay(1000);  // Esperar porque el monitor serie tenga tiempo de iniciarse
    Serial.println("ESP32 iniciant...");

    WiFi.begin(ssid, password);
    Serial.print("Connectant a WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nWiFi connectada!");
    Serial.print("IP assignada: ");
    Serial.println(WiFi.localIP());

    server.on("/", handle_root);
    server.begin();
    Serial.println("Servidor HTTP iniciat");
}

void loop() {
    server.handleClient();
}

### 🔹 A2 – Página Web Mejorada con HTML y CSS


#include <WiFi.h>
#include <WebServer.h>

// Credenciales de la WiFi
const char* ssid = "Nautilus";  
const char* password = "20000Leguas";  

// Creación del objeto servidor
WebServer server(80);

// Función para gestionar la página principal
void handle_root() {
    String HTML = "<!DOCTYPE html>\
    <html>\
    <head>\
        <meta charset='UTF-8'>\
        <meta name='viewport' content='width=device-width, initial-scale=1.0'>\
        <title>Jugadores de Fútbol</title>\
        <style>\
            body { font-family: Arial, sans-serif; background-color: #f5f5f5; margin: 0; padding: 0; text-align: center; }\
            header { background-color: #333; color: white; padding: 20px; font-size: 2em; }\
            .player-card { background-color: #fff; border: 2px solid #ddd; margin: 20px; padding: 20px; border-radius: 8px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); display: inline-block; width: 300px; text-align: center; transition: transform 0.3s ease; }\
            .player-card:hover { transform: scale(1.05); }\
            .player-card img { width: 100%; height: 200px; object-fit: cover; border-radius: 8px; }\
            .player-name { font-size: 1.5em; margin-top: 10px; color: #333; }\
            .player-info { font-size: 1.1em; margin-top: 5px; color: #555; }\
            footer { background-color: #333; color: white; padding: 10px; position: fixed; width: 100%; bottom: 0; text-align: center; }\
        </style>\
    </head>\
    <body>\
        <header>Jugadores de Fútbol Más Famosos</header>\
        <div class='player-card'>\
            <img src='https://upload.wikimedia.org/wikipedia/commons/2/2d/Lionel_Messi_2018.jpg' alt='Lionel Messi'>\
            <div class='player-name'>Lionel Messi</div>\
            <div class='player-info'>FC Barcelona (ahora PSG) | 7 Balones de Oro</div>\
        </div>\
        <div class='player-card'>\
            <img src='https://upload.wikimedia.org/wikipedia/commons/5/5d/Cristiano_Ronaldo_2018.jpg' alt='Cristiano Ronaldo'>\
            <div class='player-name'>Cristiano Ronaldo</div>\
            <div class='player-info'>Manchester United | 5 Balones de Oro</div>\
        </div>\
        <div class='player-card'>\
            <img src='https://upload.wikimedia.org/wikipedia/commons/4/47/Neymar_2019.jpg' alt='Neymar Jr'>\
            <div class='player-name'>Neymar Jr</div>\
            <div class='player-info'>PSG | 1 Copa Libertadores</div>\
        </div>\
        <footer>Web de Fútbol - Creado por Marti Fontseca</footer>\
    </body>\
    </html>";
    server.send(200, "text/html", HTML);
}

void setup() {
    Serial.begin(115200);
    delay(1000);  // Esperar para que el monitor serie se inicie
    Serial.println("ESP32 iniciando...");

    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nWiFi conectada!");
    Serial.print("IP asignada: ");
    Serial.println(WiFi.localIP());

    server.on("/", handle_root);
    server.begin();
    Serial.println("Servidor HTTP iniciado");
}

void loop() {
    server.handleClient();
}


