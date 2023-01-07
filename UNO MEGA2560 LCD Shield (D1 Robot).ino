/*******************************************************
This program will test the LCD panel
 and the buttons on D1 Robot LCD Keypad Shield
David C. Boyce, January 2023

Boards: UNO
        MEGA2560
Please Note: pin 10 must be set to INPUT to prevent damage to your shield

GitHub: https://github.com/CranialSpongeWorks

YouTube: https://www.youtube.com/@PCBoardRepair
********************************************************/

//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int LED = 13;
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
char pos[10];  //size + 1

void setup() {
 pinMode(10, INPUT); //must be set as INPUT
 pinMode(LED, OUTPUT);
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0, 0);
 lcd.print("D1 Robot LCD1602");
 lcd.setCursor(1,1);
 lcd.print("Keypad Shield");
 delay(3000);
 lcd.clear();
 lcd.setCursor(3, 0);
 lcd.print("Created By");
 lcd.setCursor(1,1);
 lcd.print("David C. Boyce");
 delay(3000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Push any button"); // print a simple message
}
 
void loop() {
 lcd.setCursor(7,1);                  // move cursor to second line "1" and 9 spaces over
 dtostrf((millis()/1000),9, 0, pos);  //unique function converts float to string
 lcd.print(pos);                      // display seconds elapsed since power-up

 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key) {             // depending on which button is pushed we perform an action
   case btnRIGHT: {
     lcd.print("RIGHT ");
     digitalWrite(LED, HIGH);
     break;
     }
   case btnLEFT: {
     lcd.print("LEFT   ");
     digitalWrite(LED, HIGH);
     break;
     }
   case btnUP: {
     lcd.print("UP    ");
     digitalWrite(LED, HIGH);
     break;
     }
   case btnDOWN: {
     lcd.print("DOWN  ");
     digitalWrite(LED, HIGH);
    break;
     }
   case btnSELECT: {
     lcd.print("SELECT");
     digitalWrite(LED, HIGH);
     break;
     }
     case btnNONE: {
     lcd.print("NONE  ");
     digitalWrite(LED, LOW);
     break;
     }
 }
}

// read buttons
int read_LCD_buttons() {
 adc_key_in = analogRead(0);      // read the value 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // no Key pressed
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  
 return btnNONE;  // when all others fail return btnNONE
}

//end