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