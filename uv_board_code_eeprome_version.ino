
// Include Libraries
#include<EEPROM.h>
#include "Arduino.h"
#include "Buzzer.h"
#include "LiquidCrystal.h"
#include "Button.h"
#include "Relay.h"


// Pin Definitions
#define BUZZER_PIN_SIG  2
#define LCD_PIN_RS  8
#define LCD_PIN_E 7
#define LCD_PIN_DB4 3
#define LCD_PIN_DB5 4
#define LCD_PIN_DB6 5
#define LCD_PIN_DB7 6
#define PUSHBUTTON_1_PIN_2  9
#define PUSHBUTTON_2_PIN_2  10
#define PUSHBUTTON_3_PIN_2  11
#define PUSHBUTTON_4_PIN_2  12
#define RELAYMODULE_PIN_SIGNAL  13

  bool Cancle ;
  bool Select ;
  bool Up ;
  bool Down ;

  int Save_couter_adress = 0;
  int Save_counter_value=1;

  int e_value;
  int a_value;
  
  int e_adress_h = 1;
  int e_value_h=0;

  int a_adress_m = 2;
  int a_value_m=0;
  
  int e_adress_s = 3;
  int e_value_s=20;

  int a_adress_h = 4;
  int a_value_h=0;
  
  int e_adress_m = 5;
  int e_value_m=0;

  int a_adress_s = 6;
  int a_value_s=20;

  int temp1,temp2,temp3,temp4;


int alarm_sec = a_value_h;
int alarm_Min = a_value_m;
int alarm_Hour = a_value_s;
int exposing_sec = e_value_s;
int exposing_Min = e_value_m;
int exposing_Hour =  e_value_h;

int a_s_value = alarm_sec;
int a_m_value = alarm_Min;
int a_h_value = alarm_Hour;
int e_s_value = exposing_sec;
int e_m_value = exposing_Min;
int e_h_value = exposing_Hour;

int Hour;
int Min;
int Sec;


