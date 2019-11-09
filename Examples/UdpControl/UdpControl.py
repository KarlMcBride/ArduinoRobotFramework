# This file is meant to target an Arduino with Ethernet shield.
# With a serial monitor open, the messages should be displayed.
# Run with 'python UdpControl.py'

import select
import socket
import time

UDP_IP = "192.168.1.20"
UDP_PORT = 8888
MESSAGE_LED_ON  = "LED_ON"
MESSAGE_LED_OFF = "LED_OFF"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM,) # UDP
sock.sendto(bytes(MESSAGE_LED_ON, "utf-8"), (UDP_IP, UDP_PORT))
data = sock.recv(1024)
print("Received message:", data)

time.sleep(5)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM,) # UDP
sock.sendto(bytes(MESSAGE_LED_OFF, "utf-8"), (UDP_IP, UDP_PORT))
data = sock.recv(1024)
print("Received message:", data)

sock.close()