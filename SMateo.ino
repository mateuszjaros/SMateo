#include <idDHT11.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 1
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal lcd(12,11,10,9,8,7);

int idDHT11pin =0;
int idDHT11intNumber = 2; 
void dht11_wrapper();
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

byte stopnie[8] ={
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000
};
byte dom[8] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B01110,
  B01110
};

byte drzewo[8] = {
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
  B00100,
  B00100,
  B00100
};


byte kropla[8] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B01110
}; 
byte cisnienie[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11001,
  B10101,
  B10001,
  B11111
};
void setup()
{
  lcd.createChar(0,stopnie);
  lcd.createChar(1,dom);
  lcd.createChar(2,drzewo);
  lcd.createChar(3,kropla);
  lcd.createChar(4,cisnienie);
  
  lcd.begin(16,2);
  Serial.begin(9600);
  sensors.begin();
  if (!bmp.begin()) {
    while (1) {}
  }
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
  
  Serial.print("Wilgotnosc DHT11 (%): ");
  Serial.println(DHT11.getHumidity(), 2);
  Serial.print("Temperatura DHT11(oC): ");
  Serial.println(DHT11.getCelsius(), 2);
  Serial.print("Temperatura DS18B20 (oC):");
  Serial.println(sensors.getTempCByIndex(0));
  Serial.print("Temperatura BMP085 (oC):");
  Serial.println(bmp.readTemperature());
  Serial.print("Cisnienie BMP085 (hPa):");
  Serial.println(bmp.readPressure()/100);
  Serial.println();
  Serial.println(); 
  
  lcd.clear();
  lcd.write((byte)1);
  sensors.requestTemperatures();
  lcd.print(sensors.getTempCByIndex(0));
  lcd.write((byte)0);
  lcd.print("C");
  lcd.write((byte)2);
  lcd.print(bmp.readTemperature());
  lcd.write((byte)0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.write((byte)3);
  lcd.print(DHT11.getHumidity(), 2);
  lcd.print("% ");
  lcd.write((byte)4);
  lcd.print(bmp.readPressure()/100);
  lcd.print("hPa");
  delay(1000);
}
