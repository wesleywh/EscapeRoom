#!/usr/bin/python
import os
from flask import Flask, request, jsonify
from flask_cors import CORS

cur_dir = os.path.dirname(os.path.realpath(__file__))

app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'
CORS(app)

@app.route('/AddRFID', methods=['POST'])
def add_rfid():
  rfid = request.form.get('RFID')
  print("Request recieved for: "+rfid)
  if rfid and not id_exists_in_file(rfid):
    with open(cur_dir+"/data/ids.txt", "a") as rfid_file:
      rfid_file.write(rfid+"\n")
  else:
    print("Already in file, skipping.")
  return "SUCCESS"

@app.route('/SetStartTime', methods=['POST'])
def set_start_time():
  start_time = request.get_json()["STARTTIME"]
  with open(cur_dir+"/data/start_time.txt", "w") as rfid_file:
    rfid_file.write(str(start_time))
  return jsonify(success=True)
  
@app.route('/GetStartTime', methods=['GET'])
def get_start_time():
  lines = []
  with open(cur_dir+"/data/start_time.txt", "r") as time_file:
    lines = time_file.readlines()
  if len(lines) > 0:
    return lines[0]
  else:
    return "FALSE"

@app.route('/GetIds', methods=['GET'])
def get_ids():
  lines = []
  with open(cur_dir+"/data/ids.txt", "r") as id_file:
    lines = id_file.readlines()
  data = [line.strip() for line in lines if line.strip()]
  return jsonify(data)

@app.route('/GetCurrentClue', methods=['GET'])
def get_current_clue():
  
  lines = []
  with open(cur_dir+"/data/clue_number.txt", "r") as clue_number_file:
    lines = clue_number_file.readlines()
  clue_number = lines[0].strip()
  
  lines = []
  with open(cur_dir+"/data/clues.txt", "r") as clue_file:
    lines = clue_file.readlines()
  clue = ""
  for line in lines:
    if line.startswith(clue_number):
      clue = line.split(clue_number+".")[1].strip()

  return {clue_number: clue}

def id_exists_in_file(rfid):
  lines = []
  with open(cur_dir+"/data/ids.txt", "r") as rfid_file:
    lines = rfid_file.readlines()
  return rfid in lines
    
if __name__ == '__main__':
    app.run(host='0.0.0.0')
