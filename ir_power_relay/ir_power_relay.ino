#include <IRremote.hpp>

const uint_fast8_t IR_RECEIVE_PIN = 8;
const uint_fast8_t IR_SEND_PIN = 3;

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
}

void loop() {
  delay(1000);
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.command);
      IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
      IrReceiver.resume(); // Enable receiving of the next value
      if (IrReceiver.decodedIRData.command == 65) {
        Serial.println("Caught 65");
        delay(1000);
        IrSender.sendSamsung(0x5343, 0x42, 2);
      }
  }

}