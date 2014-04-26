//
//  HFAAppDelegate.m
//  HighFiveSample
//
//  Created by Jo Albright on 4/26/14.
//  Copyright (c) 2014 HighFive. All rights reserved.
//

#import "HFAAppDelegate.h"
#import "HFARootViewController.h"

@implementation HFAAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    self.window.rootViewController = [[HFARootViewController alloc] initWithNibName:nil bundle:nil];
    
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    return YES;
}

@end
