# PRACTICA 5 :  Buses de comunicación II (SPI)  

El objetivo de la practica es comprender el funcionamiento del bus spi 

## Ejercicio Practico 1 LECTURA/ESCRITURA DE MEMORIA SD

El código utilizado es el siguiente:
```c 
#include <SPI.h>
#include <SD.h>

File myFile; // Objeto para manejar el archivo en la tarjeta SD

void setup() {
  Serial.begin(9600); // Inicialización de la comunicación serial
  
  Serial.print("Iniciando SD ...");
  
  // Inicialización de la tarjeta SD en el pin 4
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar la tarjeta SD");
    return;
  }
  Serial.println("Inicialización exitosa de la tarjeta SD");
  
  // Intentar abrir el archivo "archivo.txt" en la tarjeta SD
  myFile = SD.open("archivo.txt");
  
  // Verificar si se pudo abrir el archivo correctamente
  if (myFile) {
    Serial.println("archivo.txt:");
    
    // Leer el contenido del archivo y enviarlo por el puerto serial
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    
    // Cerrar el archivo después de leerlo
    myFile.close();
  } else {
    // En caso de que ocurra un error al abrir el archivo
    Serial.println("Error al abrir el archivo");
  }
}

void loop() {
  // El bucle loop está vacío ya que no se requiere ninguna tarea repetitiva
}
```

### 1. Descibir la salida por el puerto serie 

Este programa muestra cómo inicializar una tarjeta SD, abrir un archivo de texto en esa tarjeta, leer su contenido y enviarlo por el puerto serial.
Por lo tanto, por el monitor se tendría que imprimir el contenido del fichero "archivo.txt".

### 2. Explicar el funcionamiento 

1. Se incluyen dos bibliotecas. La primera `<SPI.h>` necesaria para el protocolo SPI. La segunda `<SD.h>` necesaria para controlar el acceso a los archivos de la tarjeta SD.
2. `File myFile`: Es la declaración de un objeto de tipo File con nombre myFile, que se utilizará para manejar el archivo en la tarjeta SD.
3. Función `setup()`:
   - Se inicializa la comunicación serie a 9600 baudios.
   - Se inicializa la tarjeta SD en el pin 4. (`SD.begin()`). Si la inicialización falla se imprime un mensaje.
   - Si la inicialización es exitosa, se abre el archivo "archivo.txt" utilizando la función `SD.open("archivo.txt")`.
   - Una vez abierto el archivo, se lee y se envía por el puerto serial utilizando un bucle while hasta que no hay más datos.
   - Una vez que se lee todo el archivo, se cierra utilizando `myFile.close()`.




 
 


