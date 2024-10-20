# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes

Identification:

- Travail : Machines à états finis logicielles
- Section # : 3
- Équipe # : 70
- Correcteur : Romain Lebbadi-Breteau

# LISIBILITÉ

## En-têtes en début de programme

| Pénalité par erreur                       | -1.5          |
| ----------------------------------------- | ------------- |
| Noms des auteurs                          |               |
| Description du programme                  |               |
| Identifications matérielles (Broches I/O) |               |
| Table des états ou autres s'il y a lieu   | -0.1          |
| **Résultat partiel**                      | **(1.4/1.5)** |

- -0.1: PB2 - Mauvais formattage pour `PRESS3`.

## Identificateurs significatifs (Autodocumentation)

| Points importants                       | Poids          |
| --------------------------------------- | -------------- |
| Absence de _chiffres magiques_          | (0.0/0.5)      |
| Noms de variables décrivent l'intention | (0.25/0.5)     |
| Noms de fonctions décrivent l'intention | (0.5/0.5)      |
| **Résultat partiel**                    | **(0.75/1.5)** |

- -0.25: PB1 - Le nom de variable `DELAY_MS` n'est pas descriptif.
- -0.5: PB2 - Nombres magiques dans `turnOnAmberLED`.

## Commentaires pertinents

Bonnes raisons d'un commentaire

- Explication d'un algorithme
- Procédure peu évidente (ou _hack_)
- Référence d'extraits de code copiés d'Internet
- Détail du POURQUOI d'un extrait de code

| Pénalité par erreur  | -0.5          |
| -------------------- | ------------- |
| **Résultat partiel** | **(1.0/1.0)** |

## Indentation

| Points importants                      | Poids         |
| -------------------------------------- | ------------- |
| Indentation structurée                 | (0.5/0.5)     |
| Indentation uniforme dans le programme | (0.5/0.5)     |
| **Résultat partiel**                   | **(1.0/1.0)** |

# MODULARITÉ ET COMPRÉHENSION

## Fonctions bien définies

| Pénalité par erreur                  | -0.5          |
| ------------------------------------ | ------------- |
| Responsabilité unique d'une fonction |               |
| Maximum de 4 paramètres              |               |
| Absence de code dupliqué             | -0.5          |
| etc                                  |               |
| **Résultat partiel**                 | **(0.5/1.0)** |

- -0.5: `isRelease()` devrait appeler `stateButton()` dans le return.

## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0           |
| -------------------------------------------- | -------------- |
| Utilisation appropriée des registres         |                |
| Machine à états codée clairement             |                |
| Délais et minuteries utilisés judicieusement |                |
| PWM bien établi                              |                |
| Scrutation et interruptions bien utilisées   |                |
| etc                                          | -1.25          |
| **Résultat partiel**                         | **(2.75/4.0)** |

- -1.0: `state` ne devrait pas être une variable globale.
- -0.25: PB2 - La variable `DELAY_MS` est inutile.

# FONCTIONNALITÉS

## Git

| Points importants            | Poids         |
| ---------------------------- | ------------- |
| Fichiers aux bons endroits   | (1.5/1.5)     |
| Absence de fichiers inutiles | (1.5/1.5)     |
| **Résultat partiel**         | **(3.0/3.0)** |

## Compilation

| Points importants                            | Poids         |
| -------------------------------------------- | ------------- |
| Absence de messages d'erreurs de compilation | (1.5/1.5)     |
| Absence de messages d'attention (_warning_)  | (0.5/0.5)     |
| **Résultat partiel**                         | **(2.0/2.0)** |

## Évaluation boîte noire

| Points importants            | Poids         |
| ---------------------------- | ------------- |
| Cas normal de fonctionnement | (2.0/2.5)     |
| Cas limites observables      | (2.5/2.5)     |
| **Résultat partiel**         | **(4.5/5.0)** |

- -0.5: La LED n’affiche pas correctement la couleur ambrée.

# Résultat

__Total des points: 16.9/20__

# Basé sur le commit suivant

```
commit 0c58d7c2cee6f980dcf9b76ee83c63cc589ccab2
Author: Yasmine Meraoubi <yasminemeraoubi@gmail.com>
Date:   Tue Sep 17 12:53:12 2024 -0400

    final
```

# Fichiers indésirables pertinents

Aucun

# Tous les fichiers indésirables

Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`

```
make: Entering directory '/home/romain/dev/school/inf1900-charge/inf1900-grader/correction_tp2/70/tp/tp2/pb1'
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c pb1.cpp
avr-gcc -Wl,-Map,tp2.elf.map -mmcu=atmega324pa -o tp2.elf  pb1.o \
* -lm
avr-objcopy -j .text -j .data -O ihex tp2.elf tp2.hex
make: Leaving directory '/home/romain/dev/school/inf1900-charge/inf1900-grader/correction_tp2/70/tp/tp2/pb1'

```

## Sortie de `make` dans `tp/tp2/pb2`

```
make: Entering directory '/home/romain/dev/school/inf1900-charge/inf1900-grader/correction_tp2/70/tp/tp2/pb2'
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c pb2.cpp
avr-gcc -Wl,-Map,tp2.elf.map -mmcu=atmega324pa -o tp2.elf  pb2.o \
* -lm
avr-objcopy -j .text -j .data -O ihex tp2.elf tp2.hex
make: Leaving directory '/home/romain/dev/school/inf1900-charge/inf1900-grader/correction_tp2/70/tp/tp2/pb2'

```
