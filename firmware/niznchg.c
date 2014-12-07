/*
 * niznchg.c
 *
 * Created: 2014/9/21 21:17:06
 *  Author: whowe
 */ 

#define F_CPU 8000000

#include <avr/signature.h>
const char fusedata[] __attribute__ ((section (".fuse"))) =
{0xE2, 0xDF, 0xFF};
const char lockbits[] __attribute__ ((section (".lockbits"))) =
{0xFC};


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>


typedef unsigned char byte;

#define NTC_3950 /* NTC Type can be 3950��3380 or 3435 */

#if defined(NTC_3950)
const signed char tref[256] PROGMEM =
{
    127, 127, 127, 127, 127, 127, 127, 127, 127, 124, 120, 116, 113, 109, 107, 104,
    101,  99,  97,  95,  93,  91,  90,  88,  86,  85,  84,  82,  81,  80,  78,  77,
     76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  67,  66,  65,  64,  63,  63,
     62,  61,  61,  60,  59,  58,  58,  57,  57,  56,  55,  55,  54,  54,  53,  52,
     52,  51,  51,  50,  50,  49,  49,  48,  48,  47,  47,  46,  46,  45,  45,  44,
     44,  43,  43,  42,  42,  41,  41,  41,  40,  40,  39,  39,  38,  38,  38,  37,
     37,  36,  36,  36,  35,  35,  34,  34,  34,  33,  33,  32,  32,  32,  31,  31,
     31,  30,  30,  29,  29,  29,  28,  28,  28,  27,  27,  27,  26,  26,  26,  25,
     25,  24,  24,  24,  23,  23,  23,  22,  22,  22,  21,  21,  21,  20,  20,  20,
     19,  19,  19,  18,  18,  18,  17,  17,  16,  16,  16,  15,  15,  15,  14,  14,
     14,  13,  13,  13,  12,  12,  12,  11,  11,  11,  10,  10,   9,   9,   9,   8,
      8,   8,   7,   7,   7,   6,   6,   5,   5,   5,   4,   4,   3,   3,   3,   2,
      2,   1,   1,   1,   0,   0,  -1,  -1,  -1,  -2,  -2,  -3,  -3,  -4,  -4,  -5,
     -5,  -6,  -6,  -7,  -7,  -8,  -8,  -9,  -9, -10, -10, -11, -11, -12, -13, -13,
    -14, -14, -15, -16, -16, -17, -18, -19, -19, -20, -21, -22, -23, -24, -25, -26,
    -27, -28, -29, -30, -32, -33, -35, -36, -38, -40, -43, -46, -50, -55, -63, -127
};
#elif defined(NTC_3380)
const signed char tref[256] PROGMEM =
{
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 125, 122, 
    118, 115, 113, 110, 108, 106, 103, 101,  99,  98,  96,  94,  92,  91,  89,  88,
     87,  85,  84,  83,  81,  80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,
     69,  68,  67,  67,  66,  65,  64,  63,  63,  62,  61,  60,  60,  59,  58,  58,
     57,  56,  56,  55,  54,  54,  53,  52,  52,  51,  51,  50,  49,  49,  48,  48,
     47,  47,  46,  45,  45,  44,  44,  43,  43,  42,  42,  41,  41,  40,  40,  39,
     39,  38,  38,  37,  37,  37,  36,  36,  35,  35,  34,  34,  33,  33,  32,  32,
     32,  31,  31,  30,  30,  29,  29,  29,  28,  28,  27,  27,  26,  26,  26,  25,
     25,  24,  24,  24,  23,  23,  22,  22,  22,  21,  21,  20,  20,  20,  19,  19,
     18,  18,  18,  17,  17,  16,  16,  16,  15,  15,  14,  14,  14,  13,  13,  12,
     12,  11,  11,  11,  10,  10,   9,   9,   9,   8,   8,   7,   7,   7,   6,   6,
      5,  5,    4,   4,   4,   3,   3,   2,   2,   1,   1,   1,   0,   0,  -1,  -1,
     -2,  -2,  -3,  -3,  -4,  -4,  -5,  -5,  -5,  -6,  -6,  -7,  -7,  -8,  -9,  -9,
    -10, -10, -11, -11, -12, -12, -13, -14, -14, -15, -15, -16, -17, -17, -18, -19,
    -19, -20, -21, -21, -22, -23, -24, -25, -25, -26, -27, -28, -29, -30, -31, -32,
    -34, -35, -36, -38, -39, -41, -42, -44, -46, -49, -51, -55, -59, -64, -73, -127
};
#elif defined(NTC_3435)
const signed char tref[256] PROGMEM =
{
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 126, 123, 119,
    116, 114, 111, 108, 106, 104, 102, 100,  98,  96,  94,  93,  91,  90,  88,  87,
     85,  84,  83,  82,  80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,
     68,  67,  67,  66,  65,  64,  63,  63,  62,  61,  60,  60,  59,  58,  58,  57,
     56,  56,  55,  54,  54,  53,  52,  52,  51,  51,  50,  50,  49,  48,  48,  47,
     47,  46,  46,  45,  45,  44,  44,  43,  43,  42,  42,  41,  41,  40,  40,  39,
     39,  38,  38,  37,  37,  36,  36,  35,  35,  35,  34,  34,  33,  33,  32,  32,
     31,  31,  31,  30,  30,  29,  29,  28,  28,  28,  27,  27,  26,  26,  26,  25,
     25,  24,  24,  24,  23,  23,  22,  22,  22,  21,  21,  20,  20,  20,  19,  19,
     18,  18,  18,  17,  17,  16,  16,  16,  15,  15,  14,  14,  14,  13,  13,  12,
     12,  12,  11,  11,  10,  10,  10,   9,   9,   8,   8,   8,   7,   7,   6,   6,
      6,   5,   5,   4,   4,   4,   3,   3,   2,   2,   1,   1,   0,   0,   0,  -1,
     -1,  -2,  -2,  -3,  -3,  -4,  -4,  -5,  -5,  -6,  -6,  -7,  -7,  -8,  -8,  -9,  
     -9, -10, -10, -11, -11, -12, -12, -13, -14, -14, -15, -15, -16, -17, -17, -18,
    -19, -19, -20, -21, -22, -22, -23, -24, -25, -26, -27, -28, -28, -30, -31, -32,
    -33, -34, -35, -37, -38, -40, -42, -43, -45, -48, -51, -54, -58, -63, -72, -127
};

