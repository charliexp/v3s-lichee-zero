/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "interrupt.h"

extern int tick_timer_ack(void);
static void clock_irq(int vector, void *param)
{
    tick_timer_ack();
    rt_tick_increase();
}

extern int tick_timer_init(int tick);
void rt_hw_tick_init(void)
{
    tick_timer_init(RT_TICK_PER_SECOND);
    rt_hw_interrupt_install(50, clock_irq, RT_NULL, "Tick");
    rt_hw_interrupt_umask(50);
}

void NS16550_puts(void *com_port, const char *s)
{
    while (*s) NS16550_putc(com_port, *s++);
}

void rt_hw_board_init(void)
{
    // init mmu
    rt_hw_mmu_init();
    // init interrupt
    rt_hw_interrupt_init();
#ifdef RT_USING_HEAP
    // init memheap
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

    // init tick
    rt_hw_tick_init();
    // init pin
    rt_hw_pin_init();
    // init uart
    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

int ctrlc(void) { return 0; }

