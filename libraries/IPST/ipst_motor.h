#ifndef _IPST_MOTOR_H_
#define _IPST_MOTOR_H_
#include <ipst_in_out.h>
#define MOTOR_A 1
#define MOTOR_B 2
#define MOTOR_C 3
#define MOTOR_D 4

#ifndef ALL
#define ALL 100
#endif

#ifndef ALL2
#define ALL2 102
#endif

#ifndef ALL4
#define ALL4 104
#endif

#ifndef MR12
#define MR12 112
#endif

#ifndef MR21
#define MR21 121
#endif

#define ao() motor_stop(ALL)
#define AO() motor_stop(ALL4)
//#define off(x) motor_stop(x)

int __motor3_used = 0;
int __motor4_used = 0;


#if defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__)

#define pwm1Pin 4   // pwmA connected to digital pin 4
#define dir1APin 3  // dir1A connected to digital pin 3
#define dir1BPin 2  // dir1B connected to digital pin 2
#define pwm2Pin 5  // pwmB connected to digital pin 5
#define dir2APin 6  // dir2A connected to digital pin 6
#define dir2BPin 7  // dir2B connected to digital pin 7

int __motorLastpow = 0;

void motor(char ch, int pow)
{
  long p = 0;
  if (pow >= -100 && pow <= 100)
  {
    __motorLastpow = pow;
    p = ((long)pow * 255) / 100;
    if (ch == 1 && pow >= 0)
    {
      pinMode(dir1APin, OUTPUT);
      pinMode(dir1BPin, OUTPUT);
      digitalWrite(dir1APin, LOW);
      digitalWrite(dir1BPin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
    }
    else if (ch == 1 && pow < 0)
    {
      pinMode(dir1APin, OUTPUT);
      pinMode(dir1BPin, OUTPUT);
      digitalWrite(dir1APin, HIGH);
      digitalWrite(dir1BPin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
    }
    else if (ch == 2 && pow >= 0)
    {
      pinMode(dir2APin, OUTPUT);
      pinMode(dir2BPin, OUTPUT);
      digitalWrite(dir2APin, LOW);
      digitalWrite(dir2BPin, HIGH);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }
    else if (ch == 2 && pow < 0)
    {
      pinMode(dir2APin, OUTPUT);
      pinMode(dir2BPin, OUTPUT);
      digitalWrite(dir2APin, HIGH);
      digitalWrite(dir2BPin, LOW);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }
    else if (ch == 100 && pow >= 0)
    {
      pinMode(dir1APin, OUTPUT);
      pinMode(dir1BPin, OUTPUT);
      pinMode(dir2APin, OUTPUT);
      pinMode(dir2BPin, OUTPUT);
      digitalWrite(dir1APin, LOW);
      digitalWrite(dir1BPin, HIGH);
      digitalWrite(dir2APin, LOW);
      digitalWrite(dir2BPin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }
    else if (ch == 100 && pow < 0)
    {
      pinMode(dir1APin, OUTPUT);
      pinMode(dir1BPin, OUTPUT);
      pinMode(dir2APin, OUTPUT);
      pinMode(dir2BPin, OUTPUT);
      digitalWrite(dir1APin, HIGH);
      digitalWrite(dir1BPin, LOW);
      digitalWrite(dir2APin, HIGH);
      digitalWrite(dir2BPin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }
    else if (ch == 102 && pow >= 0)
    {
      pinMode(dir1APin, OUTPUT);
      pinMode(dir1BPin, OUTPUT);
      pinMode(dir2APin, OUTPUT);
      pinMode(dir2BPin, OUTPUT);
      digitalWrite(dir1APin, LOW);
      digitalWrite(dir1BPin, HIGH);
      digitalWrite(dir2APin, LOW);
      digitalWrite(dir2BPin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }
    else if (ch == 102 && pow < 0)
    {
      pinMode(dir1APin, OUTPUT);
      pinMode(dir1BPin, OUTPUT);
      pinMode(dir2APin, OUTPUT);
      pinMode(dir2BPin, OUTPUT);
      digitalWrite(dir1APin, HIGH);
      digitalWrite(dir1BPin, LOW);
      digitalWrite(dir2APin, HIGH);
      digitalWrite(dir2BPin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }
  }
}

#else

#if defined (_POPX2_H_)
#define pwm1Pin 6   // pwmA connected to digital pin 6
#define dir1Pin 5  // dirA connected to digital pin 5
#define pwm2Pin 7  // pwmB connected to digital pin 7
#define dir2Pin 4  // dirB connected to digital pin 4
#else
#define pwm1Pin 6   // pwmA connected to digital pin 6
#define dir1Pin 4  // dirA connected to digital pin 4
#define pwm2Pin 7  // pwmB connected to digital pin 7
#define dir2Pin 5  // dirB connected to digital pin 5
#endif

#define pwm3Pin 19   // pwmA connected to digital pin 19
#define dir3Pin 16  // dirA connected to digital pin 16
#define pwm4Pin 20  // pwmB connected to digital pin 20
#define dir4Pin 17  // dirB connected to digital pin 17

int __motorLastpow = 0;

void motor(char ch, int pow)
{
  long p = 0;
  if (pow >= -100 && pow <= 100)
  {
    __motorLastpow = pow;
    p = ((long)pow * 255) / 100;
    if (ch == 1 && pow >= 0)
    {
      pinMode(dir1Pin, OUTPUT);
      digitalWrite(dir1Pin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
    }
    else if (ch == 1 && pow < 0)
    {
      pinMode(dir1Pin, OUTPUT);
      digitalWrite(dir1Pin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
    }
    else if (ch == 2 && pow >= 0)
    {
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir2Pin, LOW);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }
    else if (ch == 2 && pow < 0)
    {
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir2Pin, HIGH);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }

    else if (ch == 3 && pow >= 0)
    {
      __motor3_used = 1;
      pinMode(dir3Pin, OUTPUT);
      digitalWrite(dir3Pin, LOW);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, (int)p);
    }
    else if (ch == 3 && pow < 0)
    {
      __motor3_used = 1;
      pinMode(dir3Pin, OUTPUT);
      digitalWrite(dir3Pin, HIGH);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, -(int)p);
    }
    else if (ch == 4 && pow >= 0)
    {
      __motor4_used = 1;
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir4Pin, LOW);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, (int)p);
    }
    else if (ch == 4 && pow < 0)
    {
      __motor4_used = 1;
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir4Pin, HIGH);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, -(int)p);
    }

    else if (ch == 12 && pow < 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, HIGH);
      digitalWrite(dir2Pin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }
    else if (ch == 12 && pow >= 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, LOW);
      digitalWrite(dir2Pin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }
    else if (ch == 34 && pow >= 0)
    {
      pinMode(dir3Pin, OUTPUT);
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir3Pin, LOW);
      digitalWrite(dir4Pin, LOW);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, (int)p);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, (int)p);
    }
    else if (ch == 34 && pow < 0)
    {
      pinMode(dir3Pin, OUTPUT);
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir3Pin, HIGH);
      digitalWrite(dir4Pin, HIGH);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, -(int)p);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, -(int)p);
    }

    else if (ch == 100 && pow < 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, HIGH);
      digitalWrite(dir2Pin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }
    else if (ch == 100 && pow >= 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, LOW);
      digitalWrite(dir2Pin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }

    else if (ch == 102 && pow < 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, HIGH);
      digitalWrite(dir2Pin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }
    else if (ch == 102 && pow >= 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, LOW);
      digitalWrite(dir2Pin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }

    else if (ch == 104 && pow >= 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      pinMode(dir3Pin, OUTPUT);
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir1Pin, LOW);
      digitalWrite(dir2Pin, LOW);
      digitalWrite(dir3Pin, LOW);
      digitalWrite(dir4Pin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, (int)p);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, (int)p);
    }
    else if (ch == 104 && pow < 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      pinMode(dir3Pin, OUTPUT);
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir1Pin, HIGH);
      digitalWrite(dir2Pin, HIGH);
      digitalWrite(dir3Pin, HIGH);
      digitalWrite(dir4Pin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, -(int)p);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, -(int)p);
    }

    else if (ch == 112 && pow < 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, HIGH);
      digitalWrite(dir2Pin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }
    else if (ch == 112 && pow >= 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, LOW);
      digitalWrite(dir2Pin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }

    else if (ch == 121 && pow < 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, LOW);
      digitalWrite(dir2Pin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }
    else if (ch == 121 && pow >= 0)
    {
      pinMode(dir1Pin, OUTPUT);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir1Pin, HIGH);
      digitalWrite(dir2Pin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }
  }
}
#endif

