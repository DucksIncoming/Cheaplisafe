from pyfirmata import Arduino, util
import time

PORT =  "COM9"
ALARM = 2
RECIEVER = 11

def CentralUnit():
    try:
        board = Arduino(PORT)
    except:
        print("Arduino board not plugged in! (Or not accessible on specified port)")
        time.sleep(5000)
        quit()

    while True:
        print(board.analog[1].read())
        time.sleep(0.2)

    while True:
        recieverVoltage = board.digital[RECIEVER].read()

        print(recieverVoltage)
        time.sleep(1)
        board.digital[ALARM].write(1)
        time.sleep(1)
        board.digital[ALARM].write(0)
        #if (recieverVoltage > 0):
        #    board.digital[ALARM].write(1)
        #else:
        #    board.digital[ALARM].write(0)