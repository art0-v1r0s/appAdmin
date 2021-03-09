# Breakast Club

Project de borne Fast food en C

## Getting Started

download le projet sur Git ou Myges

### Prerequisites

Avoir les bases en C et BDD

### Installing

suivre les etapes ci-dessous :

Installer les librairies

GTK:
```
sudo apt install libgtk-3-dev
```
GLADE:
```
snap install glade
```
MYSQL:
```
sudo apt install mysql-server
```
PHPMYADMIN (simple d'utilisation) : 
```
sudo apt install phpmyadmin
```
Crée utilisateur
```
CREATE USER 'nom_utilisateur_choisi'@'localhost' IDENTIFIED BY 'mot_de_passe_solide';
```
```
GRANT ALL ON *.* TO 'nom_utilisateur_choisi'@'localhost' WITH GRANT OPTION;
```
```
FLUSH PRIVILEGES;
```
```
QUIT;
```
Connecter vous

Ajouter (Inserer) a votre BDD le fichier "Fast-Food.SQL"




## Running the project

Sur votre terminal dans le dossier entrer

COMPILER:
```
make
```
EXECUTER
```
./appAdmin
```
Pour nettoyer le dossier des executable .o 
SUPPRIMER:
```
make clean
```



## Copyright

A R T 0 - V 1 R 0 S
A R I 1 0 0 8
