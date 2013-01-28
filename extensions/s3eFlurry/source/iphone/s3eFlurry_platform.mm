/*
 * iphone-specific implementation of the s3eFlurry extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eFlurry_internal.h"
#include "s3eEdk.h"
#include "s3eEdk_iphone.h"
#include <stdio.h>

#import "FlurryAnalytics.h"
#import "FlurryAdDelegate.h"
#import "FlurryAppCircle.h"
#import "FlurryOffer.h"

#include "IwDebug.h"

s3eResult s3eFlurryInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eFlurryTerminate_platform()
{
    // Add any platform-specific termination code here
}


// -- Flurry Analytics --
//=================================================================================================

void s3eFlurryStart_platform(const char* ID)
{
    NSString* appID = [NSString stringWithUTF8String: ID];
    [FlurryAnalytics startSession:appID];

    IwTrace(FLURRY,("Session Started"));
}

void s3eFlurryLogEvent_platform(const char* eventName, const s3eBool timed)
{
    NSString* name = [NSString stringWithUTF8String: eventName];

    if(!timed)
    {
        [FlurryAnalytics logEvent:name];
        IwTrace(FLURRY,("Event Logged: \"%s\"", eventName));
    }
    else
    {
        [FlurryAnalytics logEvent:name timed:timed];
        IwTrace(FLURRY,("Timed Event Logged: \"%s\"", eventName));
    }
}

void s3eFlurryLogEventWithParameters_platform(const char* eventName, const char** eventParams, const uint32 numParams, const s3eBool timed)
{
}

void s3eFlurryEndTimedEvent_platform(const char* eventName)
{
    NSString* name = [NSString stringWithUTF8String: eventName];
    [FlurryAnalytics endTimedEvent:name withParameters: nil];

    IwTrace(FLURRY,("End Timed Event: \"%s\"", eventName));
}

void s3eFlurryLogError_platform(const char* errorName, const char* errorMessage)
{
    NSString* id = [NSString stringWithUTF8String: errorName];
    NSString* message = [NSString stringWithUTF8String: errorMessage];

    NSException *e = NULL;
    [FlurryAnalytics logError:id message:message exception:e];

    IwTrace(FLURRY,("Error Logged:\n  ID: \"%s\"\n  Message: \"%s\"", errorName, errorMessage));
}

void s3eFlurrySetUserID_platform(const char* userID)
{
    NSString* id = [NSString stringWithUTF8String: userID];
    [FlurryAnalytics setUserID:id];

    IwTrace(FLURRY,("User ID Logged: \"%s\"", userID));
}

void s3eFlurrySetUserAge_platform(const uint8 age)
{
    [FlurryAnalytics setAge:age];

    IwTrace(FLURRY,("User age Logged: \"%d\"", age));
}

void s3eFlurrySetUserGender_platform(const s3eFlurryUserGender gender)
{
    if(gender == S3E_FLURRY_MALE)
    {
        [FlurryAnalytics setGender:@"m"];
        IwTrace(FLURRY,("User gender Logged: \"Male\""));
    }
    else
    {
        [FlurryAnalytics setGender:@"f"];
        IwTrace(FLURRY,("User gender Logged: \"Female\""));
    }
}

void s3eFlurrySetLocation_platform(s3eLocation* location)
{
    [FlurryAnalytics setLatitude:location->m_Latitude
                 longitude:location->m_Longitude
        horizontalAccuracy:location->m_HorizontalAccuracy
          verticalAccuracy:location->m_VerticalAccuracy];

    IwTrace(FLURRY,("User location Logged:\n Latitude: %f\n,  Longitude %f\n  HorizontalAccuracy: %f\n  VerticalAccuracy: %f\n",
                    (float)location->m_Latitude,
                    (float)location->m_Longitude,
                    (float)location->m_HorizontalAccuracy,
                    (float)location->m_VerticalAccuracy));
}

void s3eFlurrySetSessionReportOnClose_platform(const s3eBool sendReportOnClose)
{
    [FlurryAnalytics setSessionReportsOnCloseEnabled:(BOOL)sendReportOnClose];

    if(sendReportOnClose)
        IwTrace(FLURRY,("Send report on close: ENABLED"));
    else
        IwTrace(FLURRY,("Send report on close: DISABLED"));
}

void s3eFlurrySetSessionReportOnPause_platform(const s3eBool sendReportOnPause)
{
    [FlurryAnalytics setSessionReportsOnPauseEnabled:(BOOL)sendReportOnPause];

    if(sendReportOnPause)
        IwTrace(FLURRY,("Send report on pause: ENABLED"));
    else
        IwTrace(FLURRY,("Send report on pause: DISABLED"));
}


// -- Flurry App Circle --  // Implemented for Marmamalde 5.2 and above _platform(May Change)
//=================================================================================================
UIView *banner;

void s3eFlurryAppCircleEnable_platform()
{
    [FlurryAppCircle setAppCircleEnabled:YES];
    IwTrace(FLURRY,("App Circle Enabled"));
}

void s3eFlurrySetDefaultText_platform(const char* text)
{
	// ToDo: Allow user to change default banner text
}

void s3eFlurryShowAdBanner_platform(const s3eBool show)
{
    // ToDo: Add Banner to display flurry ad
}

void s3eFlurryShowOfferWall_platform()
{
	// ToDo: Show offer wall
}