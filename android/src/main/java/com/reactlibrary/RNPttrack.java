
package com.reactlibrary;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Callback;

import android.app.Application;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.webkit.WebView;

import com.facebook.react.bridge.ReadableMap;
import com.ptmind.sdk.PtAgent;

import org.json.JSONObject;

import java.util.HashMap;

public class RNPttrack extends ReactContextBaseJavaModule {

  private final ReactApplicationContext reactContext;

  public RNPttrack(ReactApplicationContext reactContext) {
    super(reactContext);
    this.reactContext = reactContext;
  }

  @Override
  public String getName() {
    return "RNPttrack";
  }

  @ReactMethod
  public void startWithAppKey(@NonNull  String appKey, @Nullable String channel) {
      try{
          Application application = getReactApplicationContext().getCurrentActivity().getApplication();
          if(application != null) {
              PtAgent.getInstance().startWithAppKeyAndChannel(appKey, channel, application);
          }
      }catch (NullPointerException e){
          e.printStackTrace();
      }
  }

  @ReactMethod
  public void trackEvent(@NonNull String eventName, @Nullable ReadableMap properties) {
    if (properties == null) {
        PtAgent.getInstance().trackEvent(eventName,null);
    }else{
        PtAgent.getInstance().trackEvent(eventName, properties.toHashMap());
    }
  }
  @ReactMethod
  public void trackEventForEcommerce(@NonNull String actionCategory, @NonNull ReadableMap productDetails, @Nullable ReadableMap properties) {
    if (properties == null){
        PtAgent.getInstance().trackEventForEcommerce(actionCategory, new JSONObject(productDetails.toHashMap()), null);
    }else{
        PtAgent.getInstance().trackEventForEcommerce(actionCategory, new JSONObject(productDetails.toHashMap()), new JSONObject(properties.toHashMap()));
    }
  }

  @ReactMethod
  public void beginEvent(@NonNull String eventName) {
      PtAgent.getInstance().beginEvent(eventName);
  }

  @ReactMethod
  public void endEvent(@NonNull String eventName, @Nullable ReadableMap properties) {
      if (properties == null) {
          PtAgent.getInstance().endEvent(eventName,null);
      }else{
          PtAgent.getInstance().endEvent(eventName, properties.toHashMap());
      }
  }

  @ReactMethod
  public void trackException(@NonNull Integer errorCode, @NonNull String errorMessage) {
      String errorCodeStr = errorCode.toString();
      PtAgent.getInstance().trackException(errorCodeStr, errorMessage);
  }

  @ReactMethod
  public void trackUserRegister(@NonNull ReadableMap userInfo, @Nullable ReadableMap properties ) {
      if (properties == null){
          PtAgent.getInstance().trackUserRegister(new JSONObject(userInfo.toHashMap()), null);
      }else{
          PtAgent.getInstance().trackUserRegister(new JSONObject(userInfo.toHashMap()), new JSONObject(properties.toHashMap()));
      }
  }

  @ReactMethod
  public void trackUserLogin(@NonNull String userID, @Nullable ReadableMap properties) {
      if (properties == null) {
          PtAgent.getInstance().trackUserLogin(userID, null);
      }else{
          PtAgent.getInstance().trackUserLogin(userID, properties.toHashMap());
      }
  }

  @ReactMethod
  public void trackPVForCustomView(@NonNull String pageName, @Nullable ReadableMap properties) {
      if (properties == null) {
          PtAgent.getInstance().trackPVForCustomView(pageName, null);
      }else {
          PtAgent.getInstance().trackPVForCustomView(pageName, properties.toHashMap());
      }
  }

  @ReactMethod
  public void enableLogOutput() {
    PtAgent.getInstance().enableLogOutput();
  }
}