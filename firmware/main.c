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

#define PWR_CTRL PC0

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
   uint8_t stop_requested;
   uint32_t alarm_value;
   uint32_t remaining_value;      
} uv_timer_ui_t;

static uv_timer_ui_t g_timer_ui;

static
void reset_ui(uint8_t *data)
{
   uv_timer_ui_t *ui = (uv_timer_ui_t*)data;

   uv_frame_reset(&ui->frame);

   uv_frame_add_child(&ui->frame, &ui->heading.base, 0);
   uv_frame_add_child(&ui->frame, &ui->mode.base, 0);
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
      uv_frame_add_child(&ui->frame, &ui->start.base, 1);
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
void schedule_stop_countdown(void *data)
{
   uv_timer_ui_t *ui = (uv_timer_ui_t*)data;

   PORTC &= ~(1<<PWR_CTRL);
   ui->stop_requested = 1;
}

static
void start_countdown(uint8_t *data)
{
   uv_timer_ui_t *ui = (uv_timer_ui_t*)data;

   if( ui->alarm_value == 0 )
      return;

   uint32_t eeprom_alarm_value =
      eeprom_read_dword(&g_uv_timer_config.alarm_value);
   if(eeprom_alarm_value != ui->alarm_value)
      eeprom_write_dword(&g_uv_timer_config.alarm_value, ui->alarm_value);
   
   uv_timer_set_alarm(ui->alarm_value, schedule_stop_countdown, data);
   PORTC |= 1<<PWR_CTRL;

   ui->countdown_started = 1;
   reset_ui(data);
}

static
void stop_countdown(uint8_t *data)
{
   uv_timer_ui_t *ui = (uv_timer_ui_t*)data;

   PORTC &= ~(1<<PWR_CTRL);

   uv_timer_set_alarm(0, NULL, NULL);
   
   ui->alarm_value = ui->remaining_value;
   ui->countdown_started = 0;
   ui->stop_requested = 0;
   
   reset_ui(data);   
}

static
void time_set(uint8_t *data)
{
   uv_timer_ui_t *ui = (uv_timer_ui_t*)data;
   
   if(ui->disp_mode) {
      ui->alarm_value = (ui->hh.value * 60 * 60 +
                         ui->mm.value * 60 +
                         ui->ss.value) * 1000;
   } else {
      ui->alarm_value = ui->seconds.value * 1000;      
   }

   ui->remaining_value = ui->alarm_value;
}

static
void show_remaining(uv_timer_ui_t *ui)
{
   uint32_t seconds = ui->remaining_value / 1000;            
   uint32_t minutes = seconds / 60;
   uint32_t hours = minutes / 60;

   ui->ss.value = seconds - minutes * 60;
   ui->mm.value = minutes - hours * 60;
   ui->hh.value = hours;
   ui->seconds.value = seconds;
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

   DDRC |= 1<<PWR_CTRL;
   
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
   g_timer_ui.stop_requested = 0;
   g_timer_ui.alarm_value = eeprom_read_dword(&g_uv_timer_config.alarm_value);
   g_timer_ui.remaining_value = g_timer_ui.alarm_value;
   
   reset_ui((uint8_t*)&g_timer_ui);
   show_remaining(&g_timer_ui);
   
   int32_t prev_rotary_counter = rotary_get_rotary_counter();
   uint32_t prev_press_counter = rotary_get_press_counter();
   uint32_t prev_tick_value = uv_timer_get();
   uint32_t prev_count_value = uv_timer_get();
   
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

      if( timer_value - prev_tick_value >= 500 ) {
         uv_frame_dispatch(&g_timer_ui.frame, TICK, 0);
         uv_frame_render(&g_timer_ui.frame);
         prev_tick_value = timer_value;
         
      }

      prev_rotary_counter = rotary_counter;
      prev_press_counter = press_counter;
      
      if( timer_value - prev_count_value >= 1000 ) {
         if( g_timer_ui.countdown_started ) {
            if( g_timer_ui.stop_requested ) {
               g_timer_ui.remaining_value = g_timer_ui.alarm_value; 
               stop_countdown(&g_timer_ui);
            } else {
               g_timer_ui.remaining_value -=
                  min(1000, g_timer_ui.remaining_value);
            } 
            show_remaining(&g_timer_ui);
            uv_frame_render(&g_timer_ui.frame);
            prev_count_value = timer_value;
         }
      }
      
   }
   
   return 0;
}

