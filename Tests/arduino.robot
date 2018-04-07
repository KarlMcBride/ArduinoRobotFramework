*** Settings ***
#Library  Collections
#Library  OperatingSystem
Library  Process
Library  ../Libs/arduino_serial.py

*** Test Cases ***
Run Arduino Function
	${response} =  MotorStop
	Log to console  ${response}
	${response} =  MotorForward
	Log to console  ${response}
	${response} =  MotorStop
	Log to console  ${response}
	${response} =  MotorReverse
	Log to console  ${response}
	${response} =  MotorStop
	Log to console  ${response}