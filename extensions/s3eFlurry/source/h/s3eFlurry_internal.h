/*
 * Internal header for the s3eFlurry extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EFLURRY_INTERNAL_H
#define S3EFLURRY_INTERNAL_H

#include "s3eTypes.h"
#include "s3eFlurry.h"
#include "s3eFlurry_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eFlurryInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eFlurryInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eFlurryTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eFlurryTerminate_platform();
void s3eFlurryStart_platform(const char* ID);

void s3eFlurryLogEvent_platform(const char* eventName, const s3eBool timed);

void s3eFlurryLogEventWithParameters_platform(const char* eventName, const char** eventParams, const uint32 numParams, const s3eBool timed);

void s3eFlurryEndTimedEvent_platform(const char* eventName);

void s3eFlurryLogError_platform(const char* errorName, const char* errorMessage);

void s3eFlurrySetUserID_platform(const char* userID);

void s3eFlurrySetUserAge_platform(const uint8 age);

void s3eFlurrySetUserGender_platform(const s3eFlurryUserGender gender);

void s3eFlurrySetLocation_platform(s3eLocation* location);

void s3eFlurrySetSessionReportOnClose_platform(const s3eBool sendReportOnClose);

void s3eFlurrySetSessionReportOnPause_platform(const s3eBool sendReportOnPause);

void s3eFlurryAppCircleEnable_platform();

void s3eFlurrySetDefaultText_platform(const char* text);

void s3eFlurryShowAdBanner_platform(const s3eBool show);

void s3eFlurryShowOfferWall_platform();


#endif /* !S3EFLURRY_INTERNAL_H */
