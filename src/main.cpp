#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

Adafruit_SSD1306 pantalla(128, 64, &Wire, -1);
int sensorHumedad = A3;
int trigPin = 8;
int echoPin = 9;
int rele = 2;
int btnHumedad = 3;
int btnAgua = 4;
bool estadoPantalla = false;
float alturaTanque = 10.0;

void setup() {
  
  Serial.begin(115200);
  pinMode(sensorHumedad, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(rele, OUTPUT);
  pinMode(btnHumedad, INPUT_PULLUP);
  pinMode(btnAgua, INPUT_PULLUP);
  pantalla.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pantalla.setTextColor(WHITE);

}

void loop() {
// Logica para obtener de la humedad del suelo 
  int senalHumedad = analogRead(sensorHumedad);

  int lecturaSeco = 872;  
  int lecturaAgua = 330;  

  int humedad = map(senalHumedad, lecturaSeco, lecturaAgua, 0, 100);
  humedad = constrain(humedad, 0, 100);
  
// Logica para saber el nivel del agua 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000);
  float distancia = duracion * 0.034 / 2.0;

  float nivel = ((alturaTanque - distancia) / alturaTanque) * 100.0;
  if (nivel < 0) nivel = 0;
  if (nivel > 100) nivel = 100;

// Logica para activar la bomba de agua
  if (humedad > 30 || nivel < 20)
  {
    digitalWrite(rele, HIGH);
  } else 
  {
    digitalWrite(rele, LOW);
  }
  
// Logica de el muestreo de datos por pantalla 
  int btnSenalHumedad = digitalRead(btnHumedad);
  int btnSenalAgua = digitalRead(btnAgua);

  if (btnSenalHumedad == 0)
  {
    estadoPantalla = false;
  } else if (btnSenalAgua == 0)
  {
    estadoPantalla = true;
  }
  
  if (estadoPantalla)
  {
    pantalla.clearDisplay();
    
    if (nivel < 20)
    {
      pantalla.setTextSize(1);        
      pantalla.setCursor(10, 10);       
      pantalla.print("Nivel del agua bajo");

      pantalla.setTextSize(2);        
      pantalla.setCursor(25, 30);     
      pantalla.print("Alerta");
    } else
    {
      pantalla.setTextSize(1);        
      pantalla.setCursor(10, 10);       
      pantalla.print("Nivel del agua:");

      pantalla.setTextSize(2);        
      pantalla.setCursor(30, 30);     
      pantalla.print(nivel);
      pantalla.print("%");
    }

    pantalla.display();
    delay(100);

  } else
  {
    pantalla.clearDisplay();
    
    pantalla.setTextSize(1);        
    pantalla.setCursor(10, 10);       
    pantalla.print("Humedad del suelo:");

    pantalla.setTextSize(2);        
    pantalla.setCursor(45, 30);     
    pantalla.print(humedad);
    pantalla.print("%");

    pantalla.display();
    delay(100);
  }

}