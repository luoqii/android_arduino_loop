// baseed on ArduinoBlingLED : https://github.com/Lauszus/ArduinoBlinkLED

#include <Usb.h>
#include <adk.h>

USB Usb;
ADK adk(&Usb,
        // Manufacturer Name
        "bangbang.song",
        // Model Name
        "AndroidArduinoLooper",
        // Description (user-visible string)
        "impl a loop-back protocol between android and arduino",
        // Version
        "1.0",
        // URL (web page to visit if no installed apps support the accessory)
        "https://github.com/luoqii/android_arduino_loop",
        // Serial Number (optional)
        "123456789");

int loopCount;
int BUFFER_SIZE = 64;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\nADK demo start");
  if (Usb.Init() == -1) {
    Serial.print("\r\nOSCOKIRQ failed to assert");
    while (1); //halt
  }
  Serial.println("\r\nADK demo completed.");
}

void loop()
{
  Usb.Task();
  boolean ready = adk.isReady();

  //  Serial.print(" ");
  //  Serial.print(loopCount);
  //  if (ready) {
  //    Serial.println("ready OK.");
  //  }  else {
  //    Serial.println("ready KO.");
  //  }

  if (ready) {
    uint8_t msg[BUFFER_SIZE];
    uint16_t len = sizeof(msg);
    uint8_t rcode = adk.RcvData(&len, msg);
    //    Serial.print("rcode: ");
    //    Serial.print(rcode);
    //    Serial.print(" len: ");
    //    Serial.print(len);
    if (len > 0) {
      Serial.print("RCV msg: ");

      for (int i = 0 ; i < len ; i++ ) {
        Serial.print(msg[i]);
        Serial.print("");
      }
      Serial.println();
      
//      if (rcode && rcode != hrNAK)
//        USBTRACE2("Data rcv. :", rcode);
        
//      if (len > 0) {
//        Serial.print(F("\r\nData Packet: "));
//        Serial.print(msg[0]);
//      }

      rcode = adk.SndData(len, msg);
      Serial.print("snd rcode: ");
      Serial.println(rcode);
    }
  }

  loopCount++;
  delay(1000);
}