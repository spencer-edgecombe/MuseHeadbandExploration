// Copyright 2023 InteraXon, Inc.

#import <ExternalAccessory/ExternalAccessory.h>
#import <Foundation/Foundation.h>
#import "Muse/api/IXNMuseManager.h"

/**
 * Provides access to all IXNMuse devices paired to this device.
 */
@interface IXNMuseManagerMac : NSObject<IXNMuseManager>

/**
 * Returns the shared IXNMuseManager.
 */
+ (IXNMuseManagerMac *)sharedManager;

/**
 * Listener called on changes to the list of available muses.
 *
 * Redefined readwrite here (the IXNMuseManager protocol only provides a setter.)
 */
@property (nonatomic, readwrite) id<IXNMuseListener> museListener;

@end
