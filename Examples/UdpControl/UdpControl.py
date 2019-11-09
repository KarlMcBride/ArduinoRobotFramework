# This file is meant to target an Arduino with Ethernet shield.
# With a serial monitor open, the messages should be displayed.
# Run with 'python UdpControl.py'

import socket

UDP_IP = "192.168.1.20"
UDP_PORT = 8888
MESSAGE = "Hello, World!"

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.sendto(bytes(MESSAGE, "utf-8"), (UDP_IP, UDP_PORT))
data = sock.recv(1024)
print("Received message:", data)
sock.close()