#include <LiquidCrystal_I2C.h>
//각 음표의 주파수 값을 저장
#define NoteA 440
#define NoteB 493
#define NoteC 262
#define NoteD 295
#define NoteE 330
#define NoteF 349
#define NoteG 394
#define NoteHC 523
#define NoteHD 587
#define NoteHE 659
#define NoteBf 466
#define NoteEf 311
#define NoteHEf 622
#define NoteLBf 233

const int BUZ=12;
const int BTN=2;
//7segment
const int APIN1=3;
const int APIN2=4;
const int APIN3=5;
const int APIN4=6;
const int APIN5=7;
const int APIN6=8;
const int APIN7=9;
const int APIN8=10;


LiquidCrystal_I2C lcd(0x3F,16,2);
//각 음표의 박자를 배열로 담아둠 4분음표 4박
int beat[]={8,4,4,
4,3,1,8,
6,4,2,4,
12,4,
6,2,8,
4,3,1,8,
6,2,4,4,
12,4,
8,4,4,
4,4,8,
8,4,4,
4,4,4,3,1,
8,2,2,2,2,
8,4,4,
8,4,4,
12,4,
3,1,2,2,8,
3,1,2,2,8,
6,2,4,4,
12,4,
8,2,2,2,2,
12,3,1,
6,2,4,4,
12,4};
//각 위치의 멜로디를 배열로 담아둠
int melody[]= {
  NoteBf,NoteBf,NoteHC,NoteBf,NoteA,NoteG,NoteF,NoteLBf,NoteC,NoteD,NoteLBf,NoteF,0,
  NoteG,NoteF,NoteEf,NoteBf,NoteA,NoteG,NoteF,NoteF,NoteG,NoteA,NoteB,NoteHC,NoteF,
  NoteHD,NoteHD,NoteHC,NoteBf,NoteA,NoteG,NoteHC,NoteHC,NoteBf,NoteA,NoteG,NoteF,NoteD,NoteC,
  NoteLBf,0,NoteBf,NoteBf,NoteA,NoteG,0,NoteG,NoteF,NoteG,NoteA,NoteBf,0,
  NoteD,NoteEf,NoteF,0,NoteF,NoteEf,NoteF,NoteG,0,NoteG,NoteF,NoteBf,NoteBf,NoteHC,NoteHD,NoteHD,
  NoteHD,NoteHD,NoteHD,NoteHC,NoteHD,NoteHEf,NoteHEf,NoteHEf,NoteF,NoteG,NoteA,NoteHC,NoteBf,0
};
//7segment를 위한 light값
void LightG(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,LOW);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
  
}
void LightF(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,LOW);
  digitalWrite(APIN3,LOW);
  digitalWrite(APIN4,LOW);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
  
}

void LightE(int f){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,LOW);
  digitalWrite(APIN3,LOW);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  if(f==0)
    digitalWrite(APIN8,LOW);
  else
    digitalWrite(APIN8,HIGH);
}

void LightD(){
  digitalWrite(APIN1,LOW);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,LOW);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}

void LightC(){
  digitalWrite(APIN1,LOW);
  digitalWrite(APIN2,LOW);
  digitalWrite(APIN3,LOW);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,LOW);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}


void LightB(int f){
  digitalWrite(APIN1,LOW);
  digitalWrite(APIN2,LOW);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  if(f==0)
    digitalWrite(APIN8,LOW);
  else
    digitalWrite(APIN8,HIGH);
}

void LightA(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,LOW);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}

void LightClear(){
  digitalWrite(APIN1,LOW);
  digitalWrite(APIN2,LOW);
  digitalWrite(APIN3,LOW);
  digitalWrite(APIN4,LOW);
  digitalWrite(APIN5,LOW);
  digitalWrite(APIN6,LOW);
  digitalWrite(APIN7,LOW);
  digitalWrite(APIN8,LOW);
}
//쉼표일 경우 사용
void rest(int len)
{
  delay(len);
}




void setup(){
  Serial.begin(115200);
  pinMode(BTN,INPUT);
  pinMode(APIN1,OUTPUT);
  pinMode(APIN2,OUTPUT);
  pinMode(APIN3,OUTPUT);
  pinMode(APIN4,OUTPUT);
  pinMode(APIN5,OUTPUT);
  pinMode(APIN6,OUTPUT);
  pinMode(APIN7,OUTPUT);
  pinMode(APIN8,OUTPUT);
  lcd.init();
  lcd.backlight();
  attachInterrupt(digitalPinToInterrupt(BTN),buttonPressed,RISING);
  Serial.println("setup");
  
}
int row=0;
//음 하나를 실행하는 함수 input으로 음의 주파수와 길이를 넣으면 음발생+7segment표현+lcd에 주파수 표시
void pressed_note(int len,int node){
  Serial.println("In pressed_note\n");
  Serial.println(node);
  Serial.println(len);
  //쉼표인 경우 아무것도 표시하지 않음
  if (node==0)
  {
    LightClear();
    rest(len*125);
  }
  else
  {
    tone(BUZ,node);
    lcd.setCursor(0,(++row%2));
    lcd.print((String)node);
    if(node==NoteA)
      LightA();
    else if(node==NoteB)
      LightB(0);
    else if(node==NoteBf)
      LightB(1);
    else if(node==NoteC)
      LightC();
    else if(node==NoteD)
      LightD();
    else if(node==NoteE)
      LightE(0);
    else if(node==NoteEf)
      LightE(0);
    else if(node==NoteF)
      LightF();
    else if(node==NoteHC)
      LightC();
    else if(node==NoteHD)
      LightD();
    else if(node==NoteHE)
      LightE(0);
    else if(node==NoteHEf)
      LightE(1);
    else if(node==NoteLBf)
      LightB(1);
    else if(node==NoteG)
      LightG();
  delay(len*125);
  noTone(BUZ);
  
  }
  
}
bool button_state=false;
bool button_state_changed=false;
//버튼이 눌렸을 때 정지하기 위해 flag 값 대입해주는 함수
void buttonPressed(){
  button_state=(button_state==false)?true:false;
  button_state_changed=true;
  if(button_state)
    Serial.println("button state is true");
  else
    Serial.println("button state is false");
  
}
int state=0;
void loop(){
  int userInput = digitalRead(BTN);
  //Serial.println(userInput);
  delay(500);
    if(button_state_changed){
      button_state_changed=false;
      
      for(int i=state;i<(sizeof(melody)/sizeof(int));i++)
      {
          Serial.println(i);
          //Serial.println(melody[i]);
          pressed_note(beat[i],melody[i]);
          
          //버튼이 눌려 button_state값이 false가 되는 경우 break와 동시에 현재까지의 값을 state에 저장
          if(button_state==false)
          {
            state=i;
            break;
          }
            
      }
    }

}