void motor_stop(char ch)
{
#if defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__)
  if (ch == 1)
  {
    pinMode(pwm1Pin, OUTPUT);
    analogWrite(pwm1Pin, 0);
  }
  else if (ch == 2)
  {
    pinMode(pwm2Pin, OUTPUT);
    analogWrite(pwm2Pin, 0);
  }
  else if (ch == 12)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
  }
  else if (ch == 100)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
  }
  else if (ch == 102)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
  }
  
#else
  if (ch == 1)
  {
    pinMode(pwm1Pin, OUTPUT);
    analogWrite(pwm1Pin, 0);
  }
  else if (ch == 2)
  {
    pinMode(pwm2Pin, OUTPUT);
    analogWrite(pwm2Pin, 0);
  }

  else if (ch == 3)
  {
    pinMode(pwm3Pin, OUTPUT);
    analogWrite(pwm3Pin, 0);
  }
  else if (ch == 4)
  {
    pinMode(pwm4Pin, OUTPUT);
    analogWrite(pwm4Pin, 0);
  }
  else if (ch == 12)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
  }
  else if (ch == 34)
  {
    pinMode(pwm3Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm4Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm3Pin, 0);
    analogWrite(pwm4Pin, 0);
  }
  else if (ch == 100)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
  }
  else if (ch == 102)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
  }
  else if (ch == 104)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm3Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm4Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
    analogWrite(pwm3Pin, 0);
    analogWrite(pwm4Pin, 0);
  }
  else if (ch == 112)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
  }
  else if (ch == 121)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
  }


