#include "DFRobot_CCS811.h"

#define ledGreen 5
#define ledYellow 4
#define ledRed 3

DFRobot_CCS811 CCS811;

int passage = 0;

void setup() {
    pinMode(ledGreen, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    pinMode(ledRed, OUTPUT);

    Serial.begin(115200);

    while(CCS811.begin() != 0) {
        Serial.println("Failed to init chip, please check the chip connection");
    }
}

void loop() {
    if(CCS811.getCO2PPM() >= 0 && CCS811.getCO2PPM() <= 799) {
        digitalWrite(ledYellow, LOW);
        digitalWrite(ledRed, LOW);
        digitalWrite(ledGreen, HIGH);
        passage = 0;
    } else if(CCS811.getCO2PPM() >= 800 && CCS811.getCO2PPM() <= 999) {
        digitalWrite(ledYellow, HIGH);
        digitalWrite(ledRed, LOW);
        digitalWrite(ledGreen, LOW);
        if(passage == 0) {
            tone(6, 600);
            delay(500);
            noTone(6);
        }
        passage = 1;
    } else if(CCS811.getCO2PPM() >= 1000) {
        digitalWrite(ledYellow, LOW);
        digitalWrite(ledRed, HIGH);
        digitalWrite(ledGreen, LOW);
        if(passage == 0 || passage == 1) {
            tone(6, 600);
            delay(1000);
            noTone(6);
        }
        passage = 2;
    }
    
    CCS811.writeBaseLine(0x447B);
    delay(1000);
    
}
