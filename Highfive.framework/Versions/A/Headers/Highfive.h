//
//  Highfive.h
//  Highfive
//
//  Created by Jo Albright on 9/30/12.
//  Copyright (c) 2013 Jo Albright. All rights reserved.
//


#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

typedef void (^RewardWillAppearResponse)(void);
typedef void (^RewardWillDisappearResponse)(void);
typedef void (^UnavailableRewardResponse)(void);
typedef void (^FoundRewardsResponse)(NSDictionary *, NSError *);
typedef void (^BeaconFoundWithLastActivityID)(NSString *);

/**
 
 **Version 1.5.1** - This framework creates the ability to reward users based on the activities that are tracked.
 
*/

@interface Highfive : NSObject



/** @name Getting the Highfive Instance */



/**
 
 Returns a Highfive singleton that will be used throughout your app.

 @return An instance of the Highfive class.
 
*/

+ (Highfive *)handShake;



/** @name Start a User Session */



/**
 
 Will either create a new session with a new user or continue a the previous session with the saved user.

    [[Highfive handshake] startSessionWithAppID:@"YOUR_APP_ID"];
 
 @param appID A NSString. It is the red string of letters and numbers below your app name on the [Apps Page](https://www.highfive.me/dashboard/apps/) within the HighFive dashboard.

*/

- (void)startSessionWithAppID:(NSString *)appID;



//////////////////
////////////////// REWARDS
//////////////////

/** @name Reward Management */



/**
 
 Block to be called when the reward view will appear after a user has won a reward.
 
    [Highfive handShake].rewardWillAppearBlock = ^(){ NSLog(@"Reward view is appearing."); };
 
*/

@property (nonatomic,copy) RewardWillAppearResponse rewardWillAppearBlock;

/**
 
 Block to be called when the user is returning to your app.
 
     [Highfive handShake].rewardWillDisappearBlock = ^(){ NSLog(@"Coming back to app experience."); };
*/

@property (nonatomic,copy) RewardWillDisappearResponse rewardWillDisappearBlock;

/**

 Block to be called if no rewards were won when calling checkRewards.
 
    [Highfive handShake].unavailableRewardBlock = ^(){ NSLog(@"No rewards won."); };
 
*/

@property (nonatomic,copy) UnavailableRewardResponse unavailableRewardBlock;

/**
 
 Block to be called after rewards are available.
 
    [Highfive handShake].foundRewardsBlock = ^(NSDictionary *appInfo, NSError *error){ NSLog(@"%@",appInfo); };

*/

@property (nonatomic,copy) FoundRewardsResponse foundRewardsBlock;

/**
 
 Setting this variable to `YES` will turn off rewards for the user. The default value is `NO`.
 
*/

@property (nonatomic) BOOL rewardsOff;

/**
 
 Method to make a server request to refresh the available rewards for the the current app.
 
*/

- (void)getRewards;

/**
 
 Makes a request to the HighFive server to get available rewards. The block will return once request has finished with information about the available rewards.
 
    [[Highfive handshake] getRewardsWithResponse:^(NSDictionary *appInfo, NSError *error) { NSLog(@"%@",appInfo); }];
 
 @param responseBlock Block to view information about available rewards.
 
*/

- (void)getRewardsWithResponse:(void(^)(NSDictionary *appInfo, NSError *error))responseBlock;

/**

 Description
 
*/

- (void)checkRewards;

/**

 Method to check if a user has won a reward based on the activities tracked with trackActivity:withMetricInfo:.
 
    [[Highfive handshake] checkRewardsWithBeforeView:^{ NSLog(@"Reward View Opened"); } andAfterView:^{ NSLog(@"Reward View CLosed"); }];
 
 @param rewardWillAppearBlock rewardWillAppearBlock description
 @param rewardWillDisappearBlock rewardWillDisappearBlock description
 
*/

- (void)checkRewardsWithOpen:(void(^)(void))rewardWillAppearBlock andClose:(void(^)(void))rewardWillDisappearBlock;

