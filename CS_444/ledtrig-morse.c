/*
 * LED Heartbeat Trigger
 *
 * Copyright (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 *
 * Based on Richard Purdie's ledtrig-timer.c and some arch's
 * CONFIG_HEARTBEAT code.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/sched/loadavg.h>
#include <linux/leds.h>
#include <linux/reboot.h>
#include "../leds.h"
#include <linux/delay.h>

int TIME_LEN = 200;

static int panic_heartbeats;

struct heartbeat_trig_data {
    unsigned int phase;
    unsigned int period;
    struct timer_list timer;
    unsigned int invert;
};

struct sub_char_data {
    unsigned int phase;
};



/*
   static void dot(void){
   led_set_brightness_nosleep(led_cdev, LED_ON);
   mod_timer(&heartbeat_data->timer, jiffies + msecs_to_jiffies(25));
   led_set_brightness_nosleep(led_cdev, LED_OFF);
   mod_timer(&heartbeat_data->timer, jiffies + msecs_to_jiffies(25));

   printk("dot \n");
   }

   static void dash(void){
   led_set_brightness_nosleep(led_cdev, LED_ON);
   mod_timer(&heartbeat_data->timer, jiffies + msecs_to_jiffies(50));
   led_set_brightness_nosleep(led_cdev, LED_OFF);
   mod_timer(&heartbeat_data->timer, jiffies + msecs_to_jiffies(25));
   printk("dash \n");
   }
   */

unsigned int led_switch = 0;
unsigned int sub_char = 0;
unsigned int index = 0;
char *word = "qwertyuiopasdfghjklzxcvbnm a";

static void dot(struct led_classdev *led_cdev, struct heartbeat_trig_data *trigger){
    switch(led_switch){
        case 0:
            printk("dot case 0\n");
            //turn on and wait
            led_set_brightness_nosleep(led_cdev, 255);
            led_switch++;
            mod_timer(&trigger->timer, jiffies + msecs_to_jiffies(TIME_LEN));
            break;
        case 1:
            printk("dot case 1\n");
            //turn off and wait
            led_set_brightness_nosleep(led_cdev, 0);
            led_switch++;
            mod_timer(&trigger->timer, jiffies + msecs_to_jiffies(TIME_LEN));
            break;
        default:
            printk("dot default\n");
            mod_timer(&trigger->timer, jiffies + msecs_to_jiffies(TIME_LEN));
            led_switch = 0;
            sub_char++;
            break;
    }
}

static void dash(struct led_classdev *led_cdev, struct heartbeat_trig_data *trigger){
    switch(led_switch){
        case 0:
            printk("dash case 0\n");
            //turn on and wait
            led_set_brightness_nosleep(led_cdev, 255);
            led_switch++;
            mod_timer(&trigger->timer, jiffies + msecs_to_jiffies(3 * TIME_LEN));
            break;
        case 1:
            printk("dash case 1\n");
            //turn off and wait
            led_set_brightness_nosleep(led_cdev, 0);
            led_switch++;
            mod_timer(&trigger->timer, jiffies + msecs_to_jiffies(TIME_LEN));
            break;
        default:
            printk("dash default\n");
            mod_timer(&trigger->timer, jiffies + msecs_to_jiffies(TIME_LEN));
            led_switch = 0;
            sub_char++;
            break;
    }
}

static void change_speed(struct heartbeat_trig_data *trigger){
    printk("INVERT: %d\n", trigger->invert);
    if(trigger->invert == 0){
        TIME_LEN = 200;
        return;
    }
    TIME_LEN = trigger->invert;
}

