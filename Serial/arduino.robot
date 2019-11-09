*** Settings ***
#Library  Collections
#Library  OperatingSystem
Library  Process
Library  arduino_serial.py

*** Test Cases ***
Impulse Loop
    : FOR  ${delay}  IN RANGE  0.2  1.0  0.2
    \    Log  ${delay}
    \    ${log} =  BriefImpulse  ${delay}
    \    Log  ${log}
    \    Sleep  1

Insert, Wait & Remove
    ${log} =  InsertCard
    Log  ${log}
    Sleep  2
    ${log} =  RemoveCard
    Log  ${log}