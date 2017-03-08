# Git_Drone

<!-- go see [DocToc](https://github.com/thlorenz/doctoc)* for ez **Table of Contents** -->


## Introduction

1 First init of the project

1. write the `README.md`
1. More to come


### TODO

Every thing

```sh
❯ npm run test
```
#technical specification of the project 

-The drone must be autonomous. We cannot send flight command after the take off
-	Le drone doit être complètement autonome. Aucune commande en vole ne lui sera envoyée. 

-The only human action is to send the GO signal to notify the drone that he can proceed to his goal
-	La seule action humaine doit être le lancement du drone c’est-à-dire d’envoyer le signal de départ au drone pour lui signifier que tout est en place et qu’il peut effectuer sa tâche.

-The purpose of the drone is to take off from a point A in order to reach a point B. All by his own way.
-	Le drone a pour but de partir d’un point A quelconque  et d’aller à un point B par ses propre moyen. 

-The goal point B will be defined by the operator. He is completely mobile in the space. But once the point is determined you cannot move it during the drone flight.
-	Ce point B sera défini par l’opérateur il est donc complètement mobile dans l’espace. En revanche ce point ne peut pas bouger après l’envoi du signal de départ du drone.

-The B point will be a sort of electronic balise (for the moment we do not know what it will be composed of, but we will have a physical object)
-	Le point B sera représenté par une balise électronique (par électronique entendons un objet physique pouvant contenir de l’électronique).

-The length between A and B must be included into 0 and 1 000 meter
-	La distance entre le point A et B se trouve dans un périmètre de 0 à 1 000 Mètres

-The precision of the landing near the tag can be up to 1 meter. This is our precision tolerance.
-	Le drone peut se poser jusqu’à 1 M à côté de la balise. Ceci serra notre tolérance d’erreur concernant l’atterrissage. 

-We will not use any autopilot or pré built flight controller
-	Nous n’utiliserons pas de système GPS ou de hard codage dans le drone pour trouver la balise (toute fois un système GPS peut être utilisé à des fins de sécurité que nous évoquerons plus tard)

-The drone will evolve in an outdoor, clear area. That mean no wall and no construction but we cn face moving people or trees. 
-	L’espace dans lequel ces points sont placés et donc dans lequel le drone évolue est situé en extérieur et sans gros obstacles. (par gros obstacles entendons murs ou bâtiments. Il peut bien sûr y avoir des arbres ou encore des personnes mobiles)

-Concerning autonomous we plan to get something around 15 or 20 minutes. This is not our main problem, so we will not focus on energy consumpsion first.
-	L’autonomie du drone doit avoisiner les 20 Min mais ceci n’est pas une priorité, nous serons satisfait avec 15 ou même 10 min d’autonomie,  temps que le drone rempli sa mission.
