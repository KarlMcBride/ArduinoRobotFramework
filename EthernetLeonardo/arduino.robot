*** Settings ***
Library  Collections
Library  Process
Library  arduino_ethernet.py


*** Keywords ***
Verify Response Dictionary
    [Documentation]  Logs the response dictionary, and fails if 'valid' is false
    [Arguments]  ${responseDicts}
    Log Dictionary  ${responseDicts}
    ${state} =  Get From Dictionary  ${responseDicts}  valid
    Should Be True  ${state}  Arduino response was not valid.

Send String Sequence
    [Arguments]  ${string_sequence}
    ${responseDict} =  String Sequence  ${string_sequence}
    Verify Response Dictionary  ${responseDict}

Start Install
    ${responseDict} =  String Sequence  INSTALL_ISO
    Verify Response Dictionary  ${responseDict}


*** Test Cases ***

Sleep 2
    Sleep  2

Send String Test Case
    Send String Sequence  Donkey Kong

Start ISO Install Sequence
    Start Install