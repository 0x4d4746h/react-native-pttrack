//
//  PtAgent.h
//
//  Created by MiaoGuangfa on 16/6/3.
//  Copyright © 2016年 MiaoGuangfa. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * ptmind custom Bridge protocol for WebView
 */
FOUNDATION_EXTERN NSString *__nonnull const PT_WebView_Bridge_Scheme;
FOUNDATION_EXTERN NSString *__nonnull const PT_WebView_Bridge_Host;

typedef NS_ENUM(NSInteger, PTEcommerceCategory) {
    PT_Category_Impression = 0,
    PT_Category_Product_Detail,
    PT_Category_Add_Cart,
    PT_Category_Remove_Cart,
    PT_Category_Check_Out,
    PT_Category_Purchase,
    PT_Category_Refund,
    PT_Category_Add_Favorite,
    PT_Category_Remove_Favorite
};

@interface PtAgent : NSObject

+ (nonnull PtAgent *)sharedInstance;

/**
 * Start PTTrack engine with appKey(required) and the optional channel value
 * @param appKey, you can get it if you have registered an application archive in our web.
 * @param channel, the name of the application store that you published your app, default value: "AppStore".
 */
- (void)PTStartWithAppKey:(NSString *)appKey channel:(nullable NSString *)channel;

/**
 * Use this method to track an event with user-defined value.
 * @param eventName, this value can't be nil or empty
 * @param properties, you can bind some event properties for this event, if you don't need it, just pass nil.
 *
 ************************************************************************************************************************************
 * [[PtAgent sharedInstance]PTTrackEvent:@"Buy" withProperties:@{@"price":@"200.00", @"title":@"xxx", ...}];
 ************************************************************************************************************************************
 */
- (void)PTTrackEvent:(NSString *)eventName withProperties:(nullable NSDictionary *)properties;

/**
 * Use this method to track an event with user-defined value for ecommerce App.
 * @param actionCategory, this value can't be nil or empty, category list is:
    pt_user_register, pt_user_login, pt_impression, pt_product_detail, pt_add_cart,
    pt_remove_cart, pt_check_out, pt_purchase, pt_refund, pt_add_favorite, pt_remove_favorite
 * @param productDetails, you MUST pass the specific key-values according to documents for collecting product detail info.
 * @param properties, if the specific productDetails can't cover your requirements, you can pass the custom properties info.
 ************************************************************************************************************************************
 * [[PtAgent sharedInstance]PTTrackEventForEcommerce:@"pt_user_register" withProductDetails:@{@"pt_gender":@"man", @"pt_age":@"20", ...} withCustomProperties:@{@"pt_register_properties": {}}];
 ************************************************************************************************************************************
 */
- (void)PTTrackEventForEcommerce:(PTEcommerceCategory)actionCategory withProductDetails:(NSDictionary *)productDetails withCustomProperties:(nullable NSDictionary *)properties;

/**
 * Mark the begin time for the user-defined evnet.
 */
- (void)PTBeginEvent:(NSString *)eventName;

/**
 * Mark the end time for the user-defined event, you can specify the event properties for yourself.
 * This method should be paired with PTBeginEvent, and eventName must be same.
 */
- (void)PTEndEvent:(NSString *)eventName withProperties:(nullable NSDictionary *)properties;

/**
 * Track the User register info with specific properties.
 * Please use the specific keys for userInfo object, for more information, please see the document:
 userInfo = @{
     @"pt_account_id" : @"",
     @"pt_gender" : @"",
     @"pt_age" : @"",
     @"pt_register_country" : @"",
     @"pt_register_subdivision": @"",
     @"pt_register_city" : @""
 }
 */
- (void)PTTrackUserRegister:(NSDictionary *)userInfo withProperties:(nullable NSDictionary *)properties;

/**
 * Track the User login info with specific properties.
 */
- (void)PTTrackUserLogin:(NSString *)userID withProperties:(nullable NSDictionary *)properties;

/**
 * Track the error info if you want to define in some scene. For example, http request is failed...
 * @param exceptionInfo error info
 * @param code          error code
 */
- (void)PTTrackException:(NSString *)exceptionInfo exceptionCode:(NSInteger)code;

/**
 * Because the 'PV' data with default page name for UIViewController has been tracked automatically by PTTrackSDK,
 * so if you want to re-define the page name value, you can invoke this API as soon as [viewWillAppear:] is triggered.
 * The Defalut value is current class name of UIViewController
 * @param redefinedName: new page name value.
 * @param properties: bind the page properties for PV data.
 * @param viewContainer: the instance of current UIViewController.
 */
- (void)PTRedefinePVName:(NSString *)redefinedName withProperties:(nullable NSDictionary *)properties forViewContainer:(id)viewContainer;

/**
 * If you want to track 'PV' data for user-defined UIView, you can invoke this API. But DON't use it for UIViewController container,
 * because our SDK has tracked 'PV' data automatically for UIViewController.
 * @param viewContainerName: page name of UIView, this value can't be empty and nil
 * @param properties:bind the page properties for PV data.
 */
