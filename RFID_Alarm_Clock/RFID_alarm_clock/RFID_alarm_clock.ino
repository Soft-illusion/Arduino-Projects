
//Includes of the library if you code does not compile include the libraries given in library folder.

#include <SPI.h>
#include <MFRC522.h>
#include "IRremote.h"

// notes for alarm tone
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// Pins for RFID
#define SS_PIN 53
#define RST_PIN 5

// Pin for passive buzzer
#define melodyPin 6
#define led_pin 13
int song_speed = 2; // change the speed of alarm song

//pins for decimal point and each segment of display
//dp, G, F, E, D, C, B, A
const int segmentPins[]= { 37, 36, 35, 34, 33, 32, 31, 30};
const int numberofDigits=4;
const int digitPins[numberofDigits] = { 22, 23, 24, 25}; //digits 1, 2, 3, 4
int brightness = 90;

// Pins of IR reciever
int IR_receiver = 11;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
IRrecv irrecv(IR_receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

//Mario main theme melody

int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
//  Under world tone
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};

//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

//https://github.com/robsoncouto/arduino-songs
// If you want to change the alarm tone go to above page and chose your favourite.


byte digitArray[] = {0x00, 0x00,0x00,0x00};

//   A
// F   B
//   G
// E   C
//   D   .dp

const int numeral[13]= {
B11111100, //0
B01100000, //1
B11011010, //2
B11110010, //3
B01100110, //4
B10110110, //5
B10111110, //6
B11100000, //7
B11111110, //8
B11100110, //9
B00000010,  //dash
B01101110, //H
B00010000 //dash_low
};

int time_left=10;
int song = 0;
int hrs_units=0;
int hrs_tens=0;
int mins_units=0;
int mins_tens=0;
int hrs=0;
int mins=0;
int set_hrs=0;
int set_mins=0;
bool pause=false;
bool woke_up=false;
int dig1=0;
int dig2=0;
int dig3=0;
int dig4=0;

int final=0;
int fourArray[]={0,0,0,0};

int numArray[] = {0,0};

void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  pinMode(melodyPin, OUTPUT);//buzzer
  pinMode(led_pin, OUTPUT);//led indicator when singing a note
  irrecv.enableIRIn(); // Start the IR_receiver
  
  for (int i=0; i < 8; i++)
    pinMode(segmentPins[i], OUTPUT); //set segment and DP pins to output

  //sets the digit pins as outputs
  for (int i=0; i < numberofDigits; i++)
    pinMode(digitPins[i], OUTPUT);

  Serial.println("Setup complete");
  Serial.println("Use your remote to set the alarm"); 
  }

void loop() {
  final=timeToNum(set_hrs,set_mins);
  Display_once(final);

  if (irrecv.decode(&results)) // have we received an IR signal?
  {
  translateIR();
  if (results.value==0xFFA25D){
    Serial.print("Set now time");
    Serial.println("Set hrs _x:xx :");
    hrs_tens=convert(10,10,10,10);
    Serial.println("Set hrs x_:xx :");
    hrs_units=convert(hrs_tens,10,10,10);
    set_hrs = hrs_tens*10 + hrs_units;
    Serial.println("Set mins xx:_x :");
    mins_tens=convert(hrs_tens,hrs_units,10,10);
    Serial.println("Set mins xx:x_ :");
    mins_units=convert(hrs_tens,hrs_units,mins_tens,10);
    set_mins = mins_tens*10 + mins_units;
    final=timeToNum(set_hrs,set_mins);
    
    Display_once(final);
    
    if (set_mins >59){
      set_mins=59;
    }
    hrs=set_hrs;
    mins=set_mins;
    }
      
    else if (results.value==0xFFE21D){
      Serial.println("Alarm is successfully started ...");
      pause=false;
      woke_up=false;
      hrs=set_hrs;
      mins=set_mins;
       while (!pause && !woke_up){
           time_left=hrs*60+mins;
            if (time_left>0){
             Serial.print("Time left : ");
             Serial.println(time_left);
             final=timeToNum(hrs,mins);
             Display(final);
             mins=mins-1;
             if (mins<=0 && hrs>0 ){
                 mins=59;
                 hrs=hrs-1;
             }
             
             if (irrecv.decode(&results)){
              if (results.value==0xFFA25D){
                irrecv.resume(); // receive the next value
                results.value=0xF00000;
                break;
                }
              }
             irrecv.resume(); // receive the next value
             continue;
             
             
            }
             else {
             Serial.println("Wake up !!!!!!!!!!");
             //sing the tunes
                  sing();
             }
       }
      irrecv.resume(); // receive the next value
      }
    else {
      Serial.println("Hit power button to set the time and stop button to ON the timer");
    }
    Serial.print("Current timer is at ");
    Serial.print(hrs);
    Serial.print(":");
    Serial.println(mins);
    final=timeToNum(hrs,mins);
    Display_once(final);
    irrecv.resume(); // receive the next value
    
  }
}

