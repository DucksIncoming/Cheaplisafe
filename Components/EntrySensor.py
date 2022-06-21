# Used to detect when a door is opened
# https://simplisafe.com/build-my-system#:~:text=your%20Burglary%20Sensors-,Entry%20Sensor,-show%20more%20info

from pyfirmata import Arduino
import pyfirmata
import time

# Arduino Pin Variables
PORT = "COM9"

# === Digital ===
LED = 8
ULTRASONIC_WRITE = 6
TRANSMIT = 2
# === Analog ===
ULTRASONIC_READ = 2

def EntrySensor():
    global LED
    global ULTRASONIC_WRITE
    global TRANSMIT
    global ULTRASONIC_READ
    
    try:
        board = Arduino(PORT)
    except:
        print("Arduino board not plugged in! (Or not accessible on specified port)")
        time.sleep(5)
        quit()

    iterator = pyfirmata.util.Iterator(board)
    iterator.start()
    print("EntrySensor: Ready")
    board.get_pin('a:' + str(ULTRASONIC_READ) + ':i').enable_reporting()

    while True:
        board.pass_time(0.5)
        print(board.analog[ULTRASONIC_READ].read())