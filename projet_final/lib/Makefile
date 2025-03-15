# Ce Makefile vous permet de compiler des projets
# pour les microcontroleurs Atmel AVR sur 
# Linux ou Unix, en utilisant l'outil AVR-GCC. 
# Ce Makefile supporte C & C++

#####      Details specifique a la cible       #####
#####  Vous devez les adapter a votre projet   #####

# Nom du microcontroleur cible
# (exemple: 'at90s8515')
MCU=atmega324pa

# Nom de votre projet
# (utilisez un seul mot, exemple: 'monprojet')
PROJECTNAME=libstatique

# Fichiers sources
# Utilisez le suffixe .cpp pour les fichiers C++
# Listez tous les fichiers à compiler, séparés par
# un espace. exemple: 'tp1.c tp2.cpp':
SRCDIR = Button Can Led Memory Sound Timer Uart Wheel Wheel2 Obstacle LineSensor Command Transmission IRreception DrawCircuit2 DrawCircuit Segment# Subfolders
PRJSRC = $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.cpp)) # Collect .cpp files from subfolders

# Inclusions additionnels (ex: -I/path/to/mydir)
INC=

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Ne pas changer 
# Liste complete des IDs disponible avec avrdude
AVRDUDE_PROGRAMMERID=usbasp

####### variables #######

#compilateur utilise
CC=avr-gcc
#Archiveur utilise
AR=avr-ar
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f

####### Options de compilation #######

# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr  -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-DF_CPU=8000000UL \
	-Wall -DDEBUG                                        

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions     

# Archiveur pour lier les librairies utilisees
ARFLAGS=crs

####### Cible (Target) #######

#Nom des cibles par defaut
TRG=$(PROJECTNAME).a

####### Definition de tout les fichiers objets #######

# Cette fonction permet de differencier les fichiers .c
# des fichiers .cpp
# Fichier C
CFILES=$(filter %.c, $(PRJSRC))
# Fichier C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

# Liste de tout les fichiers objet que nous devons creer
OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)
	
# Pour plus d'information sur cette section, consulter :
# http://bit.ly/257R53E	
# Les fonctions $(filter pattern…,text) &
# $(patsubst pattern,replacement,text) sont pertinentes
	

####### Creation des commandes du Makefile ####### 

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make install et make clean
.PHONY: all clean 

# Make all permet simplement de compiler le projet
#
all: $(TRG)

# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(AR) $(ARFLAGS) -o $(TRG) $(OBJDEPS)

# Production des fichiers object
# De C à objet
%.o: %.c
	$(CC) $(CFLAGS) -c $<
# De C++ à objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Verification des dependances (header dependencies)
-include $(foreach dir,$(SRCDIR),$(dir)/*.d)

# Pour plus d'information sur cette section, consulter:
# http://bit.ly/2580FU8

# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) $(foreach dir,$(SRCDIR),$(dir)/*.d)

# Pour plus d'information sur les phony target, consulter:
# http://bit.ly/1WBQe61

# De plus, pour mieux comprendre les makefiles et 
# leur fonctionnement, consulter la documentation de GNU Make:
# http://bit.ly/23Vpk8s

# Finalement, ce tutoriel en ligne constitut une bonne 
# introduction au Makefile:
# http://bit.ly/1XvxsN3

#####                    EOF                   #####

