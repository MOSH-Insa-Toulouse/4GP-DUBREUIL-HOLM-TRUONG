# 4GP-DUBREUIL-HOLM-TRUONG

## SMOMAIRE
- [I) Présentation](#Présentation)
- [II) Matériel necessaire](#Matériel-necessaire)
   - [Software](#Software)
   - [Hardware](#Hardware)
- [III)Livrables](#Livrables)
   - [1) Simulation LtSpice](#Simulation-LtSpice)
   - [2) Conception PCB avec KiCad](#Conception-PCB-avec-KiCad)
   - [3) Code Arduino](#Code-Arduino)
   - [4) Application Android avec MITApp Inventor](#Application-Android-avec-MITApp-Inventor)
   - [5) Réalisation Physique du Circuit](#Réalisation-Physique-du-Circuit)
   - [6) Banc de Test Expérimental](#Banc-de-Test-Expérimental)
- [IV)Gestion de projet](#gestion-projet)
   - [1)Répartition du travail](#repartition-travail)
   - [2) Contacts](#contacts)


## I) Présentation
Ce répertoire présente l'ensemble des éléments nécessaire à la conception d'un capteur de pression en graphite réalisé dans le cadre de l'UF I4GPMH21 : Du capteur au banc de test en open source hardware.
L’objectif était de concevoir un dispositif de mesure de déformation utilisant un capteur innovant, low-tech, basé sur du graphite appliqué sur papier, selon le principe décrit dans l’article scientifique :  
**"Pencil Drawn Strain Gauges and Chemiresistors on Paper"** (Cheng-Wei Lin, Zhibo Zhao, Jaemyung Kim & Jiaxing Huang). Ce capteur, d'une simplicité remarquable, est constitué d'un morceau de papier sur lequel du graphite est appliqué à l'aide d'un crayon à papier.

![Image](https://github.com/user-attachments/assets/727cc681-f1a2-4a0d-8247-0b9f83917b50)

Le principe de fonctionnement repose sur l'observation que la déformation du papier entraîne une variation du nombre de particules de graphite interconnectées. Cette modification de la structure granulaire du graphite se traduit par une variation de la résistance et de la conductance du capteur. En exploitant cette propriété, il devient possible de remonter à la déformation subie, à l'instar d'une jauge de contrainte classique.

![Image](https://github.com/user-attachments/assets/bc79245b-acaf-44ab-830e-e222ee2b5f1d)

Le fonctionnement repose sur la variation de la conductivité électrique du graphite en fonction de la contrainte mécanique appliquée au support papier. Ce phénomène permet de mesurer la déformation avec une technologie simple, accessible et écologique.
## II) Matériel necessaire
### ***Software*** (Présenté dans l'ordre d'utilisation)
1. LtSpice : Logiciel permettant la modélisation et simulation des circuits électroniques. 
1. KiCad : Logiciel permettant le développement et conception du PCB (*Printed Board Circuit*)
1. Arduino IDE : IDE utilisé pour écrire le code du micro-contrôleur Arduino. 
1. MITApp Inventor : WebService pour le développement d'une application Android.
### ***Hardware***
1. Micro-contrôleur Arduino UNO
1. Modules 
    * Bluetooth HC-05
    * Capteur de déformation en graphite
    * Capteur de déformation du commerce
    * Écran OLED
    * Encodeur Rotatoire
    * Potentiomètre digital
    * Servo-Moteur
1. Banc de test réalisé à l'imprimante 3D

## III) Livrables
### 1) Simulation LtSpice

Un montage à transimpédance a été conçu afin d'amplifier le faible courant produit par le capteur graphite. Ce montage utilise un amplificateur opérationnel de précision (LTC1050) pour convertir le courant en tension, compatible avec les entrées analogiques d’un Arduino UNO.  

Trois filtres passe-bas ont été intégrés pour minimiser le bruit :
- Un filtre passe-bas passif (R1, C1) à l'entrée : filtre RC à 16 Hz pour réduire les perturbations en courant,
- Un filtre passe-bas actif (R3, C4) couplé à l'AOP : filtre actif à 1,6 Hz pour éliminer le bruit secteur (50 Hz),
- Un filtre passe-bas (R5, C2) à la sortie de l'AOP : filtre à 1,6 kHz pour lisser le signal final.

Des simulations transitoires et fréquentielles ont validé l’amplification et l’efficacité de la filtration (atténuation > 70 dB à 50 Hz).

#### ***Graphique***

![Image](https://github.com/user-attachments/assets/1576e794-9247-45f7-ab48-5f0affea7e4b)

#### ***Schéma du montage***
![Image](https://github.com/user-attachments/assets/8ec56f1d-8405-40e8-8d74-eb53732aa1f6)

### 2) Conception PCB avec KiCad

Dans cette section, nous présentons le processus de conception du circuit imprimé du projet, allant de la simulation électrique à la modélisation 3D, en passant par le routage des composants. L’objectif est de réaliser une carte fonctionnelle permettant l’acquisition, le traitement et la transmission du signal mesuré par le capteur graphite.


### Étape 1 : Sélection et intégration des composants

Le circuit est conçu pour intégrer et connecter plusieurs composants essentiels à l’Arduino :

- Amplificateur opérationnel **LT1050** (amplification analogique du signal capteur)
- **Servomoteur** 
- **Potentiomètre numérique** (ajustement dynamique de gain)
- **Encodeur rotatoire**
- **Écran OLED**
- **Module Bluetooth HC-05** (communication sans fil avec une application mobile)
- Deux broches dédiées au **capteur graphène**

L’ensemble des connexions logiques et électriques est établi dans le schéma du PCB sur KiCad pour s'assurer de la compatibilité avec l’Arduino.


### Étape 2 : Simulation du schéma électrique

La conception a débuté par la création d’un schéma électrique simulé sous **LTspice**. Cette simulation permet de valider le comportement du circuit d’amplification, notamment autour de l’amplificateur opérationnel **LT 1050**, qui joue un rôle essentiel dans l’amplification du signal analogique issu du capteur graphite.

Une fois le schéma validé, il est reproduit dans **KiCad** afin de préparer la conception physique du circuit.

#### ***Schematic***

![Image](https://github.com/user-attachments/assets/41834f51-993d-49a6-9831-d555f277b064)

Ici sont présenté les différents éléments qui composeront le *shield* de notre projet ainsi que l'assignation des différentes connexions. On y retrouve en haut à droite l'ensemble des pins de connexion de l'arduino, à gauche, le schéma de l'amplificateur ainsi que la connexion du capteur graphène. Enfin, en bas, on retrouve la schématisation des différents modules à intégrer.

### Étape 3 : Routage PCB dans KiCad

La phase suivante consiste à réaliser le **routage** du circuit. Cela implique de placer les composants sur le PCB, de définir les couches, les largeurs de piste et les zones de masse, puis de relier chaque broche selon le schéma précédent.

L’objectif est d’optimiser la compacité, de limiter les interférences et d’assurer la robustesse du signal analogique.

**Aperçu du PCB routé :**

![Image](https://github.com/user-attachments/assets/7d89c180-d199-42cf-8f1e-8d37468880a9)

![Image](https://github.com/user-attachments/assets/c64fc3c3-8669-43f4-a2bb-5f7fb6242ba6)
---

### Étape 4 : Visualisation 3D

Une fois le routage terminé, **KiCad** permet de générer un **modèle 3D** réaliste de la carte. Cette vue permet de vérifier l’encombrement, l’orientation des composants, et de prévoir les contraintes mécaniques ou d’intégration dans un boîtier physique.

**Modélisation 3D du PCB :**

![Image](https://github.com/user-attachments/assets/48660987-a96b-4d5e-b8db-5d6eb2de74c5)

---
### 3) Code Arduino
Le code Arduino doit permettre la réalisation des fonctions suivantes :
1. Récupérer les données du capteur graphène fait main
1. Naviguer dans un menu avec l'encodeur rotatoire et afficher sur l'écran OLED.
1. Gérer les valeurs de résistance du potentiomètre digital
1. Définir l'action du servo-moteur

Pour accomplir toutes ces actions, l'ensemble des fonctionnalités est géré à partir d'un menu à plusieurs niveau construit sur le modèle d'une machine à état.
Ainsi, dans le code deux fonctions sont construites pour gérer les mouvements de l'encodeur rotatoire et la gestion des menus.
L'arborescence finale du menu est construite comme suit : 
- Resistance R2
- Servo-moteur
   - Pousser
      - Angle 30
      - Angle 45
      - Angle 60
      - Angle 90
      - Retour
   - Tirer
      - Angle 30
      - Angle 45
      - Angle 60
      - Angle 90
      - Retour
   - Retour


Une fois l'angle selectionné, le mouvement du servo-moteur se déclenche et la mesure est réalisée (voir partie banc de test) 

---
### 4) Application Android avec MITApp Inventor

Nous avons développé une application Android avec **MIT App Inventor**. Cette application doit permettre la communication sans fil avec le module Bluetooth présent sur le *shield*, afin de visualiser les données du capteur en temps réel sur un téléphone android par exemple.

#### Objectifs

- Établir une connexion Bluetooth entre le smartphone Android et le module Arduino.
- Afficher la résistance du **potentiomètre digital** ainsi que celle du **capteur graphène**.
- Tracer une courbe en temps réel représentant l’évolution de la résistance du capteur.

#### Interface utilisateur

- Le bouton **Bluetooth** permet de se connecter au module Arduino via Bluetooth.
- Une fois connecté, le bouton change de couleur en **vert** et affiche l'état **Connected**.
- Pour se déconnecter, il suffit d'appuyer sur le bouton **Kicad**.
- Au centre de l'écran, un graphique affiche en temps réel la résistance mesurée du capteur graphène.
- En bas de l'écran, deux valeurs sont affichées :
  - La valeur de la résistance du **potentiomètre digital** séléctionnée
  - La valeur de la résistance instantanée du **capteur graphène**
 
  ![Image](https://github.com/user-attachments/assets/0ffca166-5328-4210-a755-76f6cf1dd574)

#### Blocs MIT App Inventor

L'application utilise des blocs pour :

- Établir la connexion Bluetooth
- Recevoir les données depuis l'Arduino via UART
- Traiter les données reçues et les afficher dans un graphique
- Mettre à jour l'interface en fonction de l'état de la connexion

Voici une image représentant les blocs utilisés dans le projet :

![Image](https://github.com/user-attachments/assets/ed322dd1-6f0d-4da5-89ca-ad9bb435ec90)

---
### 5) Réalisation Physique du Circuit

Le circuit final a été soudé et testé dans les laboratoires du département. Des tests ont confirmé la stabilité du signal et l’efficacité des différents modules. Les soudures ont été réalisées manuellement pour garantir une bonne qualité de connexion.

---
### 6) Banc de Test Expérimental

Le banc de test qui nous a permis de réaliser l'expérience a été developpé avec le logiciel **Fusion 360**. 
Il est composé de :
1. Un support pour le micro-contrôleur Arduino
1. Un support pour le servo moteur
1. Un bras pour lié le servo-moteur au mobile
1. Un rail 
1. Un mobile 
1. Un support pour le capteur graphène.

L'ensemble de ces pièces sont à retrouver dans le dossier "Banc de test" ainsi que la vue globale présentée plus bas.

L'idée de ce banc de test est de courber le papier à l'aide du mobile qui sera actionner par le servo-moteur. Pour avoir un ensemble de mesure à réaliser le micro-contrôleur gère l'angle de la course imposé au moteur. Ainsi, on peut raisonnablement penser que pour un même angle de course appliqué, le capteur subira toujours la même déformation. 

Les courbes de mesure à établir seront donc la variation de résistance suivant la course faite par le mobile
![Image](https://github.com/user-attachments/assets/6a50de7c-15be-4b5e-a89b-a8f4f8405a7d)

Une fois le banc installé, il n'y a plus qu'à naviguer dans le menu affiché sur l'écran OLED à l'aide de l'encodeur rotatoire pour choisir la direction du mouvement et l'inclinaison. Une fois ces paramètres séléctionné par l'utilisateur, le resultat s'affiche dans le *Serial Monitor* ici Teleplot.
![Image](https://github.com/user-attachments/assets/39f9b89d-849c-4ee4-b824-051a5b427cc9)

---
## Gestion du Projet
### 1) Répartition du travail
Au cours de ce projet, il a été necessaire de se répartir le travail pour couvrir le maximum de points importants. En cas de questions pour les futurs lecteurs ne pas hésiter à contacter les personnes sur leur différents points.
Ainsi, les tâches ont été réparties comme suit : 

- DUBREUIL Pierrick
   - KiCad : 
      - Réalisation du plans *schematic*
      - PCB : Correction d'empreintes + Routage des pistes
   - Banc de test 3D : 
      - Conception des différents éléments du banc sur Fusion 360
      - Impression des éléments du banc
   - Code Arduino : 
      - Construction du menu global
      - Gestion des commandes du servo-moteur
      - Acquisition des données du capteur graphène et affichage
- HOLM Ane-Marie
   - Développement du *front-end* de l'application Android
   - Rédaction de la *datasheet* du capteur
- TRUONG Nguyen 
   - KiCad :
      - Création d'empreintes PCB
      - Correction routage des pistes
      - Rendu 3D final
   - Code Arduino
      - Gestion de la résistance du potentiomètre digital
   - MITAPP :
      - Conception de l'application

---
### 2) Contacts
[DUBREUIL Pierrick](https://github.com/pierrickdubreuil17)(pdubreuil@insa-toulouse.fr)

[HOLM Anne-Marie](https://github.com/anemho)

[TRUONG Nguyen Gia Khanh](https://github.com/ntruonginsatls) (ntruong@insa-toulouse.fr)
