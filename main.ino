int brightness = 255/2; // base brightness value of the LED @ base temperature
int loopCounter = 0; // count the number of times the program has displayed results

// THE VALUES BELOW CAN BE CHANGED IN ACCORDANCE TO YOUR SETUP/ENVIRONMENT!
int temperatureAnalogPin = A0; // analog pin used for the VOUT (Analog Voltage Output) pin
int LEDDigitalPin = 2; // digital PWM (Pusle Width Modulation) pin used for providing fluctuating power to the LED
float baseTempInCelsius = 25; // the base temperature of the environment the temperature is in
// THE VALUES ABOVE CAN BE CHANGED IN ACCORDANCE TO YOUR SETUP/ENVIRONMENT!

void setup() {
    pinMode(2, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    Serial.print("\nLoop no.: " + String(loopCounter));
    int temperatureAnalogValue = analogRead(temperatureAnalogPin);
    float mV = calculate_mV(temperatureAnalogValue);
    float celsiusTemperature = calculateTemperatureInCelsius(mV);
    LEDFluctuation(celsiusTemperature);
    displayTemperature(mV, celsiusTemperature);
}
// the results are displayed continuosly to prevent possible abruptchange in LED brightness

float calculate_mV(int temperatureAnalogValue) {
    return temperatureAnalogValue * 5.0 * 1000 / 1023;
    // 5V reference, 1000 mV = 1V, 1023 possible analog-to-digit converter (ADC) values (excluding 0 from 2^10 possible values).
}

float calculateTemperatureInCelsius(float mV) {
    return (mV - 500) / 10;
    // 500 mV offset because in the datasheet, the analog pin releases 750 mV at 25 degrees Celsius
    // and provides an additional 10 mV per 1 degree Celsius (750mV - (25 degrees celsius * 10 mV per celsius) = 500mV offset)
    // (in accordance of the datasheet provided for TMP 36GZ)
}

float calculateTemperatureInFahrenheit(float celsius) {
    return (celsius * 1.8) + 32; 
}

void LEDFluctuation(float newTempInCelsius) {
    analogWrite(LEDDigitalPin, brightness);
    brightness = (int) ((255/2) + 6.375 * (newTempInCelsius - baseTempInCelsius));

    // This program assumes a maximum fluctuation of +/- 20 degrees Celsius to better display the fluctuation of temperature
    // the coefficient of 6.375 is calculated within the LEDBrightnessFluctuation.img file
}

void displayTemperature(float mV, float celsiusTemperature) {
    float fahrenheitTemperature = calculateTemperatureInFahrenheit(celsiusTemperature);
    Serial.print("\nMillivolts: " + String(mV));
    Serial.println("mV");
    Serial.print("Temperature (in Celsius): " + String(celsiusTemperature));
    Serial.println("\u00B0C");
    Serial.print("Temperature: (in Fahrenheit): " + String(fahrenheitTemperature));
    Serial.println("\u00B0F");
    // P.S.: Formatting strings in Arduino is a pain, apologies for the verbosity of code :(
}
