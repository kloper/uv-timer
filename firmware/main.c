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
   uv_button_t stop;
   uv_label_t ws;
   uv_label_t colon;
   uv_label_t placeholder;
   uv_frame_t frame;
} uv_timer_ui_t;

static uv_timer_ui_t g_timer_ui;

void change_mode(uint8_t *data)
{
}

void start_countdown(uint8_t *data)
{
}

void stop_countdown(uint8_t *data)
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
   
   /* hd44780_ir_write(HD44780_CMD_SET_CGRAM_ADDR); */
   /* hd44780_wait_busy(); */
   /* hd44780_dr_write(0xe); */
   /* hd44780_wait_busy(); */
   /* hd44780_dr_write(0x4); */
   /* hd44780_wait_busy(); */
   /* hd44780_dr_write(0xa); */
   /* hd44780_wait_busy(); */
   /* hd44780_dr_write(0xe); */
   /* hd44780_wait_busy(); */
   /* hd44780_dr_write(0xe); */
   /* hd44780_wait_busy(); */
   /* hd44780_dr_write(0xe); */
   /* hd44780_wait_busy(); */
   /* hd44780_dr_write(0xe); */
   /* hd44780_wait_busy(); */
   /* hd44780_dr_write(0x0); */
   /* hd44780_wait_busy(); */

   /* hd44780_ir_write(HD44780_CMD_SET_DDRAM_ADDR); */
   /* hd44780_printf("Hello UV-Timer!\n");    */
   /* hd44780_dr_write(0); */
   /* hd44780_wait_busy(); */
   /* hd44780_dr_write('M'); */
   /* hd44780_wait_busy(); */

   
   uv_label_init(&g_timer_ui.heading, "\fHello UV-Timer\n");
   uv_label_init(&g_timer_ui.ws, " ");   
   uv_label_init(&g_timer_ui.colon, ":");
   uv_label_init(&g_timer_ui.placeholder, "__");      
   uv_button_init(&g_timer_ui.mode, "MODE", change_mode,
                  (uint8_t*)&g_timer_ui);
   uv_button_init(&g_timer_ui.start, "START", start_countdown,
                  (uint8_t*)&g_timer_ui);
   uv_button_init(&g_timer_ui.stop, "STOP", stop_countdown,
                  (uint8_t*)&g_timer_ui);
   uv_frame_init(&g_timer_ui.frame);
   
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.heading.base);
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.mode.base);
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.ws.base);
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.placeholder.base);
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.colon.base);   
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.placeholder.base);
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.colon.base);      
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.placeholder.base);   
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.ws.base);
   uv_frame_add_child(&g_timer_ui.frame, &g_timer_ui.start.base);

   uv_frame_dispatch(&g_timer_ui.frame, FORWARD, 0);
   uv_frame_render(&g_timer_ui.frame);
   
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

