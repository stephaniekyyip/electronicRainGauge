# Electronic Rain Gauge

<img src = "https://github.com/stephaniekyyip/electronicRainGauge/blob/master/rainGauge.jpg?raw=true" alt = "rain gauge" width= 400px></img>

## Overview
For my senior design project, my team was tasked with with creating an environmental sensor curriculum for middle school students. We decided to create an electronic rain gauge with a corresponding curriculum.

My role in the project included constructing the rain gauge hardware and writing C/ C++ code using the Arduino IDE for the microcontroller in order to control the various electronic components. 

## How the Rain Gauge Works
The rain gauge design involves a funnel attached to a PVC pipe that allowed water to be collected in the PVC. At the bottom of the PVC pipe is a PVC container that holds the waterproofed pressure sensor, which measures the pressure of the rainwater. Wires from the pressure sensor are threaded through a waterproof box to connect the sensor to the rest of the electronic components. The second pressure sensor on the breadboard is used to find the atmospheric pressure. 

Using the two pressure sensors, the differential pressure can be calculated. The depth of the rainwater collected in the PVC tube can be found using the differential pressure after calibration is done. The differential pressure, along with the current time measured by the Real Time Clock (RTC), is logged onto a micro SD card every 15 minutes. The idea is that the rain gauge can be set outside to automatically collect rain data with minimal maintenance apart from retrieving the SD card to collect the data and changing the batteries. 

## Structure of the Rain Gauge Code
Code located in `rain_gauge_datalogging.ino`
- In a continous loop:
  - Retrieve data from the pressure sensors
  - Get the time from the real time clock
  - Create new text file or open existing text file on the SD card
  - Save the pressure data and current time onto the text file
  - Put the microcontroller to sleep to conserve power
  - Wake up the microcontroller after 15 minutes
 
 ## Software Libraries Used
 - [Adafruit Sensor Driver](https://github.com/adafruit/Adafruit_Sensor)
 - [Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library) (Pressure sensors)
 - [DS1307 RTC](https://github.com/PaulStoffregen/DS1307RTC) (Real Time Clock)
 - [LCD1602](https://www.dfrobot.com/wiki/index.php/I2C/TWI_LCD1602_Module_(SKU:_DFR0063)) (LCD screen used for testing and calibration)
 
 ## Hardware Components
 
 <img src = "https://github.com/stephaniekyyip/electronicRainGauge/blob/master/rainGaugeElectronics.jpg?raw=true" alt = "rain gauge electronics" width = 400px></img>
 
 - Microcontroller (Wemos D1 Mini ESP8266)
 - Pressure Sensors x2 (BMP280)
 - Real Time Clock (DS1307)
 - SD Card Reader (Catalex)
 - microSD card
 - 4-AA Battery Pack
 - Switch (for turning the microcontroller on/off)
 - 10k resistor for switch
 - LCD Screen (LCD1602)
 
#### For a more details on this project, please visit my website [here](https://stephaniekyyip.com/projects/rainGauge).
