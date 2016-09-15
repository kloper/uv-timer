/** -*- C -*-
 * @file
 *
 * @brief EEPROM-based configuration
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

#ifndef _uv_timer_config_h_
#define _uv_timer_config_h_


#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#define F_CPU 16000000
#define HAVE_PRINT
#define HAVE_PRINTF
#endif

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#ifndef __ASSEMBLY__

/**
 * @brief UV-Timer configuration structure
 *
 * Represents EEPROM layout containing all the configuration variables
 * used in UV-Timer.
 *
 */
typedef struct _uv_timer_config {
   uint8_t hd44780_initfunc; /**< 
         Parameter initial hd44780_reset(). Normally this contains 
         @ref HD44780_CMD_FUNC_SET command with parameters. 
         This value is crucial for switching HD44780 to 4-bit mode. 
         Also for my display FUNC_SET takes effect only immediately after
         reset. Any later invocation of this function does not affect 
         display operation. */

   uint8_t tty_height; /**< Number of lines in HD44780 display */
   uint8_t tty_linemap[8]; /**<
         HD44780 line map. Specifies exact address mapping for each HD44780
         line. Must contains tty_height byte pairs. Each pair is start address
         and end address of the corresponding line respectively.

         For example two line HD44780 16x2 display may have 40 bytes of DDRAM,
         first line occupying bytes from 0 to 19 and second line occupying
         bytes from 20 till 39. Since only 16 bytes of line is visible,
         we can define the tty_linemap as { 0, 16, 20, 36 } array.
         @note
         Each pair is left-closed, right-open interval. */
   uint8_t tty_policy; /**< TTY configuration. See @ref tty_policy_t.
                          Default 0x08 */

   uint32_t alarm_value; /**< Value of last timer alarm */
} uv_timer_config_t;

extern uv_timer_config_t EEMEM g_uv_timer_config;

#endif /* __ASSEMBLY__ */
#endif /* _uv_timer_config_h_ */
