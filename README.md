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
    * Capteur de pression en graphite
    * Capteur de pression du commerce
    * Écran OLED
    * Encodeur Rotatoire
    * Potentiomètre digital
    * Servo-Moteur
1. Banc de test

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
- **Potentiomètre numérique** (ajustement dynamique de gain ou tension de référence)
- **Encodeur rotatif**
- **Écran OLED**
- **Module Bluetooth HC-05** (communication sans fil avec une application mobile)
- Deux broches dédiées au **capteur graphique**

L’ensemble des connexions logiques et électriques est établi dans le schéma pour s'assurer de la compatibilité avec l’Arduino.


### Étape 2 : Simulation du schéma électrique

La conception a débuté par la création d’un schéma électrique simulé sous **LTspice**. Cette simulation permet de valider le comportement du circuit d’amplification, notamment autour de l’amplificateur opérationnel **LT1050**, qui joue un rôle essentiel dans l’amplification du signal analogique issu du capteur graphite.

Une fois le schéma validé, il est reproduit dans **KiCad** afin de préparer la conception physique du circuit.

#### ***Schematic***

![Image](https://github.com/user-attachments/assets/41834f51-993d-49a6-9831-d555f277b064)



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
1. Récupérer les données du capteur *Hand-made*
1. Récupérer les données du capteur commercial
1. Gérer la communication Bluetooth
1. Gérer l'affichage OLED
1. Contrôler le servo-moteur

---
### 4) Application Android avec MITApp Inventor

Dans le cadre du banc de test du projet **capteur graphique**, nous avons développé une application Android avec **MIT App Inventor**. Cette application permet la communication sans fil avec un module **Arduino** via Bluetooth, afin de visualiser les données du capteur en temps réel.

#### Objectifs

- Établir une connexion Bluetooth entre le smartphone Android et le module Arduino.
- Afficher la résistance du **potentiomètre numérique** ainsi que celle du **capteur graphite**.
- Tracer une courbe en temps réel représentant l’évolution de la résistance du capteur.

#### Interface utilisateur

- Le bouton **Bluetooth** permet de se connecter au module Arduino via Bluetooth.
- Une fois connecté, le bouton change de couleur en **vert** et affiche l'état **Connected**.
- Pour se déconnecter, il suffit d'appuyer sur le bouton **Kicad**.
- Au centre de l'écran, un graphique affiche en temps réel la résistance du capteur graphique.
- En bas de l'écran, deux valeurs sont affichées :
  - La valeur de la résistance actuelle du **potentiomètre numérique**
  - La valeur de la résistance instantanée du **capteur graphite**
 
  ![Image](https://github.com/user-attachments/assets/0ffca166-5328-4210-a755-76f6cf1dd574)

#### Blocs MIT App Inventor

L'application utilise des blocs pour :

- Établir la connexion Bluetooth
- Recevoir les données depuis l'Arduino via UART
- Traiter les données reçues et les afficher dans un graphite
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

L'ensemble de ces pièces sont à retrouver dans le dossier "Banc de test".
L'idée de ce banc de test est de couber le papier à l'aide du mobile qui sera actionner par le servo-moteur. Pour avoir un ensemble de mesure à réaliser le micro-contrôleur gère l'angle de la course imposé au moteur. Ainsi, on peut raisonnablement pensé que pour un même angle de course appliqué, le papier subira toujours la même déformation. 
Les courbes de mesure à établir seront donc la varoiation de résistance suivant la course faite par le mobile
![Image](https://github.com/user-attachments/assets/fdeb2f92-acbf-40aa-b921-e516e770c923)

---
## Contacts
[DUBREUIL Pierrick](https://github.com/pierrickdubreuil17)

[HOLM Anne-Marie](https://github.com/anemho)

[TRUONG Nguyen Gia Khanh](https://github.com/ntruonginsatls) (ntruong@insa-toulouse.fr)
