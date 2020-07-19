/* https://github.com/sadr0b0t/arduino-timer-api */
#include "timer-api.h"

/* https://github.com/JChristensen/DS3232RTC */
/* dependency https://github.com/PaulStoffregen/Time */
#include <DS3232RTC.h>

#define TUBES_LINES 60
#define TUBES_COUNT 6
#define DATA  12
#define STROBE  11
#define CLOCK 10
#define DIM_LEVEL 1

tmElements_t tm;

// Bit array for 6 nixie tubes, 12 bits for each tube, 4 hv5812 80 in total
boolean nixieDisplayArray[TUBES_LINES];

// array of int numbers for the poisoning prevention
int digits[TUBES_COUNT][10];

/* see schematic : the HV5812 drivers */
/* number in the array is calculated in the following way: */
/* base + (20 - hv5812_line) */
/* example: tube 6, 0 digit: 0  + (20 - 19) = 61 */

/*            0    1   2   3   4   5   6   7   8  9 */
int nixie6[]={56, 40, 41, 42, 43, 44, 45, 59, 58, 57};
int nixie5[]={49, 55, 54, 53, 52, 51, 50, 46, 47, 48};
int nixie4[]={36, 20, 21, 22, 23, 24, 25, 39, 38, 37};
int nixie3[]={29, 35, 34, 33, 32, 31, 30, 26, 27, 28};
int nixie2[]={16,  0,  1,  2,  3,  4,  5, 19, 18, 17};
int nixie1[]={ 9, 15, 14, 13, 12, 11, 10, 6,   7,  8};


/* Millis delay time variable */
unsigned long previous_millis = 0;
int time_d = 0;
bool update_clock = false;

/*  encoder pins */
int pinA = 2;
int pinB = 3;
int pinSW = 13;

/* delay beetween two readings */
volatile long pause    = 50;
volatile long lastTurn = 0;
/* turn count */
volatile int count = 0;
int actualcount    = 0;
/* encoder step state   from -4 to 0 and from 0 to 4*/
volatile int state = 0;

volatile int sw_state = 0;
volatile long last_sw = 0;
int prev_sw_state = 0;

/* pins temp variables */
volatile int pinAValue = 0;
volatile int pinBValue = 0;
volatile int pinSWValue = 0;

/* encoder button state */
enum _sw_state {
  SW_NOTPRESS,
  SW_PRESSED,
  SW_LONG_PRESSED
};

/* tubes modes: clock (hour-min-sec) or calendar (year-month-day) */
enum _show {
    CLOCK_SC,
    CALENDAR,
    MODE_END
};

/* mode: show or edit */
enum _edit {
    SHOW,
    EDIT_1,
    EDIT_2,
    EDIT_3,
    EDIT_4,
    EDIT_5,
    EDIT_6,
    EDIT_END
};

static enum _show c_show, new_show;
static enum _edit edit;
String time_string;

void A()
{
  if (micros() - lastTurn < pause)
    return; /* if time less then 'pause' we should ignore the reading */
  /* get A and B states */
  pinAValue = digitalRead(pinA);
  pinBValue = digitalRead(pinB);
  /* disable irq */
  cli();
  if (state == 0  && !pinAValue &&  pinBValue || state == 2  && pinAValue && !pinBValue) {
    state += 1; /* if condition is true then state ++ */
    lastTurn = micros();
  }
  if (state == -1 && !pinAValue && !pinBValue || state == -3 && pinAValue &&  pinBValue) {
    state -= 1; /* if condition is true then state -- */
    lastTurn = micros();
  }
  /* check : do we have full step 4 sinals 2 impulses */
  setCount(state);
  /* enable irq */
  sei(); // enable IRQ

  /* if something wrong - roll back state */
  if (pinAValue && pinBValue && state != 0)
    state = 0;
}

