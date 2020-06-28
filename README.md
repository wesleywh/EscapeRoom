# EscapeRoom
Just a lot of helpful scripts and hardware setup that I have been building for my own, just for fun, escape room.

------------------------------------------------------------

## (4SequencePuzzle.ino) RC522 x4 w/ Arduino Nano
This is a puzzel that will require the user to place 4 RFID tags/chips into the right RFID slot. If they do that correctly it will spin a servo motor which will unlock the box.

For this code to work you need the following 2 libraries:
* Liquid Crystal
* MFRC522

### Shared Connections
|RC522 (x4) Pin|Arudino Uno Pin|
|----|----|
|3.3V|3.3V|
|RST|D10|
|GND|GND|
|MISO|D12|
|MOSI|D11|
|SCK|D13|

### Individual Connections (Unique SDA Pin on RC522)

|RC522 (1) | Arudino Uno |
| -----| -----|
|SDA|D6|

|RC522 (2) | Arudino Uno |
| -----| -----|
|SDA|D7|

|RC522 (3) | Arudino Uno |
| -----| -----|
|SDA|D8|

|RC522 (4) | Arudino Uno |
| -----| -----|
|SDA|D9|


## Servo Motor SG90 1PC
|Servo|Arduino|
|-------|------|
|Red|5V|
|Orange|D2|
|Brown|GND|

-------------------------------------------------------------

## (IDOnly.ino) RC522 W/ Arduino Nano
This is used a slot reader in combination with a server. This will read the rfid and send it to the computer via USB which will then store it and be used to update a progress bar. It will help the user to know how far along the puzzel they are.

### PIN SETUP

|RC522 Pin|Arudino Nano Pin|
|----|----|
|3.3V|3.3V|
|RST|D9|
|GND|GND|
|MISO|D12|
|MOSI|D11|
|SCK|D13|
|SDA|D10|

This is required to use the `IDOnly.ino` file. This file is to be uploaded to the arduino.

## Server Scripts
These scripts make use of `python`,`bash`, and `javascript`.

For the python scripts you need to install the following:
```
pip install serial
pip install flask
pip install pyserial
pip install flask_cors
```
`serial` & `pyserial` is to read the serial connection for the arudino<br/>
`flask` is to run a backend api server that our javascript frontend will call via `jquery` ajax.<br/>
`flask_cors` is to make this callable from different ip address so the javascript can be hosted anywhere and still call the backend python api server.<br/>

------------------------
# Just some notes:
## LCD1602 w/ Arudino
|LCD1602| Arudino Uno|
|----|-----|
|VSS|GND|
|VDD|5V|
|VO|GND|
|RS|D12|
|RW|GND|
|E|D11|
|D4|D5|
|D5|D4|
|D6|D3|
|D7|D2|
|A|5V|
|K|GND|

## Programming ESP8266 w/ Arduino
### Arudino Setup
Connect RST -> GND (Makes it a passthrough)

|ESP8266|Arduino Nano|
|----|----|
|GND|GND|
|VCC|3.3V|
|URXD|RXD|
|UTXD|TX1|
|REST|-|
|CH_PD|CONNECT TO VCC Of ESP8266|
|GPIO2|-|
|GPIO0|CONNECT TO GND OF ESP8266|
