# Used to detect when a door is opened
# https://simplisafe.com/build-my-system#:~:text=your%20Burglary%20Sensors-,Entry%20Sensor,-show%20more%20info

import serial
import time

# Arduino Variables
PORT = "COM9"

def parseInt(sin):
  import re
  m = re.search(r'^(\d+)[.,]?\d*?', str(sin))
  return int(m.groups()[-1]) if m and not callable(sin) else None

def EntrySensor():
    distance = 0
    
    try:
        serialIn = serial.Serial(port=PORT, baudrate=9600, timeout=0.1)
    except:
        print("Arduino board not plugged in! (Or not accessible on specified port)")
        time.sleep(5)
        quit()
        

    print("Preparing...")
    time.sleep(5)
    print("Done!")


    while True:
        if (serialIn.in_waiting):
            serialRead = serialIn.readline()
            serialRead = parseInt(serialRead.decode('utf'))
            if (type(serialRead) == int):
                distance = serialRead
            print(distance)