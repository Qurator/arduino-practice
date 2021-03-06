//code from https://www.instructables.com/id/Arduino-Light-Sensitive-Bar-Graph/
int soundSensor = 2;
const int NbrLEDs = 6;
const int ledPins[] = { 13, 12, 11, 10,9, 8 };
const int analogInPin = 0;  // Analog input pin connected to variable resistor
const int wait = 30;

bool enable = false;
unsigned long soundDetectedTime;

// Swap values of the following two constants if cathodes are connected to Gnd
const boolean LED_ON = LOW;
const boolean LED_OFF = HIGH;

int sensorValue = 0;        // value read from the sensor
int ledLevel = 0;           // sensor value converted into LED 'bars'

void setup() {
	Serial.begin(9600);
	pinMode(soundSensor, INPUT);
	for (int led = 0; led < NbrLEDs; led++)
	{
		pinMode(ledPins[led], OUTPUT);                             // make all the LED pins outputs
	}
}

void loop() {
	int soundSensorValue = digitalRead(soundSensor);
	if (soundSensorValue == 1) {
		shouldLEDShow();
	}


	if (enable) {
		sensorValue = analogRead(analogInPin);                 // read the analog in value
		ledLevel = map(sensorValue, 0, 700, 0, NbrLEDs);  // map to the number of LEDs

		for (int led = 0; led < NbrLEDs; led++)
		{
			//Serial.println(ledLevel);
			if (led < ledLevel) {
				digitalWrite(ledPins[led], LED_ON);                    // turn on pins less than the level
			}
			else {
				digitalWrite(ledPins[led], LED_OFF);                 // turn off pins higher than the level
			}
		}
	}
	else {
		for (int led = 0; led < NbrLEDs; led++) {
			digitalWrite(ledPins[led], LED_OFF);
		}
	}
}

void shouldLEDShow() {
	if (millis() - soundDetectedTime > 1000) {
		if (enable) {
			enable = false;
		}
		else {
			enable = true;
		}
	}
}