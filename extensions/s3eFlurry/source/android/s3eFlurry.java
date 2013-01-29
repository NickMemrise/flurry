/*
java implementation of the s3eFlurry extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

import android.view.View;
import android.view.ViewGroup;

import com.flurry.android.*;

import android.util.Log;

//import android.content.Context;
import android.R;
import android.widget.Button;
import android.widget.TextView;
import android.graphics.Typeface;
import android.view.Gravity;
import android.widget.LinearLayout;
import android.widget.FrameLayout;

import java.util.HashMap;

class s3eFlurry
{
    AppCircle appCircle;
    View m_PromoView;
    boolean m_isBannerDisplayed = false;
    String message = "Flurry for Marmalade SDK";

	private boolean CheckAppCircle()
	{
		appCircle = FlurryAgent.getAppCircle();
        return(appCircle != null);
	}
	
    // Flurry Analaytics
    public void s3eFlurryStart(String ID)
    {
        FlurryAgent.onStartSession(LoaderAPI.getActivity(), ID);
        Log.d("s3eFlurry", "////// App Circle Session Started //////");
    }
    public void s3eFlurryLogEvent(String eventName, boolean timed)
    {
        if(timed)
            FlurryAgent.logEvent(eventName);
        else
            FlurryAgent.logEvent(eventName, timed);
    }
	public void s3eFlurryLogEventWithParameters(String eventName, String[] eventParams, boolean timed)
	{
		HashMap<String, String> params = new HashMap<String, String>();
		
		int numParams = eventParams.length / 2;
		
		for(int i=0; i<numParams; i++)
		{
			int index = i * 2;
			params.put(eventParams[index], eventParams[index+1]);
		}
		
        if(timed)
            FlurryAgent.logEvent(eventName, params);
        else
            FlurryAgent.logEvent(eventName, params, timed);
	}
    public void s3eFlurryEndTimedEvent(String eventName)
    {
        FlurryAgent.endTimedEvent(eventName);
    }
    public void s3eFlurryLogError(String errorName, String errorMessage)
    {
        FlurryAgent.onError(errorName, errorMessage, "");
    }
    public void s3eFlurrySetUserID(String userID)
    {
        FlurryAgent.setUserId(userID);
    }
    public void s3eFlurrySetUserAge(int age)
    {
        FlurryAgent.setAge(age);
    }
    public void s3eFlurrySetUserGender(boolean isMale)
    {
        if(isMale)
            FlurryAgent.setGender(Constants.MALE);
        else
            FlurryAgent.setGender(Constants.FEMALE);
    }
    public void s3eFlurrySetLocation()
    {
    }
    public void s3eFlurrySetSessionReportOnClose()
    {
    }
    public void s3eFlurrySetSessionReportOnPause()
    {
    }

    // Flurry App Circle
    public void s3eFlurryAppCircleEnable()
    {
		FlurryAgent.setCatalogIntentName("s3e.offer.intent");
        FlurryAgent.enableAppCircle();
        Log.d("s3eFlurry", "////// App Circle Enabled //////");
    }
    public void s3eFlurrySetDefaultText(String text)
    {
        Log.d("S3EFLURRY", "Setting text");
        message = text;
        Log.d("s3eFlurry", "////// Default Banner Text Changed: " + message + " //////");
    }
    public void s3eFlurryShowAdBanner(boolean showBanner)
    {
        if(true == showBanner) // Show Banner
        {
			if(CheckAppCircle())
            {
                appCircle.setDefaultNoAdsMessage(message);

                final ViewGroup viewGroup = LoaderActivity.m_Activity.m_FrameLayout;
                m_PromoView = appCircle.getHook(LoaderActivity.m_Activity, "s3eAPPCIRCLE_BANNER_HOOK", com.flurry.android.Constants.MODE_LANDSCAPE);

                if (viewGroup == null)
                {
                    Log.d("View Error", "View group not found");
                    return;
                }

                if (m_PromoView == null)
                {
                    Log.d("Flurry Banner Error", "Banner View Failed");
                    return;
                }

                // Define the layout parameters of the view
                final LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(
                                                        LinearLayout.LayoutParams.FILL_PARENT,//LinearLayout.LayoutParams.WRAP_CONTENT,
                                                        80);//LinearLayout.LayoutParams.FILL_PARENT);

                LoaderAPI.getActivity().LoaderThread().runOnOSThread(new Runnable()
                {
                    public void run()
                    {
                        if(m_PromoView != null && !m_isBannerDisplayed)
                        {
                            // Must add our group to index level 1 or it will not be shown
                            viewGroup.addView(m_PromoView, 1, lp);
                            Log.d("s3eFlurry", "Banner Displayed");
                            m_isBannerDisplayed = true; // We should ensure we only add the view once
                        }
                    }
                });
            }
            else
                Log.d("S3EFLURRY", "App Circle is not enabled");
        }
        else // Hide Banner
        {
            final ViewGroup viewGroup = LoaderActivity.m_Activity.m_FrameLayout;
            viewGroup.removeView(m_PromoView);
            Log.d("s3eFlurry", "////// View Removed //////");
            m_isBannerDisplayed = false;
        }
    }
    public void s3eFlurryShowOfferWall()
	{
		if(CheckAppCircle())
		{
        	appCircle.openCatalog(LoaderActivity.m_Activity, "s3eAPPCIRCLE_OFFERWALL_HOOK");
        }
		else
			Log.d("S3EFLURRY", "App Circle is not enabled");
    }
}
