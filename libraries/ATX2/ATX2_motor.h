#ifndef _ATX2_MOTOR_H_
#define _ATX2_MOTOR_H_
#include <ATX2_in_out.h>
#include <ATX2_XIO.h> //
#define MOTOR_A 1
#define MOTOR_B 2
#define MOTOR_C 3
#define MOTOR_D 4
#define MOTOR_E 5
#define MOTOR_F 6

#ifndef ALL
#define ALL 100
#endif

#ifndef ALL2
#define ALL2 102
#endif

#ifndef ALL4
#define ALL4 104
#endif

#ifndef ALL6
#define ALL6 106
#endif

#ifndef MR12
#define MR12 112
#endif

#ifndef MR21
#define MR21 121
#endif

#define ao() motor_stop(12)
#define AO() motor_stop(ALL6)
//#define off(x) motor_stop(x)

#define pwm1Pin 6   // pwmA connected to digital pin 6
#define dir1Pin 5  // dirA connected to digital pin 4
#define pwm2Pin 7  // pwmB connected to digital pin 7
#define dir2Pin 4  // dirB connected to digital pin 5

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
      pinMode(dir3Pin, OUTPUT);
      digitalWrite(dir3Pin, LOW);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, (int)p);
    }
    else if (ch == 3 && pow < 0)
    {
      pinMode(dir3Pin, OUTPUT);
      digitalWrite(dir3Pin, HIGH);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, -(int)p);
    }
    else if (ch == 4 && pow >= 0)
    {
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir4Pin, LOW);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, (int)p);
    }
    else if (ch == 4 && pow < 0)
    {
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir4Pin, HIGH);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, -(int)p);
    }
    else if (ch == 5 && pow >= 0)
    {
      // extend to XIO
      __XIOxfer(0x11, (int)p, 0x00, 0xff);
    }
    else if (ch == 5 && pow < 0)
    {
      // extend to XIO
      __XIOxfer(0x15, -(int)p, 0x00, 0xff);
    }
    else if (ch == 6 && pow >= 0)
    {
      // extend to XIO
      __XIOxfer(0x12, (int)p, 0x00, 0xff);
    }
    else if (ch == 6 && pow < 0)
    {
      // extend to XIO
      __XIOxfer(0x1A, -(int)p, 0x00, 0xff);
    }

    if (ch == 12 && pow >= 0)
    {
      pinMode(dir1Pin, OUTPUT);
      digitalWrite(dir1Pin, LOW);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir2Pin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }
    else if (ch == 12 && pow < 0)
    {
      pinMode(dir1Pin, OUTPUT);
      digitalWrite(dir1Pin, HIGH);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir2Pin, HIGH);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, -(int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, -(int)p);
    }
    else if (ch == 34 && pow >= 0)
    {
      pinMode(dir3Pin, OUTPUT);
      digitalWrite(dir3Pin, LOW);
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir4Pin, LOW);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, (int)p);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, (int)p);
    }
    else if (ch == 34 && pow < 0)
    {
      pinMode(dir3Pin, OUTPUT);
      digitalWrite(dir3Pin, HIGH);
      pinMode(dir4Pin, OUTPUT);
      digitalWrite(dir4Pin, HIGH);
      pinMode(pwm3Pin, OUTPUT);
      analogWrite(pwm3Pin, -(int)p);
      pinMode(pwm4Pin, OUTPUT);
      analogWrite(pwm4Pin, -(int)p);
    }

    else if (ch == 56 && pow >= 0)
    {
      // extend to XIO
      __XIOxfer(0x13, (int)p, 0x00, 0xff);
    }
    else if (ch == 56 && pow < 0)
    {
      // extend to XIO
      __XIOxfer(0x1F, -(int)p, 0x00, 0xff);
    }
    else if (ch == 102 && pow >= 0)
    {
      pinMode(dir1Pin, OUTPUT);
      digitalWrite(dir1Pin, LOW);
      pinMode(dir2Pin, OUTPUT);
      digitalWrite(dir2Pin, LOW);
      pinMode(pwm1Pin, OUTPUT);
      analogWrite(pwm1Pin, (int)p);
      pinMode(pwm2Pin, OUTPUT);
      analogWrite(pwm2Pin, (int)p);
    }
    else if (ch == 102 && pow < 0)
    {
      pinMode(dir1Pin, OUTPUT);
      digitalWrite(dir1Pin, HIGH);
      pinMode(dir2Pin, OUTPUT);
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
      ////			__XIOxfer(0x13,(int)p,0x00,0xff);
    }
    else if (ch == 100 && pow < 0)
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
      ////			__XIOxfer(0x1F,-(int)p,0x00,0xff);
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
      ////			__XIOxfer(0x13,(int)p,0x00,0xff);
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
      ////			__XIOxfer(0x1F,-(int)p,0x00,0xff);
    }
    else if (ch == 106 && pow >= 0)
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
      __XIOxfer(0x13, (int)p, 0x00, 0xff);
    }
    else if (ch == 106 && pow < 0)
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
      __XIOxfer(0x1F, -(int)p, 0x00, 0xff);
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

