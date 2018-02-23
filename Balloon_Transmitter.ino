// Include the RFM69 and SPI libraries:
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RFM69.h>
#include <SPI.h>
#include <NMEAGPS.h>
#include <GPSport.h>

// Addresses for this node. CHANGE THESE FOR EACH NODE!

#define NETWORKID     0   // Must be the same for all nodes
#define MYNODEID      2   // My node ID
#define TONODEID      1   // Destination node ID

// RFM69 frequency, uncomment the frequency of your module:

#define FREQUENCY       RF69_433MHZ
//#define FREQUENCY     RF69_915MHZ

// AES encryption (or not):

#define ENCRYPT       false // Set to "true" to use encryption
#define ENCRYPTKEY    "PASSWORD" // Use the same 16-byte key on all nodes

// Use ACKnowledge when sending messages (or not):

#define USEACK        false // Request ACKs or not

// Packet sent/received indicator LED (optional):

#define ONE_WIRE_BUS 5


OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

 float Celcius=0;
 
// Create a library object for our RFM69HCW module:

RFM69 radio;

void setup()
{
  // Open a serial port so we can send keystrokes to the module:

  Serial.begin(1200);
  sensors.begin();
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" ready"); 
  gpsPort.begin(9600);

  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  //radio.setHighPower(); // Always use this for RFM69HCW

  // Turn on encryption if desired:

  if (ENCRYPT)
    radio.encrypt(ENCRYPTKEY);
}

void loop()
{
  float latitude = (fix.latitude());
  float longitude = (fix.longitude());
   while (gps.available( gpsPort )) {
    fix = gps.read();
   if (fix.valid.location) {
    String Location;
    Location += String(latitude, 6);
    Location += F(" , ");
    Location += String(longitude , 6);
    digitalWrite(3, HIGH);
    digitalWrite(4,LOW);
    Serial.println(Location);
    radio.send(TONODEID, &Location, sizeof(Location));
    delay(1000);
   }
   else 
   {
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    Serial.print("Initializing...   ");
    Serial.println (fix.satellites);
      
   
   }
   }         
}

