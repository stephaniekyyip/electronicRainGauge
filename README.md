# Electronic Rain Gauge

For my senior design project, my team was tasked with with creating an environmental sensor curriculum for middle school students. We decided to create an electronic rain gauge with a corresponding curriculum.

The rain gauge used two pressure sensors to find a differential pressure, which can be used to to find the depth of rainwater collected in a PVC tube after calibration. This pressure measurement, along with the current time measured by the Real Time Clock (RTC), was logged onto a micro SD card at a set interval of 15 minutes. The idea was that the rain gauge can be set outside to automatically collect rain data with minimal maintenance, which only includes retrieving the SD card to collect data and changing the batteries. 

In addition to constructing the rain gauge hardware, I also wrote the code for the micrcontroller to control the pressure sensors and other electronic components. 

### Structure of Rain Gauge Code:
- Setup SPI and I2C for communication between the microcontroller and components
- Repeat forever:
  - Retrieve data from the pressure sensors
  - Get the time from the real time clock
  - Create a new text file on the SD card reader
  - Save the pressure data and time onto the text file
  - Put the microcontroller to sleep to conserve power
  - Wake up the microcontroller after 15 minutes

