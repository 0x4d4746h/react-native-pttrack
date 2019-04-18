
#import "RNPttrack.h"
#import "PtAgent.h"

@implementation RNPttrack

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(startWithAppKey:(NSString *)appKey channel:(nullable NSString *)channel)
{
    /**
     * Start PTTrack engine with appKey(required) and the optional channel value
     * @param appKey, you can get it if you have registered an application archive in our web.
     * @param channel, the name of the application store that you published your app, default value: "AppStore".
     */
    [[PtAgent sharedInstance]PTStartWithAppKey:appKey channel:channel];
}

RCT_EXPORT_METHOD(trackEvent:(NSString *)eventName properties:(nullable NSDictionary *)properties)
{
    /**
     * Use this method to track an event with user-defined value.
     * @param eventName, this value can't be nil or empty
     * @param properties, you can bind some event properties for this event, if you don't need it, just pass nil.
     *
     ************************************************************************************************************************************
     * [[PtAgent sharedInstance]PTTrackEvent:@"Buy" withProperties:@{@"price":@"200.00", @"title":@"xxx", ...}];
     ************************************************************************************************************************************
     */
    [[PtAgent sharedInstance]PTTrackEvent:eventName withProperties:properties];
}

RCT_EXPORT_METHOD(trackEventForEcommerce:(NSString *)actionCategory productDetails:(NSDictionary *)productDetails customProperties:(nullable NSDictionary *)properties)
{
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

    NSArray * actionCategoryPool = @[@"pt_impression", @"pt_product_detail", @"pt_add_cart", @"pt_remove_cart", @"pt_check_out", @"pt_purchase", @"pt_refund", @"pt_add_favorite", @"pt_remove_favorite"];
    [[PtAgent sharedInstance]PTTrackEventForEcommerce:[actionCategoryPool indexOfObject:actionCategory] withProductDetails:productDetails withCustomProperties:properties];
}

RCT_EXPORT_METHOD(beginEvent:(NSString *)eventName)
{
    /**
     * Mark the begin time for the user-defined evnet.
     */
    [[PtAgent sharedInstance]PTBeginEvent:eventName];
}

RCT_EXPORT_METHOD(endEvent:(NSString *)eventName properties:(nullable NSDictionary *)properties)
{
    /**
     * Mark the end time for the user-defined event, you can specify the event properties for yourself.
     * This method should be paired with PTBeginEvent, and eventName must be same.
     */
    [[PtAgent sharedInstance]PTEndEvent:eventName withProperties:properties];
}

RCT_EXPORT_METHOD(trackUserRegister:(NSDictionary *)userInfo properties:(nullable NSDictionary *)properties)
{
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
    [[PtAgent sharedInstance]PTTrackUserRegister:userInfo withProperties:properties];
}

RCT_EXPORT_METHOD(trackUserLogin:(NSString *)userID properties:(nullable NSDictionary *)properties)
{
    /**
     * Track the User login info with specific properties.
     */
    [[PtAgent sharedInstance]PTTrackUserLogin:userID withProperties:properties];
}

RCT_EXPORT_METHOD(trackException:(NSInteger)exceptionCode exceptionInfo:(nullable NSString *)exceptionInfo)
{
    /**
     * Track the error info if you want to define in some scene. For example, http request is failed...
     * @param exceptionInfo error info
     * @param code          error code
     */
    [[PtAgent sharedInstance]PTTrackException:exceptionInfo exceptionCode:exceptionCode];
}

RCT_EXPORT_METHOD(trackPVForCustomViewContainer:(NSString *)viewContainerName properties:(nullable NSDictionary *)properties)
{
    /**
     * If you want to track 'PV' data for user-defined UIView, you can invoke this API. But DON't use it for UIViewController container,
     * because our SDK has tracked 'PV' data automatically for UIViewController.
     * @param viewContainerName: page name of UIView, this value can't be empty and nil
     * @param properties:bind the page properties for PV data.
     */
    [[PtAgent sharedInstance]PTTrackPVForCustomViewContainer:viewContainerName withProperties:properties];
}

RCT_EXPORT_METHOD(enableLogOutput)
{
    [[PtAgent sharedInstance]PTEnableLogOutput];
}

@end
  
