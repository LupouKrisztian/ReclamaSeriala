#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String codv = ""; 
bool codcorect = 0;
String serialS = "";
String text1 = "";
String text2 = "";
int l1 = 0;
int l2 = 0;
int valPot;

int melody[] = {
  175, 175, 220, 247, 175, 175, 175, 220, 
  247, 175, 247, 208, 208, 262, 208, 185, 0
};

int noteDurations[] = {
  7, 7, 7, 3, 7, 7, 7, 7, 3, 7, 3, 7, 7, 5, 3, 3, 4
};


void setup() {
  analogReference(DEFAULT);
  lcd.begin(16, 2);
 
  Serial.begin(9600); 
  Serial.println("Introduceti codul de verificare");
  pinMode(A0, INPUT); 
  digitalWrite(A0, HIGH);
}

void loop() {
  valPot = analogRead(A0);
  
  if (codcorect == 0)
    codverif();
  if (codcorect){
    reclama();
  }
}

void codverif(){
  if (Serial.available()) {
      delay(100);
      while (Serial.available() > 0) {
         codv = Serial.readString();
         if (codv == "proiect") {
         Serial.println("Cod de verificare corect");
         codcorect = 1;
         }
         else {
         Serial.println("Cod de verificare incorect, mai incercati");
         }
           
      }
  }
}

void reclama() {
  if (Serial.available()) {
    delay(100);
    while (Serial.available() > 0) {
      serialS = Serial.readString();
    }
  }
   if(serialS.substring(0,1)=="1"){
     lcd.clear();
     text1 = serialS.substring(1);
     l1 = text1.length();
     l2 = text2.length();
     animatii();
   }  
   if(serialS.substring(0,1)=="2"){
     lcd.clear();
     text2 = serialS.substring(1);
     l1 = text1.length();
     l2 = text2.length();
     animatii();
   }
   if(serialS == "clear"){
     lcd.clear();
     text1 = "";
     text2 = "";
     l1 = 0;
     l2 = 0;
   }
   delay(500);
}

void animatii(){
  
  if(valPot >= 0 && valPot < 300)
    animatie1();
  else
    if(valPot >= 300 && valPot < 600)
      animatie2();
    else
      if(valPot >= 600 && valPot < 750)
        animatie3();
      else
        if(valPot >= 750 && valPot < 900)
          animatie4();
        else
          if(valPot >= 900 && valPot < 1000){
          animatie2();
          animatie4();
          animatie3();
          }
          else{
          lcd.print(text1);
          lcd.setCursor(0,1);
          lcd.print(text2);
          }
}

void animatie1(){
    for(int i = 0; i < 16; i++)
    {  if(i < l1)
         lcd.print(text1[i]);
     
       lcd.setCursor(i,1);
     
       if(i < l2)
         lcd.print(text2[i]);
     
       lcd.setCursor(i+1,0);
       
       int noteDuration = 1000 / noteDurations[i];
       tone(8, melody[i], noteDuration);
       delay(400);
    }
}
void animatie2(){
    int j = 0;
    for(int i = 0; i < 15; i++)
    {  if(i < l1){
         lcd.print(text1[i]);
         if(j <= 16)
         {
           int noteDuration = 1000 / noteDurations[j];
           tone(8, melody[j], noteDuration);
           j = j + 1;
         }
         delay(400);
       }
       lcd.setCursor(i,1);
       if(i < l2){
         lcd.print(text2[i]);
         if(j <= 16)
         {
           int noteDuration = 1000 / noteDurations[j];
           tone(8, melody[j], noteDuration);
           j = j + 1;
         }
         delay(400);
       }
       lcd.setCursor(i+1,0);
    }
  while(j <= 16){
       int noteDuration = 1000 / noteDurations[j];
       tone(8, melody[j], noteDuration);
       j = j + 1;
       delay(400);
  }
}
void animatie3(){
    for(int i = 16; i >= 0; i--)   
    {  lcd.clear();
       lcd.setCursor(i,0);
       lcd.print(text1);
       lcd.setCursor(i,1);
       lcd.print(text2);
       
       int noteDuration = 1000 / noteDurations[16-i];
       tone(8, melody[16-i], noteDuration);
       delay(400);
    }
}
void animatie4(){
    for(int i = 0; i <= 16; i++)   
    {  lcd.clear();
       lcd.setCursor(i,0);
       lcd.print(text1);
       lcd.setCursor(i,1);
       lcd.print(text2);
     
       int noteDuration = 1000 / noteDurations[i];
       tone(8, melody[i], noteDuration);
       delay(400);
    }
}
