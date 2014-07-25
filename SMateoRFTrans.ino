#include <VirtualWire.h>
#include <idDHT11.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2

char msg[21];
int ldrPin = A0; // fotorezystor
int rainPin = A1; // czujnik deszczu
int gndPin = A2; // czujnik wilgotności gleby

Adafruit_BMP085 bmp;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int transmit_pin = 12;
const int receive_pin = 4;
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
  Serial.print("Humidity (%): "); // podgląd odczytów z czujników
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

 int t = (sensors.getTempCByIndex(0)*100); //wartości czujników jako zmienne
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
 
 char msg[21];

sprintf(msg, "%d.%d.%d.%d.%d.%d.",t, w, c, l, r, g); 

for (int i = 0; i < strlen(msg); i++) {
Serial.print(msg[i]);}
digitalWrite(13,HIGH);
vw_send((uint8_t *)msg, strlen(msg));
vw_wait_tx(); 
digitalWrite(13,LOW);

Serial.println("\n");
Serial.print(msg); // drukowanie na serialu wysłanej wiadomości
Serial.println("\n");

delay(200);
}
