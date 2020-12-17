
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

//7segment를 위한 light값
void Light0(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,LOW);
  digitalWrite(APIN8,LOW);
  
}

void Light1(){
  digitalWrite(APIN1,LOW);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,LOW);
  digitalWrite(APIN5,LOW);
  digitalWrite(APIN6,LOW);
  digitalWrite(APIN7,LOW);
  digitalWrite(APIN8,LOW);
  
}

void Light2(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,LOW);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,LOW);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}

void Light3(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,LOW);
  digitalWrite(APIN6,LOW);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}

void Light4(){
  digitalWrite(APIN1,LOW);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,LOW);
  digitalWrite(APIN5,LOW);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}

void Light5(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,LOW);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,LOW);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}

void Light6(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,LOW);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}

void Light7(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,LOW);
  digitalWrite(APIN5,LOW);
  digitalWrite(APIN6,LOW);
  digitalWrite(APIN7,LOW);
  digitalWrite(APIN8,LOW);
}

void Light8(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,HIGH);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}

void Light9(){
  digitalWrite(APIN1,HIGH);
  digitalWrite(APIN2,HIGH);
  digitalWrite(APIN3,HIGH);
  digitalWrite(APIN4,HIGH);
  digitalWrite(APIN5,LOW);
  digitalWrite(APIN6,HIGH);
  digitalWrite(APIN7,HIGH);
  digitalWrite(APIN8,LOW);
}

void LightF(){
  digitalWrite(APIN1,LOW);
  digitalWrite(APIN2,LOW);
  digitalWrite(APIN3,LOW);
  digitalWrite(APIN4,LOW);
  digitalWrite(APIN5,LOW);
  digitalWrite(APIN6,LOW);
  digitalWrite(APIN7,LOW);
  digitalWrite(APIN8,HIGH);
  
}
void setup(){
  Serial.begin(115200);
  
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
  
  Serial.println("setup");
  
}





void loop(){
  int len=0,num=0;
  char input[30]={0,};
  String test;
  while(Serial.available()>0){
    input[len]=Serial.read();
    test+=input[len];
    len++;
  }
  
  /*
  Serial.flush();
  if(Serial.available())
    Serial.print("flush Failed .../ "+inputString);
  delay(400);
  */
  

  if(strncmp("picture",input,7)==0)
  {
    Serial.println("Taking picture");
    tone(BUZ,NoteC);
    delay(100);
    tone(BUZ,NoteE);
    delay(100);
    tone(BUZ,NoteG);
    delay(100);
    tone(BUZ,NoteHC);
    delay(100);
    noTone(BUZ);
    input[0]='T';
  }
  else if(strncmp("LCD",input,3)==0)
  {
    String inputString="";
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("20173596LSM");
    Serial.println(len);
    for(int i=3;i<len;i++)
    {
      inputString += input[i];  
    }
    lcd.setCursor(0,1);
    lcd.print(inputString);
    Serial.println("LCD ..."+inputString);
    input[0]='T';
    inputString="";
    len=0;
  }
  else if(strncmp("seg7",input,4)==0)
  {
    Serial.println("seg7 : "+input[4]);
    num=atoi(&input[4]);
    switch(num){
        case 0 :
          Light0();
          break;
        case 1:
          Light1();
          break;
        case 2:
          Light2();
          break;
        case 3 :
          Light3();
          break;
        case 4:
          Light4();
          break;
        case 5:
          Light5();
          break;
        case 6 :
          Light6();
          break;
        case 7:
          Light7();
          break;
        case 8:
          Light8();
          break;
        case 9:
          Light9();
          break;
        case -1:
          LightF();
        default:
          break;
      }
      input[0]='T';
      
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("20173596LSM");
  }
  for(int i=0;i<len+1;i++)
    input[i]=0;
  
  len=0;
  
}
