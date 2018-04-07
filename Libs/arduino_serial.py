import serial
import time

def AssertMotor(val):
	returnString = "empty"

	try:
		arduino = serial.Serial("COM4",9600)
		time.sleep(2)
		returnString = "Connection to COM4 established succesfully!\n"
	except Exception as e:
		returnString = e

	#Note: for characters such as 'a' I set data = b'a' to convert the data in bytes
	#However the same thing does not work with numbers...
	data = 0
	data = arduino.write(val.encode('ascii')+'\r\n')
	time.sleep(2)
	returnString = arduino.readline()
	arduino.close()

	return returnString