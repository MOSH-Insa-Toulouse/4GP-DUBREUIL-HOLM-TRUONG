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
##### Schéma du montage
![Schem](https://private-user-images.githubusercontent.com/159114395/427711064-7f09b13b-6513-4aae-9651-4c5d3be11e2d.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDMxMDEzNDIsIm5iZiI6MTc0MzEwMTA0MiwicGF0aCI6Ii8xNTkxMTQzOTUvNDI3NzExMDY0LTdmMDliMTNiLTY1MTMtNGFhZS05NjUxLTRjNWQzYmUxMWUyZC5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMzI3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDMyN1QxODQ0MDJaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1iMWMyMGIxYzE5YjJiNDdlZjhjZGFjOTM0MDFmYTcyMzgzMmQ4ZTE5ZGYzNzU2ZWMzNzRiODFjYjM2ZWVkNGFmJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.SNY8-krY5Y3t1eixZfK5xMW18EnUoTkCQSTpguYGR-0)
### Conception PCB avec KiCad
#### ***Schematic***
![Schematic](https://private-user-images.githubusercontent.com/159114395/427706696-69191b74-6cab-475c-a771-d1da2ce62b25.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDMxMDA3NzUsIm5iZiI6MTc0MzEwMDQ3NSwicGF0aCI6Ii8xNTkxMTQzOTUvNDI3NzA2Njk2LTY5MTkxYjc0LTZjYWItNDc1Yy1hNzcxLWQxZGEyY2U2MmIyNS5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMzI3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDMyN1QxODM0MzVaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT05NzZjOGZiMmExYzUzMzFkNjQwZmMzZTQ3YWQ4YmQ2YWE4YWYxMTU4YTExNTYzYzk1NzE2NzU2MjE1OWZiODczJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.dxGNtmAtj5LKc0gcwcDr5T-1cyzDMHGNiOOLVnf09so)

#### ***PCB Editor***
![PCB](https://private-user-images.githubusercontent.com/159114395/427710018-6f81671d-c8af-4ca8-b360-56f7b37c1010.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDMxMDExNjIsIm5iZiI6MTc0MzEwMDg2MiwicGF0aCI6Ii8xNTkxMTQzOTUvNDI3NzEwMDE4LTZmODE2NzFkLWM4YWYtNGNhOC1iMzYwLTU2ZjdiMzdjMTAxMC5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMzI3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDMyN1QxODQxMDJaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT04MWU2MmRhNTFjZDg2MWQ3YTA5OTViZGY4NWJlYWY3YWVjNTc1NTUyYTk2NzZiNGFmNWFmZThlZDJiNTk1NjkwJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.yy_Xw6SySsbUzpAKJ-4dfs-Jr_l7zaDHZTiup6-al3M)


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

[TRUONG Nguyen](https://github.com/ntruonginsatls)
