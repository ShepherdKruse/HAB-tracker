#include <RFM69.h>
#include <SPI.h>

// Addresses for this node. CHANGE THESE FOR EACH NODE!

#define NETWORKID     0   // Must be the same for all nodes
#define MYNODEID      1   // My node ID
#define TONODEID      2   // Destination node ID

// RFM69 frequency, uncomment the frequency of your module:

#define FREQUENCY   RF69_433MHZ
//#define FREQUENCY     RF69_915MHZ

// AES encryption (or not):

#define ENCRYPT       false // Set to "true" to use encryption
#define ENCRYPTKEY    "PASSWORD" // Use the same 16-byte key on all nodes

// Use ACKnowledge when sending messages (or not):

#define USEACK        false // Request ACKs or not

// Packet sent/received indicator LED (optional):

#define LED           9 // LED positive pin
#define GND           8 // LED ground pin

// Create a library object for our RFM69HCW module:

RFM69 radio;

void setup()
{
  // Open a serial port so we can send keystrokes to the module:

  Serial.begin(1200);
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" ready");  


  // Initialize the RFM69HCW:

  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  //radio.setHighPower(); // Always use this for RFM69HCW

  // Turn on encryption if desired:

  if (ENCRYPT)
    radio.encrypt(ENCRYPTKEY);
}

void loop()
{
 

  if (radio.receiveDone()) // Got one!
  {

float testValueReceived = 0.0;

    for (byte i = 0; i < radio.DATALEN; i++)
    {
      ((double*)&testValueReceived)[i] = radio.DATA[i];
    }
    
    Serial.print(testValueReceived);
  
    // RSSI is the "Receive Signal Strength Indicator",
    // smaller numbers mean higher power.

    Serial.print(", RSSI ");
    Serial.println(radio.RSSI);
  }
}
