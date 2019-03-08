#include <GSM.h>
#include <GSM3MobileClientService.h>
#include <GSM3ShieldV1BaseProvider.h>
#include <GSM3ShieldV1ServerProvider.h>
#include <GSM3MobileMockupProvider.h>
#include <GSM3ShieldV1ModemVerification.h>
#include <GSM3MobileServerService.h>
#include <GSM3MobileServerProvider.h>
#include <GSM3ShieldV1ClientProvider.h>
#include <GSM3ShieldV1.h>
#include <GSM3MobileVoiceProvider.h>
#include <GSM3ShieldV1AccessProvider.h>
#include <GSM3ShieldV1ScanNetworks.h>
#include <GSM3MobileNetworkRegistry.h>
#include <GSM3CircularBuffer.h>
#include <GSM3ShieldV1DirectModemProvider.h>
#include <GSM3ShieldV1MultiClientProvider.h>
#include <GSM3SoftSerial.h>
#include <GSM3IO.h>
#include <GSM3ShieldV1DataNetworkProvider.h>
#include <GSM3ShieldV1BandManagement.h>
#include <GSM3MobileSMSProvider.h>
#include <GSM3MobileNetworkProvider.h>
#include <GSM3MobileDataNetworkProvider.h>
#include <GSM3MobileClientProvider.h>
#include <GSM3ShieldV1VoiceProvider.h>
#include <GSM3MobileAccessProvider.h>
#include <GSM3ShieldV1CellManagement.h>
#include <GSM3ShieldV1ModemCore.h>
#include <GSM3ShieldV1PinManagement.h>
#include <GSM3VoiceCallService.h>
#include <GSM3SMSService.h>
#include <GSM3ShieldV1SMSProvider.h>
#include <GSM3ShieldV1MultiServerProvider.h>
#include <GSM3MobileCellManagement.h>


/*

 This example tests to see if the modem of the
 GSM shield is working correctly. You do not need
 a SIM card for this example.

 Circuit:
 * GSM shield attached

 Created 12 Jun 2012
 by David del Peral
 modified 21 Nov 2012
 by Tom Igoe

 http://www.arduino.cc/en/Tutorial/GSMToolsTestModem

 This sample code is part of the public domain

 */

// libraries
#include <GSM.h>

// modem verification object
GSMModem modem;

// IMEI variable
String IMEI = "";

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start modem test (reset and check response)
  Serial.print("Starting modem test...");
  if (modem.begin()) {
    Serial.println("modem.begin() succeeded");
  } else {
    Serial.println("ERROR, no modem answer.");
  }
}

void loop() {
  // get modem IMEI
  Serial.print("Checking IMEI...");
  IMEI = modem.getIMEI();

  // check IMEI response
  if (IMEI != NULL) {
    // show IMEI in serial monitor
    Serial.println("Modem's IMEI: " + IMEI);
    // reset modem to check booting:
    Serial.print("Resetting modem...");
    modem.begin();
    // get and check IMEI one more time
    if (modem.getIMEI() != NULL) {
      Serial.println("Modem is functoning properly");
    } else {
      Serial.println("Error: getIMEI() failed after modem.begin()");
    }
  } else {
    Serial.println("Error: Could not get IMEI");
  }
  // do nothing:
  while (true);
}
