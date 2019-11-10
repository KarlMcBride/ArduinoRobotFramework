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

Set Colour - White
    ${responseDict} =  Enable Red
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Enable Green
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Enable Blue
    Verify Response Dictionary  ${responseDict}

Set Colour - Red
    ${responseDict} =  Enable Red
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Disable Green
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Disable Blue
    Verify Response Dictionary  ${responseDict}

Set Colour - Yellow
    ${responseDict} =  Enable Red
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Enable Green
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Disable Blue
    Verify Response Dictionary  ${responseDict}

Set Colour - Green
    ${responseDict} =  Disable Red
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Enable Green
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Disable Blue
    Verify Response Dictionary  ${responseDict}

Set Colour - Blue
    ${responseDict} =  Disable Red
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Disable Green
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Enable Blue
    Verify Response Dictionary  ${responseDict}

Set Colour - Pink
    ${responseDict} =  Enable Red
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Disable Green
    Verify Response Dictionary  ${responseDict}
    ${responseDict} =  Enable Blue
    Verify Response Dictionary  ${responseDict}

Toggle RGB Fade On
    ${responseDict} =  Enable RGB Fade
    Verify Response Dictionary  ${responseDict}

Toggle LED Off
    ${responseDict} =  Turn RGB Off
    Verify Response Dictionary  ${responseDict}


*** Test Cases ***
Led Toggle
    Toggle RGB Fade On
    Set Colour - White
    Sleep  2.55
    Set Colour - Red
    Sleep  2.55
    Set Colour - Yellow
    Sleep  2.55
    Set Colour - Green
    Sleep  2.55
    Set Colour - Blue
    Sleep  2.55
    Set Colour - Pink
    Sleep  2.55
    Toggle LED Off