# Thermometers

Measure temperature (°F) and humidity (\%RH) using two Raspberry Pi boards. Store readings in local CSV files, and aggregate the data on one machine ('server').

## Hardware Requirements:
- Two I2C-capable Raspberry Pi boards with network access.
- LAN Router with reserved IP for at least one Pi.
- Two Adafruit Si7021 chips.
- Prototyping board and/or jumper wires.

## Software Requirements:
- [`WiringPi`](http://WiringPi.com) *Distributed under [GNU LGPLv3](https://www.gnu.org/licenses/lgpl-3.0.html). This project and its author are not affiliated with WiringPi.*
