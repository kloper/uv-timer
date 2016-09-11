/** -*- C -*-
 * @file
 *
 * @brief Permanently running timer with alarm
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

#include <string.h>
#include <stdint.h>

#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include "config.h"
#include "timer.h"

static uint32_t g_uv_timer = 0;

ISR(TIMER2_COMPA_vect)
{
   PINC |= 1<<PC5;   
   g_uv_timer++;
}

void uv_timer_init(void)
{
   DDRC |= (1<<PC5);
   
   TCCR2B = 0;   
   TCCR2A = 1<<WGM21;
   TCNT2 = 0;
   OCR2A = 249;
   TIMSK2 |= 1<<OCIE2A;
   TCCR2B = 4;
}

uint32_t uv_timer_get(void)
{
   uint32_t value;
   cli();
   value = g_uv_timer;
   sei();
   return value;
}
