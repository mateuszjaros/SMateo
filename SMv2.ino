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

int czas = 0;

void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  sensors.begin();
  if (!bmp.begin()) {
    while (1) {}
  }
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(3, OUTPUT);
}
void dht11_wrapper() {
  DHT11.isrCallback();
}
void loop()
{
 int ghumidity = analogRead(A1);
 int rain = analogRead(A0);
 int ldr = analogRead(A2);
 int lldr = map(ldr,0,1023,0,100);
 int rain1 = map(rain, 0,1023,100,0);
 
 if (czas <3)
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Temperatures");
   lcd.setCursor(0,1);
   lcdtempin();
   lcdtempout();
 }
 else if (czas >= 3 && czas <6)
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Humidity");
   lcd.setCursor(0,1);
   lcdhumidity();
 }
 else if (czas >=6 && czas <9)
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Pressure");
   lcd.setCursor(0,1);
   lcdpressure();
 }
 else if (czas >=9 && czas <12)
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Rain");
   lcd.setCursor(0,1);
   lcdrain();
 }
 else if (czas >=12 && czas <15)
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Ground Humidity");
   lcd.setCursor(0,1);
   lcdghumidity();
 }
 else
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Light");
   lcd.setCursor(0,1);
   lcdldr();
 }
 
 (czas ++);
 delay(1000);
 
}


void lcdtempin()
{
  sensors.requestTemperatures();
  lcd.print("In");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print("C");
}


void lcdtempout()
{
  sensors.requestTemperatures();
  lcd.print("Out");
  lcd.print(sensors.getTempCByIndex(1));
  lcd.print("C");
}


void lcdhumidity()
{
  int result = DHT11.acquireAndWait();
  switch (result)
  {
  case IDDHTLIB_OK: 
    break;
  default: 
    break;  
  }
  
  lcd.print(DHT11.getHumidity(), 2);
  lcd.print("% ");
}


void lcdpressure()
{
  lcd.print(bmp.readPressure()/100);
  lcd.print("hPa");
}


void shumidity()
{
  Serial.print("Humidity DHT11 (%): ");
  Serial.println(DHT11.getHumidity(), 2);
}


void stempDHT11()
{
  Serial.print("Temperatura DHT11(oC): ");
  Serial.println(DHT11.getCelsius(), 2);
}


void stempDS18B200()
{
  Serial.print("Temperatura DS18B20 (oC):");
  Serial.println(sensors.getTempCByIndex(0));
}


void stempDS18B201()
{
  Serial.print("Temperatura DS18B20 (oC):");
  Serial.println(sensors.getTempCByIndex(1));
}


void stempBMP085()
{
  Serial.print("Temperatura BMP085 (oC):");
  Serial.println(bmp.readTemperature());
}

void spressure()
{
  Serial.print("Cisnienie BMP085 (hPa):");
  Serial.println(bmp.readPressure()/100);
}

void lcdrain()
{
  lcd.print(rain1);
}

void srain()
{
  Serial.print("Rain: ");
  Serial.println(rain);
}

void lcdghumidity()
{
 int ghumidity1 = map(ghumidity, 0,1023,100,0);
  lcd.print(ghumidity1);
}


void sghumidity()
{
  Serial.print("Ground Humidity: ");
  Serial.println(ghumidity);
}

void lcdldr()
{
  lcd.print(lldr);
}


void sldr()
{
  Serial.print("LDR");
  Serial.println(ldr);
}


void lcdlight()
{
  if (ldr =<900)
  {
    analogWrite(3,255);
  }
  else if (ldr =<500 && ldr >900)
  {
    analogWrite(3, 150);
  }
  else if (ldr >500)
  {
    map(ldr, 0,500,1,149);
  }

  