/**
 
 Customizes the animation speed for the reward view.
 
    [[Highfive handshake] rewardViewSettings:@{@"showspeed":@"0.5",@"hidespeed":@"0.4"}];
 
 @param settings A NSDictionary.
 
*/

- (void)rewardViewSettings:(NSDictionary *)settings;



//////////////////
////////////////// LOCATION
//////////////////



/** @name Location Management */



/**

 Used to find the user's location with Core Location. Will prompt the user to use location services if they have not already approved this app.

    [[Highfive handshake] findUserLocation:^(CLLocation *loc) { NSLog(@"%@",loc); }];

 @param response Block to be called after the user's location is found.

*/

- (void)findUserLocation:(void(^)(CLLocation *loc))response;

/**
 
 You can set the user location based on your own location tracking.

    [[Highfive handshake] updateUserLocation:userLocation];

 @param location CLLocation
 
*/

- (void)updateUserLocation:(CLLocation *)location;

/**
 
 You can pass the FourSquare venue ID to give us the users location.

    [[Highfive handshake] updateFoursquareLocation:venueID];
 
 @param venueID NSString.
 
*/

- (void)updateFoursquareLocation:(NSString *)venueID;



//////////////////
////////////////// BEACONS
//////////////////



/** @name Beacon Management */



/**

 Block to be called when a beacon is found. This block will contain an NSString with the value of the last activity ID.
 
    [Highfive handShake].beaconFoundWithLastActivityID = ^(NSString *activityID){ NSLog(@"Activity ID :%@",activityID); };
 
*/

@property (nonatomic,copy) BeaconFoundWithLastActivityID beaconFoundWithLastActivityID;

/**

 Description
 
 @param UUID UUID description
 
*/

- (void)listenForBeaconWithUUID:(NSUUID *)UUID;



//////////////////
////////////////// ACTIVITIES
//////////////////



/** @name Activity Tracking */



/**
 
 Collects activities for possible rewards.
 
    [[Highfive handshake] trackActivity:@"Running" withMetrics:@[@{@"name":@"Miles",@"value":@10}]];

 @param activityType activityType must be an exact match (case sensitive) to the activity types for your app. You can find these on the "View" page for your app. [Apps Page](https://www.highfive.me/dashboard/apps/)

 @param metrics NSArray of NSDictionary objects.
 
 @warning This method will be deprecated in version 1.6.0
 
*/

- (void)trackActivity:(NSString *)activityType withMetrics:(NSArray *)metrics;

/**
 
 Collects activities for possible rewards.
 
    [[Highfive handshake] trackActivity:@"Running" withMetrics:@{@"Miles":@10}];
 
 @param activityType activityType must be an exact match (case sensitive) to the activity types for your app. You can find these on the "View" page for your app. [Apps Page](https://www.highfive.me/dashboard/apps/)
 
 @param metricinfo NSDictionary.
 
 */

- (void)trackActivity:(NSString *)activityType withMetricInfo:(NSDictionary *)metricinfo;



//////////////////
////////////////// USER
//////////////////



/** @name User Information Management */



/**

 Setting this variable to `YES` will turn off the saving of user information. The default value is `NO`.
 
 @see addUserInfo:
 @see getUserInfo
 
*/

@property (nonatomic) BOOL userInfoOff;

/**

 Update the user information with a NSDictionary.

 @param userInfo A NSDictionary.

 @see userInfoOff
 @see getUserInfo

*/

- (void)addUserInfo:(NSDictionary *)userInfo;

/**

 Returns a NSDictionary of user information.

 @return NSDictionary.

 @see userInfoOff
 @see addUserInfo:
 
*/

- (NSDictionary *)getUserInfo;



//////////////////
//////////////////
//////////////////



/** @name Testing */



/**

 Clears all session information, allowing the ability to start a new user session. You must call startSessionWithAppID: to create a new user.

 @warning This was built for testing. Use it at your own risk within a live environment.
 
*/

- (void)clearSession;

@end