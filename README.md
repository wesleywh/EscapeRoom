# EscapeRoom
Just a lot of helpful scripts and hardware setup that I have been building for my own, just for fun, escape room.

## (Puzzle.ino) RC522 x4 w/ Arduino Nano
### Shared Connections
|RC522 (x4) Pin|Arudino Nano Pin|
|----|----|
|3.3V|3.3V|
|RST|D8|
|GND|GND|
|MOSI|D11|
|MISO|D12|
|SCK|D13|

### Individual Connections (Unique SDA Pin on RC522)

|RC522 (1) | Arudino Nano |
| -----| -----|
|SDA|D3|

|RC522 (2) | Arudino Nano |
| -----| -----|
|SDA|D4|

|RC522 (3) | Arudino Nano |
| -----| -----|
|SDA|D5|

|RC522 (4) | Arudino Nano |
| -----| -----|
|SDA|D6|

## (IDOnly.ino) RC522 W/ Arduino Nano
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
