#include "sound.h"


Sound::Sound(){
    initialisationTimer2Ctc ();
}

Sound::~Sound(){
    TCCR2A &= ~(1 << COM2A0);
    TCCR2B &= ~((1 << WGM22) | (1 << CS20)); 
}

void Sound::initialisationTimer2Ctc () {
    DDRD |= (1 << PD7) | (1 << PD6);
    TCNT2 = 0;
    TCCR2A |=  (1 << WGM21) | (1 << COM2A0);
    TCCR2B |= (1 << WGM22) | (1 << CS21); 
}

void Sound::playSound (uint16_t note){ 
    TCCR2B |= (1 << CS22) | (1<<CS21);
    PORTD |= (1 << PD7);
    PWM_FREQUENCY= DEFAULT_FREQUENCY * pow( TWO, (note-SIXTY_NINE) / TWELVE);
    OCR2A = (F_CPU/(TWO*PRESCALER*PWM_FREQUENCY)-1);

}

void Sound::stopSound () {
    TCCR2B &= ~((1 << CS21)| (1<<CS22));
}