#include <WiFi.h>
#include <WebServer.h>

// Credenciales WiFi
const char* ssid = "iPhone de Ruben";
const char* password = "ruben2299";

WebServer server(80);

// Pines motores
#define ENA 4
#define IN1 16
#define IN2 17
#define IN3 18
#define IN4 19
#define ENB 5

// Pines sensores
#define TRIG_FRONT 12
#define ECHO_FRONT 26
#define TRIG_BACK 14
#define ECHO_BACK 32

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_BACK, OUTPUT);
  pinMode(ECHO_BACK, INPUT);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  ledcAttachPin(ENA, 0); ledcAttachPin(ENB, 1);
  ledcSetup(0, 1000, 8); ledcSetup(1, 1000, 8);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(1000);
  Serial.println("WiFi conectado: " + WiFi.localIP().toString());

  server.on("/F", []() {
    if (readDistance(TRIG_FRONT, ECHO_FRONT) > 20) {
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      ledcWrite(0, 150); ledcWrite(1, 150);
    } else stopMotors();
    server.send(200, "text/plain", "Avanzando");
  });

  server.on("/B", []() {
    if (readDistance(TRIG_BACK, ECHO_BACK) > 20) {
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
      ledcWrite(0, 150); ledcWrite(1, 150);
    } else stopMotors();
    server.send(200, "text/plain", "Retrocediendo");
  });

  server.on("/L", []() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    ledcWrite(0, 150); ledcWrite(1, 150);
    server.send(200, "text/plain", "Izquierda");
  });

  server.on("/R", []() {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    ledcWrite(0, 150); ledcWrite(1, 150);
    server.send(200, "text/plain", "Derecha");
  });

  server.on("/S", []() {
    stopMotors();
    server.send(200, "text/plain", "Parado");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

