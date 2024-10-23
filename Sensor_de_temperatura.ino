#include "DHT.h"

#define DHTPIN A0     // Pin donde está conectado el sensor
#define DHTTYPE DHT11   // Cambia a DHT22 si usas un sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Esperar un momento para asegurar la lectura del sensor
  delay(2000);

  // Leer la humedad
  float h = dht.readHumidity();
  // Leer la temperatura en Celsius
  float t = dht.readTemperature();
  // Leer la temperatura en Fahrenheit
  float f = dht.readTemperature(true);

  // Verificar si alguna lectura falló e imprimir un error
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error al leer el sensor DHT");
    return;
  }

  // Calcular el índice de calor en Fahrenheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en Celsius
  float hic = dht.computeHeatIndex(t, h, false);

  // Imprimir los valores en el Serial Monitor
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}