void B();
void B()
{
  if (micros() - lastTurn < pause) return;
  pinAValue = digitalRead(pinA);
  pinBValue = digitalRead(pinB);

  cli();
  if (state == 1 && !pinAValue && !pinBValue || state == 3 && pinAValue && pinBValue) {
    state += 1;
    lastTurn = micros();
  }
  if (state == 0 && pinAValue && !pinBValue || state == -2 && !pinAValue && pinBValue) {
    state -= 1;
    lastTurn = micros();
  }
  setCount(state);
  sei();

  if (pinAValue && pinBValue && state != 0)
    state = 0;
}



void setup()
{
  int count, count_tubes;
  /* initial modes: show and mode is hours-minuties */
  edit = SHOW;
  c_show = CLOCK_SC;
  new_show = CLOCK_SC;

  for (count = 0; count < 10; count++)
   for (count_tubes = 0; count_tubes < TUBES_COUNT; count_tubes++)
     digits[count_tubes][count] = count;


  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(STROBE, OUTPUT);
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA, LOW);
  digitalWrite(STROBE, LOW);
  /* encoder pins */
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinSW, INPUT);
  /* pull-up encoder pins */
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinSW, HIGH);
  /* encoder pins interupts */
  attachInterrupt(0, A, CHANGE);
  attachInterrupt(1, B, CHANGE);
  /* timer : read and process sw pin */
  timer_init_ISR_20Hz(TIMER_DEFAULT);
  /* enable serial output */
  Serial.begin(9600);
  PreventPosoning();
  /* get time from RTC */
  RTC.read(tm);
}

void UpdateTubes()
{
    for (int i = 0; i < TUBES_LINES; i++)
    {
        digitalWrite(DATA, nixieDisplayArray[i]);
        digitalWrite(CLOCK, HIGH);
        digitalWrite(CLOCK, LOW);
    }
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
}

void MoveNum()
{

  int count, count_tubes;

  for (count = 0; count < TUBES_COUNT; count++) {
    int a, b;

    a = random(10);
    b = random(10);

    while (a == b) {
      a = random(10);
    }

    int temp;
    temp = digits[count][a];
    digits[count][a] =  digits[count][b];
    digits[count][b] = temp;
  }
}


void PreventPosoning()
{
  int count = 0;

  MoveNum();

  for (; count <= 9; count++) {
    for (int i = TUBES_LINES; i >= 0; i--)
        nixieDisplayArray[i] = 1;

    nixieDisplayArray[nixie1[digits[0][count]]] = 0;
    nixieDisplayArray[nixie2[digits[1][count]]] = 0;
    nixieDisplayArray[nixie3[digits[2][count]]] = 0;
    nixieDisplayArray[nixie4[digits[3][count]]] = 0;
    nixieDisplayArray[nixie5[digits[4][count]]] = 0;
    nixieDisplayArray[nixie6[digits[5][count]]] = 0;

    UpdateTubes();
    delay(150);
  }
}

