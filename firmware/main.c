/** -*- C -*-
 * @file
 *
 * @brief Main file for UV-Timer
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
#include "hd44780.h"
#include "print.h"
#include "rotary.h"
#include "term.h"
#include "timer.h"

typedef struct _uv_timer_ui {
   uv_label_t heading;
   uv_button_t mode;
   uv_button_t start;
   uv_grabber_t stop;
   uv_label_t ws;
   uv_label_t colon;
   uv_frame_t frame;
   uv_counter_t hh;
   uv_counter_t mm;
   uv_counter_t ss;
   uv_counter_t seconds;
   uint8_t disp_mode;
   uint8_t countdown_started;
} uv_timer_ui_t;

static uv_timer_ui_t g_timer_ui;

static
void reset_ui(uint8_t *data)
{
   uv_timer_ui_t *ui = (uv_timer_ui_t*)data;

   uv_frame_reset(&ui->frame);

   uv_frame_add_child(&ui->frame, &ui->heading.base, 0);
   uv_frame_add_child(&ui->frame, &ui->mode.base, 1);
   uv_frame_add_child(&ui->frame, &ui->ws.base, 0);
   
   if(ui->disp_mode) {
      uv_frame_add_child(&ui->frame, &ui->hh.base.base, 0);
      uv_frame_add_child(&ui->frame, &ui->colon.base, 0);   
      uv_frame_add_child(&ui->frame, &ui->mm.base.base, 0);
      uv_frame_add_child(&ui->frame, &ui->colon.base, 0);      
      uv_frame_add_child(&ui->frame, &ui->ss.base.base, 0);   
   } else {
      uv_frame_add_child(&ui->frame, &ui->seconds.base.base, 0);   
   }      

   uv_frame_add_child(&ui->frame, &ui->ws.base, 0);
   if(!ui->countdown_started)
      uv_frame_add_child(&ui->frame, &ui->start.base, 0);
   else
      uv_frame_add_child(&ui->frame, &ui->stop.base, 1);
   
   uv_frame_render(&g_timer_ui.frame);
}

static
void change_mode(uint8_t *data)
{
   uv_timer_ui_t *ui = (uv_timer_ui_t*)data;
   
   ui->disp_mode = !ui->disp_mode;
   reset_ui(data);
}

static
void start_countdown(uint8_t *data)
{
   uv_timer_ui_t *ui = (uv_timer_ui_t*)data;

   ui->countdown_started = 1;
   reset_ui(data);
}

static
void stop_countdown(uint8_t *data)
{
   uv_timer_ui_t *ui = (uv_timer_ui_t*)data;

   ui->countdown_started = 0;
   reset_ui(data);   
}

static
void time_set(uint8_t *data)
{
}

int main(int argc, char *argv[])
{
   uint8_t reset_value = 0;
   
   reset_value = eeprom_read_byte(&g_uv_timer_config.hd44780_initfunc);
   
   hd44780_reset(reset_value);
   
   hd44780_ir_write(HD44780_CMD_DISPLAY         |
        	    HD44780_CMD_DISPLAY_ON      |
        	    HD44780_CMD_DISPLAY_CURS_ON |
        	    HD44780_CMD_DISPLAY_CURS_BLINK );
   hd44780_wait_busy();
   
   hd44780_ir_write(HD44780_CMD_EMS |
        	    HD44780_CMD_EMS_INCR);
   hd44780_wait_busy();

   rotary_init();
   uv_timer_init();

   sei();

   hd44780_print_reset();
   
   uv_label_init(&g_timer_ui.heading, "\f      UV-Timer\n");
   uv_label_init(&g_timer_ui.ws, " ");   
   uv_label_init(&g_timer_ui.colon, ":");
   uv_button_init(&g_timer_ui.mode, "MODE", change_mode,
                  (uint8_t*)&g_timer_ui);
   uv_button_init(&g_timer_ui.start, "START", start_countdown,
                  (uint8_t*)&g_timer_ui);
   uv_grabber_init(&g_timer_ui.stop, "STOP", stop_countdown,
                  (uint8_t*)&g_timer_ui);
   uv_counter_init(&g_timer_ui.hh, time_set,
                   0, 99, 2, (uint8_t*)&g_timer_ui);
   uv_counter_init(&g_timer_ui.mm, time_set,
                   0, 59, 2, (uint8_t*)&g_timer_ui);
   uv_counter_init(&g_timer_ui.ss, time_set,
                   0, 59, 2, (uint8_t*)&g_timer_ui);
   uv_counter_init(&g_timer_ui.seconds, time_set,
                   0, 1000000, 8, (uint8_t*)&g_timer_ui);

   g_timer_ui.disp_mode = 1;
   g_timer_ui.countdown_started = 0;
   
   reset_ui((uint8_t*)&g_timer_ui);
   
   int32_t prev_rotary_counter = rotary_get_rotary_counter();
   uint32_t prev_press_counter = rotary_get_press_counter();
   uint32_t prev_timer_value = uv_timer_get();
   
   while(1) {
      int32_t rotary_counter = rotary_get_rotary_counter();
      uint32_t press_counter = rotary_get_press_counter();
      uint32_t timer_value = uv_timer_get();
   
      if( prev_rotary_counter < rotary_counter ) {
         uv_frame_dispatch(&g_timer_ui.frame, FORWARD,
                           rotary_counter-prev_rotary_counter);
         uv_frame_render(&g_timer_ui.frame);
      } else if( prev_rotary_counter > rotary_counter ) {
         uv_frame_dispatch(&g_timer_ui.frame, BACKWARD,
                           prev_rotary_counter - rotary_counter);
         uv_frame_render(&g_timer_ui.frame);
      }

      if( prev_press_counter < press_counter ) {
         uv_frame_dispatch(&g_timer_ui.frame, PRESS,
                           press_counter - prev_press_counter);
         uv_frame_render(&g_timer_ui.frame);
      }

      if( timer_value - prev_timer_value >= 500 ) {
         uv_frame_dispatch(&g_timer_ui.frame, TICK, 0);
         uv_frame_render(&g_timer_ui.frame);
		 prev_timer_value = timer_value;
      }
      
      prev_rotary_counter = rotary_counter;
      prev_press_counter = press_counter;
   }
   
   return 0;
}

