README (English)
Robot Navigation and Circuit Mapping Project
Description:
This project involves two robots working together to navigate and map a circuit defined by black tape. The first robot navigates the circuit, calculates distances and parameters, and transmits this data via infrared communication to the second robot. The second robot receives the data, processes it, and displays a visual representation of the circuit.

Key Features:

Navigation: The first robot follows a black tape circuit using infrared sensors and calculates the distances between segments.

Data Transmission: The robot transmits the circuit data (segment lengths, positions, etc.) to the second robot using infrared communication.

Circuit Visualization: The second robot receives the data and displays a graphical representation of the circuit.

Technologies Used:

Microcontroller: AVR (ATmega series)

Sensors: Infrared sensors for line detection and distance measurement.

Communication: Infrared (IR) for data transmission between robots.

Programming: C/C++ with AVR libraries for motor control, sensor reading, and communication.

How It Works:

The first robot navigates the circuit, detecting black tape segments and measuring distances.

It calculates the parameters of the circuit (segment lengths, positions, etc.).

The robot transmits this data to the second robot using infrared communication.

The second robot receives the data and processes it to generate a visual representation of the circuit.

Project Structure:

main.cpp: Main program controlling the robot's navigation, data calculation, and transmission.

Modules: Includes libraries for motor control (Wheel), sensor reading (LineSensor), infrared communication (IRReceiver), and circuit visualization (RobotAffichage).

Requirements:

AVR microcontroller (ATmega series)

Infrared sensors

Motors and wheels for robot movement

Piezo buzzer for sound feedback

LEDs for status indication

Authors:
Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel, Praise Mbay Mansang

README (Français)
Projet de Navigation Robotique et Cartographie de Circuit
Description :
Ce projet met en œuvre deux robots qui collaborent pour naviguer et cartographier un circuit défini par un ruban noir. Le premier robot parcourt le circuit, calcule les distances et les paramètres, puis transmet ces données par communication infrarouge au deuxième robot. Ce dernier reçoit les données, les traite, et affiche une représentation visuelle du circuit.

Fonctionnalités Clés :

Navigation : Le premier robot suit un circuit de ruban noir à l'aide de capteurs infrarouges et calcule les distances entre les segments.

Transmission de Données : Le robot transmet les données du circuit (longueurs des segments, positions, etc.) au deuxième robot via une communication infrarouge.

Visualisation du Circuit : Le deuxième robot reçoit les données et affiche une représentation graphique du circuit.

Technologies Utilisées :

Microcontrôleur : AVR (série ATmega)

Capteurs : Capteurs infrarouges pour la détection de ligne et la mesure de distance.

Communication : Infrarouge (IR) pour la transmission de données entre les robots.

Programmation : C/C++ avec des bibliothèques AVR pour le contrôle des moteurs, la lecture des capteurs et la communication.

Fonctionnement :

Le premier robot parcourt le circuit, détecte les segments de ruban noir et mesure les distances.

Il calcule les paramètres du circuit (longueurs des segments, positions, etc.).

Le robot transmet ces données au deuxième robot via une communication infrarouge.

Le deuxième robot reçoit les données et les traite pour générer une représentation visuelle du circuit.

Structure du Projet :

main.cpp : Programme principal contrôlant la navigation du robot, le calcul des données et la transmission.

Modules : Inclut des bibliothèques pour le contrôle des moteurs (Wheel), la lecture des capteurs (LineSensor), la communication infrarouge (IRReceiver), et la visualisation du circuit (RobotAffichage).

Matériel Requis :

Microcontrôleur AVR (série ATmega)

Capteurs infrarouges

Moteurs et roues pour le déplacement du robot

Buzzer piézoélectrique pour le retour sonore

LEDs pour l'indication de statut

Auteurs :
Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel, Praise Mbay Mansang
