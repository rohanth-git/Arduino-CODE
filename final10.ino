
#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display


Adafruit_SSD1306 display(128, 64);  // Create display


#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font
#include <Fonts/FreeMono9pt7b.h>  // Add a custom font


int n;

int Variable1;
#define analogPinR     A0          
#define chargePin      12         
#define dischargePin   10        
#define resistorValue  10000.0F
//const int buttonPin1 = 2;
const int buttonPin2 = 2;
const int buttonPin3 = 7;
const int buttonPin4 = 8;
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                
float nanoFarads;

int analogPinC = A1;
int V_measured= 0;
int V2_measured= 0;
int Vin= 5;
float Vout= 0;
int apply_voltage = 2;

float R2= 0;
float R_Ref =0;
float buffer= 0;

int ch2K = 5;
int ch20K = 4;
int ch200K = 3;
int ch1M = 6;


int Scale=9;
const int num = 10;
double pulse, frequency, capacitance, inductance;
int buttonState1= 0;
int buttonState2= 0;
int buttonState3= 0;
int buttonState4= 0;
class res
{
  public :
  void resistor()
  {
  if (num == 10)
{  
  digitalWrite(apply_voltage,HIGH);
  pinMode(ch2K,INPUT);
  pinMode(ch20K,INPUT);
  pinMode(ch200K,INPUT);
  pinMode(ch1M,OUTPUT);
  digitalWrite(ch1M,LOW);
  
  float R1= 1; // Set this values to the value of the used resistor in M ohms
  V_measured= analogRead(analogPinR); //in 8bits
 
      buffer= V_measured * Vin;
      Vout= (buffer)/1024.0;  //in volts
      buffer= (Vin/Vout) -1;
      R_Ref = R1 * buffer;
  
      if (R_Ref > 2)
      {
        Serial.print("Increase scale");
               
        delay(1000);
      }
  
      if (R_Ref < 2)
      {
        Serial.print("----[1M]----");
        Serial.print("\n");
        Serial.print("\n");
        Serial.print("Resistance: ");
        Serial.print(R_Ref);
        Serial.print(" ");
        Serial.print("M ohms");
        Serial.print("\n");
        
        
        delay(1000);
        display.clearDisplay();  // Clear the display so we can refresh
        display.setFont(&FreeMono9pt7b);  // Set a custom font
        display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
        display.setCursor(0, 10);
        display.print("RESISTANCE:");
        display.setCursor(0, 24);
        display.print(R_Ref);
        display.setCursor(0, 38);
        display.print("  M ohms");
        display.display();
        delay(10000);
      }
      ///////////////////-2k-/////////////////////
if (R_Ref < 2000)
{  
  digitalWrite(apply_voltage,HIGH);
  pinMode(ch2K,OUTPUT);
  pinMode(ch20K,INPUT);
  pinMode(ch200K,INPUT);
  pinMode(ch1M,INPUT);
  digitalWrite(ch2K,LOW);
  
  float R1= 1; // Set this values to the value of the used resistor in K ohms
  V_measured= analogRead(analogPinR); //in 8bits
  
      buffer= V_measured * Vin;
      Vout= (buffer)/1024.0;  //in volts
      buffer= (Vin/Vout) -1;
      R2= R1 * buffer*1000; //*1000 because we express it in ohms 
  
      if (R2 > 1000)
      {
        Serial.print("Increase scale");
             
        delay(1000);
      }
  
      if (R2 < 1000)
      {
        Serial.print("----[2K]----");
        Serial.print("\n");
        Serial.print("\n");
        Serial.print("Resistance: ");
        Serial.print(R2);
        Serial.print(" ");
        Serial.print("  ohms");
        Serial.print("\n");
        
       
        delay(1000);
        delay(1000);
        display.clearDisplay();  // Clear the display so we can refresh
        display.setFont(&FreeMono9pt7b);  // Set a custom font
        display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
        display.setCursor(0, 10);
        display.print("RESISTANCE:");
        display.setCursor(0, 24);
        display.print(R2);
        display.setCursor(0, 38);
        display.print(" ohms");
        display.display();
        delay(10000);
}
  }
}
  }
};

    class ind
    {
      public:
      void inductor()
      {
      digitalWrite(13, HIGH);
  delay(5);//give some time to charge inductor.
  digitalWrite(13,LOW);
  delayMicroseconds(100); //make sure resination is measured
  pulse = pulseIn(11,HIGH,5000);//returns 0 if timeout
  if(pulse > 0.1){ //if a timeout did not occur and it took a reading:
    
    
  //#error insert your used capacitance value here. Currently using 2uF. Delete this line after that
  capacitance = 2.E-6; // - insert value here
  
  
  frequency = 1.E6/(2*pulse);
  inductance = 1./(capacitance*frequency*frequency*4.*3.14159*3.14159);//one of my profs told me just do squares like this
  inductance *= 1E6; //note that this is the same as saying inductance = inductance*1E6

  //Serial print
  Serial.print("High for uS:");
  Serial.print( pulse );
  Serial.print("\tfrequency Hz:");
  Serial.print( frequency );
  Serial.print("\tinductance uH:");
  Serial.println( inductance );
  delay(10);
  display.clearDisplay();  // Clear the display so we can refresh
  display.setFont(&FreeMono9pt7b);  // Set a custom font
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
  display.setCursor(0, 10);
  display.print("inductance:");
  display.setCursor(0, 24);
  display.print(inductance);
  display.display();
  delay(10000);
}
      
    }
    };
 class cap
 {
  public:
  void capacitor()
  {
  digitalWrite(chargePin, HIGH);  
  startTime = millis();
  while(analogRead(analogPinC) < 648){       
  }

  elapsedTime= millis() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) * 1000;   
  Serial.print(elapsedTime);       
  Serial.print(" mS    ");         

  if (microFarads > 1){
    Serial.print((long)microFarads);       
    Serial.println(" microFarads");
    display.clearDisplay();  // Clear the display so we can refresh
    display.setFont(&FreeMono9pt7b);  // Set a custom font
    display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
    display.setCursor(0, 10);
    display.print("capacitor:");
    display.setCursor(0, 24);
    display.print((long)microFarads);
    display.setCursor(0, 38);
    display.print(" microFarads");
    display.display();
    delay(10000);             
  }

  else{
    nanoFarads = microFarads * 1000.0;      
    Serial.print((long)nanoFarads);         
    Serial.println(" nanoFarads");          
    delay(500); 
    display.clearDisplay();  // Clear the display so we can refresh
    display.setFont(&FreeMono9pt7b);  // Set a custom font
    display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
    display.setCursor(0, 10);
    display.print("capacitor:");
    display.setCursor(0, 24);
    display.print((long)nanoFarads);
    display.setCursor(0, 38);
    display.print(" nanoFarads");
    display.display();
    delay(10000);
  }

  digitalWrite(chargePin, LOW);            
  pinMode(dischargePin, OUTPUT);            
  digitalWrite(dischargePin, LOW);          
  while(analogRead(analogPinC) > 0){         
  }

  pinMode(dischargePin, INPUT);     
 }
 };