#endif

void init();
void init_port();
void init_adc();
void init_pwm();

void output_pwm(unsigned short pow);

unsigned short read_adc(byte source);
signed char read_temp();

void led_on(byte led);
void led_off(byte led);

void welcome();
void detect_batt();
signed short charge_fast();
signed short charge_trickle();
void batt_alert(char mode);

#define IBAT  (1 << REFS0) | (0x0d << MUX0) /* External VRef, Differential PA1-PA2, Gain 20x */
#define VBAT  (1 << REFS0) | (2 << MUX0)    /* External VRef, Single-end PA2 */
#define TBAT  (1 << REFS0) | (3 << MUX0)    /* External VRef, Single-end PA3 */

#define RED     PORTB1 
#define GREEN   PORTB0


#define BATT_VALID_LOW 231
#define BATT_VALID_HIGH 912
#define TEMP_VALID_LOW -10
#define TEMP_VALID_HIGH 49


#define CHG_FAST_CURRENT 605    /* I * 0.25 ohm / 4.3 * 20 gain / 3.667v * 1023 */
#define CHG_TRICKLE_CURRENT 330    /* I * 0.25 ohm / 4.3 * 20 gain / 3.667v * 1023 */

#define CHG_FULL 0
#define CHG_FUSE -1
#define CHG_TEMP -2
#define CHG_OTHER -3
#define CHG_BATT_GONE -4

#define CHG_PWM_MIN 10
#define CHG_PWM_MAX 254

#define CHG_FAST_STOP_VOLTAGE 903   /* V / 4.3 / 3.667 * 1023 */
#define CHG_CURRENT_FUSE 1022
#define CHG_START_THRESHOLD 300  /* detects if charge started */
#define CHG_CURRENT_TOO_LOW 10   /* detects if battery gone */


int main(void)
{
    signed short ret;
    
    init();

    welcome();
    
    while (1)
    {
        detect_batt();

        led_on(RED);
        led_off(GREEN);
        
        ret = charge_fast();
        led_off(RED);
        output_pwm(0);
        
        switch (ret)
        {
            case CHG_FULL:
                led_on(GREEN);
                break;
                
            case CHG_BATT_GONE:
                continue;
                
            case CHG_FUSE:
                batt_alert(1);
                continue;
                
            case CHG_TEMP:            
                batt_alert(0);
                continue;

            default:
                continue;
        }
       
        charge_trickle();
        
        _delay_ms(100);
    }
}

void init()
{
    init_port();
    init_pwm();
    init_adc();
    wdt_enable(WDTO_8S);
}

