import os
import sys
import glob
import serial
import serial.tools.list_ports
import requests

cur_dir = os.path.dirname(os.path.realpath(__file__))
main_server_ip = "192.168.0.22"
sent_rfids = []

def process_serial_input(port, baudrate=9600):
    ser = serial.Serial(port, baudrate)
    print("Reading on port: "+port)
    while True:
        msg = str(ser.readline())
        if msg:
            rfid = msg[2:][:-5]
            if type(rfid) is int and int(rfid) == 0000: continue
            if "START" not in rfid:
                if rfid not in sent_rfids:
                    send_to_api(rfid)
                else:
                    print(rfid+" Already read, skipping.")
            else:
                print("Initialized.")
            
def send_to_api(rfid):
    try:
        endpoint = "http://"+main_server_ip+":5000/AddRFID"
        print("Sending "+rfid+" to "+endpoint)
        r = requests.post(endpoint, timeout=2, data = { "RFID": rfid })
        print("SUCESS")
        sent_rfids.append(rfid)
    except:
        print("FAILED")

try:
    process_serial_input("1")
except Exception as ex:
    print("Attempting to auto find port")
    ports = list(serial.tools.list_ports.comports())
    found_port = ""
    for p in ports:
        if "usb serial" in str(p).lower() or "arduino" in str(p).lower() or "usb-serial" in str(p).lower():
            found_port = str(p).split('-')[0].strip()
            break
    if found_port:
        process_serial_input(found_port)
    else:
        for p in ports:
            print(p)
        sys.exit("Unable to determine port to use.")
        