

/*
 * 
 * 
 *   L   a    f    C    R    b
 *   
 *   e    d    :    c    g    ?    
 */
int A = 1;
int B = 2;
int C = 3;
int D = 4;
int E = 5;
int F = 6;
int G = 7;
int DP = 8;

int D1 = 9;
int D2 = 10;
int D3 = 11;

int OFF = HIGH;
int ON = LOW;
int D_ON = HIGH;
int D_OFF = LOW;


void setup() {
  // put your setup code herE, to run once:

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
}

void loop() {
  // put your main code herE, to run repeatedly:
//  lightAll();
//  delay(500);

//  one();
//  delay(500);
//  
//  two();
//  delay(500);
//  
//  three();
//  delay(500);
//  
//  four();
//  delay(500);
//  
//  five();
//  delay(500);
//  
//  six();
//  delay(500);
//  
//  seven();
//  delay(500);
//  
//  eight();
//  delay(500);
//  
//  nine();
//  delay(500);
//
//  zero();
//  delay(5000);

  showNumber(234);
}

void showNumber(int number) {
  if (number > 999 || number <= 0) {
    Serial.println("invalie number");
  }

  int delay_ms = 5;

  int number1 = number / 100;
  int number2 = number % 100 / 10;
  int number3 = number % 100 % 10 ;

  
  digitalWrite(D1,D_ON);
  digitalWrite(D2,D_OFF);
  digitalWrite(D3,D_OFF);
  showDigit(number1);
  delay(delay_ms);
  
  digitalWrite(D1,D_OFF);
  digitalWrite(D2,D_ON);
  digitalWrite(D3,D_OFF);
  showDigit(number2);
  delay(delay_ms);

  
  digitalWrite(D1,D_OFF);
  digitalWrite(D2,D_OFF);
  digitalWrite(D3,D_ON);
  showDigit(number3);
  delay(delay_ms);
  
}

void showDigit(int digit) {
  if (digit == 0) {
    zero();
  }
  if (digit == 1) {
    one();
  }
  if (digit == 2) {
    two();
  }
  if (digit == 3) {
    three();
  }
  if (digit == 4) {
    four();
  }
  if (digit == 5) {
    five();
  }
  if (digit == 6) {
    six();
  }
  if (digit == 7) {
    seven();
  }
  if (digit == 8) {
    eight();
  }
  if (digit == 9) {
    nine();
  }
}

void clean () {
  digitalWrite(A,OFF);
}

void lightAll() {  
  digitalWrite(D1,D_ON);
  digitalWrite(A,ON);
  digitalWrite(B,ON);
  digitalWrite(C,ON);
  digitalWrite(D,ON);
  digitalWrite(E,ON);
  digitalWrite(F,ON);
  digitalWrite(G,ON);
  digitalWrite(DP,ON);
  
  digitalWrite(D2,D_ON);
  digitalWrite(A,ON);
  digitalWrite(B,ON);
  digitalWrite(C,ON);
  digitalWrite(D,ON);
  digitalWrite(E,ON);
  digitalWrite(F,ON);
  digitalWrite(G,ON);
  digitalWrite(DP,ON);
  
  digitalWrite(D3,D_ON);
  digitalWrite(A,ON);
  digitalWrite(B,ON);
  digitalWrite(C,ON);
  digitalWrite(D,ON);
  digitalWrite(E,ON);
  digitalWrite(F,ON);
  digitalWrite(G,ON);
  digitalWrite(DP,ON);
}

void dispDec(int x)  //设定开启小数点
{
  digitalWrite(DP, ON);
}
 
void clearLEDs()  //清屏
{
  digitalWrite(A, OFF);
  digitalWrite(B, OFF);
  digitalWrite(C, OFF);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F, OFF);
  digitalWrite(G, OFF);
  digitalWrite(DP, OFF);
}
 
void zero()  //定义数字0时阴极那些管脚开关
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F, ON);
  digitalWrite(G, OFF);
}
 
void one()  //定义数字1时阴极那些管脚开关
{
  digitalWrite(A, OFF);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F, OFF);
  digitalWrite(G, OFF);
}
 
void two()  //定义数字2时阴极那些管脚开关
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, OFF);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F, OFF);
  digitalWrite(G, ON);
}
 
void three()  //定义数字3时阴极那些管脚开关
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F, OFF);
  digitalWrite(G, ON);
}
 
void four()  //定义数字4时阴极那些管脚开关
{
  digitalWrite(A, OFF);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F, ON);
  digitalWrite(G, ON);
}
 
void five()  //定义数字5时阴极那些管脚开关
{
  digitalWrite(A, ON);
  digitalWrite(B, OFF);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F, ON);
  digitalWrite(G, ON);
}
 
void six()  //定义数字6时阴极那些管脚开关
{
  digitalWrite(A, ON);
  digitalWrite(B, OFF);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F, ON);
  digitalWrite(G, ON);
}
 
void seven()  //定义数字7时阴极那些管脚开关
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F, OFF);
  digitalWrite(G, OFF);
}
 
void eight()  //定义数字8时阴极那些管脚开关
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F, ON);
  digitalWrite(G, ON);
}
 
void nine()  //定义数字9时阴极那些管脚开关
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F, ON);
  digitalWrite(G, ON);
}
