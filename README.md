# Temperature-LED-Dynamic-Arduino
This project infuses an LED and a temperature sensor to dynamically change the brightness of the LED to visibly display temperature changes in the environment given a base temperature.
NOTE:
The base temperature is set to 25 degrees celsius and may need to be changed accordingly to your eenvironment/setup.
The analog and digital pin number is set to A0 and 2 respectively, and they may need to be changed accordingly to your environment/setup.
(^ These can be changed by editing the respective variable values within the main.ino file located at the top of the file content^)
This program only requires a change +/- 20 degrees Celsius, limiting the maximum possible change in temperature for the purpose of better displaying changes in temperature by reducing the amount of temperature change required to brighten or dim the LED.
The temperature sensor used for this project was a TMP 36GZ.
The resistance used was 220 Ohms with +/- 5% of the stated resistance value (Gold band).
