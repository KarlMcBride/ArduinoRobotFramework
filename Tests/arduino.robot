*** Settings ***
#Library  Collections
#Library  OperatingSystem
Library  Process
Library  ../Libs/arduino_serial.py

*** Test Cases ***
Run Arduino Function
	${response} =  AssertMotor  1
	Log to console  ${response}
	${response} =  AssertMotor  2
	Log to console  ${response}
	${response} =  AssertMotor  1
	Log to console  ${response}
	${response} =  AssertMotor  3
	Log to console  ${response}
	${response} =  AssertMotor  1
	Log to console  ${response}