import serial
import time
from serial.tools import list_ports

movementDuration = 0.1

MOVEMENT_STOP = "1"
MOVEMENT_INSERT = "3"
MOVEMENT_REMOVE = "2"

def FindBoard():
    # Arduino VID + PID (from device manager -> details -> device instance path)
    arduino_port = list(list_ports.grep("2341:0043"))[0][0]
    return arduino_port

def AssertCardMotor(arduino, val):
    returnString = "empty"

    try:
        arduino.write(val.encode('ascii')+'\r\n')
        returnString = arduino.readline()
        time.sleep(movementDuration)
    except Exception as e:
        returnString = e

    return returnString

def ConnectToArduino():
    comm_port = FindBoard()
    ret = serial.Serial(comm_port, 9600, timeout=0.01)
    time.sleep(1)
    return ret

def CloseConnection(port):
    port.close()

# Briefly pulse in one direction, wait, then briefly pulse in opposite direction
def BriefImpulse(impulseDelay):
    arduino = ConnectToArduino()
    log = AssertCardMotor(arduino, MOVEMENT_STOP)
    log = log + AssertCardMotor(arduino, MOVEMENT_INSERT)
    log = log + AssertCardMotor(arduino, MOVEMENT_STOP)
    time.sleep(impulseDelay)
    log = log + AssertCardMotor(arduino, MOVEMENT_REMOVE)
    log = log + AssertCardMotor(arduino, MOVEMENT_STOP)
    arduino.close()
    return log

def InsertCard():
    arduino = ConnectToArduino()
    log = AssertCardMotor(arduino, MOVEMENT_STOP)
    log = log + AssertCardMotor(arduino, MOVEMENT_INSERT)
    log = log + AssertCardMotor(arduino, MOVEMENT_STOP)
    arduino.close()
    return log

def RemoveCard():
    arduino = ConnectToArduino()
    log = AssertCardMotor(arduino, MOVEMENT_STOP)
    log = log + AssertCardMotor(arduino, MOVEMENT_REMOVE)
    log = log + AssertCardMotor(arduino, MOVEMENT_STOP)
    arduino.close()
    return log
