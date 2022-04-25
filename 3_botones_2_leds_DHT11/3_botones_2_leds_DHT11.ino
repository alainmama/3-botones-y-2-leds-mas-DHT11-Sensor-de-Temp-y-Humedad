/*
 * Lectura de botones - Encendido de Leds
 * Por: Alain Manzo
 * Fecha: 24 de Abril de 2022
 * 
 * Este programa muestra las instrucciones básicas para la lectura
 * de botones y el encendido de leds
 */

// Bibliotecas
#include "DHT.h"

// Constantes
const int BOTON1 = 13; //Manual
const int BOTON2 = 14; //Alta demanda
const int BOTON3 = 15; //Sobre Carga
const int LED1 = 16;   //Refrigeración manual
const int LED2 = 2;    //Refrigeración automática

const float TMP = 28.00;

#define DHTPIN 12
#define DHTTYPE DHT11 

// Variables
int dato1;
int dato2;
int dato3;

// Definición de objetos
DHT dht(DHTPIN, DHTTYPE);

// Condiciones iniciales - Se ejecuta sólo una vez al energizar
void setup() {// Inicio de void setup ()
  // Aquí va tu código
  pinMode (BOTON1, INPUT_PULLUP); // Configurar el pin donde se conecta el boton como entrada
  pinMode (BOTON2, INPUT_PULLUP); // Configurar el pin donde se conecta el boton como entrada
  pinMode (BOTON3, INPUT_PULLUP); // Configurar el pin donde se conecta el boton como entrada
  pinMode (LED1, OUTPUT); //Cofigurar el pin donde se conecta el led como salida de voltaje
  pinMode (LED2, OUTPUT); //Cofigurar el pin donde se conecta el led como salida de voltaje
  digitalWrite (LED1, LOW); //0, false, LOW, 1, true, HIGH
  digitalWrite (LED2, LOW); //0, false, LOW, 1, true, HIGH

  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();//Iniciar comunicacion con el sensor DHT
  delay(1000);
  
}// Fin de void setup

// Cuerpo del programa - Se ejecuta constamente
void loop() {// Inicio de void loop
  // put your main code here, to run repeatedly:
  dato1 = digitalRead (BOTON1); // Leer el boton 1
  dato2 = digitalRead (BOTON2); // Leer el boton 2 
  dato3 = digitalRead (BOTON3); // Leer el boton 3
  
  //*******Lectura del sensor*********
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
   // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.println(t);

  //Enciende refrigeración manual si el boton manual se presiona
  if(dato1 == 0){
    digitalWrite (LED1, HIGH);}
  else{
    digitalWrite (LED1, LOW);}

  //La refrigeración manual tiene prioridad sobre la refrigeración automática
  if((dato1 == 0 && dato2 == 0)&& dato3 == 1){
    digitalWrite (LED1, HIGH);
    digitalWrite (LED2, LOW);}
 
  //Si hay alta demanda o sobrecarga se activa la refrigeracion automatica
  if((dato2 == 0 || dato3 == 0)&& dato1 == 1){
    digitalWrite (LED2, HIGH);}   
  else{
    digitalWrite (LED2, LOW);}

  //Si la temperatura es alta (mayor a un umbral) se activa la refrigeración manual
  if(dato1 == 1 && dato2 == 1 && dato3 == 1 && t > TMP){
    digitalWrite (LED2, HIGH);}   

  //Si tengo alta demanda o sobrecarga y ademas temperatura alta, se activan ambas refrigeraciones  
  if(dato1 == 1 && (dato2 == 0 || dato3 == 0) && t > TMP){
    digitalWrite (LED1, HIGH);
    digitalWrite (LED2, HIGH);}   



}// Fin de void loop

// Funcioes del usuario
