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

Enable RGB Fade
    ${responseDict} =  RGB Fade
    Verify Response Dictionary  ${responseDict}

Enable RGB Static
    ${responseDict} =  RGB Static
    Verify Response Dictionary  ${responseDict}

Toggle LED Off
    ${responseDict} =  RGB Off
    Verify Response Dictionary  ${responseDict}

Set RGB Scalars
    [Arguments]  ${red}  ${green}  ${blue}
    ${responseDict} =  Configure Rgb Scalars  ${red}  ${green}  ${blue}
    Verify Response Dictionary  ${responseDict}
    Sleep  3


*** Test Cases ***

RGB Fade Test
    Enable RGB Fade
    Set RGB Scalars  255  0    0    # Red
    Set RGB Scalars  255  255  0    # Yellow
    Set RGB Scalars  0    255  0    # Green
    Set RGB Scalars  0    255  255  # Cyan
    Set RGB Scalars  0    0    255  # Blue
    Set RGB Scalars  255  0    255  # Pink
    Set RGB Scalars  255  255  255  # White

RGB Static Test
    Enable RGB Static
    Set RGB Scalars  255  0    0    # Red
    Set RGB Scalars  255  255  0    # Yellow
    Set RGB Scalars  0    255  0    # Green
    Set RGB Scalars  0    255  255  # Cyan
    Set RGB Scalars  0    0    255  # Blue
    Set RGB Scalars  255  0    255  # Pink
    Set RGB Scalars  255  255  255  # White