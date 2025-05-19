# 4GP-DUBREUIL-HOLM-TRUONG
## Présentation
Ce répertoire présente l'ensemble des éléments nécessaire à la conception d'un capteur de pression en graphite réalisé dans le cadre de l'UF I4GPMH21 : Du capteur au banc de test en open source hardware.
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
#### ***Schéma du montage***

![Image](https://github.com/user-attachments/assets/8ec56f1d-8405-40e8-8d74-eb53732aa1f6)

### Conception PCB avec KiCad
#### ***Schematic***

![Image](https://github.com/user-attachments/assets/41834f51-993d-49a6-9831-d555f277b064)

#### ***PCB Editor***

![Image](https://github.com/user-attachments/assets/7d89c180-d199-42cf-8f1e-8d37468880a9)

### ***3D figure***

![Image](https://github.com/user-attachments/assets/48660987-a96b-4d5e-b8db-5d6eb2de74c5)

![PCB_Zoom](https://private-user-images.githubusercontent.com/159114395/427707407-24e7c373-4ed5-4451-ad44-48b8578d2677.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDMxMDExOTAsIm5iZiI6MTc0MzEwMDg5MCwicGF0aCI6Ii8xNTkxMTQzOTUvNDI3NzA3NDA3LTI0ZTdjMzczLTRlZDUtNDQ1MS1hZDQ0LTQ4Yjg1NzhkMjY3Ny5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMzI3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDMyN1QxODQxMzBaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT00MmE0NTVmMDFjOTQzY2RjYzUxZWZkZDYyZWIxZTBjZjI1ZjkyNjEwZTQ2OTYwZjNhMWZhY2ZlZDNhZmMzYWE4JlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.CuN2I4dctzHIWRDvm5KdSwq-A_jlzrphd5sgUXLNqCo)

### Code Arduino
Le code Arduino doit permettre la réalisation des fonctions suivantes :
1. Récupérer les données du capteur *Hand-made*
1. Récupérer les données du capteur commercial
1. Gérer la communication Bluetooth
1. Gérer l'affichage OLED
1. Contrôler le servo-moteur

### Application Android avec MITApp Inventor
###
## Contacts
[DUBREUIL Pierrick](https://github.com/pierrickdubreuil17)

[HOLM Anne-Marie](https://github.com/anemho)

[TRUONG Nguyen Gia Khanh](https://github.com/ntruonginsatls)