// object initialization
Buzzer buzzer(BUZZER_PIN_SIG);
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
Button pushButton_1(PUSHBUTTON_1_PIN_2);
Button pushButton_3(PUSHBUTTON_3_PIN_2);
Button pushButton_2(PUSHBUTTON_2_PIN_2);
Button pushButton_4(PUSHBUTTON_4_PIN_2);
Relay relayModule(RELAYMODULE_PIN_SIGNAL);


 void a_s_Change_the_value(){  
  
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Change_the_value");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm Time");
  lcd.setCursor(0, 1);
  lcd.print("H");
  lcd.setCursor(1, 1);
  lcd.print(alarm_Hour);
  lcd.setCursor(5, 1);
  lcd.print("M");
  lcd.setCursor(6, 1);
  lcd.print(a_m_value);
  lcd.setCursor(10, 1);
  lcd.print("S");
  lcd.setCursor(11, 1);
  lcd.print(a_s_value);
  lcd.display();
  if(a_s_value > 60){
      a_m_value = a_m_value + 1;
      a_s_value = a_s_value - 60;
    }
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    alarm_sec = a_s_value;
    a_value_s = a_s_value;
    a_secs();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_secs();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_s_value++;
    a_s_Change_the_value();
    
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_s_value--;
    a_s_Change_the_value();
  }
  else{
    a_s_Change_the_value();
  }
  
 }
 //////
 void a_m_Change_the_value(){
  
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm Time");
  lcd.setCursor(0, 1);
  lcd.print("H");
  lcd.setCursor(1, 1);
  lcd.print(a_h_value);
  lcd.setCursor(5, 1);
  lcd.print("M");
  lcd.setCursor(6, 1);
  lcd.print(a_m_value);
  lcd.setCursor(10, 1);
  lcd.print("S");
  lcd.setCursor(11, 1);
  lcd.print(alarm_sec);
  lcd.display();
  if(a_m_value > 60){
      a_h_value = a_h_value + 1;
      a_m_value = a_m_value - 60;
    }
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    alarm_Min = a_m_value;
    a_value_m = a_m_value;
    a_Min();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_Min();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_m_value++;
    a_m_Change_the_value();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_m_value--;
    a_m_Change_the_value();
  }
  else{
    a_m_Change_the_value();
  }
  
 }
 //////
 ////
 void a_h_Change_the_value(){  
  
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Change_the_value");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("alarm Time");
  lcd.setCursor(0, 1);
  lcd.print("H");
  lcd.setCursor(1, 1);
  lcd.print(a_h_value);
  lcd.setCursor(5, 1);
  lcd.print("M");
  lcd.setCursor(6, 1);
  lcd.print(alarm_Min);
  lcd.setCursor(10, 1);
  lcd.print("S");
  lcd.setCursor(11, 1);
  lcd.print(alarm_sec);
  lcd.display();
  if(a_h_value>220){
    a_h_value = 220;
  }
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    alarm_Hour = a_h_value;
    a_value_h = a_h_value;
    a_Hours();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_Hours();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_h_value++;
    a_h_Change_the_value();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_h_value--;
    a_h_Change_the_value();
  }
  else{
    a_h_Change_the_value();
  }
  
 }
 //////
 void e_s_Change_the_value(){
  
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Change_the_value");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing Time");
  lcd.setCursor(0, 1);
  lcd.print("H");
  lcd.setCursor(1, 1);
  lcd.print(exposing_Hour);
  lcd.setCursor(5, 1);
  lcd.print("M");
  lcd.setCursor(6, 1);
  lcd.print(e_m_value);
  lcd.setCursor(10, 1);
  lcd.print("S");
  lcd.setCursor(11, 1);
  lcd.print(e_s_value);
  lcd.display();
  if(e_s_value > 60){
      e_m_value = e_m_value + 1;
      e_s_value = e_s_value - 60;
    }
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_sec = e_s_value;
    e_value_s = e_s_value;
    e_secs();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_secs();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_s_value++;
    e_s_Change_the_value();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_s_value--;
    e_s_Change_the_value();
  }
  else{
    e_s_Change_the_value();
  }
  
 }
 //////
 void e_m_Change_the_value(){
  
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Change_the_value");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing Time");
  lcd.setCursor(0, 1);
  lcd.print("H");
  lcd.setCursor(1, 1);
  lcd.print(e_h_value);
  lcd.setCursor(5, 1);
  lcd.print("M");
  lcd.setCursor(6, 1);
  lcd.print(e_m_value);
  lcd.setCursor(10, 1);
  lcd.print("S");
  lcd.setCursor(11, 1);
  lcd.print(exposing_sec);
  lcd.display();
  if(e_m_value > 60){
      e_h_value = e_h_value + 1;
      e_m_value = e_m_value - 60;
    }
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_Min = e_m_value;
    e_value_m = e_m_value;
    e_Min();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_Min();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_m_value++;
    e_m_Change_the_value();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_m_value--;
    e_m_Change_the_value();
  }
  else{
    e_m_Change_the_value();
  }
  
 }
 //////
 ////
 void e_h_Change_the_value(){
  
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Change_the_value");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing Time");
  lcd.setCursor(0, 1);
  lcd.print("H");
  lcd.setCursor(1, 1);
  lcd.print(e_h_value);
  lcd.setCursor(5, 1);
  lcd.print("M");
  lcd.setCursor(6, 1);
  lcd.print(exposing_Min);
  lcd.setCursor(10, 1);
  lcd.print("S");
  lcd.setCursor(11, 1);
  lcd.print(exposing_sec);
  lcd.display();
  if(e_h_value>220){
    e_h_value = 220;
  }
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_Hour = e_h_value;
    e_value_h = e_h_value;
    e_Hours();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_Hours();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_h_value++;
    e_h_Change_the_value();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_h_value--;
    e_h_Change_the_value();
  }
  else{
    e_h_Change_the_value();
  }
  
 }
 //////
  ////

 void alarm_time(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("ATIME");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing Time");
  lcd.setCursor(0, 1);
  lcd.print("Alarm Time*");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_Hours();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    settings();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_time();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    save_option();
  }
  else{
    alarm_time();
  }
  
 }
 ////
 void save_option(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("save_option");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm Time");
  lcd.setCursor(0, 1);
  lcd.print("Save*");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    save();
  }
  if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    settings();
  }
  if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    alarm_time();
  }
  if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_time();
  }
  else{
    save_option();
  }
  
 }
 //////
 void save(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("save");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Want to save");
  lcd.setCursor(0, 1);
  lcd.print("Permanently(Y/N)");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("saving...");
    lcd.display();
    if(e_value_h>220){
      e_value_h=220;
    }
    if(a_value_h>220){
      a_value_h=220;
    }
    if(e_value_m>220){
     e_value_m =220;
    }
    if(a_value_m>220){
      a_value_m=220;
    }
    if(e_value_s>220){
      e_value_s=220;
    }
    if(a_value_s>220){
      a_value_s=220;
    }
    if(Save_counter_value>220){
      Save_counter_value=220;
    }
    EEPROM.write(e_adress_h, e_value_h);
    EEPROM.write(a_adress_h, a_value_h);
    EEPROM.write(e_adress_m, e_value_m);
    EEPROM.write(a_adress_m, a_value_m);
    EEPROM.write(e_adress_s, e_value_s);
    EEPROM.write(a_adress_s, a_value_s);
    Save_counter_value++;
    EEPROM.write(Save_couter_adress, Save_counter_value); 
    Save_counter_value = EEPROM.read(Save_couter_adress);
    if(Save_counter_value == 250){
      e_adress_h = e_adress_h + 7;
      a_adress_h = a_adress_h + 7;
      e_adress_m = e_adress_m + 7;
      a_adress_m = a_adress_m + 7;
      e_adress_s = e_adress_s + 7;
      a_adress_s = a_adress_s + 7;
      Save_couter_adress = Save_couter_adress + 7;
      Save_counter_value = 0;
    }
    delay(10);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Done Saving..)");
    lcd.display();
    
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_time();
  }
  
  else{
    save();
  }
  
 }
 //////
    ////
 void a_secs(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("secs");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm Time");
  lcd.setCursor(0, 1);
  lcd.print("hour  min  sec*");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_s_Change_the_value();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    alarm_time();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_Min();
  }
  else{
    a_secs();
  }
  
 }
 //////
 ////
 void a_Min(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Min");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm Time");
  lcd.setCursor(0, 1);
  lcd.print("hour  min* sec");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_m_Change_the_value();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    alarm_time();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_Hours();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_secs();
  }
  else{
    a_Min();
  }
  
 }
 //////
 ////
 void a_Hours(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Hours");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm Time");
  lcd.setCursor(0, 1);
  lcd.print("hour* min  sec");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_h_Change_the_value();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    alarm_time();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    a_Min();
  }
  else{
    a_Hours();
  }
  
 }
 //////
  ////
 void e_secs(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("secs");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing Time");
  lcd.setCursor(0, 1);
  lcd.print("hour  min  sec*");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_s_Change_the_value();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_time();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_Min();
  }
  else{
    e_secs();
  }
  
 }
 //////
 ////
 void e_Min(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Min");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing Time");
  lcd.setCursor(0, 1);
  lcd.print("hour  min* sec");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_m_Change_the_value();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_time();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_Hours();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_secs();
  }
  else{
    e_Min();
  }
  
 }
 //////
 ////
 void e_Hours(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Hours");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing Time");
  lcd.setCursor(0, 1);
  lcd.print("hour* min  sec");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_h_Change_the_value();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_time();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_Min();
  }
  else{
    e_Hours();
  }
  
 }
 //////
  ////
 void exposing_time(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("exposing_time");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing Time*");
  lcd.setCursor(0, 1);
  lcd.print("Alarm Time");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    e_Hours();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    settings();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    alarm_time();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    save_option();
  }
  else{
    exposing_time();
    
  }
  
 }
 //////////
 void expose(){
  e_value = (exposing_Hour*60*60)+(exposing_Min*60)+exposing_sec;
  a_value = (alarm_Hour*60*60)+(alarm_Min*60)+alarm_sec;
  Hour = exposing_Hour;
  Min = exposing_Min;
  Sec = exposing_sec;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing...");
  delay(1000);  
  lcd.display();
  Exposing(e_value,a_value);
 }
 //////
 void Exposing(int ETIME,int ATIME){
  int i = ETIME;
  int j = ATIME;
  temp1 = ETIME/3600;
  temp2 = ETIME%3600;
  temp3 = temp2/60;
  temp4 = temp2%60;
  if(i != 0){
  Serial.println("performing_opreration");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Remaining");
  lcd.setCursor(0, 1);
  lcd.print("H");
  lcd.setCursor(1, 1);
  lcd.print(temp1);
  lcd.setCursor(5, 1);
  lcd.print("M");
  lcd.setCursor(6, 1);
  lcd.print(temp3);
  lcd.setCursor(10, 1);
  lcd.print("S");
  lcd.setCursor(11, 1);
  lcd.print(temp4);
  lcd.display();
  if(j < 0){buzzer.on();}
  relayModule.on();
  delay(100);
  buzzer.off();
  delay(100);
  if(j < 0){buzzer.on();}
  relayModule.on();
  delay(100);
  buzzer.off();
  delay(700);
  i = i-1;
  j = j-1;
 Exposing(i,j);
  }
  else{
  lcd.clear();
  lcd.setCursor(0, 0);
  relayModule.off();
  lcd.print("compleated...");
  buzzer.on();
  delay(1000);
  buzzer.off();
   Start_();
   i=60;
  }
  
 }
 ////
 void confirm_to_start(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("confirm_to_start");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("confirm to start");
  lcd.setCursor(0, 1);
  lcd.print("<<  Y/N  >>");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    expose();
  }
  else if(Cancle == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    Start_();
  }
  else{
    confirm_to_start();
  }
  
 }
 //////

 void settings(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("settings");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start");
  lcd.setCursor(0, 1);
  lcd.print("Settings*");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    exposing_time();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    Start_();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    Start_();
  }
else{
    settings();
  }
  
 }

 void Start_(){
  Cancle = pushButton_1.onPress();
  Select = pushButton_2.onPress();
  Up = pushButton_3.onPress();
  Down = pushButton_4.onPress();
  Serial.println("Start_");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start*");
  lcd.setCursor(0, 1);
  lcd.print("Settings");
  lcd.display();
  if(Select == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    confirm_to_start();
  }
  else if(Down == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    settings();
  }
  else if(Up == 1){
    buzzer.on();
    delay(100);
    buzzer.off();
    settings();
  }
  else{
    Start_();
  }
  
 }
 
 void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    // set up the LCD's number of columns and rows
    lcd.begin(16, 2);
    pushButton_1.init();
    pushButton_2.init();
    pushButton_3.init();
    pushButton_4.init();
    relayModule.off();
    exposing_Hour = EEPROM.read(e_adress_h);
    exposing_Min = EEPROM.read(a_adress_m);
    exposing_sec = EEPROM.read(e_adress_s);
    alarm_Hour = EEPROM.read(a_adress_h);
    alarm_Min = EEPROM.read(e_adress_m);
    alarm_sec = EEPROM.read(a_adress_s);
    Start_();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
 
}