#endif
  __motorLastpow = 0;
}

void motor(char ch, int pow, int step)
{
  int i;
  if (pow > __motorLastpow)
  {
    for (i = __motorLastpow; i <= pow; i++)
    {
      motor(ch, i);
      delay(step);
    }
    __motorLastpow = pow;
  }
  else
  {
    for (i = __motorLastpow; i >= pow; i--)
    {
      motor(ch, i);
      delay(step);
    }
    __motorLastpow = pow;
  }
}

void fd(int8_t speed)
{
  motor(ALL, speed);
}
void fd2(int8_t speed1, int8_t speed2)
{
  motor(1, speed1);
  motor(2, speed2);
}
void bk(int8_t speed)
{
  motor(ALL, -speed);
}
void bk2(int8_t speed1, int8_t speed2)
{
  motor(1, -speed1);
  motor(2, -speed2);
}
void tl(int8_t speed)
{
  motor(1, 0);
  motor(2, speed);
}
void tr(int8_t speed)
{
  motor(1, speed);
  motor(2, 0);
}
void sl(int8_t speed)
{
  //     motor(1,-speed);
  //     motor(2,speed);
  motor(MR21, speed);
}
void sr(int8_t speed)
{
  //     motor(1,speed);
  //     motor(2,-speed);
  motor(MR12, speed);
}
// 4WD function helper not defined on POP-X2
#endif
