/* https://github.com/sadr0b0t/arduino-timer-api */
#include "timer-api.h"

/* https://github.com/JChristensen/DS3232RTC */
/* dependency https://github.com/PaulStoffregen/Time */
#include <DS3232RTC.h>

#define TUBES_LINES 80

#define SHUT  4
#define DATA  10
#define STROBE  11
#define CLOCK 12

tmElements_t tm;

// Bit array for 6 nixie tubes, 12 bits for each tube, 4 hv5812 80 in total
boolean nixieDisplayArray[TUBES_LINES];

/* see schematic : the HV5812 drivers */



#define T_L(base) (base + (20 - 

/* number in the array is calculated in the following way: */
/* base + (20 - hv5812_line) */
/* example: tube 6, 0 digit: 60 + (20 - 19) = 61 */

          /*  0,  1, 2, 3, 4, 5, 6, 7,  8,  9 */
int nixie1[]={10, 4, 5, 6, 7, 8, 9, 13, 12, 11};
int nixie2[]={ 3, 19,18, 17, 16, 15, 14, 0, 1, 2};
int nixie3[]={30,  24,  25,  26,  27,  28,  29,  33,  32,  31};
int nixie4[]={23, 39, 38, 37, 36, 35, 34, 20, 21, 22};
//            0    1   2   3   4   5   6   7   8  9
int nixie5[]={46, 54, 53, 52, 50, 49, 48, 47, 43, 45};
int nixie6[]={61, 65, 66, 67, 69, 64, 63, 62, 79, 60};

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

/* tubes modes: show year, month - day, hour - minuties */
/* minuties - seconds  */

enum _show {
  YEAR,
  MON_DAY,
  HOUR_MIN,
  MIN_SEC,
  MODE_END
};

/* mode: show or edit */
enum _edit {
  SHOW,
  EDIT_1,
  EDIT_2,
  EDIT_3,
  EDIT_4,
  EDIT_END
};

static enum _show c_show, new_show;
static enum _edit edit;
String time_string;

void setup()
{
  /* initial modes: show and mode is hours-minuties */
  edit = SHOW;
  c_show = HOUR_MIN;
  new_show = HOUR_MIN;

  pinMode(SHUT, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(STROBE, OUTPUT);
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA, LOW);
  digitalWrite(STROBE, LOW);
  /* turn on tubes power supply, boost converter MAX1771*/
  digitalWrite(SHUT, LOW);
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
  /* get time from RTC */
  RTC.read(tm);
}

void PrintTime()
{
  switch (c_show) {
    case (YEAR):
      Serial.print("s: YEAR ");
    break;
    case (MON_DAY):
      Serial.print("s: MON_DAY ");
    break;
    case (HOUR_MIN):
      Serial.print("s: HOUR_MIN ");
    break;
    case (MIN_SEC):
      Serial.print("s: MIN_SEC ");
    break;
    default:
    break;
  }

  switch (edit) {
    case (SHOW):
      Serial.print("e:SHOW ");
    break;
    case (EDIT_1):
      Serial.print("e:EDIT_1 ");
    break;
    case (EDIT_2):
      Serial.print("e:EDIT_2 ");
    break;
    case (EDIT_3):
      Serial.print("e:EDIT_3 ");
    break;
    case (EDIT_4):
      Serial.print("e:EDIT_4 ");
    break;
    default:
    break;
  }

  Serial.print(tm.Year);
  Serial.print(" : ");
  Serial.print(tm.Month);
  Serial.print(":");
  Serial.print(tm.Day);
  Serial.print(" : ");
  if(tm.Hour < 10)   Serial.print("0");
  Serial.print(tm.Hour);
  Serial.print(":");
  if(tm.Minute < 10) Serial.print("0");
  Serial.print(tm.Minute);
  Serial.print(":");
  if(tm.Second < 10) Serial.print("0");
  Serial.println(tm.Second);
}

void UpdateTubes()
{
    for (int i = 0; i < TUBES_LINES; i++)
    {
        digitalWrite(DATA, nixieDisplayArray[i]);
        digitalWrite(CLOCK, HIGH);
        delay (1);
        digitalWrite(CLOCK, LOW);
        delay (1);
    }
    digitalWrite(STROBE, HIGH);
    delay (1);
    digitalWrite(STROBE, LOW);
}

void PreventPosoning()
{
  int count = 0;

  for (; count <= 9; count++) {
    for (int i = 59; i >= 0; i--)
        nixieDisplayArray[i] = 1;

    nixieDisplayArray[nixie1[count]] = 0;
    nixieDisplayArray[nixie2[count]] = 0;
    nixieDisplayArray[nixie3[count]] = 0;
    nixieDisplayArray[nixie4[count]] = 0;
    nixieDisplayArray[nixie5[count]] = 0;
    nixieDisplayArray[nixie6[count]] = 0;

    UpdateTubes();
  }
}

