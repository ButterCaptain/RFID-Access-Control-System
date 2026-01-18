#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define RST_PIN 7
#define SS_PIN 10
#define SERVO_PIN 9


Servo myservo;
MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);


String lockCode = "";
bool firstCard = true;
bool isOpen = true; // Tracks current servo state (0 = locked, 90 = unlocked)


// Convert UID to a hex string
String getCardID(MFRC522::Uid uid) {
String id = "";
 for (byte i = 0; i < uid.size; i++) {
   if (uid.uidByte[i] < 0x10) id += "0"; // Leading zero
   id += String(uid.uidByte[i], HEX);
 }
 return id;
}


// Print card ID to LCD
void displayCardID(MFRC522::Uid uid) {
 for (byte i = 0; i < uid.size; i++) {
   if (uid.uidByte[i] < 0x10) lcd.print("0");
   lcd.print(rfid.uid.uidByte[i], HEX);
   lcd.print(" ");
 }
}


void setup() {
 Serial.begin(9600);
 SPI.begin();
 rfid.PCD_Init();
 myservo.attach(SERVO_PIN);


 lcd.init();
 lcd.backlight();
 lcd.setCursor(0, 0);
 lcd.print("Scan RFID Tag");
}


void loop() {
 if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
   return;


 String scannedCode = getCardID(rfid.uid);
 Serial.println(scannedCode);


 if (firstCard) {
   lockCode = scannedCode;
   firstCard = false;


   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("KEY SET:");
   lcd.setCursor(0, 1);
   displayCardID(rfid.uid);
   delay(500);
 } else if (scannedCode.equalsIgnoreCase(lockCode)) {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Access Granted");


   // Toggle the servo state
   if (!isOpen) {
     Serial.println("Unlock");
     myservo.write(90);  // Unlock
     isOpen = true;
   } else {
     Serial.println("Lock");
     myservo.write(0);   // Lock
     isOpen = false;
   }
   delay(2000);
 }
 else {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Access Denied");
   delay(2000);
 }


 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Scan RFID Tag");


 rfid.PICC_HaltA();
 rfid.PCD_StopCrypto1();
}