void sing() {
  Serial.println(" 'Mario Theme'");
  int size = sizeof(melody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    check_rfid();
    if (time_left>0){
    return;
    }
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / (tempo[thisNote]*song_speed);

    buzz(melodyPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    buzz(melodyPin, 0, noteDuration);
  }
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(led_pin, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(led_pin, LOW);

}

void check_rfid() {
   // Look for new cards
  showFour(11,1,12,12);
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
//  if (content.substring(1) == "7A 89 84 80") // Change here the UID of the card/cards that you want to give access
                                               // Run identify_tag.ino in order to get the ID of your RFID and update the if loop.
                                               // Then also update else to get output of wrong card. 
                                               
//  {
    Serial.println("Good Morning !!! Have a good Day");
    Serial.println();
    hrs=set_hrs;
    mins=set_mins;
    time_left=hrs*60+mins;
    woke_up=true;
    delay(3000);
//  }

//  else {
//    Serial.println(" Wrong Card");
//    delay(3000);
//  }
}

void translateIR() {
  switch(results.value) {
  case 0xFFA25D: Serial.println("POWER"); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;
  case 0xFF30CF: Serial.println("1");    break;
  case 0xFF18E7: Serial.println("2");    break;
  case 0xFF7A85: Serial.println("3");    break;
  case 0xFF10EF: Serial.println("4");    break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6");    break;
  case 0xFF42BD: Serial.println("7");    break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  
  default: 
    Serial.println(" other button   ");
  }

  delay(500); // Do not get immediate repeat


}

void Display (int orig_number)
{
  int number=0;
  for (int i=0; i<50 ; i++){     // change value from 50 to 3000(50X60) in the for loop to convert the clock from MIN:SEC to HRS:MIN 
    delay_corrector(orig_number);
    number=orig_number;
    if (number == 0)
      showDigit (0, numberofDigits-1); //display 0 in the rightmost digit
    else {
      for (int digit= numberofDigits-1; digit >=0; digit--)
      {
        if (number > 0) {
          showDigit(number % 10, digit);
          number= number/10;
        }
      }
  
    }
  }
}


int convert(int n1, int n2, int n3, int n4) {
  int number =-1;
  while (number==-1){
    showFour(n1, n2, n3, n4);
    if (irrecv.decode(&results)) // have we received an IR signal?
    {
    switch(results.value)
      {
      case 0xFF6897: number=0;    break;
      case 0xFF30CF: number=1;    break;
      case 0xFF18E7: number=2;    break;
      case 0xFF7A85: number=3;    break;
      case 0xFF10EF: number=4;    break;
      case 0xFF38C7: number=5;    break;
      case 0xFF5AA5: number=6;    break;
      case 0xFF42BD: number=7;    break;
      case 0xFF4AB5: number=8;    break;
      case 0xFF52AD: number=9;    break;  
    
      default: 
        number=-1;
    
      }// End Case
      delay(500); // Do not get immediate repeat
      irrecv.resume(); // receive the next value
      if (number!=-1){
      Serial.println(number);
      }
     
    }
  }
  return number;
}

void convertToNum(int num){
  int a = num / 10;      
  int b = num % 10;
  numArray[0]=a;
  numArray[1]=b;
  }

void allDash() {
  for (int digit= numberofDigits-1; digit >=0; digit--) {
    showDigit(10, digit);
  }
}

void delay_corrector(int number) {
  if (number>999){
    delay(0);
    }
   else if (number>99){
    delay(5);
   }
   
   else if (number>9) {
    delay(10);
   }
   else {
    delay(15);
    }
    
  }


void Display_once (int number) {
  if (number == 0)
    showDigit (0, numberofDigits-1); //display 0 in the rightmost digit
  else {
    for (int digit= numberofDigits-1; digit >=0; digit--)
    {
      if (number > 0) {
        showDigit(number % 10, digit);
        number= number/10;
      }
    }

  }
}

//Displays given number on a 7-segment display at the given digit position
void showDigit (int number, int digit) {
  digitalWrite(digitPins[digit], HIGH);
  for (int segment= 1; segment < 8; segment++) {
    boolean isBitSet= bitRead(numeral[number], segment);
    //isBitSet= ! isBitSet; //remove this line if common cathode display
    digitalWrite(segmentPins[segment], isBitSet);
   }
    delay(5);
    digitalWrite(digitPins[digit], LOW);
 }

 void showFour (int n1,int n2,int n3,int n4) {
  int fourArray[]={n1,n2,n3,n4};
  for(int i = 0; i<4; i++){
    digitalWrite(digitPins[i], HIGH);
    for (int segment= 1; segment < 8; segment++) {
    boolean isBitSet= bitRead(numeral[fourArray[i]], segment);
    digitalWrite(segmentPins[segment], isBitSet);
   }
   delay(5);
    digitalWrite(digitPins[i], LOW);
  }
}
  
int timeToNum(int hrs, int mins){
  final=hrs*100+mins;
  return final;
  }
