#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LiquidCrystal.h>

// Pin definitions
#define SS_PIN 53
#define RST_PIN 3
#define RELAY_PIN 7  // Pin connected to relay module
#define BUZZER_PIN 4
#define GREEN_LED_PIN 5
#define RED_LED_PIN 6
#define GPS_RX_PIN 25
#define GPS_TX_PIN 24

// Create instances
MFRC522 rfid(SS_PIN, RST_PIN);                     // Create MFRC522 instance.
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);  // Create a SoftwareSerial object for GPS module.
TinyGPSPlus gps;                                   // Create a TinyGPS++ object.
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);           // Initialize the LCD

// Define allowed RFID card IDs
byte allowedCards[][4] = {
  { 0x6F, 0x8E, 0x68, 0x2F },  
  { 0xD3, 0x35, 0xDD, 0xC9 }   
};

// Number of allowed cards
int numAllowedCards = sizeof(allowedCards) / sizeof(allowedCards[0]);

bool vehicleAccessed = false;  // Flag to track vehicle access

void setup() {
  // Serial.begin(9600);  // Initialize serial communications.
  gpsSerial.begin(9600);
  SPI.begin();                               // Initialize SPI bus.
  rfid.PCD_Init();                           // Initialize RFID reader.
  rfid.PCD_SetAntennaGain(rfid.RxGain_max);  // Set RFID antenna gain to maximum

  // Initialize the LCD
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
  displayWelcomeMessage();

  // Initialize relay control pin
  pinMode(RELAY_PIN, OUTPUT);

  // Initialize LED and buzzer pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  // Serial.println("Setup completed.");  // Debug message
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    if (isCorrectRFID()) {
      startEngine();
      delay(300);  // Engine startup delay
    } else {
      incorrectRFID();
    }
    rfid.PICC_HaltA();  // Halt PICC
    rfid.PCD_StopCrypto1();  // Stop encryption on PCD
  }

  // Read GPS data and display on LCD
while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
        if (gps.location.isValid()) {
            double latitude = gps.location.lat();
            double longitude = gps.location.lng();
            
            // Display on LCD
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Lat: ");
            lcd.print(latitude, 6);
            lcd.setCursor(0, 1);
            lcd.print("Lng: ");
            lcd.print(longitude, 6);
            
            // Display on Serial Monitor
            Serial.print("Latitude: ");
            Serial.println(latitude, 6);
            Serial.print("Longitude: ");
            Serial.println(longitude, 6);

            delay(2000);  // Display update delay
            displayWelcomeMessage();
        } else {
            lcd.setCursor(0, 1);
            lcd.print("Waiting for GPS");

            Serial.println("Waiting for GPS signal...");
        }
    }
}


  // Continue to display the welcome message if the vehicle hasn't been accessed
  if (!vehicleAccessed) {
    displayWelcomeMessage();
  }
}

bool isCorrectRFID() {
  // Read the scanned card's UID
  byte currentCardUID[4];
  for (byte i = 0; i < 4; i++) {
    currentCardUID[i] = rfid.uid.uidByte[i];
  }

  // Check if the scanned card's UID matches any allowed card
  for (int i = 0; i < numAllowedCards; i++) {
    if (memcmp(currentCardUID, allowedCards[i], sizeof(currentCardUID)) == 0) {
      return true;  // Scanned card is allowed
    }
  }

  return false;  // Scanned card is not allowed
}

void startEngine() {
  // Sound buzzer for countdown
  for (int count = 1; count <= 3; count++) {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print(count);
    tone(BUZZER_PIN, 100);  // Sound buzzer
    delay(500);  // Wait for 0.5 second
    noTone(BUZZER_PIN); // Turn off buzzer for 0.5 second
    delay(500);
  }
   digitalWrite(RELAY_PIN, HIGH); 
  lcd.clear();
  lcd.setCursor(1, 0);  // Center "Engine Started."
  lcd.print("Engine Started.");
  // Serial.println("Engine started.");  // Debug message
  digitalWrite(GREEN_LED_PIN, HIGH);  // Turn on green LED
  digitalWrite(RED_LED_PIN, LOW);     // Turn off red LED
      // Activate relay (start engine)

  // Sound buzzer for 3 seconds
  for (int i = 0; i < 1000; i += 100) {
    tone(BUZZER_PIN, 100);  // Sound buzzer
    delay(100);
    delay(100);
    noTone(BUZZER_PIN);
  }

  lcd.clear();
  lcd.setCursor(1, 0);  // Center "Vehicle is accessed."
  lcd.print("Vehicle accessed");
  vehicleAccessed = true;
}


void stopEngine() {
  lcd.clear();
  lcd.setCursor(0, 0);  // Center "Engine Stopped." (16 - 14) / 2 = 1
  lcd.print("Engine Stopped.");
  // Serial.println("Engine Stopped.");  // Debug message
  digitalWrite(GREEN_LED_PIN, LOW);   // Turn off green LED
  digitalWrite(RELAY_PIN, LOW);       // Deactivate relay (stop engine)
  tone(BUZZER_PIN, 100);  
     delay(2000);
  noTone(BUZZER_PIN);                 // Turn off buzzer
}

void incorrectRFID() {
  lcd.clear();
  lcd.setCursor(3,0 );
  lcd.print("Wrong ID!");
  // Serial.println("Wrong  ID!");  // Debug message
  digitalWrite(GREEN_LED_PIN, LOW);   // Turn off green LED
  digitalWrite(RED_LED_PIN, HIGH);    // Turn on red LED
  // digitalWrite(RELAY_PIN, LOW);       // Deactivate relay (stop engine)

  
  // Sound buzzer for 5 seconds
  unsigned long buzzerStartTime = millis();
  while (millis() - buzzerStartTime < 500) {
    tone(BUZZER_PIN, 100);  // Sound buzzer
    delay(100);
    noTone(BUZZER_PIN);
    delay(100);
  }
    delay(50);
  stopEngine();
    delay(1000);
  // Clear LCD and continue scanning
  lcd.clear();
  delay(2000);
  displayWelcomeMessage();
}


void displayWelcomeMessage() {
  static char msg[] = "Hello Sir !!! Scan ID to access the vehicle.... ";
  static int pos = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) {
    lcd.print(msg[(pos + i) % strlen(msg)]);
  }
  pos++;
  delay(250);  // Adjust delay for scrolling speed
}
