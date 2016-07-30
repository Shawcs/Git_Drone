#include "batterie.h"
#include "arduino.h"

unsigned long Depart;
const int pin = 15; //ref batterie
float volt;
double tensionbat;
double tensionbatMV;
const int led1 = 8; //led rouge
const int led2 = 9;//led orange
const int led3= 11;//led verte
const int led6=6;//led témoin de branchement verte
const int led7=5;//led témoin de branchement rouge


double TENSION(){   // --------------fonction de calcul tension  ----------------//
  volt = analogRead(pin);  //lecture de la tension de la batterie 
  tensionbat = volt * 4.88;
  tensionbatMV=tensionbat/1000;
  return tensionbatMV;
  //Serial.println(tensionbat/1000);
}

int TENSIONSHECK(){ //--------------focntion de shecage de la batterie--------------//

  if(TENSION()< 0.4)//voyant comme quoi la carte ne recoit pas de courants switch off
    return 1;

  if (TENSION() < 500) //batterie très faible
    return 2;

  if (TENSION() < 3000) //moyenne charge
    return 3;

  if (TENSION()  > 4500) //charge maxi de la batterie
    return 4;
}

void VOYANTS_BATTERIE(){
digitalWrite(led1,LOW);//rouge
    digitalWrite(led2,LOW);//orange
    digitalWrite(led3,LOW);//vert
    digitalWrite(led6,LOW);//etat du passage courant ou non
    digitalWrite(led7,LOW);//etat du switch 
    if((millis()-Depart)>=1000){

      if (TENSIONSHECK()==1){
        tensionbat=0; 
        digitalWrite(led7,HIGH);
        Depart=millis();
      }

      if(TENSIONSHECK()==2){
        digitalWrite(led1,HIGH);
        digitalWrite(led6,HIGH);
        digitalWrite(led7,LOW);
        Depart=millis(); 
      }

      if(TENSIONSHECK()==3){
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led6,HIGH);
        digitalWrite(led7,LOW);
        Depart=millis(); 
      }

      if(TENSIONSHECK()==4){
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led3,HIGH);
        digitalWrite(led6,HIGH);
        digitalWrite(led7,LOW); 
        Depart=millis(); 
      }
    }
}

void INIT_BATTERIE(){
     Depart = millis();
    pinMode(pin, INPUT);
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(led3,OUTPUT);
    pinMode(led6,OUTPUT);
    pinMode(led7,OUTPUT);
  }
