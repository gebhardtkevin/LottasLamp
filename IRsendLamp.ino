/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;

//IR-LED
const int sendPin =  3;
const int vsPin = 4;
const int gndPin = 2;

//LED
const int ledPlus = 9;
const int ledMinus = 10;

//Buttons
const int btn1 = 6;
const int btn2 = 7;
const int btn3 = 8;
const int btn1Gnd = 11;
const int btn2Gnd = 12;
const int btn3Gnd = 13;

int outState = LOW;

//codes from the remote control
unsigned long brighter =  0xFF00FF;
unsigned long darker =  0xFF40BF;
unsigned long white = 0xFFC03F;
unsigned long off = 0xFF609F;
unsigned long on = 0xFFE01F;
unsigned long r = 0xFF10EF;
unsigned long g = 0xFF906F;
unsigned long b = 0xFF50AF;

unsigned long flash = 0xFFF00F;
unsigned long strobe = 0xFFC837;
unsigned long smooth = 0xFFE817;
unsigned long mode = 0xFFD827;

unsigned long r1 = 0xFF30CF;
unsigned long g1 = 0xFFB04F;
unsigned long b1 = 0xFF708F;
unsigned long r2 = 0xFF08F7;
unsigned long g2 = 0xFF8877;
unsigned long b2 = 0xFF48B7;
unsigned long r3 = 0xFF28D7;
unsigned long g3 = 0xFFA857;
unsigned long b3 = 0xFF6897;
unsigned long r4 = 0xFF18E7;
unsigned long g4 = 0xFF9867;
unsigned long b4 = 0xFF58A7;

boolean timerFlag=false;
boolean onFlag = false;
const long timerDuration=1800000; //30 Minutes
unsigned long timerEnd = 0;

void setup()
{
  //setup for IR-LED
  pinMode(vsPin,OUTPUT);
  pinMode(gndPin,OUTPUT);
  pinMode(sendPin,OUTPUT);
  digitalWrite(vsPin, HIGH);
  digitalWrite(gndPin,LOW);

  //LED
  pinMode(ledPlus,OUTPUT);
  pinMode(ledMinus,OUTPUT);
  digitalWrite(ledMinus, LOW);
  digitalWrite(ledPlus,LOW);

  //pinmodes for buttons
  pinMode(btn1Gnd,OUTPUT);
  pinMode(btn2Gnd,OUTPUT);
  pinMode(btn3Gnd,OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  digitalWrite(btn1Gnd,LOW);
  digitalWrite(btn2Gnd,LOW);
  digitalWrite(btn3Gnd,LOW);
  send(on);
  onFlag=true;
  Serial.begin(9600);
}

void send(unsigned long instruction){
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(instruction, 32);
    Serial.print("sende Instruction");
    Serial.println(instruction,HEX);
    delay(40);
    
  }
}

void onButton1Pressed(){
  Serial.println("Button1");
  if (onFlag){
    send(off);
    onFlag=false;
  }else{
    send(on);
    send(white);
    onFlag=true;
  }
  timerFlag=false;
}

void onButton2Pressed(){
    Serial.println("Button2");
  onFlag=true;
  send(on);
  send(smooth);
  timerFlag=false;
}

void onButton3Pressed(){
    Serial.println("Button3");
      send (on);
      onFlag=true;
  //send(on);
  //send(white);
  timerFlag=true;
  timerEnd=millis()+timerDuration;
}


void loop() {
  if (digitalRead(btn1)==LOW){
    onButton1Pressed();
  }

  if (digitalRead(btn2)==LOW){
    onButton2Pressed();
  }

  if (digitalRead(btn3)==LOW){
    onButton3Pressed();
  }

  if (timerFlag){
    digitalWrite(ledPlus,HIGH);
    Serial.println("Timer start");
    Serial.println(millis());
    Serial.println(timerEnd);
    if (millis()>timerEnd){
      send(off);
      onFlag=false;
      Serial.println("Timer end");
      timerFlag=false;
    }
  }else{
      digitalWrite(ledPlus,LOW);
  }
  
}
