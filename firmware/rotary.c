/** -*- C -*-
 * @file
 *
 * @brief Rotary encoder driver
 *
 * Copyright (c) 2014-2017 Dimitry Kloper <kloper@users.sf.net>. 
 * All rights reserved.
 *
 * @page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * official policies, either expressed or implied, of the Pato Project.
 */

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include "config.h"
#include "rotary.h"

static uint32_t g_rotary_counter = 0;
static uint16_t g_rotary_state = 0;
static uint8_t g_press_counter = 0;

static void rotary_schedule_sample(void)
{
   TCCR0B = 0;   
   TCCR0A = 0;
   TCNT0 = 0;
   OCR0A = 64;
   TIMSK0 |= 1<<OCIE0A;
   TCCR0B = 4;
}

ISR(PCINT1_vect)
{
   rotary_schedule_sample();
}

ISR(TIMER0_COMPA_vect)
{
   PINC |= 1<<PC5;
   
   TCCR0B = 0; 

   uint8_t state = PINC;
   uint8_t rotary_state = ((state & (1<<ROTA)) >> (ROTA-1)) |
                          ((state & (1<<ROTB)) >> ROTB);
   if( rotary_state != 3 ) {
      g_rotary_state = (g_rotary_state << 2) | rotary_state;
   } else {
      switch(g_rotary_state) {
         case 0b100001:
            g_rotary_counter++;
            break;
         case 0b010010:
            g_rotary_counter--;
            break;
         default:
            break;
      }
      g_rotary_state = 0;
   }

   if( !(state & (1<<ROTP)) ) {
      g_press_counter++;
   }
}

void rotary_init(void)
{   
   DDRC |= (1<<PC5);
   DDRC &= ~((1<<ROTA)|(1<<ROTB)|(1<<ROTP));

   PCMSK1 |= (1<<ROTA)|(1<<ROTB)|(1<<ROTP);
   PCICR |= 1<<PCIE1;
}

uint32_t rotary_get_rotary_counter(void)
{
   uint32_t counter = 0;
   cli();
   counter = g_rotary_counter;
   sei();

   return counter;
}

uint32_t rotary_get_press_counter(void)
{
   uint32_t counter = 0;
   cli();
   counter = g_press_counter;
   sei();

   return counter;
}
