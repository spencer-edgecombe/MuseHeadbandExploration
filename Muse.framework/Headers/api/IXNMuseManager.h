// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from sdk_bridge.djinni

#import "Muse/api/IXNAdvertisingStats.h"
#import <Foundation/Foundation.h>
@class IXNMuse;
@protocol IXNMuseListener;

/**
 * The default time in seconds after which a headband will be removed from the list
 * of muses if \classlink{MuseManager} has had no contact with it.
 * <p>
 * This has a value of 30 seconds.
 */
extern int64_t const IXNMuseManagerDEFAULTREMOVEFROMLISTAFTER;

/**
 * Discovers the available %Muse headbands that this device can connect to.<br><br>
 * To connect to a headband, first call \functionlink{MuseManager,setMuseListener,set_muse_listener}
 * to receive callbacks when a headband is discovered.  Then call
 * \inlinelink{MuseManager.startListening(),IXNMuseManager::startListening:,MuseManager::start_listening()}
 *  When \classlink{MuseManager}
 * detects a headband you will receive a
 * \inlinelink{MuseListener.museListChanged(),::IXNMuseListener::museListChanged:,MuseListener::muse_list_changed()}
 *  callback.  You can then call
 * \inlinelink{MuseManager.getMuses(),::IXNMuseManager::getMuses:,MuseManager::get_muses()}
 *  followed by the appropriate function on the \classlink{Muse}
 * to connect to the headband.
 *
 * \sa \classlink{Muse}
 * \sa \classlink{MuseListener}
 */
@protocol IXNMuseManager

/**
 * Returns all currently available \classlink{Muse} headbands.
 *
 * The returned list is sorted lexicographically by Muse name.
 *
 * Note that until you start listening, this list will be empty.
 * \return The list of available muses.
 */
- (nonnull NSArray<IXNMuse *> *)getMuses;

/**
 * Start listening for any possible Muse devices.
 *
 * As Muses are discovered, they are added to the list returned by
 * \inlinelink{MuseManager.getMuses(),::IXNMuseManager::getMuses:,MuseManager::get_muses()}
 *
 * Listening is a fairly heavyweight operation, so it should be disabled
 * when it is not needed, e.g. after a device has been found. Specifically,
 * you *must* call \inlinelink{stopListening(),MuseManager::stopListening:,stop_listening()}
 *  before you try to connect to a Muse you have previously discovered.
 * \if IOS_ONLY
 *
 * MU-01 devices are discovered as they connect to the device, either by
 * re-establishing a connection to the last iOS device they connected to, or
 * by the user connecting to them from the OS's Bluetooth settings. If they
 * go offline, they are removed from the list.
 *
 * Any already-known \muse2014 devices will be added to the list immediately;
 * others will trickle in as events are received.
 *
 * \muse2016 and later devices are discovered as their discovery events are passed to the
 * library from the OS.
 * \elseif ANDROID_ONLY
 *
 * You must call MuseManagerAndroid.setContext() prior to calling startListening() or
 * stopListening(), and the context should persist at least from before the
 * call to startListening() till after the call to stopListening(). An
 * application context is a good candidate for this.
 * \elseif WINDOWS_ONLY
 *
 * \else
 * MISSING_DOCUMENTATION
 * \endif
 */
- (void)startListening;

/**
 * Stop listening for Muse devices.
 *
 * Stops receiving advertising packets or modifying the list of Muses
 * returned by \inlinelink{MuseManager.getMuses(),::IXNMuseManager::getMuses:,MuseManager::get_muses()}
 *  If this is called while not scanning, it is a no-op.
 * \if ANDROID_ONLY
 *
 * You must call MuseManagerAndroid.setContext() prior to calling startListening() or
 * stopListening(), and the context should persist at least from before the
 * call to startListening() till after the call to stopListening(). An
 * application context is a good candidate for this.
 * \endif
 */
- (void)stopListening;

/**
 * Set the listener to be notified on changes to the list of Muses.
 * \param listener The listener that will receive the callback when a
 * Muse is discovered.
 */
- (void)setMuseListener:(nullable id<IXNMuseListener>)listener;

/**
 * Returns information about the advertising packets seen by LibMuse.
 * This is intended for internal usage at Interaxon and is currently
 * only implemented on Android for \muse2016 or later. This function does nothing on iOS or Windows.
 */
- (nonnull IXNAdvertisingStats *)getAdvertisingStats:(nullable IXNMuse *)m;

/**
 * Erases all previously stored information about advertising packets.
 * This is intended for internal usage at Interaxon and is currently
 *  only implemented \muse2016 or later. This function does nothing on iOS.
 */
- (void)resetAdvertisingStats;

/**
 * \classlink{MuseManager}
 * will automatically remove a \muse2016 or later headband from the list of Muses if it
 * has not received some type of communication from the headband within this
 * time period.
 *
 * By default this is
 * \inlinelink{MuseManager.DEFAULT_REMOVE_FROM_LIST_AFTER,30 seconds,MuseManager::DEFAULT_REMOVE_FROM_LIST_AFTER}.
 *  To have \muse2016 or later headbands remain in the list until the next call to
 * \inlinelink{MuseManager.startListening(),IXNMuseManager::startListening:,MuseManager::start_listening()}
 *  set the time to 0.
 *
 * \param time Specified in seconds, the time to wait before removing a headband from the
 * list.  If set to 0, headbands will not be removed automatically.
 */
- (void)removeFromListAfter:(int64_t)time;

@end
