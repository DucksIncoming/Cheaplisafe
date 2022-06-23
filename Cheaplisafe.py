from Components.CentralUnit import *
from Components.EntrySensor import *
from Components.GlassBreak import *
from Components.Keypad import *
from Components.MotionSensor import *
from Components.PanicButton import *
from Components.WirelessCam import *

# MODE: Sets which component's code to use
# Options:
#   0. CentralUnit
#   1. EntrySensor
#   2. MotionSensor
#   3. WirelessCam
#   4. GlassBreakSensor
#   5. PanicButton
#   6. Keypad

MODE = 0

NameSwitch = {
    0: "Central Unit",
    1: "Entry Sensor",
    2: "Motion Sensor",
    3: "Wireless Camera",
    4: "Glass Break",
    5: "Panic Button",
    6: "Keypad"
}

print(" *=== Starting Cheaplisafe on mode: " + str(NameSwitch.get(MODE, "[N/A]")) + " ===* ")

# I'll make this less disgusting later
if (MODE == 0):
    CentralUnit()
elif (MODE == 1):
    EntrySensor()
elif (MODE == 2):
    MotionSensor()
elif (MODE == 3):
    WirelessCam()
elif (MODE == 4):
    GlassBreak()
elif (MODE == 5):
    PanicButton()
elif (MODE == 6):
    Keypad()