void DisplayTime(int level)
{
    int digit1, digit2, digit3, digit4, digit5, digit6;

    switch (c_show) {
      case (CALENDAR): {
        int s = (int)tm.Year;
        int temp_year = s + 1970;
        digit1  = (tm.Day / 1)  % 10;
        digit2  = (tm.Day / 10) % 10;
        digit3  = (tm.Month / 1)  % 10;
        digit4  = (tm.Month / 10) % 10;
        digit5  = (temp_year / 1)  % 10;
        digit6  = (temp_year / 10) % 10;
      break;
      }
      case (CLOCK_SC):
        digit1  = (tm.Second / 1)  % 10;
        digit2  = (tm.Second / 10) % 10;
        digit3  = (tm.Minute / 1)  % 10;
        digit4  = (tm.Minute / 10) % 10;
        digit5  = (tm.Hour / 1)  % 10;
        digit6  = (tm.Hour / 10) % 10;
      break;
      default:
        digit1 = 0;
        digit2 = 0;
        digit3 = 0;
        digit4 = 0;
        digit5 = 0;
        digit6 = 0;
      break;
    }

    /* Translate values to cathodes numbers connected to outputs of the HV5812 */
    digit1 = nixie1[digit1];
    digit2 = nixie2[digit2];
    digit3 = nixie3[digit3];
    digit4 = nixie4[digit4];
    digit5 = nixie5[digit5];
    digit6 = nixie6[digit6];

    for (int i = 0; i < TUBES_LINES; i++)
        nixieDisplayArray[i] = 1;

    /* Set bits corresponding to the nixie tubes cathodes */
    if ((edit == SHOW) || (level < DIM_LEVEL))  {
        nixieDisplayArray[digit1] = 0;
        nixieDisplayArray[digit2] = 0;
        nixieDisplayArray[digit3] = 0;
        nixieDisplayArray[digit4] = 0;
        nixieDisplayArray[digit5] = 0;
        nixieDisplayArray[digit6] = 0;
    } else {
        if (edit == EDIT_1)
            nixieDisplayArray[digit1] = 0;
        if (edit == EDIT_2)
            nixieDisplayArray[digit2] = 0;
        if (edit == EDIT_3)
            nixieDisplayArray[digit3] = 0;
        if (edit == EDIT_4)
            nixieDisplayArray[digit4] = 0;
        if (edit == EDIT_5)
            nixieDisplayArray[digit5] = 0;
        if (edit == EDIT_6)
            nixieDisplayArray[digit6] = 0;
    }

    UpdateTubes();
}

void loop()
{
    static int blink = 0;
    static int dim;

    if (actualcount != count) {
        actualcount = count;
        Serial.println(actualcount);
    }

    if (update_clock) {
        RTC.write(tm);
        update_clock = false;
    }

    if (c_show != new_show) {
        c_show = new_show;
        DisplayTime(10);
    }
   //PreventPosoning();
    unsigned long current_millis = millis();
    if(current_millis - previous_millis >= 1) {
        previous_millis = current_millis;
        blink += 1;
        dim = (dim > 10) ? 0 : dim + 1;

        if (blink > 20) {
            blink = 0;

            /*  In case if we  Read time from RTC  */
            if ((edit == SHOW) && (!update_clock)) {
              RTC.read(tm);
              if (tm.Second == 0)
                PreventPosoning();
              edit = SHOW;
            }
        }

        DisplayTime(dim);
    }
}


/*
        digit1 = nixie1[digit];
        digit2 = nixie2[digit];
        digit3 = nixie3[digit];
        digit4 = nixie4[digit];
        digit5 = nixie5[digit];
        digit6 = nixie6[digit];

        for (int i = 0; i < TUBES_LINES; i++)
            nixieDisplayArray[i] = 1;

        Set bits corresponding to the nixie tubes cathodes
        nixieDisplayArray[digit1] = 0;
        nixieDisplayArray[digit2] = 0;
        if (dim > 9)
            nixieDisplayArray[digit3] = 0;
        nixieDisplayArray[digit4] = 0;
        nixieDisplayArray[digit5] = 0;
        nixieDisplayArray[digit6] = 0;
        UpdateTubes();

*/

void timer_handle_interrupts(int timer) {
  static int press_count = 0, not_press_count = 0;
  static enum _sw_state state_button;

  pinSWValue = digitalRead(pinSW);

  if (pinSWValue == 0) {
    if ((press_count > 1) && (state_button != SW_PRESSED)) {
      state_button = SW_PRESSED;
      /* Serial.println("BUTTON :: SW_PRESSED"); */
      edit = edit + 1;
      if (edit == EDIT_END) {
        update_clock = true;
        edit = SHOW;
        /* Serial.println("update_clock :: true; edit = SHOW"); */
      }
    }
    not_press_count = 0;
    press_count++;
    return;
  }
  if ((pinSWValue == 1) && (state_button != SW_NOTPRESS)) {
    if (not_press_count > 1) {
      state_button = SW_NOTPRESS;
      /* Serial.println("BUTTON :: SW_NOTPRESS"); */
      return;
    }
    press_count = 0;
    not_press_count++;
  }
}


