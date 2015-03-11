#include <SoftwareSerial.h>

SoftwareSerial calc(10, 11); //That's RX and TX

void setup()  
{
    Serial.begin(9600);
    calc.begin(9600);
}

void loop()
{
    if(calc.available()) {
        char data = calc.read();
        Serial.write(data);
    }
    
    Serial.write(0x55);
    
    if(Serial.available()) calc.write(Serial.read());
}
