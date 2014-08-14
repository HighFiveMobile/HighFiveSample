HighFive Demo App
==============

This is a demo app to get developers started using the HighFive SDK

- [Full documentation](https://www.highfive.me/documentation/Classes/Highfive.html)

- [Download Highfive SDK](https://www.highfive.me/downloads/Highfive.framework.1.5.1.zip) or you can grab the SDK from this repo.


### Getting Started

You will find the demo code in [HFARootViewController.m](https://github.com/HighFiveMobile/HighFiveSample/blob/master/HighFiveSample/HFARootViewController.m)

We need to set the **APP_ID** : *line 26*

```
[[Highfive handShake] startSessionWithAppID:@"APP_ID"];
```

We make a request to get available rewards from the server : *line 36*

You don't need to do anything with the returned **appInfo**, it is just for your own testing.

```
[[Highfive handShake] getRewardsWithResponse:^(NSDictionary *appInfo, NSError *error) {
        
	// Look at the information returned with the request.
	NSLog(@"%@",appInfo);
	
	if(error != nil)
	{
	    // What happened?
	    NSLog(@"%@",error);
	}
        
}];
```

When a user does an activity, we need to run the track method. : *line 60*

```
NSString * activityName = @"Running";
NSString * activityMetric = @"Miles";
NSInteger activityMetricAmount = 5;

// Track an activity.
[[Highfive handShake] trackActivity:activityName withMetricInfo:@{activityMetric:@(activityMetricAmount)}];
```

Once users are done with their activity you can check to see if they have won a reward. : *line 74*

If they have won a reward, the reward view will appear. There are two blocks that can be set for when the view opens and is closed by being dismissed / redeemed by the user.

```
// Check if a reward has been achieved after tracking an activity.
[[Highfive handShake] checkRewardsWithOpen:^{
    
    // Reward view is opening
    
} andClose:^{

    // Reward view is closing after user either dismissed or redeemed.
    
}];
```
If you want to listen for the user not winning a reward, you can set this block. : *line 68* 

You should set this before calling **checkRewards**.

```
[Highfive handShake].unavailableRewardBlock = ^{
  
    // This will run after checkRewards if no rewards were achieved.
    
};
```