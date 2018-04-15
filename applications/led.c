
#include "rtthread.h"
#include "board.h"
#include "rtdevice.h"

void led_thread_entry(void* parameter)
{
    unsigned char count = 0;       //计数器
    
    extern int _hw_pin_init(void);
    _hw_pin_init();

    rt_pin_mode(0,PIN_MODE_OUTPUT);
    rt_pin_mode(1,PIN_MODE_OUTPUT);
    rt_pin_mode(2,PIN_MODE_OUTPUT);
    rt_pin_write(0,PIN_HIGH);
    rt_pin_write(1,PIN_HIGH);
    rt_pin_write(2,PIN_HIGH);
	
    while (1)
    {
        switch(count)
        {
            case 0:
                rt_pin_write(0,PIN_LOW);
                rt_pin_write(1,PIN_HIGH);
                rt_pin_write(2,PIN_HIGH);
                break;
            case 1:
                rt_pin_write(0,PIN_HIGH);
                rt_pin_write(1,PIN_LOW);
                rt_pin_write(2,PIN_HIGH);
                break;
            case 2:
                rt_pin_write(0,PIN_HIGH);
                rt_pin_write(1,PIN_HIGH);
                rt_pin_write(2,PIN_LOW);
                break;
        }
		
	    count = (count + 1) % 3;
	    rt_thread_delay(500);
    }
}


void led_test(void * parameter)
{
	rt_thread_t t;

    /* 创建任务 */
    t = rt_thread_create("led",led_thread_entry,parameter,512,20,10);

    if (t)
    {
        rt_kprintf("\033[0;33m create thread 1 is success \033[0m \n");
        rt_thread_startup(t);
    }
	
}


