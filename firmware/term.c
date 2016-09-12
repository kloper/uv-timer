/** -*- C -*-
 * @file
 *
 * @brief Minimal terminal graphics framework
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
#include <stdio.h>

#include <avr/eeprom.h>

#include "config.h"
#include "hd44780.h"
#include "print.h"
#include "term.h"

static char g_inverse_text[10];

static
uint32_t uv_widget_dispatch(uv_widget_t *widget,
                            uv_event_t event,
                            uint32_t event_data)
{
   switch(event) {
      case PRESS:
         if( widget->on_press )
            return widget->on_press(widget, event_data);
         break;
      case FORWARD:
         if( widget->on_forward )
            return widget->on_forward(widget, event_data);
         break;
      case BACKWARD:
         if( widget->on_backward )
            return widget->on_backward(widget, event_data);
         break;
      case FOCUS:
         if( widget->on_focus )
            return widget->on_focus(widget, event_data);
         break;
      case TICK:
         if( widget->on_tick )
            return widget->on_tick(widget, event_data);
         break;
   }

   return 0;
}

static
void uv_widget_init(uv_widget_t *widget)
{
   widget->on_event = uv_widget_dispatch;
   widget->on_press = NULL;
   widget->on_forward = NULL;
   widget->on_backward = NULL;
   widget->on_focus = NULL;
   widget->on_tick = NULL;
   widget->render = NULL;
}

static
const char *uv_label_render(uv_widget_t *widget) {
   uv_label_t *label = (uv_label_t*)widget;

   return label->text;
}

void uv_label_init(uv_label_t *widget, const char *text)
{
   uv_widget_init(&widget->base);
   widget->base.render = uv_label_render;
   widget->text = text;
}

static
const char *uv_button_render(uv_widget_t *widget) {
   uv_button_t *button = (uv_button_t*)widget;

   if( !button->inverse_text )
      return button->text;

   int inverse_text_len = min(sizeof(g_inverse_text)-1,
                              strlen(button->text));
   memset(g_inverse_text, button->inverse_char, inverse_text_len);
   g_inverse_text[inverse_text_len] = 0;

   return g_inverse_text;   
}

static
uint32_t uv_button_focus(uv_widget_t *widget,
                         uint32_t event_data)
{
   uv_button_t *button = (uv_button_t*)widget;
   if( !event_data )
      button->inverse_text = 0;
   return 1;
}

static
uint32_t uv_button_tick(uv_widget_t *widget,
                        uint32_t event_data)
{
   uv_button_t *button = (uv_button_t*)widget;

   button->inverse_text = !button->inverse_text;
   
   return 1;
}

static
uint32_t uv_button_press(uv_widget_t *widget,
                         uint32_t event_data)
{
   uv_button_t *button = (uv_button_t*)widget;
   
   if( button->press_action ) {
      button->press_action(button->user_data);
      return 1;
   }

   return 0;
}

void uv_button_init(uv_button_t *button, const char *text,
                    uv_action_callback_t press_callback,
                    uint8_t *user_data)
{
   uv_widget_init(&button->base);
   
   button->base.render = uv_button_render;
   button->base.on_focus = uv_button_focus;
   button->base.on_press = uv_button_press;
   button->base.on_tick = uv_button_tick;
   
   button->text = text;   
   button->press_action = press_callback;
   button->inverse_text = 0;
   button->inverse_char = 0xfd;
   button->user_data = user_data;
}

static
void uv_counter_press(uint8_t *data)
{
   uv_counter_t *counter = (uv_counter_t*)data;

   counter->active = !counter->active;
   if( counter->active ) 
      counter->base.inverse_char = 0xfc;
   else
      counter->base.inverse_char = 0xfd;
}

static
uint32_t uv_counter_forward(uv_widget_t *widget,
                            uint32_t event_data)
{
   uv_counter_t *counter = (uv_counter_t*)widget;

   if( !counter->active )
      return 0;

   uint32_t size = counter->max_value - counter->min_value + 1;
   counter->value = (counter->value + event_data) % size;
   
   return 1;
}

static
uint32_t uv_counter_backward(uv_widget_t *widget,
                             uint32_t event_data)
{
   uv_counter_t *counter = (uv_counter_t*)widget;

   if( !counter->active )
      return 0;

   uint32_t size = counter->max_value - counter->min_value + 1;
   counter->value = (counter->value - event_data + size) % size;
   
   return 1;
}

static
const char *uv_counter_render(uv_widget_t *widget) {
   uv_counter_t *counter = (uv_counter_t*)widget;

   int size = snprintf(counter->text, 0, "%ld", counter->value);

   memset(counter->text, '0', counter->disp_width);
   snprintf(counter->text + max(0, counter->disp_width - size),
            size+1, "%ld", counter->value);
   
   return uv_button_render(&counter->base.base);
}

void uv_counter_init(uv_counter_t *counter, 
                     uv_action_callback_t assign_action,
                     uint32_t min_value,
                     uint32_t max_value,
                     uint8_t disp_width,
                     uint8_t *user_data)
{
   uv_button_init(&counter->base, counter->text,
                  uv_counter_press, (uint8_t*)counter);
   
   counter->base.base.render = uv_counter_render;
   counter->base.base.on_forward = uv_counter_forward;
   counter->base.base.on_backward = uv_counter_backward;
   
   counter->assign_action = assign_action;
   counter->active = 0;
   counter->min_value = min_value;
   counter->max_value = max_value;
   counter->value = min_value;
   counter->disp_width = min(disp_width, sizeof(counter->text)-1);
   counter->user_data = user_data;
}


static
uint32_t uv_grabber_forward(uv_widget_t *widget,
                            uint32_t event_data)
{
   return 1;
}

static
uint32_t uv_grabber_backward(uv_widget_t *widget,
                             uint32_t event_data)
{
   return 1;
}

void uv_grabber_init(uv_grabber_t *grabber, const char *text,
                    uv_action_callback_t press_callback,
                    uint8_t *user_data)
{
   uv_button_init(grabber, text,
                  press_callback, user_data);

   grabber->base.on_forward = uv_grabber_forward;
   grabber->base.on_backward = uv_grabber_backward;
}


void uv_frame_init(uv_frame_t *frame)
{
   memset((uint8_t*)frame, '\0', sizeof(uv_frame_t));
}

void uv_frame_reset(uv_frame_t *frame)
{
   if( frame->nchildren == 0 )
      return 0;

   uv_widget_t *w = frame->children[frame->focus];
   w->on_event(w, FOCUS, 0);

   frame->nchildren = 0;
}

int uv_frame_add_child(uv_frame_t *frame, uv_widget_t *widget, uint8_t focus)
{
   if( frame->nchildren >= UV_FRAME_MAX_CHILDREN )
      return -1;

   if(focus)
      frame->focus = frame->nchildren;
   
   frame->children[frame->nchildren++] = widget;
   
   return frame->nchildren-1;
}

uint32_t uv_frame_dispatch(uv_frame_t *frame,
                           uv_event_t event,
                           uint32_t event_data)
{
   if( frame->nchildren == 0 )
      return 0;

   uint8_t focus = frame->focus;   
   uv_widget_t *w = frame->children[focus];

   uint32_t rc = w->on_event(w, event, event_data);
   if( rc )
      return rc;

   while(1) {
      switch(event) {
         case FORWARD:
            frame->focus++;
			if( frame->focus == frame->nchildren )
				frame->focus = 0;
            break;
         case BACKWARD:
			if( frame->focus == 0 )
				frame->focus = frame->nchildren;
            frame->focus--;
            break;
         default:
            return 0;
      }

      if( frame->focus == focus )
         return 0;

      w->on_event(w, FOCUS, 0);
      
      w = frame->children[frame->focus];
      rc = w->on_event(w, FOCUS, 1);
      if( rc )
         break;
   }

         
   return rc;
}

void uv_frame_render(uv_frame_t *frame)
{
   for(int i = 0; i < frame->nchildren; i++)
   {
      uv_widget_t *w = frame->children[i];
      if( w->render )
         hd44780_printf("%s", w->render(w));
   }
}