void motor_stop(char ch)
{
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
  else if (ch == 5)
  {
    // extend to XIO
    __XIOxfer(0x11, 0, 0x00, 0xff);
  }
  else if (ch == 6)
  {
    // extend to XIO
    __XIOxfer(0x12, 0, 0x00, 0xff);
  }
  else if (ch == 12)
  {
    pinMode(pwm1Pin, OUTPUT);
    analogWrite(pwm1Pin, 0);
    pinMode(pwm2Pin, OUTPUT);
    analogWrite(pwm2Pin, 0);
  }
  else if (ch == 34)
  {
    pinMode(pwm3Pin, OUTPUT);
    analogWrite(pwm3Pin, 0);
    pinMode(pwm4Pin, OUTPUT);
    analogWrite(pwm4Pin, 0);
  }
  else if (ch == 56)
  {
    __XIOxfer(0x13, 0, 0x00, 0xff);
  }
  else if (ch == ALL2)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
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
  else if (ch == ALL)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm3Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm4Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
    analogWrite(pwm3Pin, 0);
    analogWrite(pwm4Pin, 0);
    ////		__XIOxfer(0x13,0,0x00,0xff);
  }
  else if (ch == ALL4)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm3Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm4Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
    analogWrite(pwm3Pin, 0);
    analogWrite(pwm4Pin, 0);
    ////		__XIOxfer(0x13,0,0x00,0xff);
  }
  else if (ch == ALL6)
  {
    pinMode(pwm1Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm2Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm3Pin, OUTPUT);  // set ledPin pin as output
    pinMode(pwm4Pin, OUTPUT);  // set ledPin pin as output
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
    analogWrite(pwm3Pin, 0);
    analogWrite(pwm4Pin, 0);
    __XIOxfer(0x13, 0, 0x00, 0xff);
  }
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
  motor(12, speed);
}
void fd2(int8_t speed1, int8_t speed2)
{
  motor(1, speed1);
  motor(2, speed2);
}
void bk(int8_t speed)
{
  motor(12, -speed);
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
  motor(1, -speed);
  motor(2, speed);
}
void sr(int8_t speed)
{
  motor(1, speed);
  motor(2, -speed);
}
// For 4 WD
void FD(int8_t speed)
{
  motor(ALL, speed);
}
void FD2(int8_t speed1, int8_t speed2)
{
  motor(12, speed1);
  motor(34, speed2);
}
void BK(int8_t speed)
{
  motor(ALL, -speed);
}
void BK2(int8_t speed1, int8_t speed2)
{
  motor(12, -speed1);
  motor(34, -speed2);
}
void TL(int8_t speed)
{
  motor(12, 0);
  motor(34, speed);
}
void TR(int8_t speed)
{
  motor(12, speed);
  motor(34, 0);
}
void SL(int8_t speed)
{
  motor(12, -speed);
  motor(34, speed);
}
void SR(int8_t speed)
{
  motor(12, speed);
  motor(34, -speed);
}
#endif
