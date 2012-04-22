/*
 * This file is part of the Marmalade SDK Code Samples.
 *
 * Copyright (C) 2001-2011 Ideaworks3D Ltd.
 * All Rights Reserved.
 *
 * This source code is intended only as a supplement to Ideaworks Labs
 * Development Tools and/or on-line documentation.
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

/**
 * @page Examples3eFlurry S3E Flurry Example
 *
 * The following example demonstrates the use of the s3eFlurry API.
 *
 * The example allows:
 *    - Starting a (timed/non timed) flurry session
 *    - Logging an event
 *    - Logging an error
 *    - Logging a user's ID
 *    - Logging a user's age
 *    - Logging a user's gender
 *    - Logging a user's location
 *
 * The functions required to achieve this are:
 *
 *    - s3eFlurryStart()
 *    - s3eFlurryLogEvent()
 *    - s3eFlurryEndTimedEvent()
 *    - s3eFlurryLogError()
 *    - s3eFlurrySetUserID()
 *    - s3eFlurrySetUserAge()
 *    - s3eFlurrySetUserGender()
 *    - s3eFlurrySetLocation()
 *    - s3eFlurrySetSessionReportOnClose()
 *    - s3eFlurrySetSessionReportOnPause()
 *
 * All examples will follow this basic pattern; a brief description of what
 * the example does will be given followed by a list of all the important
 * functions and, perhaps, classes.
 *
 * The application waits for buttons to be pressed before using any
 * Flurry functionality.
 * Detection of button presses is handled using the generic code in ExamplesMain.cpp
 *
 * Messges are output to screen using PrintMessages().
 *
 * The following graphic illustrates the example output.
 *
 * @image html s3eFlurryImage.png
 *
 * @include s3eFlurry.cpp
 */

#include "ExamplesMain.h"
#include "s3eOSReadString.h"
#include "s3eFlurry.h"
//#include "s3eLocation.h" // for logging location

#include <stdlib.h> // for atoi()

/*
 * Device Location
 */
//static s3eLocation g_Location;
static s3eResult g_Error = S3E_RESULT_ERROR;

/*
 * Buttons
 */
// Flurry Analytics Buttons
static Button* g_ButtonLogEvent = NULL;
static Button* g_ButtonLogTimedEvent = NULL;
static Button* g_ButtonEndTimedEvent = NULL;
static Button* g_ButtonLogError = NULL;
static Button* g_ButtonUserInfo = NULL;
static Button* g_ButtonUserLocation = NULL;
static Button* g_ButtonToggleSendOnClose = NULL;
static Button* g_ButtonToggleSendOnPause = NULL;
// Flurry AppCircle Buttons
static Button* g_ButtonSetDefaultMessage = NULL;
static Button* g_ButtonToggleAdBanner = NULL;
static Button* g_ButtonShowOfferWall = NULL;


/*
 * Name Constants
 */
#define MAX_CHAR_SIZE 256
bool bSendSessionReportOnClose = true;
bool bSendSessionReportOnPause = true;
bool bShowBanner = false;