void DisplayTime()
{
    int digit1, digit2, digit3, digit4;
    /* In case if we  Read time from RTC */
    if ((edit == SHOW) && (!update_clock)) {
      RTC.read(tm);
      if (tm.Second == 0)
        PreventPosoning();
    }

    /* Print time on serial monitor: debug purpose */
    /* PrintTime(); */

    switch (c_show) {
      case (YEAR): {
        int s = (int)tm.Year;
        int temp_year = s + 1970;
        digit1  = (temp_year / 1)  % 10;
        digit2  = (temp_year / 10) % 10;
        digit3  = (temp_year / 100)  % 10;
        digit4  = (temp_year / 1000) % 10;
      }
      break;
      case (MON_DAY):
        digit1  = (tm.Day / 1)  % 10;
        digit2  = (tm.Day / 10) % 10;
        digit3  = (tm.Month / 1)  % 10;
        digit4  = (tm.Month / 10) % 10;
      break;
      case (HOUR_MIN):
        digit1  = (tm.Minute / 1)  % 10;
        digit2  = (tm.Minute / 10) % 10;
        digit3  = (tm.Hour / 1)  % 10;
        digit4  = (tm.Hour / 10) % 10;
      break;
      case (MIN_SEC):
        digit1  = (tm.Second / 1)  % 10;
        digit2  = (tm.Second / 10) % 10;
        digit3  = (tm.Minute / 1)  % 10;
        digit4  = (tm.Minute / 10) % 10;
      break;
      default:
        digit1 = 0;
        digit2 = 0;
        digit3 = 0;
        digit4 = 0;
      break;
    }

    /* Translate values to cathodes numbers connected to outputs of the HV5812 */
    digit1 = nixie1[digit1];
    digit2 = nixie2[digit2];
    digit3 = nixie3[digit3];
    digit4 = nixie4[digit4];

    for (int i = 39; i >= 0; i--)
        nixieDisplayArray[i] = 1;

    /* Set bits corresponding to the nixie tubes cathodes */
    nixieDisplayArray[digit1] = 0;
    nixieDisplayArray[digit2] = 0;
    nixieDisplayArray[digit3] = 0;
    nixieDisplayArray[digit4] = 0;

    UpdateTubes();
}

void loop()
{
  static int digit = 0;

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
    DisplayTime();
  }

  unsigned long current_millis = millis();
  if(current_millis - previous_millis >= 1000) {
    int digit1, digit2, digit3, digit4, digit5, digit6;
    previous_millis = current_millis;
    //DisplayTime();

    digit1 = nixie1[digit];
    digit2 = nixie2[digit];
    digit3 = nixie3[digit];
    digit4 = nixie4[digit];
    digit5 = nixie5[digit];
    digit6 = nixie6[digit];

    for (int i = 0; i < TUBES_LINES; i++)
        nixieDisplayArray[i] = 1;

    /* Set bits corresponding to the nixie tubes cathodes */
    nixieDisplayArray[digit1] = 0;
    nixieDisplayArray[digit2] = 0;
    nixieDisplayArray[digit3] = 0;
    nixieDisplayArray[digit4] = 0;
    nixieDisplayArray[digit5] = 0;
    nixieDisplayArray[digit6] = 0;

    UpdateTubes();

    digit = (digit >= 9) ? 0 : digit + 1;
    
  }

}


void timer_handle_interrupts(int timer) {
  static int press_count = 0, not_press_count = 0;
  static enum _sw_state state;

  pinSWValue = digitalRead(pinSW);

  if (pinSWValue == 0) {
    if ((press_count > 1) && (state != SW_PRESSED)) {
      state = SW_PRESSED;
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
  if ((pinSWValue == 1) && (state != SW_NOTPRESS)) {
    if (not_press_count > 1) {
      state = SW_NOTPRESS;
      /* Serial.println("BUTTON :: SW_NOTPRESS"); */
      return;
    }
    press_count = 0;
    not_press_count++;
  }
}

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

void setCount(int state) {
  int digit1, digit2, digit3, digit4;

  if (state == 4 || state == -4) {  /* do we have full step? */
    if (edit == SHOW) {
      count += (int)(state / 4);
      /* change mode (year, min-hour and etc */
      new_show = (count < 0) ? (-count % (MODE_END)) : (count % (MODE_END));
    } else {
      int new_val = (int)(state / 4);

      switch (c_show) {
      case (YEAR): {
      int real_year = tm.Year + 1970;
      digit1  = (real_year / 1)  % 10;
      digit2  = (real_year / 10) % 10;
      digit3  = (real_year / 100)  % 10;
      digit4  = (real_year / 1000) % 10;

      if (edit == EDIT_1)
        digit1 += new_val;
      if (edit == EDIT_2)
        digit2 += new_val;
      if (edit == EDIT_3)
        digit3 += new_val;
      if (edit == EDIT_4)
        digit4 += new_val;

      real_year = ((digit1 + digit2 * 10 + digit3 * 100 + digit4 * 1000) - 1970) % 256;
      tm.Year =  real_year;
    }
    break;
    case (MON_DAY):
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
            tm.Month = 12;
          else if (((digit3 + digit4 * 10) % 13) > 13)
            tm.Month = 1;
          else
            tm.Month = (digit3 + digit4 * 10) % 13;
    break;
    case (HOUR_MIN):
          digit1  = (tm.Minute / 1)  % 10;
          digit2  = (tm.Minute / 10) % 10;
          digit3  = (tm.Hour / 1)  % 10;
          digit4  = (tm.Hour / 10) % 10;

          if (edit == EDIT_1)
            digit1 += new_val;
          if (edit == EDIT_2)
            digit2 += new_val;

          if ((digit1 + 10 * digit2) < 0)
            tm.Minute = 59;
          else if ((digit1 + 10 * digit2) > 59)
            tm.Minute = 0;
          else
            tm.Minute = (digit1 + 10 * digit2);
          if (edit == EDIT_3)
            digit3 += new_val;
          if (edit == EDIT_4)
            digit4 += new_val;

          if ((digit3 + digit4 * 10) < 0)
            tm.Hour = 23;
          else if ((digit3 + digit4 * 10) > 23)
            tm.Hour = 0;
          else
            tm.Hour = (digit3 + digit4 * 10);
    break;
    case (MIN_SEC):
    break;
    default:
    break;
    }
    }

  lastTurn = micros();
  }
}
