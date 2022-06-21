import Components.Alarm as al
import Components.CentralUnit as cu
import Components.EntrySensor as es
import Components.GlassBreak as gb
import Components.Keypad as kp
import Components.MotionSensor as ms
import Components.PanicButton as pb
import Components.WirelessCam as wc

# MODE: Sets which component's code to use
# Options:
#   0. CentralUnit
#   1. EntrySensor
#   2. MotionSensor
#   3. WirelessCam
#   4. GlassBreakSensor
#   5. PanicButton
#   6. Keypad
#   7. Alarm

MODE = 1

ModeSwitch = {
    0: cu.CentralUnit(),
    1: es.EntrySensor(),
    2: ms.MotionSensor(),
    3: wc.WirelessCam(),
    4: gb.GlassBreak(),
    5: pb.PanicButton(),
    6: kp.Keypad(),
    7: al.Alarm(),
}