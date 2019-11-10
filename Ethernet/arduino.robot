*** Settings ***
Library  Collections
#Library  OperatingSystem
Library  Process
Library  arduino_ethernet.py


*** Keywords ***
Verify Response Dictionary
    [Documentation]  Logs the response dictionary, and fails if 'valid' is false
    [Arguments]  ${responseDicts}
    Log Dictionary  ${responseDicts}
    ${state} =  Get From Dictionary  ${responseDicts}  valid
    Should Be True  ${state}  Arduino response was not valid.


Toggle LED On
    ${responseDict} =  Turn LED On
    Verify Response Dictionary  ${responseDict}

Toggle LED Off
    ${responseDict} =  Turn LED Off
    Verify Response Dictionary  ${responseDict}


*** Test Cases ***
Led Toggle
    Toggle LED On
    Sleep  2.55
    Toggle LED Off
    Sleep  1