//Example Main
void ExampleInit()
{
    InitMessages(10,60);

    g_ButtonLogEvent = NewButton("Log Event");
    g_ButtonLogTimedEvent = NewButton("Log Timed Event");
    g_ButtonEndTimedEvent = NewButton("End Timed Event");
    g_ButtonLogError = NewButton("Log Error");
    g_ButtonUserInfo = NewButton("Set User Info");
    g_ButtonUserLocation = NewButton("Log User Location");
    g_ButtonToggleSendOnClose = NewButton("Disable send session report on close");
    g_ButtonToggleSendOnPause = NewButton("Disable send session report on pause");

    g_ButtonSetDefaultMessage = NewButton("Set Default Banner Message");
    g_ButtonToggleAdBanner = NewButton("Toggle Ad Banner");
    g_ButtonShowOfferWall = NewButton("Display Offer Wall");

    g_ButtonLogEvent->m_Enabled = false;
    g_ButtonLogTimedEvent->m_Enabled = false;
    g_ButtonEndTimedEvent->m_Enabled = false;
    g_ButtonLogError->m_Enabled = false;
    g_ButtonUserInfo->m_Enabled = false;
    g_ButtonUserLocation->m_Enabled = false;
    g_ButtonToggleSendOnClose->m_Enabled = false;
    g_ButtonToggleSendOnPause->m_Enabled = false;

    g_ButtonSetDefaultMessage->m_Enabled = false;
    g_ButtonToggleAdBanner->m_Enabled = false;
    g_ButtonShowOfferWall->m_Enabled = false;

    if (!s3eFlurryAvailable())
    {
        AppendMessageColour(RED,"Extension Not Available");
        return;
    }

    // Enable AppCircle
    // We need to call this *before* calling s3eFlurryStart
    s3eFlurryAppCircleEnable();

    //iOS Applicaton Key
    if(s3eDeviceGetInt (S3E_DEVICE_OS) == S3E_OS_ID_IPHONE)
        s3eFlurryStart("DNWX7I7XZYYL9V1QAZFC");
    //Android Applicaton Key
    else if(s3eDeviceGetInt (S3E_DEVICE_OS) == S3E_OS_ID_ANDROID)
        s3eFlurryStart("HD4EZJ147ELQAT9H43KM");


    g_ButtonLogEvent->m_Enabled = true;
    g_ButtonLogTimedEvent->m_Enabled = true;
    g_ButtonEndTimedEvent->m_Enabled = true;
    g_ButtonLogError->m_Enabled = true;
    g_ButtonUserInfo->m_Enabled = true;
    g_ButtonUserLocation->m_Enabled = true;
    g_ButtonToggleSendOnClose->m_Enabled = true;
    g_ButtonToggleSendOnPause->m_Enabled = true;

    g_ButtonSetDefaultMessage->m_Enabled = true;
    g_ButtonToggleAdBanner->m_Enabled = true;
    g_ButtonShowOfferWall->m_Enabled = true;

    s3eLocationStart();
}

void ExampleTerm()
{
    s3eLocationStop();
}

