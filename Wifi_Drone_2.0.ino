#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WebServer.h>
BlynkTimer timer;
///////////////////////BLYNK CONFIGURATION////////////////////////
char auth[] = "oCYrRs6S6raUKTeP-WMYctAgNOG7UTBS";
char ssid[] = "Rohan";
char pass[] = "PAssWOrd";
//////////////////////////////////////////////////////////////////


#define CPU_MHZ 80
#define CHANNEL_NUMBER 8  //set the number of chanels
#define CHANNEL_DEFAULT_VALUE 1100  //set the default servo value
#define FRAME_LENGTH 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PULSE_LENGTH 300  //set the pulse length
#define onState 0  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 15 //set PPM signal output pin on the arduino
#define DEBUGPIN 4

volatile unsigned long next;
volatile unsigned int ppm_running=1;

int ppm[CHANNEL_NUMBER];
unsigned int alivecount=0;
int lastval;
void inline ppmISR(void){
  static boolean state = true;

  if (state) {  //start pulse
    digitalWrite(sigPin, onState);
    next = next + (PULSE_LENGTH * CPU_MHZ);
    state = false;
    alivecount++;
  } 
  else{  //end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;
  
    digitalWrite(sigPin, !onState);
    state = true;

    if(cur_chan_numb >= CHANNEL_NUMBER){
      cur_chan_numb = 0;
      calc_rest = calc_rest + PULSE_LENGTH;// 
      next = next + ((FRAME_LENGTH - calc_rest) * CPU_MHZ);
      calc_rest = 0;
      digitalWrite(DEBUGPIN, !digitalRead(DEBUGPIN));
    }
    else{
      next = next + ((ppm[cur_chan_numb] - PULSE_LENGTH) * CPU_MHZ);
      calc_rest = calc_rest + ppm[cur_chan_numb];
      cur_chan_numb++;
    }     
  }
  timer0_write(next);
}

void handleRoot() {
   if(ppm_running==0)
  {
    noInterrupts();
    timer0_isr_init();
    timer0_attachInterrupt(ppmISR);
    next=ESP.getCycleCount()+1000;
    timer0_write(next);
    for(int i=0; i<CHANNEL_NUMBER; i++){
      ppm[i]= CHANNEL_DEFAULT_VALUE;
    }
    ppm_running=1;
    interrupts();
  }
}

void setup() {
  pinMode(sigPin,OUTPUT);
  digitalWrite(sigPin, !onState); //set the PPM signal pin to the default state (off)
  pinMode(DEBUGPIN,OUTPUT);
  digitalWrite(DEBUGPIN, !onState); //set the PPM signal pin to the default state (off)
Blynk.begin(auth, ssid, pass);
  noInterrupts();
  timer0_isr_init();
  timer0_attachInterrupt(ppmISR);
  next=ESP.getCycleCount()+1000;
  timer0_write(next);
  for(int i=0; i<CHANNEL_NUMBER; i++){
    ppm[i]= CHANNEL_DEFAULT_VALUE;
  }
  interrupts();
  Serial.begin(115200);
      ppm[0]=1500;
      ppm[1]=1500;
      ppm[2]=1000;
      ppm[3]=1500;
      ppm[4]=1000;
      ppm[5]=1000;
      ppm[6]=1000;
      ppm[7]=1000;
}

unsigned long time_now = 0;



void loop(){
  if (Blynk.connected()) {
    Blynk.run();
    Serial.println("running");
  }
  else{
    Serial.println("disconected to blynk");
  }
  timer.run();
  

  if(WiFi.status() != WL_CONNECTED)
  {
    if(ppm[2]!= 1100){
      lastval--;
    ppm[2] = lastval;
    ppm[0] = 1500;
    ppm[1] = 1500;
    delay(100);
    //
   // other_long_operation();    
    Serial.println(ppm[2]);
  //  WiFi.begin(ssid, pass);
    
      
    }
    
    
      
  }
  else{
    Serial.println("Connected to wifi");
  }
}

BLYNK_WRITE(V5) // V5 is the number of Virtual Pin  
{
  ppm[0] = param.asInt();
  
}
BLYNK_WRITE(V6) // V5 is the number of Virtual Pin  
{
  ppm[1] = param.asInt();
  
}
BLYNK_WRITE(V7) // V5 is the number of Virtual Pin  
{
  ppm[2] = param.asInt();
  lastval = ppm[2];
 
}
BLYNK_WRITE(V8) // V5 is the number of Virtual Pin  
{
  ppm[3] = param.asInt();

}
BLYNK_WRITE(V9) // V5 is the number of Virtual Pin  
{
  ppm[4] = param.asInt();

}
BLYNK_WRITE(V10) // V5 is the number of Virtual Pin  
{
  ppm[5] = param.asInt();

}BLYNK_WRITE(V11) // V5 is the number of Virtual Pin  
{
  ppm[6] = param.asInt();

}BLYNK_WRITE(V12) // V5 is the number of Virtual Pin  
{
  ppm[7] = param.asInt();

}
