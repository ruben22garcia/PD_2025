# PRACTICA 5 :  Buses de comunicación I (Introducción y I2C)  

El objetivo de la practica es comprender el funcionamiento de los buses
  sistemas de comunicación entre periféricos;  estos elementos pueden 
  ser internos o externos  al procesador.

Esta es la primera practica de  4 donde se verán los buses i2c, spi,
 i2s , usart.

Para lo cual realizaremos una practica en cada caso donde controlaremos 
 un periférico de ejemplo

## Ejercicio Practico 1  ESCÁNER I2C

Programar el siguiente codigo,  colocar varios dispositivos  I2C 

```
En el caso de ESP32 por defecto:

| I2C Device | ESP32                    |
| ---------- | ------------------------ |
| SDA        | SDA (default is GPIO 21) |
| SCL        | SCL (default is GPIO 22) |
| GND        | GND                      |
| VCC        | usually 3.3V or 5V       |
```

como en la figura siguiente 

![](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/09/I2C-communication-protocol-ESP32.png?resize=1024%2C577&quality=100&strip=all&ssl=1)

Las resistencias de pull-up  dependen del numero de dispositivos ; 
aunque un valor usual es  3k3 


### 1. Descibir la salida por el puerto serie 

El código utilizado es el siguiente:
```c 
#include <Arduino.h>
#include <Wire.h>

void setup()
{
    Wire.begin();
    Serial.begin(115200);
    while (!Serial);
    // Leonardo: wait for serial monitor
    Serial.println("\nI2C Scanner");
}

void loop()
{
    byte error, address;
    int nDevices;
    Serial.println("Scanning...");
    nDevices = 0;
    for(address = 1; address < 127; address++ )
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address<16)
            {
                Serial.print("0");
            }
            Serial.print(address,HEX);
            Serial.println(" !");

            nDevices++;
        }
        else if (error==4)
        {
            Serial.print("Unknown error at address 0x");
            if (address<16)
            {
                Serial.print("0");
            }
            Serial.println(address,HEX);
        }
    }
    if (nDevices == 0)
    {
        Serial.println("No I2C devices found\n");
    }
    else
    {
        Serial.println("done\n");
        delay(5000);
        // wait 5 seconds for next scan
    }
}
```

En este caso, la salida por el puerto serie nos muestra en que dirección está el periférico que hemos conectado con el protocolo I2C, en código hexadecimal.

### 2. Explicar el funcionamiento 
1. Para el funcionamiento de este código y este protocolo I2C se debe incluir la librería `<Wire.h>`.
2. Función `setup()`;
   - Iniciamos la comunicación I2C con `Wire.begin()`.
   - Iniciamos la comunicación serie con `Serial.begin(115200)` a 115200 baudios.
   - `while(!Serial)` espera hasta que la conexión serie este disponible.
   - Finalmente imprime un mensaje en el puerto serial para indicar que el programa está escaneando dispositivos I2C.
3. Función `loop()`:
   - Imprime un mensaje indicando que la comunicación está en curso.
   - Iniciliza el contador de dispositivos encontrados con `nDevices = 0`.
   - Un bucle for busca en todas las direcciones, desde la 1 hasta la 126.
     - `Wire.beginTransmission(address);`: Intenta comenzar la transmisión a la dirección del dispositivo actual.
     - `error = Wire.endTransmission();`: Finaliza la transmisión y verifica si el dispositivo en la dirección actual respondió.
     - `if (error == 0) { ... }`: Si el dispositivo respondió, se imprime su dirección.
     - `else if (error == 4) { ... }`: Si hubo un error (código 4), se imprime una indicación de error.
   - Después del bucle for se verifica si se han encontrado dispositivos. En el caso de que se hayan encontrado se escribe el mensaje "done" y en caso contrario, se espera 5 segundos y vuelve a iniciar un nuevo escaneo.

