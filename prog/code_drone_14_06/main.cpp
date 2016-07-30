#include <Servo.h>
#include "Arduino.h"
#include "main.h"
#include "distance.h"


int vitesseActuelle=0;    // Vitesse actuelle du moteur
int vitesseEnReception=0; // Vitesse en cours de réception
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int a =0;
unsigned long tempoEcriture;
//----------Partie batterie--------------//
unsigned long Depart;
const int pin = 15; //ref batterie
float volt;
float tensionbat;
const int led1 = 8; //led rouge
const int led2 = 9;//led orange
const int led3= 11;//led verte
const int led6=6;//led témoin de branchement verte
const int led7=5;//led témoin de branchement rouge

void INITIALISATION(){   //-------------- initialisation des moteurs--------------//
  unsigned long tempsCourant=millis();
  long temps=0;
  volt = analogRead(pin);  //lecture de la tension de la batterie 
  tensionbat = volt * 4.88;
  Serial.println(tensionbat/1000);

  if(tensionbat<0.4){
    Serial.println("la batterie n'est pas branchée oue st à plat");
  }
  else{

    while(millis()<=2000) {//initialisation des esc puissance max pendant 2000 Ms
      if(tempsCourant-temps>10){
        servo1.writeMicroseconds(1964);
        servo2.writeMicroseconds(1964);
        servo3.writeMicroseconds(1964);
        servo4.writeMicroseconds(1964);
        Serial.println("vitesse du moteur 1964 ");
        temps=tempsCourant;
      }
    }

    while(millis()<=4000){ //initialisation des esc au minimum pendant 2000 Ms
      if(tempsCourant-temps>10){
        servo1.writeMicroseconds(960);
        servo2.writeMicroseconds(960);
        servo3.writeMicroseconds(960);
        servo4.writeMicroseconds(960);
        Serial.println("vitesse du moteur 960 ");
        a=0;
        temps=tempsCourant;
      } 
      if (a==0){
        a=1;
        Serial.println("Initialisation OK. Ready to flight up pour un decolage manuel pour la saisie");
      }
    }
  }
}

float TENSION(){   // --------------fonction de calcul tension  ----------------//
  volt = analogRead(pin);  //lecture de la tension de la batterie 
  tensionbat = volt * 4.88;
  tensionbatMV=tensionbat/1000;
  return tensionbatMV;
  //Serial.println(tensionbat/1000);
}

int TENSIONSHEK(){ //--------------focntion de shecage de la batterie--------------//

  if(TENSION<0.4)//voyant comme quoi la carte ne recoit pas de courants switch off
    return 1;

  if (TENSION<500) //batterie très faible
    return 2;

  if (TENSION<3000) //moyenne charge
    return 3;

  if (TENSION>4500) //charge maxi de la batterie
    return 4;
}

char QUESTION(){ // -------------- demander de lire le moniteur serie--------------//
  char inByte =Serial.read();

  Serial.println("saisir la vitesse des hélices");
  while(Serial.available()!='n'){

    // Réccupération du temps actuel :
    unsigned long tempoActuel = millis();

    // Lecture des données du serial si il y en a :
    while (Serial.available() > 0) {       
      char inByte = Serial.read();

      // Si l'on reçoit un chiffre, on l'affect à vitesseEnReception
      if ( ( inByte >= '0' ) ){//&& ( inByte <= '9' ) ) {
        vitesseEnReception = ( ( vitesseEnReception * 10 ) + ( inByte - '0' ) );
      }

      // Si on reçoit un \n, on affecte vitesseEnReception à vitesseActuelle
      if ( inByte == '\n' ) {
        // Petite protection pour ne pas affecter n'importe quoi dans vitesseActuelle
        if ( ( vitesseEnReception >= 0 ) && ( vitesseEnReception <= 100 ) ) {
          vitesseActuelle = vitesseEnReception;
        }
        // Puis remise à zero de vitesseEnReception
        vitesseEnReception = 0;
      }         

    }
  }
  
  void setup(){
    //------------Partie batterie-----------//
    Depart = millis();
    pinMode(pin, INPUT);
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(led3,OUTPUT);
    pinMode(led6,OUTPUT);
    pinMode(led7,OUTPUT);

    //----------Partie Moteur-----------//
    delay(1000);  
    servo1.attach(A0);
    servo2.attach(A2);
    servo3.attach(A3);
    servo4.attach(A4);
    Serial.begin(9600);
    vitesseActuelle = 0;
    vitesseEnReception = 0;
    tempoEcriture = 0;
    Serial.println("fin du setup ");
    Serial.println("Debut de l'initialisation des esc ");
    delay(1000);
    void INITIALISATION();
  }



  void loop() {
    //------Partie batterie---------//
    digitalWrite(led1,LOW);//rouge
    digitalWrite(led2,LOW);//orange
    digitalWrite(led3,LOW);//vert
    digitalWrite(led6,LOW);//etat du passage courant ou non
    digitalWrite(led7,LOW);//etat du switch 
    if((millis()-Depart)>=1000){

      if (TENSIONSHEK()==1){
        tensionbat=0; 
        digitalWrite(led7,HIGH);
        Depart=millis();
      }

      if(TENSIONSJEK()==2){
        digitalWrite(led1,HIGH);
        digitalWrite(led6,HIGH);
        digitalWrite(led7,LOW);
        Depart=millis(); 
      }

      if(TENSIONSHEK()==3){
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led6,HIGH);
        digitalWrite(led7,LOW);
        Depart=millis(); 
      }

      if(TENSIONSHEK()==4){
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led3,HIGH);
        digitalWrite(led6,HIGH);
        digitalWrite(led7,LOW); 
        Depart=millis(); 
      }


    }


    //---------partie moteur-----------//
    if (TENSION < 0,4){ //si la tension est nul alors pas d'initialisation du drone
      Serial.println("la batterie est à plat");
    }
    else
      if (DISTANCEOK == true)
        char QUESTION(); //appel de la fonction de question

    if ( ( tempoActuel - tempoEcriture ) >= 80 ){ //voir si un re scale n'est pas envisageable pour fit avec les bornes (12/06/15)

      // Affectation de la vitesse
      // Note : ( 1000 + ( v * 20 ) ) permet d'écrire une vitesse entre 1000 et 2000 si v est entre 0 et 100
      servo1.writeMicroseconds( 1000 + ( vitesseActuelle * 20 ) );
      servo2.writeMicroseconds( 1000 + ( vitesseActuelle * 20 ) );
      servo3.writeMicroseconds( 1000 + ( vitesseActuelle * 20 ) );
      servo4.writeMicroseconds( 1000 + ( vitesseActuelle * 20 ) );
      Serial.print("vitesse du moteur");
      Serial.println(1000 + ( vitesseActuelle * 20 ));
      Serial.println(vitesseActuelle);
      Serial.println(" ");
      tempoEcriture = tempoActuel;      
    }
  }
}   


