//
//  HFARootViewController.m
//  HighFiveSample
//
//  Created by Jo Albright on 4/26/14.
//  Copyright (c) 2014 HighFive. All rights reserved.
//

#import "HFARootViewController.h"

#import <Highfive/Highfive.h>

@interface HFARootViewController ()

@end

@implementation HFARootViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        
#warning You must replace APP_ID with the one given in the https://www.highfive.me/dashboard
        [[Highfive handShake] startSessionWithAppID:@"APP_ID"];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Grab available rewards from the server.
    [[Highfive handShake] getRewardsWithResponse:^(NSDictionary *appInfo, NSError *error) {
        
        // Look at the information returned with the request.
        NSLog(@"%@",appInfo);
        
        if(error != nil)
        {
            // What happened?
            NSLog(@"%@",error);
        }
        
    }];
    
    float buttonWidth = 200;
    float buttonHeight = 40;
    
    UIButton * trackActivityButton = [[UIButton alloc] initWithFrame:CGRectMake((SCREEN_HEIGHT - buttonHeight) / 2, (SCREEN_WIDTH - buttonWidth) / 2, buttonWidth, buttonHeight)];
    trackActivityButton.backgroundColor = [UIColor darkGrayColor];
    
    [trackActivityButton addTarget:self action:@selector(trackActivity) forControlEvents:UIControlEventTouchUpInside];
}

- (void)trackActivity
{
    NSString * activityName = @"Running";
    NSString * activityMetric = @"Miles";
    NSInteger activityMetricAmount = 5;
    
    // Track an activity.
    [[Highfive handShake] trackActivity:activityName withMetricInfo:@{activityMetric:@(activityMetricAmount)}];
    
    
    [Highfive handShake].unavailableRewardBlock = ^{
      
        // This will run after checkRewards if no rewards were achieved.
        
    };
    
    // Check if a reward has been achieved after tracking an activity.
    [[Highfive handShake] checkRewardsWithOpen:^{
        
        // Reward view is opening
        
    } andClose:^{
    
        // Reward view is closing after user either dismissed or redeemed.
        
    }];
}

@end
