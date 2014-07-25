#include <VirtualWire.h>
#include <idDHT11.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 1

char msg[25];
int ldrPin = A0;
int rainPin = A1;
int gndPin = A2;

Adafruit_BMP085 bmp;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;

int idDHT11pin = 0; 
int idDHT11intNumber = 2;
void dht11_wrapper(); 
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

void setup()
{
Serial.begin(9600);
  sensors.begin();
  if (!bmp.begin()) {
    while (1) {}
  }
  
    vw_set_tx_pin(transmit_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  
  pinMode(ldrPin, INPUT);
  pinMode(rainPin, INPUT);
  pinMode(gndPin, INPUT);
  
  
}

void dht11_wrapper() {
  DHT11.isrCallback();
}
void loop()
{
  int result = DHT11.acquireAndWait();
  switch (result)
  {
  case IDDHTLIB_OK: 
    break;
  case IDDHTLIB_ERROR_CHECKSUM: 
    break;
  case IDDHTLIB_ERROR_ISR_TIMEOUT: 
    break;
  case IDDHTLIB_ERROR_RESPONSE_TIMEOUT: 
    break;
  case IDDHTLIB_ERROR_DATA_TIMEOUT: 
    break;
  case IDDHTLIB_ERROR_ACQUIRING: 
    break;
  case IDDHTLIB_ERROR_DELTA: 
    break;
  case IDDHTLIB_ERROR_NOTSTARTED: 
    break;
  default: 
    break;  
  }
  sensors.requestTemperatures();
  Serial.print("Humidity (%): ");
  Serial.println(DHT11.getHumidity(), 2);
  Serial.print("Cisnienie BMP085 (hPa):");
  Serial.println(bmp.readPressure()/100);
  Serial.print("Temperatura DS18B20 (oC):");
  Serial.println(sensors.getTempCByIndex(0));
  Serial.print("Jasnosc: ");
  Serial.println(map(analogRead(ldrPin), 0, 1023, 0, 999));
  Serial.print("Opady: ");
  Serial.println(map(analogRead(rainPin), 0, 1023, 0, 999));
  Serial.print("Gleba: ");
  Serial.println(map(analogRead(gndPin), 0, 1023, 0, 999));
  Serial.println();
  Serial.println(); 

 int t = (sensors.getTempCByIndex(0)*100);
 int w = (DHT11.getHumidity());
 int c = (bmp.readPressure()/100);
 int l = (map(analogRead(ldrPin), 0, 1023, 0, 999));
 int r = (map(analogRead(rainPin), 0, 1023, 0, 999));
 int g = (map(analogRead(gndPin), 0, 1023, 0, 999));
 Serial.println(t);
 Serial.println(w);
 Serial.println(c);
 Serial.println(l);
 Serial.println(r);
 Serial.println(g);
 
 char msg[25];
int n = sprintf(msg, "%d.%d.%d.%d.%d.%d.",t, w, c, l, r, g);
  msg.toCharArray(Msg,(msg.length()+1));
    for (int i = 0; i <= msg.length(); i++) {
    Serial.print(Msg[i]);}
      vw_send((uint8_t *)Msg, strlen(Msg));
    vw_wait_tx(); 
 // msg.toCharArray(Msg, (msg.length()+1));
  //vw_send((uint8_t *)msg, 25);
  //vw_wait_tx(); // Wait until the whole message is gone
  //digitalWrite(13, LOW);
  delay(200);
Serial.println("\n");
Serial.print(msg);
Serial.println("\n");

}
