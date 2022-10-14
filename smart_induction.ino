/*
  PIN CONNECTIONS
  -------------------------------
   GND  --> GND
   VCC  --> 3.3V
   DATA --> GPIO2
  -------------------------------
  CHPD --> R=10k --> VCC

  -------------------------------

*/
//= DEFINES ========================================================================================
#define ESP8266_GPIO0 0        // HIGH is 3.3V
#define ESP8266_GPIO1 1        // TX
#define ESP8266_GPIO2 2        // HIGH is 3.3V
#define ESP8266_GPIO3 3        // RX

#define RCSwitchDisableReceiving

#define PIN_RF_TX ESP8266_GPIO2
#define RF433_CODE 9094706  // KitchenHoodRemote - button 3

//= INCLUDES =======================================================================================
#include <RCSwitch.h>
#include <ESP8266WiFi.h>

//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = ESP8266_GPIO3;  // choose the pin for the LED

const int rf_pulse_length = 351;
const unsigned int rf_code_length = 24;
const unsigned int rf_repeat_count = 10;
const int rf_protocol = 1;  // (default is 1, will work for most outlets)

//= VARIABLES ======================================================================================
RCSwitch rfTx = RCSwitch();

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  //Serial.begin(115200);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  //----------------------------------------
  digitalWrite(LED_INDICATOR_PIN, HIGH);
  //
  WiFi.mode(WIFI_OFF);
  //
  rfTx.enableTransmit(PIN_RF_TX);
  //
  rfTx.setProtocol(rf_protocol);
  // set pulse length.
  rfTx.setPulseLength(rf_pulse_length);
  // set number of transmission repetitions.
  //rfTx.setRepeatTransmit(rf_repeat_count);
  //----------------------------------------
  //
  delay(100);
  digitalWrite(LED_INDICATOR_PIN, LOW);
}
//==================================================================================================
void loop() {
  if (shouldSendRfCode()) {
    //Serial.println("Send RF code!");
    transmitRfCode(RF433_CODE, rf_code_length);
  }
  //
  delay(10 * 1000);
}
//==================================================================================================
bool shouldSendRfCode() {
  return true;
}
//==================================================================================================
void transmitRfCode(unsigned long code, unsigned int code_length) {
  digitalWrite(LED_INDICATOR_PIN, HIGH);
  rfTx.send(code, code_length);
  delay(100);
  digitalWrite(LED_INDICATOR_PIN, LOW);
}
//==================================================================================================