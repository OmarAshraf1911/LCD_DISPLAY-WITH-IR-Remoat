#include <LiquidCrystal.h> // Import LiquidCrystal library
#include <IRremote.h> // Import IRremote library
#define RECV_PIN 9 // Receiver pin
unsigned int command; // Variable to store the infrared command
unsigned int col = 0; // Variable to store column position
unsigned int row = 0; // Variable to store row position
// Initialize the LiquidCrystal library
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Print a message
void printMessage(int col, int row){
lcd.clear(); // Clear LCD
lcd.setCursor(col, row); // Set cursor at position (col, row)
lcd.print("Hello Omar"); // Display text
}
void setup() {
Serial.begin(9600); // Begin serial communication at 9600 baud rate
IrReceiver.begin(RECV_PIN); // Start the receiver
lcd.begin(16, 2); // Set up the LCD's number of columns and rows
printMessage(0, 0); // Print a message at position (0, 0)
}
void loop() {
if (IrReceiver.decode()) { // If a button is pressed
command = IrReceiver.decodedIRData.command; // Get the infrared command
Serial.println(command, HEX); // Print button command in hexadecimal
switch(command) // Check the infrared command
{
case 0x9: // Right arrow button
if(col < 15) // Check max position
col++; // Move right
break;
case 0x7: // Left arrow button
if(col > 0) // Check min position
col--; // Move left
break;
}
printMessage(col, row); // Print a message at position (col, row)
IrReceiver.resume(); // Receive the next value
}
delay(50); // Short delay to improve performance
}