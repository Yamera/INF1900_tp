# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes

Identification:

+ Travail    : Capteurs et conversion analogique/numérique
+ Section #  : 3
+ Équipe #   : 70
+ Correcteur : Laurent Bourgon

# LISIBILITÉ

## En-têtes en début de programme

| Pénalité par erreur                       | -1.5          |
| ----------------------------------------- | ------------- |
| Noms des auteurs                          |               |
| Description du programme                  |               |
| Identifications matérielles (Broches I/O) |               |
| Table des états ou autres s'il y a lieu   |               |
| __Résultat partiel__                      | __(1.5/1.5)__ |

## Identificateurs significatifs (Autodocumentation)

| Points importants                       | Poids         |
| --------------------------------------- | ------------- |
| Absence de *chiffres magiques*          | (0.0/0.5)     |
| Noms de variables décrivent l'intention | (0.5/0.5)     |
| Noms de fonctions décrivent l'intention | (0.5/0.5)     |
| __Résultat partiel__                    | __(1.0/1.5)__ |

+ (-0.5) (PB1) : Nombres magiques, ligne 102.
+ (-0.0) (PB2) : Nombres magiques, ligne 52/58.

## Commentaires pertinents

Bonnes raisons d'un commentaire

+ Explication d'un algorithme
+ Procédure peu évidente (ou *hack*)
+ Référence d'extraits de code copiés d'Internet
+ Détail du POURQUOI d'un extrait de code

| Pénalité par erreur  | -0.5          |
| -------------------- | ------------- |
| __Résultat partiel__ | __(1.0/1.0)__ |

## Indentation

| Points importants                      | Poids         |
| -------------------------------------- | ------------- |
| Indentation structurée                 | (0.5/0.5)     |
| Indentation uniforme dans le programme | (0.5/0.5)     |
| __Résultat partiel__                   | __(1.0/1.0)__ |

# MODULARITÉ ET COMPRÉHENSION

## Fonctions bien définies

| Pénalité par erreur                  | -0.5          |
| ------------------------------------ | ------------- |
| Responsabilité unique d'une fonction |               |
| Maximum de 4 paramètres              |               |
| Absence de code dupliqué             |               |
| etc                                  |               |
| __Résultat partiel__                 | __(1.0/1.0)__ |

## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0          |
| -------------------------------------------- | ------------- |
| Utilisation appropriée des registres         | -1.0          |
| Machine à états codée clairement             |               |
| Délais et minuteries utilisés judicieusement |               |
| PWM bien établi                              |               |
| Scrutation et interruptions bien utilisées   |               |
| etc                                          |               |
| __Résultat partiel__                         | __(3.0/4.0)__ |

+ (-1.0) (PB1) : Utilisation inappropriée du registre `PORTD`, ligne 55.

# FONCTIONNALITÉS

## Git

| Points importants            | Poids         |
| ---------------------------- | ------------- |
| Fichiers aux bons endroits   | (1.5/1.5)     |
| Absence de fichiers inutiles | (1.5/1.5)     |
| __Résultat partiel__         | __(3.0/3.0)__ |

## Compilation

| Points importants                            | Poids         |
| -------------------------------------------- | ------------- |
| Absence de messages d'erreurs de compilation | (1.5/1.5)     |
| Absence de messages d'attention (*warning*)  | (0.5/0.5)     |
| __Résultat partiel__                         | __(2.0/2.0)__ |

## Évaluation boîte noire

| Points importants            | Poids         |
| ---------------------------- | ------------- |
| Cas normal de fonctionnement | (2.5/2.5)     |
| Cas limites observables      | (2.5/2.5)     |
| __Résultat partiel__         | __(5.0/5.0)__ |

# Résultat

__Total des points: 18.5/20__

# Basé sur le commit suivant

```
commit b13b49a2157bbd540bbcc2ad191da93286da3406
Merge: 24c9e00 9be5442
Author: Yasmine Meraoubi <yasminemeraoubi@gmail.com>
Date:   Sat Oct 19 20:48:03 2024 -0400

    final
```

# Fichiers indésirables pertinents

Aucun

# Tous les fichiers indésirables

Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp6/pb1`

```
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c pb1.cpp
avr-gcc -Wl,-Map,tp6.elf.map -mmcu=atmega324pa -o tp6.elf  pb1.o \
 -lm
avr-objcopy -j .text -j .data -O ihex tp6.elf tp6.hex

```

## Sortie de `make` dans `tp/tp6/pb2`

```
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c pb2.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c can.cpp
avr-gcc -Wl,-Map,tp6.elf.map -mmcu=atmega324pa -o tp6.elf  pb2.o can.o \
 -lm
avr-objcopy -j .text -j .data -O ihex tp6.elf tp6.hex

```