static void led_heartbeat_function(unsigned long data)
{
    struct led_classdev *led_cdev = (struct led_classdev *) data; 
    struct heartbeat_trig_data *heartbeat_data = led_cdev->trigger_data;
    unsigned long brightness = LED_OFF;
    unsigned long delay = 0;
    int i = 0;
    change_speed(heartbeat_data);
   
    //led_set_brightness_nosleep(led_cdev, 0);

    switch(heartbeat_data->phase){
        case 'a':
    printk("a\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'b':
    printk("b\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'c':
    printk("c\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'd':
    printk("d\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'e':
    printk("e\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'f':
    printk("f\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'g':
    printk("g\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'h':
    printk("h\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'i':
    printk("i\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'j':
    printk("j\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'k':
    printk("k\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'l':
    printk("l\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'm':
    printk("m\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'n':
    printk("n\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'o':
    printk("o\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'p':
    printk("p\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'q':
            printk("q\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'r':
            printk("r\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 's':
            printk("s\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 't':
            printk("t\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'u':
            printk("u\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'v':
            printk("v\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'w':
            printk("w\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'x':
            printk("x\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'y':
            printk("y\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        case 'z':
            printk("z\n");
            switch(sub_char){
                case 0:
                    printk("sub_char case 0\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 1:
                    printk("sub_char case 1\n");
                    dash(led_cdev, heartbeat_data);
                    break;
                case 2:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                case 3:
                    printk("sub_char case 1\n");
                    dot(led_cdev, heartbeat_data);
                    break;
                default:
                    printk("sub_char default\n");
                    sub_char = 0;
                    heartbeat_data->phase = word[index];
                    index++;
                    mod_timer(&heartbeat_data->timer, jiffies);
                    break;
            }
            break;
        //using to represent space
        case '(':
            printk("space\n");
            mod_timer(&heartbeat_data->timer, jiffies + msecs_to_jiffies(TIME_LEN*7));
            index++;    
            break;
        default:
            index = 0;
            heartbeat_data->phase = word[0];
            mod_timer(&heartbeat_data->timer, jiffies + msecs_to_jiffies(TIME_LEN*7));
            printk("DONE!\n");
            break;
    }
    
    /*
       if (unlikely(panic_heartbeats)) {
       led_set_brightness_nosleep(led_cdev, LED_OFF);
       return;
       }

       if (test_and_clear_bit(LED_BLINK_BRIGHTNESS_CHANGE, &led_cdev->work_flags))
       led_cdev->blink_brightness = led_cdev->new_blink_brightness;

    // acts like an actual heart beat -- ie thump-thump-pause... 
    switch (heartbeat_data->phase) {
    case 0:
    //            
    //             * The hyperbolic function below modifies the
    //             * heartbeat period length in dependency of the
    //             * current (1min) load. It goes through the points
    //             * f(0)=1260, f(1)=860, f(5)=510, f(inf)->300.
    //             
    heartbeat_data->period = 300 +
    (6720 << FSHIFT) / (5 * avenrun[0] + (7 << FSHIFT));
    heartbeat_data->period =
    msecs_to_jiffies(heartbeat_data->period);
    delay = msecs_to_jiffies(70);
    heartbeat_data->phase++;
    if (!heartbeat_data->invert)
    brightness = led_cdev->blink_brightness;
    break;
    case 1:
    delay = heartbeat_data->period / 4 - msecs_to_jiffies(70);
    heartbeat_data->phase++;
    if (heartbeat_data->invert)
    brightness = led_cdev->blink_brightness;
    break;
    case 2:
    delay = msecs_to_jiffies(70);
    heartbeat_data->phase++;
    if (!heartbeat_data->invert)
    brightness = led_cdev->blink_brightness;
    break;
    default:
    delay = heartbeat_data->period - heartbeat_data->period / 4 -
    msecs_to_jiffies(70);
    heartbeat_data->phase = 0;
    if (heartbeat_data->invert)
    brightness = led_cdev->blink_brightness;
    break;
    }

    led_set_brightness_nosleep(led_cdev, brightness);
    mod_timer(&heartbeat_data->timer, jiffies + delay);
    */
}

static ssize_t led_invert_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);
    struct heartbeat_trig_data *heartbeat_data = led_cdev->trigger_data;

    return sprintf(buf, "%u\n", heartbeat_data->invert);
}

static ssize_t led_invert_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);
    struct heartbeat_trig_data *heartbeat_data = led_cdev->trigger_data;
    unsigned long state;
    int ret;

    ret = kstrtoul(buf, 0, &state);
    if (ret)
        return ret;

    heartbeat_data->invert = state;

    return size;
}

static DEVICE_ATTR(speed, S_IRUGO | S_IWUSR, led_invert_show, led_invert_store);

static void to_lower(void){
    int i;
    for(i = 0; i < strlen(word); i++){
        if(word[i] >= 'A' && word[i] <= 'Z'){
            word[i] += 32;
        }
    }
}


static void heartbeat_trig_activate(struct led_classdev *led_cdev)
{
    struct heartbeat_trig_data *heartbeat_data;
    int rc;

    heartbeat_data = kzalloc(sizeof(*heartbeat_data), GFP_KERNEL);
    if (!heartbeat_data)
        return;

    led_cdev->trigger_data = heartbeat_data;
    rc = device_create_file(led_cdev->dev, &dev_attr_speed);
    if (rc) {
        kfree(led_cdev->trigger_data);
        return;
    }

    to_lower();
    printk("Lower word: %s", word);

    heartbeat_data->phase = (int) word[0];

    setup_timer(&heartbeat_data->timer,
            led_heartbeat_function, (unsigned long) led_cdev);
    //heartbeat_data->phase = 0;
    if (!led_cdev->blink_brightness)
        led_cdev->blink_brightness = led_cdev->max_brightness;
    led_heartbeat_function(heartbeat_data->timer.data);
    set_bit(LED_BLINK_SW, &led_cdev->work_flags);
    led_cdev->activated = true;
}



static void heartbeat_trig_deactivate(struct led_classdev *led_cdev)
{
    struct heartbeat_trig_data *heartbeat_data = led_cdev->trigger_data;

    if (led_cdev->activated) {
        del_timer_sync(&heartbeat_data->timer);
        device_remove_file(led_cdev->dev, &dev_attr_speed);
        kfree(heartbeat_data);
        clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
        led_cdev->activated = false;
    }
}

static struct led_trigger heartbeat_led_trigger = {
    .name     = "morse",
    .activate = heartbeat_trig_activate,
    .deactivate = heartbeat_trig_deactivate,
};

static int heartbeat_reboot_notifier(struct notifier_block *nb,
        unsigned long code, void *unused)
{
    led_trigger_unregister(&heartbeat_led_trigger);
    return NOTIFY_DONE;
}

static int heartbeat_panic_notifier(struct notifier_block *nb,
        unsigned long code, void *unused)
{
    panic_heartbeats = 1;
    return NOTIFY_DONE;
}

static struct notifier_block heartbeat_reboot_nb = {
    .notifier_call = heartbeat_reboot_notifier,
};

static struct notifier_block heartbeat_panic_nb = {
    .notifier_call = heartbeat_panic_notifier,
};

static int __init heartbeat_trig_init(void)
{
    int rc = led_trigger_register(&heartbeat_led_trigger);

    if (!rc) {
        atomic_notifier_chain_register(&panic_notifier_list,
                &heartbeat_panic_nb);
        register_reboot_notifier(&heartbeat_reboot_nb);
    }
    return rc;
}

static void __exit heartbeat_trig_exit(void)
{
    unregister_reboot_notifier(&heartbeat_reboot_nb);
    atomic_notifier_chain_unregister(&panic_notifier_list,
            &heartbeat_panic_nb);
    led_trigger_unregister(&heartbeat_led_trigger);
}

module_init(heartbeat_trig_init);
module_exit(heartbeat_trig_exit);

MODULE_AUTHOR("Atsushi Nemoto <anemo@mba.ocn.ne.jp>");
MODULE_DESCRIPTION("Morse LED trigger");
MODULE_LICENSE("GPL");