#include "IwDebug.h"
bool ExampleUpdate()
{
    Button* pressed = GetSelectedButton();
    if (!pressed)
    {
        return true;
    }

    if (pressed == g_ButtonLogEvent)
    {
        char EventName[MAX_CHAR_SIZE];

        // Event Name: Key used to recognise event
        strcpy(EventName, s3eOSReadStringUTF8("Enter Event Name:", 0));
        s3eFlurryLogEvent(EventName, false);

        AppendMessageColour(GREEN, "Non Timed Event Logged");
    }
    else if (pressed == g_ButtonLogTimedEvent)
    {
        char EventName[MAX_CHAR_SIZE];

        // Event Name: Key used to recognise event
        strcpy(EventName, s3eOSReadStringUTF8("Enter Event Name:", 0));
        s3eFlurryLogEvent(EventName, true);

        AppendMessageColour(GREEN, "Timed Event Logged");
    }
    else if (pressed == g_ButtonEndTimedEvent)
    {
        char EventName[MAX_CHAR_SIZE];

        // Event Name: Key used to recognise event
        strcpy(EventName, s3eOSReadStringUTF8("Enter Event Name:", 0));
        s3eFlurryEndTimedEvent(EventName);
    }
    else if (pressed == g_ButtonLogError)
    {
        char Error[MAX_CHAR_SIZE];
        char Message[MAX_CHAR_SIZE];

        // Error ID: ID you can use to recognise this error
        strcpy(Error, s3eOSReadStringUTF8("Enter Error ID:", 0));
        // Error Message: Message describing the error
        strcpy(Message, s3eOSReadStringUTF8("Error Message:", 0));
        s3eFlurryLogError(Error, Message);
    }
    else if (pressed == g_ButtonUserInfo)
    {
        char userID[MAX_CHAR_SIZE];
        // User ID: Set an ID that can be used to recognise this user
        strcpy(userID, s3eOSReadStringUTF8("Enter User ID:", 0));
        s3eFlurrySetUserID(userID);

        char userAge[MAX_CHAR_SIZE];
        // User Age: Set the user's age
        strcpy(userAge, s3eOSReadStringUTF8("Enter User Age:", S3E_OSREADSTRING_FLAG_NUMBER));
        uint8 age = atoi(userAge);
        s3eFlurrySetUserAge(age);

        char userGender[MAX_CHAR_SIZE];
        // User Gender: Set the user's gender
        strcpy(userGender, s3eOSReadStringUTF8("Enter User Gender\n\"M\" or \"F\"", 0));
        if(!strcmp(userGender,"m") || !strcmp(userGender,"M"))
        {
            s3eFlurrySetUserGender(S3E_FLURRY_MALE);
            AppendMessageColour(GREEN, "Logged User Gender: Male");
        }
        else if(!strcmp(userGender,"f") || !strcmp(userGender,"F"))
        {
            s3eFlurrySetUserGender(S3E_FLURRY_FEMALE);
            AppendMessageColour(GREEN, "Logged User Gender: Female");
        }
        else
            AppendMessageColour(RED, "Gender given not valid");

        AppendMessageColour(GREEN, "Logged User age: %i", age);
        AppendMessageColour(GREEN, "Logged User ID: %s", userID);
    }
    else if (pressed == g_ButtonUserLocation)
    {
        //g_Error = s3eLocationGet(&g_Location);
        if(g_Error == S3E_RESULT_ERROR)
            AppendMessageColour(RED, "Could not determine location");
        else
        {
        //    s3eFlurrySetLocation(&g_Location);
            AppendMessageColour(GREEN, "Logged user location");
        }
    }
    else if (pressed == g_ButtonToggleSendOnClose)
    {
        bSendSessionReportOnClose = !bSendSessionReportOnClose;
        s3eFlurrySetSessionReportOnClose(bSendSessionReportOnClose);
        if(bSendSessionReportOnClose)
        {
            AppendMessageColour(GREEN, "Session report send on close: Enabled");
            g_ButtonToggleSendOnClose->m_Name = (char*)"Disable send session report on close";
        }
        else
        {
            AppendMessageColour(GREEN, "Session report send on close: Disabled");
            g_ButtonToggleSendOnClose->m_Name = (char*)"Enable send session report on close";
        }
    }
    else if (pressed == g_ButtonToggleSendOnPause)
    {
        bSendSessionReportOnPause = !bSendSessionReportOnPause;
        s3eFlurrySetSessionReportOnPause(bSendSessionReportOnPause);
        if(bSendSessionReportOnPause)
        {
            AppendMessageColour(GREEN, "Session report send on pause: Enabled");
            g_ButtonToggleSendOnPause->m_Name = (char*)"Disable send session report on pause";
        }
        else
        {
            AppendMessageColour(GREEN, "Session report send on pause: Disabled");
            g_ButtonToggleSendOnPause->m_Name = (char*)"Enable send session report on pause";
        }
    }

    else if (pressed == g_ButtonSetDefaultMessage)
    {
        char message[MAX_CHAR_SIZE];

        // User Gender: Set the user's gender
        strcpy(message, s3eOSReadStringUTF8("Enter a default message to be shown in the event no banner is available",0));
        s3eFlurrySetDefaultText(message);
    }
    else if (pressed == g_ButtonToggleAdBanner)
    {
        bShowBanner = !bShowBanner;
        s3eFlurryShowAdBanner(bShowBanner);

        if(bShowBanner)
            AppendMessageColour(GREEN, "Ad Banner: Enabled");
        else
            AppendMessageColour(GREEN, "Ad Banner: Disabled");

    }
    else if (pressed == g_ButtonShowOfferWall)
    {
        s3eFlurryShowOfferWall();
    }
    return true;
}

void ExampleRender()
{
    int x = 20;
    int y = GetYBelowButtons();

    y += 14;

    PrintMessages(x, y);
}
