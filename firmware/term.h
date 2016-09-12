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

#ifndef _uv_timer_term_h_
#define _uv_timer_term_h_

#define UV_FRAME_MAX_CHILDREN 16
#define UV_COUNTER_MAX_WIDTH 8

typedef enum _uv_event {
   PRESS,
   FORWARD,
   BACKWARD,
   FOCUS,
   TICK
} uv_event_t;

struct _uv_widget;
typedef uint32_t (*uv_event_manager_t)(struct _uv_widget *widget,
                                       uv_event_t event,
                                       uint32_t event_data);

typedef uint32_t (*uv_event_callback_t)(struct _uv_widget *widget,
                                      uint32_t event_data);

typedef const char *(*uv_render_callback_t)(struct _uv_widget *widget);

typedef void (*uv_action_callback_t)(uint8_t *data);

typedef struct _uv_widget {
   uv_event_manager_t on_event;   
   uv_event_callback_t on_press;
   uv_event_callback_t on_forward;
   uv_event_callback_t on_backward;
   uv_event_callback_t on_focus;
   uv_event_callback_t on_tick;
   uv_render_callback_t render;
} uv_widget_t;

typedef struct _uv_label {
   uv_widget_t base;
   const char *text;
} uv_label_t;

typedef struct _uv_button {
   uv_widget_t base;
   const char *text;
   uv_action_callback_t press_action;
   uint8_t *user_data;
   uint8_t inverse_text;
   uint8_t inverse_char;
} uv_button_t;

typedef struct _uv_counter {
   uv_button_t base;
   uv_action_callback_t assign_action;
   uint8_t active;
   uint32_t min_value;
   uint32_t max_value;
   uint32_t value;
   uint8_t disp_width;
   char text[UV_COUNTER_MAX_WIDTH];
   uint8_t *user_data;
} uv_counter_t;

typedef struct _uv_frame {
   uv_widget_t *children[UV_FRAME_MAX_CHILDREN];
   uint8_t nchildren;
   uint8_t focus;
} uv_frame_t;

extern void uv_label_init(uv_label_t *widget, const char *text);
extern void uv_frame_init(uv_frame_t *frame);
extern void uv_button_init(uv_button_t *button, const char *text,
                           uv_action_callback_t press_callback,
                           uint8_t *user_data);
extern int uv_frame_add_child(uv_frame_t *frame, uv_widget_t *widget);
extern uint32_t uv_frame_dispatch(uv_frame_t *frame,
                                  uv_event_t event,
                                  uint32_t event_data);
extern void uv_frame_render(uv_frame_t *frame);
extern void uv_counter_init(uv_counter_t *counter, 
                            uv_action_callback_t assign_action,
                            uint32_t min_value,
                            uint32_t max_value,
                            uint8_t disp_width,
                            uint8_t *user_data);

#endif /* _uv_timer_term_h_ */
