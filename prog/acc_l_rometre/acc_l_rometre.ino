#include <AcceleroMMA7361.h>

AcceleroMMA7361 accelero; // Création du composant
int x; // Création des variables pour les 3 accélérations 
int y;
int z;
const int led=2;
const int led1=3;
const int led2=4;
const int led3=5;
const int led4=6;
const int led5=7;
const int led6=8;
const int led7=9;

void setup()
{
   pinMode(led, OUTPUT);
    pinMode(led1,OUTPUT);
     pinMode(led2,OUTPUT);
      pinMode(led3, OUTPUT);
    pinMode(led4,OUTPUT);
     pinMode(led5,OUTPUT);
      pinMode(led6, OUTPUT);
    pinMode(led7,OUTPUT);
    
 Serial.begin(9600); // Démarrer la liaison série
 accelero.begin(13, 12, 11, 10, A0, A1, A2); // Démarrer le composant
 accelero.setARefVoltage(5); // Régler la tension de référence
 accelero.setSensitivity(LOW); // Régler la sensibilité du composant +/-6G
 accelero.calibrate(); // Calibrer le composant
}

void loop()
{
 x = accelero.getXAccel(); // Lecture de l'axe X
 y = accelero.getYAccel(); // Lecture de l'axe Y
 z = accelero.getZAccel(); // Lecture de l'axe Z
 Serial.print("\nx: "); // Afficher la valeur de l'axe X
 Serial.print(x);
 Serial.print(" \ty: "); // Afficher la valeur de l'axe Y
 Serial.print(y);
 Serial.print(" \tz: "); // Afficher la valeur de l'axe Z
 Serial.print(z);
 Serial.print("\tG*10^-2");
 delay(500); // Délais pour rendre ça lisible
 
 if (x==4){
   digitalWrite(led,HIGH);
   delay(50);
   digitalWrite(led,LOW);
 }
  if (x==3){
   digitalWrite(led1,HIGH);
   delay(50);
   digitalWrite(led1,LOW);
 }
  if (x==2){
   digitalWrite(led2,HIGH);
   delay(50);
   digitalWrite(led2,LOW);
 }
  if (x==1){
   digitalWrite(led3,HIGH);
   delay(50);
   digitalWrite(led3,LOW);
 }
   if (x==0){
   digitalWrite(led4,HIGH);
   delay(500);
   digitalWrite(led4,LOW);
 }
   if (x==-1){
   digitalWrite(led5,HIGH);
   delay(50);
   digitalWrite(led5,LOW);
 }
   if (x==-2){
   digitalWrite(led6,HIGH);
   delay(50);
   digitalWrite(led6,LOW);
 }
   if (x==-3){
   digitalWrite(led7,HIGH);
   delay(50);
   digitalWrite(led7,LOW);
 }
 
 
}
