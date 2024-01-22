#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <thread>

// Pin definitions
#define LCD_CLK 18
#define LCD_DIN 23
#define LCD_DC 4
#define LCD_RST 2
#define LCD_CS 15
#define POT_PIN 12
#define SWITCH_PIN 13

// LCD object
Adafruit_PCD8544 lcd = Adafruit_PCD8544(LCD_CLK, LCD_DIN, LCD_DC, LCD_CS, LCD_RST);
int x_index = 0;
const int my_height = 48;
const int my_width = 84;
const int headerSpace = 10;

// Declare functions
void updateLCD();
void printHeader(int lcdHeight);
void homeScreen();

void updateLCD() {
    while (true) {
        // Read potentiometer value
        int potValue = analogRead(POT_PIN);

        // Map potentiometer value to LCD height
        int lcdHeight = map(potValue, 0, 1023, 0, my_height-headerSpace);
        
        // Print header 
        printHeader(lcdHeight);

        if (x_index < my_width) lcd.drawFastVLine(x_index, 0, lcdHeight, BLACK);
        else{ 
            lcd.scroll(0,-1,0,0,my_width-1,my_height-headerSpace);
            lcd.drawFastVLine(my_width-1, 0, lcdHeight, BLACK);
        }

        // Display graph
        lcd.display();

        // Delay for smooth update
        delay(500);
        x_index++;
    }
}
void printHeader(int lcdHeight) {
    lcd.setCursor(0, 0);
    lcd.setTextSize(0);
    lcd.printf("pressure: ");
    lcd.printf("%d", lcdHeight);
    lcd.printf(" bar");
    lcd.drawFastHLine(0, headerSpace, lcd.width(), BLACK);
}


void setup() {
    // Initialize LCD
    Serial.begin(9600);
    lcd.begin();
    lcd.setContrast(50);
    lcd.clearDisplay();
    lcd.display();

    // Start the updateLCD thread
    std::thread lcdThread(updateLCD);
    lcdThread.detach();
}

void loop() {
}


