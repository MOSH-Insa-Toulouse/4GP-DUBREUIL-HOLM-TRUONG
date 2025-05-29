# 4GP-DUBREUIL-HOLM-TRUONG

## SMOMAIRE
- [Présentation](#Présentation)
- [Matériel necessaire](#Matériel-necessaire)
   - [Software](#Software)
   - [Hardware](#Hardware)
- [Livrables](#Livrables)
   - [Simulation LtSpice](#Simulation-LtSpice)
   - [Code Arduino](#Code-Arduino)
   - [Application Android avec MITApp Inventor](#Application-Android-avec-MITApp-Inventor)
   - [Réalisation Physique du Circuit](#Réalisation-Physique-du-Circuit)
   - [Banc de Test Expérimental](#Banc-de-Test-Expérimental)

## Présentation
Ce répertoire présente l'ensemble des éléments nécessaire à la conception d'un capteur de pression en graphite réalisé dans le cadre de l'UF I4GPMH21 : Du capteur au banc de test en open source hardware.
L’objectif était de concevoir un dispositif de mesure de déformation utilisant un capteur innovant, low-tech, basé sur du graphite appliqué sur papier, selon le principe décrit dans l’article scientifique :  
**"Pencil Drawn Strain Gauges and Chemiresistors on Paper"** (Cheng-Wei Lin, Zhibo Zhao, Jaemyung Kim & Jiaxing Huang). Ce capteur, d'une simplicité remarquable, est constitué d'un morceau de papier sur lequel du graphite est appliqué à l'aide d'un crayon à papier.

![Image](https://github.com/user-attachments/assets/727cc681-f1a2-4a0d-8247-0b9f83917b50)

Le principe de fonctionnement repose sur l'observation que la déformation du papier entraîne une variation du nombre de particules de graphite interconnectées. Cette modification de la structure granulaire du graphite se traduit par une variation de la résistance et de la conductance du capteur. En exploitant cette propriété, il devient possible de remonter à la déformation subie, à l'instar d'une jauge de contrainte classique.

![Image](https://github.com/user-attachments/assets/bc79245b-acaf-44ab-830e-e222ee2b5f1d)

Le fonctionnement repose sur la variation de la conductivité électrique du graphite en fonction de la contrainte mécanique appliquée au support papier. Ce phénomène permet de mesurer la déformation avec une technologie simple, accessible et écologique.
## Matériel necessaire
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

## Livrables
### Simulation LtSpice


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

### Conception PCB avec KiCad

Le circuit imprimé a été entièrement conçu à l'aide du logiciel **KiCad**, incluant :
- Schéma électrique complet,
- Création et affectation des empreintes,
- Routage double face optimisé sans vias superflus.
#### ***Schematic***

![Image](https://github.com/user-attachments/assets/41834f51-993d-49a6-9831-d555f277b064)

#### ***PCB Editor***

![Image](https://github.com/user-attachments/assets/7d89c180-d199-42cf-8f1e-8d37468880a9)

### ***3D figure***

![Image](https://github.com/user-attachments/assets/48660987-a96b-4d5e-b8db-5d6eb2de74c5)


### Code Arduino
Le code Arduino doit permettre la réalisation des fonctions suivantes :
1. Récupérer les données du capteur *Hand-made*
1. Récupérer les données du capteur commercial
1. Gérer la communication Bluetooth
1. Gérer l'affichage OLED
1. Contrôler le servo-moteur

### Application Android avec MITApp Inventor

L’application Android a été conçue via **MIT App Inventor**, offrant :
- Une interface intuitive,
- La visualisation en temps réel des valeurs de résistance,
- Le contrôle du potentiomètre numérique à distance.

L’application utilise une commande spécifique (« read ») pour vider le tampon Bluetooth avant chaque lecture, assurant la fiabilité des données.

### Réalisation Physique du Circuit

Le circuit final a été soudé et testé dans les laboratoires du département. Des tests ont confirmé la stabilité du signal et l’efficacité des différents modules. Les soudures ont été réalisées manuellement pour garantir une bonne qualité de connexion.

### Banc de Test Expérimental

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
## Contacts
[DUBREUIL Pierrick](https://github.com/pierrickdubreuil17)

[HOLM Anne-Marie](https://github.com/anemho)

[TRUONG Nguyen Gia Khanh](https://github.com/ntruonginsatls)(ntruong@insa-toulouse.fr)