void setCount(int state) {
    int digit1, digit2, digit3, digit4, digit5, digit6;

    if (state == 4 || state == -4) {  /* do we have full step? */
        if (edit == SHOW) {
            count += (int)(state / 4);
            /* change mode (year, min-hour and etc */
            new_show =
                 (count < 0) ? (-count % (MODE_END)) : (count % (MODE_END));
        } else {
            int new_val = (int)(state / 4);
            switch (c_show) {
            case (CALENDAR):
                if ((edit == EDIT_5) || (edit == EDIT_6)) {
                    int real_year = tm.Year + 1970;
                    digit1  = (real_year / 1)  % 10;
                    digit2  = (real_year / 10) % 10;
                    digit3  = (real_year / 100)  % 10;
                    digit4  = (real_year / 1000) % 10;

                    if (edit == EDIT_5)
                      digit1 += new_val;
                    if (edit == EDIT_6)
                      digit2 += new_val;

                    real_year = ((digit1 + digit2 * 10 + digit3 * 100 +
                        digit4 * 1000) - 1970) % 256;
                    tm.Year =  real_year;
                } else {
                    digit1  = (tm.Day / 1)  % 10;
                    digit2  = (tm.Day / 10) % 10;
                    digit3  = (tm.Month / 1)  % 10;
                    digit4  = (tm.Month / 10) % 10;
                    if (edit == EDIT_1)
                        digit1  += new_val;
                    if (edit == EDIT_2)
                        digit2  += new_val;
                    if (((digit2 * 10 + digit1) % 32) < 1)
                        tm.Day = 31;
                    else if ((digit2 * 10 + digit1) > 32)
                        tm.Day = 1;
                    else
                        tm.Day =  (digit2 * 10 + digit1) % 32;

                    if (edit == EDIT_3)
                        digit3  += new_val;
                    if (edit == EDIT_4)
                        digit4  += new_val;

                    if  (((digit3 + digit4 * 10) % 13) < 1)
                        tm.Month = 1;
                    else if (((digit3 + digit4 * 10) % 13) > 13)
                        tm.Month = 1;
                    else
                        tm.Month = (digit3 + digit4 * 10) % 13;
                }
            break;
            case (CLOCK_SC):
                digit1  = (tm.Second / 1) % 10;
                digit2  = (tm.Second / 10) % 10;
                digit3  = (tm.Minute / 1)  % 10;
                digit4  = (tm.Minute / 10) % 10;
                digit5  = (tm.Hour / 1)  % 10;
                digit6  = (tm.Hour / 10) % 10;

                if (edit == EDIT_1)
                    digit1 += new_val;
                if (edit == EDIT_2)
                    digit2 += new_val;
                if (edit == EDIT_3)
                    digit3 += new_val;
                if (edit == EDIT_4)
                    digit4 += new_val;
                if (edit == EDIT_5)
                    digit5 += new_val;
                if (edit == EDIT_6)
                    digit6 += new_val;

                if ((digit1 + 10 * digit2) < 0)
                    tm.Second = 59;
                else if ((digit1 + 10 * digit2) > 59)
                    tm.Second = 0;
                else
                    tm.Second = (digit1 + 10 * digit2);

                if ((digit3 + 10 * digit4) < 0)
                    tm.Minute = 59;
                else if ((digit3 + 10 * digit4) > 59)
                    tm.Minute = 0;
                else
                    tm.Minute = (digit3 + 10 * digit4);

                if ((digit5 + digit6 * 10) < 0)
                    tm.Hour = 23;
                else if ((digit5 + digit6 * 10) > 23)
                    tm.Hour = 0;
                else
                    tm.Hour = (digit5 + digit6 * 10);

                break;
            default:
            break;
            }
        }
      lastTurn = micros();
      }
}
