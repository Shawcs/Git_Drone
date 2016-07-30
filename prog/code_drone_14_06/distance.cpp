#include "Ultrasonic.h"

// définition des broches utilisées 
Ultrasonic monCapteur(3,2);  
int maDistance=0;
 int distanceMin=10;
 int distanceMax=40;

/*        cette partie est à inclure dans le code main
void setup() 
{ 
  Serial.begin(9600); 
}

void loop() 
{ 
  unsigned long tempoActuel = millis();

   if ( ( tempoActuel - tempoEcriture ) >= 10 ){
  if(DISTANCELOIN()==true){
  Serial.println("PAS DE PROBLEME plus de 20cm");
  //Serial.println(maDistance);
}
  else if(DISTANCEPROCHE()==true){
  Serial.println("ATTENTION moins de 10cm ");
  //Serial.println(maDistance);
}
  else if (DISTANCEOK()==true){
  Serial.println("DANS LA ZONE DE COMFORT on est bon");
  //Serial.println(maDistance);
}
  else{
  Serial.println("oups");
 // Serial.println(maDistance);
  }
  
   tempoEcriture = tempoActuel;
   }
  
}
*/
 
float DISTANCE(){//traitement des données recus pour éviter les erreurs
unsigned long duree=millis(); //permet de savoir combien de temps on met à recevoir la distance
unsigned long temps=0;
  maDistance = monCapteur.convert( monCapteur.timing(), 1 );
  duree=millis()- duree;
  if(duree > 10){   //au 15/06 n'a pas l'air de fonctionner
    return 100;       //créer un blocage du capteur à une distance max egale à 100 ici fictive 
  Serial.println(maDistance);
}                  //nous sert à pas ce faire niquer des temps de réponses trop long
  else{
  //Serial.println(maDistance);
  return maDistance;
  }
} 

bool DISTANCEOK(){
  
if (distanceMin < DISTANCE() <= distanceMax)
  return true;
     else
  return false;

 }
 
 bool DISTANCEPROCHE(){
  if (DISTANCE() <= distanceMin)
       return true;
    else
       return false;
 }
 
 bool DISTANCELOIN()
{
 if(DISTANCE() > distanceMax)
      return true;
   else 
      return false;
}
