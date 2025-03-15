/**
 * segment.h
 * Définition de la classe Segment pour représenter un segment de circuit
 *
 * Cette classe permet de représenter un segment de circuit avec sa position de
 * départ, sa position de fin et sa colonne.
 *
 * Auteur: Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel et Praise Mbay
 * Mansang
 * Date: 16 avril 2024
 */

#include <avr/io.h>
#ifndef SEGMENT_H
#define SEGMENT_H

class Segment {
public:
  uint8_t startLine;
  uint8_t endLine;
  uint8_t column;

  Segment() = default;
  Segment(uint8_t startLine, uint8_t endLine, uint8_t column);
};

#endif