void setup() {
  
  Serial.begin(9600);             
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);
  pinMode(V_measured,INPUT); 
  pinMode(analogPinR,INPUT);
  pinMode(apply_voltage,OUTPUT);
  
  //Detect the range mode (0-1kK; 10k-100k; 100k-1M)
  pinMode(Scale,INPUT);

//We set this pins as input for now. 
  pinMode(ch2K,INPUT);
  pinMode(ch20K,INPUT);
  pinMode(ch200K,INPUT);
  pinMode(ch1M,INPUT);
  pinMode(11, INPUT);
  pinMode(13, OUTPUT);
  delay(200);
  //pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C
 
  display.clearDisplay();  // Clear the buffer

  display.setTextColor(WHITE);  // Set color of the text

  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3

  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                               // To override this behavior (so text will run off the right side of the display - useful for
                               // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                               // with setTextWrap(true).

  display.dim(0);
  Serial.println("RLC CALCULATOR");
    delay(3000);
    Serial.println("ENTER THE OPTION:");
    Serial.println("1.resistor calculator");
    Serial.println("2.inductor calculator");
    Serial.println("3.capacitor calculator"); 
    display.clearDisplay();  // Clear the display so we can refresh
    display.setFont(&FreeMono9pt7b);  // Set a custom font
    display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
    display.setCursor(0, 10);
    display.println("RLC CALCULATOR");
    display.display();
    delay(3000);
    display.clearDisplay();  // Clear the display so we can refresh
    display.setFont(&FreeMono9pt7b);  // Set a custom font
    display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
    display.setCursor(0, 10);
    display.println("ENTER THE OPTION:");
    display.setCursor(0, 24);
    display.println("1.resistor calculator");
    display.setCursor(0, 38);
    display.println("2.inductor calculator");
    display.setCursor(0, 52);
    display.println("3.capacitor calculator");
    display.display();


}
void loop()
{
//  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

   if (buttonState2==HIGH)
  { 
    n=1;
    exit;
  }
  else if (buttonState3==HIGH)
  {
    n=2;
    exit;
  }
  else if (buttonState4==HIGH)
  { 
    n=3;
     exit;
  }
  
    
  switch(n){
    case 1:{
       
      display.clearDisplay();  // Clear the display so we can refresh
      display.setFont(&FreeMono9pt7b);  // Set a custom font
      display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
      display.setCursor(0, 10);
      display.println("resisror");
      display.setCursor(0, 24);
      display.println("calculator");
      display.display();
      testr();
    
    }
    break;
    case 2:{
       
      display.clearDisplay();  // Clear the display so we can refresh
      display.setFont(&FreeMono9pt7b);  // Set a custom font
      display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
      display.setCursor(0, 10);
      display.println("inductor");
      display.setCursor(0, 24);
      display.println("calculator");
      display.display();
      testl();
    
    }
    break;
    case 3:{
       
      display.clearDisplay();  // Clear the display so we can refresh
      display.setFont(&FreeMono9pt7b);  // Set a custom font
      display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
      display.setCursor(0, 10);
      display.println("capacitor");
      display.setCursor(0, 24);
      display.println("calculator");
      display.display();
      testc();
    
    }
    break;
   
    
  }
  delay(10000);
  

}
void testr()
{
   res R;
   R.resistor();
}
void testl()
{
  ind I;
  I.inductor();
}
void testc()
{
  cap C;
  C.capacitor();
}
