// baseed on ArduinoBlingLED : https://github.com/Lauszus/ArduinoBlinkLED

#include <Usb.h>
#include <adk.h>

USB Usb;
ADK adk(&Usb,"bangbang.song", // Manufacturer Name
             "AndroidArduinoLooper", // Model Name
             "imple a loop-back protocol between android and arduino", // Description (user-visible string)
             "1.0", // Version
             "https://github.com/luoqii/android_arduino_loop", // URL (web page to visit if no installed apps support the accessory)
             "123456789"); // Serial Number (optional)

#define LED 13 // Pin 13 is occupied by the SCK pin on a normal Arduino (Uno, Duemilanove etc.), so use a different pin
int loopCount;
int BUFFER_SIZE = 1024;
void setup()
{
  Serial.begin(115200);
  Serial.print("\r\nADK demo start");
  if (Usb.Init() == -1) {
    Serial.print("\r\nOSCOKIRQ failed to assert");
    while(1); //halt
  }
  pinMode(LED, OUTPUT);
}

void loop()
{    
  Usb.Task();
  boolean ready = adk.isReady();
  Serial.print(" ");
  Serial.print(loopCount);
  if (ready) {
    Serial.println("ready OK.");
  }
  else {
      Serial.println("ready KO.");
  }
  if(ready) {
    uint8_t msg[BUFFER_SIZE];
    uint16_t len = sizeof(msg);
    uint8_t rcode = adk.RcvData(&len, msg);
    Serial.print("rcode: ");
    Serial.print(rcode);
    Serial.print(" len: ");
    Serial.print(len);
    if (len >0) {
    Serial.print(" msg: ");
    }
    for (int i = 0 ; i < len ; i++ ) {
    Serial.print(msg[i]);
    Serial.print("");
    }
    Serial.println();
    if(rcode && rcode != hrNAK)
      USBTRACE2("Data rcv. :", rcode);
    if(len > 0) {
      Serial.print(F("\r\nData Packet: "));
      Serial.print(msg[0]);
      digitalWrite(LED,msg[0] ? HIGH : LOW);
    }
    
    rcode = adk.SndData(len, msg);
    Serial.print("snd rcode: ");
    Serial.println(rcode);
  } 
  else
    digitalWrite(LED, LOW); 
    
    loopCount++;
    delay(1000);
}
