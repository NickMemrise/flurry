/*
Generic implementation of the s3eFlurry extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eFlurry_internal.h"
s3eResult s3eFlurryInit()
{
    //Add any generic initialisation code here
    return s3eFlurryInit_platform();
}

void s3eFlurryTerminate()
{
    //Add any generic termination code here
    s3eFlurryTerminate_platform();
}

void s3eFlurryStart(const char* ID)
{
	s3eFlurryStart_platform(ID);
}

void s3eFlurryLogEvent(const char* eventName, const s3eBool timed)
{
	s3eFlurryLogEvent_platform(eventName, timed);
}

void s3eFlurryLogEventWithParameters(const char* eventName, const char** eventParams, const uint32 numParams, const s3eBool timed)
{
	s3eFlurryLogEventWithParameters_platform(eventName, eventParams, numParams, timed);
}

void s3eFlurryEndTimedEvent(const char* eventName)
{
	s3eFlurryEndTimedEvent_platform(eventName);
}

void s3eFlurryLogError(const char* errorName, const char* errorMessage)
{
	s3eFlurryLogError_platform(errorName, errorMessage);
}

void s3eFlurrySetUserID(const char* userID)
{
	s3eFlurrySetUserID_platform(userID);
}

void s3eFlurrySetUserAge(const uint8 age)
{
	s3eFlurrySetUserAge_platform(age);
}

void s3eFlurrySetUserGender(const s3eFlurryUserGender gender)
{
	s3eFlurrySetUserGender_platform(gender);
}

void s3eFlurrySetLocation(s3eLocation* location)
{
	s3eFlurrySetLocation_platform(location);
}

void s3eFlurrySetSessionReportOnClose(const s3eBool sendReportOnClose)
{
	s3eFlurrySetSessionReportOnClose_platform(sendReportOnClose);
}

void s3eFlurrySetSessionReportOnPause(const s3eBool sendReportOnPause)
{
	s3eFlurrySetSessionReportOnPause_platform(sendReportOnPause);
}

void s3eFlurryAppCircleEnable()
{
	s3eFlurryAppCircleEnable_platform();
}

void s3eFlurrySetDefaultText(const char* text)
{
	s3eFlurrySetDefaultText_platform(text);
}

void s3eFlurryShowAdBanner(const s3eBool show)
{
	s3eFlurryShowAdBanner_platform(show);
}

void s3eFlurryShowOfferWall()
{
	s3eFlurryShowOfferWall_platform();
}