void init_port()
{
    /* Clear Output */
    PORTA = 0x00;
    PORTB = 0x00;
    
    /* PA[7..0] Input, PB2 as PWM Out, LEDs out */
    DDRA = 0x00;
    DDRB = 1 << DDB2 | 1 << RED | 1 << GREEN;
}

void init_pwm()
{
    /* Fast PWM */
    TCCR0A = 0 << COM0A0 | 3 << WGM00; /* Not to turn on right now */
    /* Fast PWM, Prescaler div1 */
    TCCR0B = 0 << WGM02 | 1 << CS00;
}

void init_adc()
{
    /* ADC Enable, Prescaler factor 64 */ 
    ADCSRA = (1 << ADEN) | (7 << ADPS0);
    /* Left Adjusted */
    ADCSRB = (1 << ADLAR);
    /* Digital Buffer All Cleared */
    DIDR0 = 0xff;
    /* Initial Input VBAT*/
    ADMUX = VBAT;
}

unsigned short read_adc(byte source)
{
    ADMUX = source;
    
    /* Give up the first conversion */
    ADCSRA |= (1 << ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
    
    /* Do another conversion */
    ADCSRA |= (1 << ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
    
    return ADCL | (ADCH << 8);
}


signed char read_temp()
{
    unsigned char tbat;
    
    tbat = read_adc(TBAT) >> 8;
    
    return pgm_read_byte(tref + tbat);
}

void output_pwm(unsigned short pow)
{
    if (pow == 0)
    {
        TCCR0A &= ~(3 << COM0A0); /* Turn off pwm */
        OCR0A = 0;
    }
    else
    {
        TCCR0A |= 2 << COM0A0; /* Turn on pwm */
        OCR0A = pow - 1;
    }
}

void led_on(byte led)
{
    PORTB |= (1 << led);
}

void led_off(byte led)
{
    PORTB &= ~(1 << led);
}

void welcome()
{
    int i;
    for (i = 0; i < 5; i ++)
    {
        led_off(GREEN);
        led_on(RED);
        _delay_ms(100);

        led_off(RED);
        led_on(GREEN);
        _delay_ms(50);
        
        wdt_reset();
    }
    led_off(GREEN);
    led_off(RED);
}

void detect_batt()
{
    signed char tbat;
    short vbat;
    short tick = 0;
    short detect_count = 0;
    
    output_pwm(0);
    led_off(RED);

    while (1)
    {
        vbat = read_adc(VBAT) >> 6;
        tbat = read_temp();
        
        if ((vbat >= BATT_VALID_LOW ) && (vbat <= BATT_VALID_HIGH)
            && (tbat >= TEMP_VALID_LOW ) && (tbat <= TEMP_VALID_HIGH))
        {
            detect_count ++;
            
            if (detect_count >= 5)   /* detect battery valid 3 times in a row to avoid jitter */
            {
                led_off(GREEN);
                return;
            }                
        }
        else
        {
            detect_count = 0;
        }
        
        if ((tick & 0x07) == 0)
            led_on(GREEN);
        else
            led_off(GREEN);

        tick ++;
        _delay_ms(150);
        wdt_reset();
    }
}

#define TICK_PER_SECOND   305

signed short charge_fast()
{
    unsigned char pwm;
    short ibat, vbat;
    signed char tbat;
    short seconds = 0, tick = 0;
    short old_sec = 0;
    short started = 0;
    short p2cnt = 0;

    pwm = CHG_PWM_MIN;

    led_off(GREEN);
    led_on(RED);
    
    while (1)
    {
        output_pwm(pwm);
        
        ibat = (read_adc(IBAT) >> 6);
        ibat += (read_adc(IBAT) >> 6);
        ibat += (read_adc(IBAT) >> 6);
        ibat += (read_adc(IBAT) >> 6);

        ibat = ibat >> 2;

        if ((ibat >= CHG_CURRENT_FUSE) ||
            ((pwm == CHG_PWM_MIN) && (ibat > CHG_FAST_CURRENT)))
        {
            output_pwm(0);
            return CHG_FUSE; /* Finished because of Short Current */
        }
        
        if (started)
        {        
            if (ibat <= CHG_CURRENT_TOO_LOW)
            {
                output_pwm(0);
                return CHG_BATT_GONE;
            }
        }
        else
        {
            if (ibat > CHG_START_THRESHOLD)
            {
                started = 1;
            }
        }            
        
        tbat = read_temp();
        if (tbat < TEMP_VALID_LOW)
        {
            output_pwm(0);
            return CHG_BATT_GONE;
        }
                
        if (tbat > TEMP_VALID_HIGH)
        {
            output_pwm(0);
            return CHG_TEMP; /* Temperature Fault */
        }

        if (ibat < CHG_FAST_CURRENT)
        {
            if (pwm < CHG_PWM_MAX)
            {
                pwm ++;
            }
        }
        else if (ibat > CHG_FAST_CURRENT)
        {
            if (pwm > CHG_PWM_MIN)
            {
                pwm --;
            }
        }
        
        if (seconds > 3600) 
        {
            output_pwm(0);
            return CHG_FULL; /* Finish by Timeout */
        }
                
        if (old_sec != seconds) /* Trigger when seconds change */
        {
            old_sec = seconds;
#ifdef DEBUG
    led_on(GREEN);
    _delay_ms(1);
    led_off(GREEN);
#endif    
            wdt_reset();

            if ((seconds & 0x03 ) == 0) /* V check every 4 second */
            {
                vbat = (read_adc(VBAT) >> 6) + (read_adc(VBAT) >> 6);
                vbat = vbat >> 1;
                
                if (vbat > CHG_FAST_STOP_VOLTAGE) /* do stop-and-measure only in later phase */
                {
                    output_pwm(0);
#ifdef DEBUG                
    led_on(GREEN);
#endif                
                    _delay_ms(500);
                    tick += TICK_PER_SECOND / 2;
#ifdef DEBUG
    led_off(GREEN);
#endif                
            
                    p2cnt ++;

                    vbat = (read_adc(VBAT) >> 6) + (read_adc(VBAT) >> 6);
                    vbat = vbat >> 1;
            
                    if ((vbat >= CHG_FAST_STOP_VOLTAGE) || (p2cnt > 75))
                    {
                        output_pwm(0);
                        return CHG_FULL; /* Finish at Target Voltage */
                    }
                }                    
            }
        }
        
        tick ++;
        if (tick > TICK_PER_SECOND)
        {
            tick -= TICK_PER_SECOND;
            seconds ++;  /* takes about 1 second (measured) */
        }
        _delay_ms(1);
    }
}

signed short charge_trickle()
{
    signed char tbat;
    short vbat;
    short ibat;
    unsigned t = 0;
    short i;
    unsigned char pwm;
    
    output_pwm(0);
    
    led_on(GREEN);
    led_off(RED);
    
    pwm = CHG_PWM_MIN;
    
    while (1)
    {
        vbat = read_adc(VBAT) >> 6;
        tbat = read_temp();
        
        if ((vbat < BATT_VALID_LOW ) || (tbat < TEMP_VALID_LOW ) || (tbat > TEMP_VALID_HIGH))
        {
            break;
        }
        
        if ((t & 0x7) == 0)  /* approximately 400ms * 8 = 3.2s */
        {
            led_on(RED);
            for (i = 0; i < 150; i ++)
            {
                output_pwm(pwm);
                        
                ibat = (read_adc(IBAT) >> 6);
                ibat += (read_adc(IBAT) >> 6);
                ibat += (read_adc(IBAT) >> 6);
                ibat += (read_adc(IBAT) >> 6);

                ibat = ibat >> 2;

                if (ibat >= CHG_CURRENT_FUSE)
                {
                    output_pwm(0);
                    return -1; /* Short Current */
                }
                        
                if (ibat < CHG_TRICKLE_CURRENT)
                {
                    if (pwm < CHG_PWM_MAX)
                    {
                        pwm ++;
                    }
                }
                else if (ibat > CHG_TRICKLE_CURRENT)
                {
                    if (pwm > CHG_PWM_MIN)
                    {
                        pwm --;
                    }
                }
                _delay_ms(1);
            }
            led_off(RED);
            output_pwm(0);
        }

        t ++;
        _delay_ms(400);
        wdt_reset();
    }
    
    led_off(GREEN);
    return 0;
}

void batt_alert(char mode)
{
    signed char tbat;
    short vbat;
    unsigned int tick = 0;

    output_pwm(0);
    
    while (1)
    {
        vbat = read_adc(VBAT) >> 6;
        tbat = read_temp();
        
        if ((vbat < BATT_VALID_LOW ) || (tbat < TEMP_VALID_LOW ))
        {
            led_off(RED);
            break;
        }
        
        if ((tick & 0x01) == 0)
        {
            led_on(RED);
            led_off(GREEN);
        }            
        else
        {
            led_off(RED);
            if (mode)
            {
                led_on(GREEN);
            }                
        }            
            
        tick ++;
        _delay_ms(200);
        wdt_reset();
    }
}

