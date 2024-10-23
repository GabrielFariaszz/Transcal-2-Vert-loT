#include "DHT.h"

#define umidadeAnalogica A0 //Atribui o pino A0 a variável umidade - leitura analógica do sensor
#define umidadeDigital 7 //Atribui o pino 7 a variável umidadeDigital - leitura digital do sensor
#define LedVermelho 5 //Atribui o pino 7 a variável LedVermelho
#define LedVerde 6 //Atribui o pino 6 a variável LedVerde
#define DHTPIN A4     // Pin donde está conectado el sensor
#define DHTTYPE DHT11   // Cambia a DHT22 si usas un sensor DHT22
int nRainIn = A2;
int nRainDigitalIn = 2;
int nRainVal;
boolean bIsRaining = false;
String strRaining;

DHT dht(DHTPIN, DHTTYPE);

int valorumidade; //Declaração da variável que armazenará o valor da umidade lida - saída analogica
int valorumidadeDigital; //Declaração da variável que armazenara a saída digital do sensor de umidade do solo

void setup() {
  Serial.begin(9600); //Incia a comunicação serial
  pinMode(umidadeAnalogica, INPUT); //Define umidadeAnalogica como entrada
  pinMode(umidadeDigital, INPUT); //Define umidadeDigital como entrada
  pinMode(LedVermelho, OUTPUT); //Define LedVermelho como saída
  pinMode(LedVerde, OUTPUT); //Define LedVerde como saída
  dht.begin();
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
}

void loop() {

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  //PARTE DO SENSOR DE CHUVA
  nRainVal = analogRead(nRainIn);
  bIsRaining = !(digitalRead(nRainDigitalIn));
  
  if(bIsRaining){
    strRaining = "YES";
  }
  else{
    strRaining = "NO";
  }
  
  Serial.print("Raining?: ");
  Serial.print(strRaining);  
  Serial.print("t Moisture Level: ");
  Serial.println(nRainVal);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //PARTE DO SENSOR UMIDADE DO SOLO
  valorumidade = analogRead(umidadeAnalogica); //Realiza a leitura analógica do sensor e armazena em valorumidade
  valorumidade = map(valorumidade, 1023, 315, 0, 100); //Transforma os valores analógicos em uma escala de 0 a 100
  Serial.print("Umidade encontrada: "); //Imprime mensagem
  Serial.print(valorumidade); //Imprime no monitor serial o valor de umidade em porcentagem
  Serial.println(" % " );

  if (valorumidade < 50){
    digitalWrite(3,HIGH);
  }
  else{
    digitalWrite(3,LOW);
  }

  valorumidadeDigital = digitalRead(umidadeDigital); //Realiza a leitura digital do sensor e armazena em valorumidadeDigital
  if (valorumidadeDigital == 0) { //Se esse valor for igual a 0, será mostrado no monitor serial que o solo está úmido e o led verde se acende
    Serial.println("Status: Solo úmido");
    digitalWrite(LedVermelho, LOW);
    digitalWrite(LedVerde, HIGH);
  }
  else { // se esse valor for igual a 1, será mostrado no monitor serial que o solo está seco e o led vermelho se acende
    Serial.println("Status: Solo seco");
    digitalWrite(LedVermelho, HIGH);
    digitalWrite(LedVerde, LOW);
  }
  delay(1500); //Atraso de 500ms
}