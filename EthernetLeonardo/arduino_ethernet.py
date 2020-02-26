# This file is meant to target an Arduino with Ethernet shield.
# With a serial monitor open, the messages should be displayed.

import select
import socket
import time

UDP_IP = "172.16.230.118"
UDP_PORT = 8888


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

def StringSequence(_string_sequence):
    request = "SEQ," + _string_sequence
    return SendAndVerifyResponse(request)


if __name__ == "__main__":
    print(StringSequence("Main says hello"))