- (void)PTTrackPVForCustomViewContainer:(NSString *)viewContainerName withProperties:(nullable NSDictionary *)properties;


/**
 *  Set all PT defined log output enabled, default is NO
 */
- (void)PTEnableLogOutput;

/**
 * You should register PtAgent javaScript bridge module after webView is finished loading.
 * We register this bridge module as the properties of javaScript window object.
 * And then you can invoke the ptmind javaScript API for packing js event for yourself.
 * @param webView current webView object
 *
 * If you are using UIWebView, please invoke this method in delegate method:
 * - (void)webViewDidFinishLoad:(UIWebView *)webView {
 *      [[PtAgent sharedInstance]PTRegisterJavascriptBridgeForWebView:webView];
 * }
 * If you are using WKWebView, please invoke this method in delegate method:
 * - (void)webView:(WKWebView *)webView didFinishNavigation:(null_unspecified WKNavigation *)navigation {
 *      [[PtAgent sharedInstance]PTRegisterJavascriptBridgeForWebView:webView];
 * }
 *
 * Finally, you can collect your js event with our methods in javascript level.
 ************************************************************************************************************************************
 * We have provided the following APIs for you:
 *
 *   PtAgentWebViewJSBridge.PTTrackEvent(eventName, eventProperties);
 *   PtAgentWebViewJSBridge.PTPackVirtualPageView(virtualPageViewName, PVProperties);
 *   PtAgentWebViewJSBridge.PTTrackException(exceptionInfo, exceptionCode);
 *   PtAgentWebViewJSBridge.PTBeginEvent(eventName);
 *   PtAgentWebViewJSBridge.PTEndEvent(eventName, eventProperties);
 *
 * and recommend you to invoke these methods by this following way:
 *    if (window.PtAgentWebViewJSBridge) {
 *        var attributes = {
 *            'product': 'English Book',
 *            'price': 100
 *        };
 *        var attributes_json = JSON.stringify(attributes);
 *        PtAgentWebViewJSBridge.PTTrackEvent('TestEventName', attributes_json);
 *    }
 *
 *    if (window.PtAgentWebViewJSBridge) {
 *        var attributes = {
 *            'product': 'English Book',
 *            'price': 100
 *        };
 *        var attributes_json = JSON.stringify(attributes);
 *        PtAgentWebViewJSBridge.PTPackVirtualPageView('WebViewDemoPage', attributes_json);
 *    }
 *
 *    if (window.PtAgentWebViewJSBridge) {
 *       PtAgentWebViewJSBridge.PTTrackException('this is an test error info', 110);
 *    }
 *
 *    if (window.PtAgentWebViewJSBridge) {
 *       PtAgentWebViewJSBridge.PTBeginEvent('loginTime');
 *    }
 *
 *    if (window.PtAgentWebViewJSBridge) {
 *        var attributes = {
 *            'userName': 'xxxx',
 *            'email': 'xx@xx.com'
 *        };
 *        var attributes_json = JSON.stringify(attributes);
 *       PtAgentWebViewJSBridge.PTEndEvent('loginTime', attributes_json);
 *    }
 *
 ************************************************************************************************************************************
 *
 */
- (void)PTRegisterJavascriptBridgeForWebView:(id)webView;

/**
 * Parse the web URL request scheme and host info, if they equal to PT_WebView_Bridge_Scheme and PT_WebView_Bridge_Host,
 * then, DO NOT to navigate URL, just return NO.
 * @param NSURL: NSURLRequest.URL, WKNavigationAction.request.URL
 *
 ************************************************************************************************************************************
 * If you are using UIWebView, please invoke this method in this way:
 * - (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType{
 *    NSURL *requestURL = [request URL];
 *    if ([[requestURL scheme] isEqualToString:PT_WebView_Bridge_Scheme] && [[requestURL host] isEqualToString:PT_WebView_Bridge_Host]) {
 *        [[PtAgent sharedInstance]PTJavascriptTrackEventBridgeProtocol:requestURL];
 *        return NO;
 *    }
 *
 *    //Your code implementation...
 *    return YES;
 * }
 *
 * If you are using WKWebView, please invoke this method in this way:
 * - (void)webView:(WKWebView *)webView decidePolicyForNavigationAction:(WKNavigationAction *)navigationAction decisionHandler:(void (^)(WKNavigationActionPolicy))decisionHandler{
 *    NSURL *requestURL = [navigationAction.request URL];
 *    if ([[requestURL scheme] isEqualToString:PT_WebView_Bridge_Scheme] && [[requestURL host] isEqualToString:PT_WebView_Bridge_Host]) {
 *        [[PtAgent sharedInstance]PTJavascriptTrackEventBridgeProtocol:requestURL];
 *        decisionHandler(WKNavigationActionPolicyCancel);
 *    }else {
 *       decisionHandler(WKNavigationActionPolicyAllow);
 *    }
 * }
 ************************************************************************************************************************************
 *
 */
- (void)PTJavascriptTrackEventBridgeProtocol:(NSURL *)webRequestURL;

@end

NS_ASSUME_NONNULL_END
