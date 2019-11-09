# This file is meant to target an Arduino with Ethernet shield.
# With a serial monitor open, the messages should be displayed.

import select
import socket
import time

UDP_IP = "192.168.1.20"
UDP_PORT = 8888
MESSAGE_LED_ON  = "LED_ON"
MESSAGE_LED_OFF = "LED_OFF"

# Send message to Arduino and get response
def ConnectAndSendUdpMessage(_message):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM,) # UDP
    sock.sendto(bytes(_message, "utf-8"), (UDP_IP, UDP_PORT))
    receivedData = str(sock.recv(1024))
    sock.close()
    return receivedData

# Validates response by expecting expectedComponent inside response
def ValidateUdpResponse(_response, _expectedComponent):
    respStatus = False
    if _expectedComponent in _response:
        # Removing extra 1 due to encapsulation with '
        _response = _response[:-len(_expectedComponent)-1]
        respStatus = True
    return respStatus

# Sends message via UDP and returns response message and valid flag
def SendAndVerifyResponse(_message):
    responseMessage = ConnectAndSendUdpMessage(_message)
    responseValid   = ValidateUdpResponse(responseMessage, _message)
    responseDictionary = {"message":responseMessage, "valid":responseValid}
    return responseDictionary

def TurnLedOn():
    return SendAndVerifyResponse(MESSAGE_LED_ON)

def TurnLedOff():
    return SendAndVerifyResponse(MESSAGE_LED_OFF)


if __name__ == "__main__":
    print(TurnLedOn())
    time.sleep(5)
    print(TurnLedOff())