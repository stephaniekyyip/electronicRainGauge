### Pin connections from each electronic component to the Wemos microcontroller

| Name of Component | Pin on Component => Pin on Microcontroller |
| --- | --- |
| SD Card Reader | <b>CS</b> => D3 <br> <b>SCK</b> => D5 <br> <b>MOSI</b> => D7 <br> <b>MISO</b> => D6 <br> <b>VCC</b> => 5V <br> <b>GND</b> => G|
| Real Time Clock (RTC) | <b>32K</b> => N/A <br> <b>SQW</b> => N/A <br> <b>SCL</b> => D1 <br> <b>SDA</b> => D2 <br> <b>VCC</b> => 3V3 <br> <b>GND</b> => G |
| Pressure Sensor #1 (Atomospheric pressure only)| <b>SDO</b> => 3V3 <br> <b>CSB</b> => 3V3 <br> <b>SDA</b> => D2 <br> <b>SCL</b> => D1 <br> <b>GND</b> => G <br> <b>VCC</b> => 3V3 |
| Pressure Sensor #2 (Atomospheric + rainwater pressure) | <b>SDO</b> => G <br> <b>CSB</b> => 3V3 <br> <b>SDA</b> => D2 <br> <b>SCL</b> => D1 <br> <b>GND</b> => G <br> <b>VCC</b> => 3V3 |
| LCD Screen | <b>SCL</b> => D1 <br> <b>SDA</b> => D2 <br> <b>VCC</b> => 5V <br> <b>GND</b> => G |
