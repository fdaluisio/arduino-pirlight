
#define PirPin 2

const int ledPin=13;
const int relayPin = 8;
const int lightPin = 0;
unsigned long tacceso = 300000; // 5 min in millis = 5*60*1000;
const int thresholdlight=400;
boolean movement = LOW;
boolean light = LOW;
boolean debug = 0;
unsigned long htime = 0;
boolean firstrun = 1;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin,LOW);
  pinMode(PirPin, INPUT);
  digitalWrite(PirPin,LOW);
  pinMode(lightPin,INPUT);
  digitalWrite(lightPin,LOW);
    //give the sensor some time to calibrate
  Serial.print("10 sec of calibrating PIR sensor ");
  for(int i = 0; i < 10; i++){
    Serial.print(".");
    delay(1000);
  }
}

void loop() {
  light = isLightDetected();
  movement = isPeopleDetected();
  if (debug) {
    Serial.println(millis());
    Serial.println(htime);
    Serial.println(htime+tacceso);
  }
  if ( millis() > htime + tacceso | firstrun ) {
    if(light && movement ) {
        if (debug) digitalWrite(ledPin,HIGH);
        digitalWrite(relayPin, HIGH);
        if (debug) Serial.println("Ti ho visto!");
        // imposto il tempo in cui si accende
        htime = millis();
        if (firstrun) firstrun = 0;
        if (debug) {
          Serial.print("htime: ");
          Serial.print(htime);
          Serial.print("; htime + tacceso: ");
          Serial.println(htime+tacceso);
        }
    }
    else {
        if (debug) digitalWrite(ledPin,LOW);
        digitalWrite(relayPin, LOW);
        if (debug) Serial.println("visto niente o troppa luce");
    }
  }
  if (debug) Serial.print("End loop ");
  if (debug) Serial.println(firstrun);  
  delay(1000);
}

/***************************************************************/
/*Function: Detect whether anyone moves in it's detecting range*/
/*Return:-boolean, true is someone detected.*/
boolean isPeopleDetected()
{
	int sensorValue = digitalRead(PirPin);
	if(sensorValue == HIGH)//if the sensor value is HIGH?
	{
	   if (debug) Serial.println("PirSensor true");	
           return true;
	}
	else
	{
	  if (debug) Serial.println("PirSensor false");
  	  return false;
	}
}

/*********************************************************************/
/*Function: Detect if lighsensor value readed is more than threshold */
/*Return:-boolean, true if lower than a threshold                    */
boolean isLightDetected()
{
	int sensorValue = analogRead(lightPin);
	if(sensorValue < thresholdlight)
	{
	  if (debug) {
            Serial.print("LightSensor true ");
            Serial.println(sensorValue);
          }
          return true;
	}
	else
	{
          if (debug) {
	    Serial.print("LightSensor false ");
            Serial.println(sensorValue);
          }
          return false;
	}
}
