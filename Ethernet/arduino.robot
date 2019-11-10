*** Settings ***
Library  Collections
Library  Process
Library  arduino_ethernet.py

Suite Teardown  Rgb Off


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
    [Setup]  Enable RGB Fade
    [Template]  Set RGB Scalars
        100  0    0    # Red
        100  10   0    # Orange
        50   25   0    # Yellow
        0    60   0    # Green
        0    25   25   # Cyan
        0    0    50   # Blue
        50   0    50   # Pink
        25  0     50   # Purple
        25   25   25   # White

RGB Static Test
    [Setup]  Enable RGB Static
    [Template]  Set RGB Scalars
        100  0    0    # Red
        100  10   0    # Orange
        50   25   0    # Yellow
        0    60   0    # Green
        0    25   25   # Cyan
        0    0    50   # Blue
        50   0    50   # Pink
        25  0     50   # Purple
        25   25   25   # White