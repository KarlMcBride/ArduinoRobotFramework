# This file is meant to target an Arduino with Ethernet shield.
# With a serial monitor open, the messages should be displayed.

import select
import socket
import time

UDP_IP = "192.168.1.20"
UDP_PORT = 8888
MESSAGE_RGB_FADE  = "RGB_FADE"
MESSAGE_RED_ON    = "RED_ON"
MESSAGE_RED_OFF   = "RED_OFF"
MESSAGE_GREEN_ON  = "GREEN_ON"
MESSAGE_GREEN_OFF = "GREEN_OFF"
MESSAGE_BLUE_ON   = "BLUE_ON"
MESSAGE_BLUE_OFF  = "BLUE_OFF"
MESSAGE_RGB_OFF   = "RGB_OFF"


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


def EnableRgbFade():
    return SendAndVerifyResponse(MESSAGE_RGB_FADE)

def TurnRgbOff():
    return SendAndVerifyResponse(MESSAGE_RGB_OFF)

def DisableRed():
    return SendAndVerifyResponse(MESSAGE_RED_OFF)

def EnableRed():
    return SendAndVerifyResponse(MESSAGE_RED_ON)

def DisableGreen():
    return SendAndVerifyResponse(MESSAGE_GREEN_OFF)

def EnableGreen():
    return SendAndVerifyResponse(MESSAGE_GREEN_ON)

def DisableBlue():
    return SendAndVerifyResponse(MESSAGE_BLUE_OFF)

def EnableBlue():
    return SendAndVerifyResponse(MESSAGE_BLUE_ON)


if __name__ == "__main__":
    print(EnableRgbFade())
    time.sleep(5)
    print(TurnRgbOff())