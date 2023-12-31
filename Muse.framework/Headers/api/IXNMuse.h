// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from sdk_bridge.djinni

#import "Muse/api/IXNConnectionState.h"
#import "Muse/api/IXNMuseDataPacketType.h"
#import "Muse/api/IXNMuseModel.h"
#import "Muse/api/IXNMusePreset.h"
#import "Muse/api/IXNNotchFrequency.h"
#import <Foundation/Foundation.h>
@class IXNMuseConfiguration;
@class IXNMuseVersion;
@protocol IXNMuseConnectionListener;
@protocol IXNMuseDataListener;
@protocol IXNMuseErrorListener;


/**
 * Provides the client interface to a specific %Muse Headband.
 *
 * This class maps to a single %Muse Headband, providing an API for receiving
 * connection events and data packets, as well as the ability to inspect
 * various properties of the headband it corresponds to. Users can initiate
 * and halt a connection to the device, enable data transmission, find out
 * the human-readable name of the headband, etc.
 *
 * This class should never be constructed directly by a user; rather,
 * references to it can be retrieved from MuseManager.
 *
 * There are two main ways of interacting with a %Muse:
 *   1. calling \inlinelink{runAsynchronously(),::IXNMuse::runAsynchronously(),run_asynchronously()}<br>
 *   2. calling \inlinelink{connect(),::IXNMuse::connect(),connect()}
 *      on your own and then repeatedly calling
 *      \inlinelink{execute(),::IXNMuse::execute(),execute()}.
 *
 * If you call \inlinelink{runAsynchronously(),::IXNMuse::runAsynchronously(),run_asynchronously()},
 * you do not need to call
 * \inlinelink{connect(),::IXNMuse::connect(),connect()}
 *  or \inlinelink{execute(),::IXNMuse::execute(),execute()}
 *  on your own.  Everything is taken care of by LibMuse for the duration of the
 * connection (i.e. until you receive a disconnected event).
 *
 * If you call \inlinelink{connect(),::IXNMuse::connect(),connect()}
 *  on your own, you are responsible
 * for calling \inlinelink{execute(),::IXNMuse::execute(),execute()}
 *  on your own as well.  Execute performs small, non-blocking steps of work such
 * as initiating a connection, streaming data or disconnecting.
 * If \inlinelink{execute(),::IXNMuse::execute(),execute()}
 *  is not called, no work is performed.  The %Muse will not
 * transition its connection state and you will not receive any data.  If you are
 * using this method of interacting with a %Muse you need to continue calling
 *\inlinelink{execute(),::IXNMuse::execute(),execute()}
 *  until you receive a DISCONNECTED event through a
 * registered connection listener.
 * It may take multiple execute calls to reach the DISCONNECTED after issuing the
 * disconnect request.  Failure to wait for the DISCONNECTED event can result in
 * unanticipated consequences.
 */
@interface IXNMuse : NSObject

/**
 * Initiate a connection to a %Muse headband.
 *
 * This call is non-blocking and returns immediately.
 * Since this returns before the connection is established, you
 * should instead use a connection listener to implement any
 * logic, such as updating a UI element, on successful connection.
 * When the connection is successful you will receive a CONNECTED event.
 * If the connection is unsuccessful you will receive a DISCONNECTED event.
 *
 * <b>Threading:</b> method is thread-safe.
 */
- (void)connect;

/**
 * Disconnects your mobile device from %Muse Headband.
 *
 * If you are calling \inlinelink{execute(),::IXNMuse::execute(),execute()}
 *  on your own, remember to continue calling
 * \inlinelink{execute(),::IXNMuse::execute(),execute()}
 *  until you receive the DISCONNECTED event.
 *
 * <B>Threading:</B> method is thread-safe. <br>
 *
 * If you don't want to receive disconnection event, unregister listeners
 * manually first.
 */
- (void)disconnect;

/**
 * Runs a single, non-blocking step of processing.
 *
 * Reads data from Bluetooth if there is any; updates the connection state;
 * sends packets to listeners; etc. This should be called relatively
 * frequently: max 250ms, ideally 20ms.
 *
 * If you are listening for computed values (e.g. band powers) rather than
 * just raw EEG samples, then be aware that this method may trigger some
 * amount of processing in the foreground before it returns. If this has
 * undesirable effects on app performance, then you may want to move it to a
 * dedicated thread.
 *
 * Also be aware that all packets will be received on the same thread as
 * \inlinelink{execute(),::IXNMuse::execute(),execute()}
 *  is run.
 *
 * <B>Threading:</b> This method is NOT thread safe. You must synchronize
 * the Muse object on your own if you wish to call it concurrently from more
 * than one thread.
 */
- (void)execute;

/**
 * Connect to a headband out of the main logic flow.
 *
 * This method handles all the connection logic for a single connection to a
 * headband (i.e. starting with issuing a "connecting" event and ending with
 * issuing a "disconnected" event). It may run in a separate thread or an
 * event loop on the main thread; the details are platform-specific.
 *
 * If this method is used, then all packets are
 * delivered on the main thread.
 * \if WINDOWS_ONLY
 * Windows is an exception.  On Windows all packets are delivered on a
 * dedicated thread other than the main thread.
 * \endif
 *
 * The lifetime of effect of this method ends on disconnection; if you want
 * to initiate a new connection to a headband that has disconnected, you
 * should call \inlinelink{runAsynchronously(),::IXNMuse::runAsynchronously(),run_asynchronously()}
 *  on it again.
 *
 * If this method is called multiple times within the lifetime of a single
 * connection, any subsequent calls will do nothing other than print a log
 * message.
 *
 * Note that there is currently a race condition if
 * \inlinelink{runAsynchronously(),::IXNMuse::runAsynchronously(),run_asynchronously()}
 *  is called
 *  1. as a result of a DISCONNECTED packet, and
 *  2. on a different thread from the one that delivered the notification.
 *
 * This will be resolved in a future library release. For now, call
 * \inlinelink{runAsynchronously(),::IXNMuse::runAsynchronously(),run_asynchronously()}
 *  on the same thread that sent the DISCONNECTED packet,
 * or after some modest delay (say 1 second.)
 *
 * <B>Threading:</B> This method is thread safe.
 */
- (void)runAsynchronously;

/**
 * Returns current connection state. <br><br>
 * <B>Threading:</B> method is thread-safe.
 * \return The current connection state.
 */
- (IXNConnectionState)getConnectionState;

/**
 * Returns Bluetooth MAC address of the %Muse Headband. <br><br>
 * <B>Threading:</B> method is thread-safe.
 * \return The MAC address of the %Muse Headband.
 */
- (nonnull NSString *)getMacAddress;

/**
 * Returns Bluetooth name of the %Muse Headband. <br><br>
 * <B>Threading:</B> method is thread-safe.
 * \return The name of the %Muse Headband.
 */
- (nonnull NSString *)getName;

/**
 * Returns the RSSI of this device.
 *
 * Only implemented on low-energy Muses. Returns NaN if called on
 * non-low-energy Muses.
 *
 * <B>Threading:</b> method is thread-safe.
 * \return The RSSI of a low-energy %Muse or NaN if the %Muse is
 * not low-energy.
 */
- (double)getRssi;

/**
 * Returns the model of the %Muse Headband. Eg. MU-02, GL-01, etc...
 *
 * This should return a value for every Muse currently available.
 *
 * <B>Threading:</B> method is thread-safe.
 * \return The model of the %Muse Headband.
 */
- (IXNMuseModel)getModel;

/**
 * Returns the time at which this device was most recently discovered.
 *
 * Muse devices broadcast service information every few seconds, and this is
 * the last time LibMuse has heard this broadcast info.
 *
 * Only implemented on low-energy Muses. Returns NaN if called on
 * non-low-energy Muses.
 *
 * The value is in microseconds since some common start time (e.g. epoch,
 * device start time, or app start time) that is guaranteed not to change
 * within a running app process. The value may be used e.g. to determine
 * which of two devices was discovered more recently than the other. It
 * should not be used as an absolute time, nor should the common start time
 * be assumed to be the same between any two running app instances.
 *
 * \if IOS_ONLY
 * This value is computed via:
 *
 *     CACurrentMediaTime() * 1000.0 * 1000.0.
 *
 * You may therefore use CACurrentMediaTime() to recover deltas from the
 * current time to e.g. implement "only muses discovered in the last 20
 * seconds."
 * \endif
 * \return The time at which this device was most recently discovered.
 */
- (double)getLastDiscoveredTime;

/**
 * \if WINDOWS_ONLY
 * When LibMuse tries connect to a %Muse, it will by default try only once
 * before giving up. This is due to the fact that the user must allow
 * the app permission to access the headband through a UI dialog. Setting
 * this to a number larger than one will cause the UI dialog to pop up
 * multiple times.
 * \else
 * When LibMuse tries connect to a %Muse, it will by default try 3 times
 * before giving up.  This function allows you to change the number of
 * tries from 3 to anything you want.  numTries must be a positive integer.
 * \endif
 * This function only works for model MU-02 Muses, calling it on a MU-01
 * will do nothing.  This function was added for internal
 * testing purposes, and we do not anticipate that 3rd party clients of
 * the LibMuse library will need to modify this value. <br>
 *
 * <B>Threading:</B> This method is thread safe.
 * \caseparam{numTries, numTries, The number of times to try to connect before giving up.}
 */
- (void)setNumConnectTries:(int32_t)numTries;

/**
 * Returns struct which contains all information about
 * Muse configuration. <BR>
 *
 * <B>Threading:</B> method is thread-safe.
 * \warning The %Muse Configuration object is only populated during
 * connection routine or after headband settings (like preset or
 * notch frequency) are changed. If this is called before the %Muse
 * is connected, the configuration will be \c null.
 * \return The configuration information of this %Muse or \c null if the
 * configuration is unknown.
 */
- (nullable IXNMuseConfiguration *)getMuseConfiguration;

/**
 * Returns all information about the version of the %Muse. <BR>
 *
 * <B>Threading:</B> method is thread-safe.
 * \warning The %Muse Version is populated during connection routine only.
 * If this is called before the %Muse is connected, the version will be
 * \c null.
 * \return The version of this %Muse or \c null if the
 * version is unknown.
 */
- (nullable IXNMuseVersion *)getMuseVersion;

/**
 * Registers a connection listener. The same listener cannot be registered
 * twice. If the listener was already registered, then this method does nothing.
 * <br><br>
 * <B> Threading: </B> method is thread-safe.
 * \param listener The listener to register.
 */
- (void)registerConnectionListener:(nullable id<IXNMuseConnectionListener>)listener;

/**
 * Unregisters connection listeners. <br><br>
 * <B> Threading: </B> method is thread-safe.
 * \param listener The listener to unregister.
 */
- (void)unregisterConnectionListener:(nullable id<IXNMuseConnectionListener>)listener;

/**
 * Registers a data listener. You can register the same listener to listen
 * for different packet types - just call this method again. It's your
 * responsibility to make sure that the listener handles all packet types
 * correctly.
 *
 * If this listener was already registered for this specific type then this
 * method does nothing.
 *
 * <B> Threading: </B> method is thread-safe.
 * \param listener The listener to register.
 * \param type The type of data packet the listener will receive.
 */
- (void)registerDataListener:(nullable id<IXNMuseDataListener>)listener
                        type:(IXNMuseDataPacketType)type;

/**
 * Unregisters a data listener that was registered before.
 *
 * If the listener was not registered before, then this method does nothing.
 *
 * <B>Threading:</B> method is thread-safe.
 * \param listener The listener to unregister.
 * \param type The type of data packet the listener will stop receiving.
 */
- (void)unregisterDataListener:(nullable id<IXNMuseDataListener>)listener
                          type:(IXNMuseDataPacketType)type;

/**
 * Registers an error listener.
 *
 * <B>Threading:</B> method is thread-safe.
 * \param listener The listener to register.
 */
- (void)registerErrorListener:(nullable id<IXNMuseErrorListener>)listener;

/**
 * Unregisters an info listener that was registered before.
 *
 * If the listener was not registered before, then this method does nothing.
 *
 * <B>Threading:</B> method is thread-safe.
 * \param listener The listener to unregister.
 */
- (void)unregisterErrorListener:(nullable id<IXNMuseErrorListener>)listener;

/**
 * Unregisters all registered connection listeners and data
 * listeners.
 *
 * <B>Threading:</B> method is thread-safe.
 */
- (void)unregisterAllListeners;

/**
 * Changes %Muse Headband settings.
 * <B> Threading: </B> method is thread-safe.
 * You can call it in the middle of execute operation, but in this case
 * be aware that this operation will interrupt data streaming to set new
 * preset. Data streaming will be restored after that.
 * If method is called before connection is established, the right setting
 * will be passed to device during connection routine.
 * \param preset The new preset.
 */
- (void)setPreset:(IXNMusePreset)preset;

/**
 * Toggles the LED indicator state on %Muse headbands supporting sleep.
 * \warning The headband must be in the CONNECTED state before calling this method.
 * <B> Threading: </B> method is thread-safe.
 * \param enable \c true to turn indicator LEDs on. \c false to turn them off.
 */
- (void)enableLedIndicator:(BOOL)enable;

/**
 * Starts/stops data transmission (but keep-alive packets will be still sent).
 * If you're using low-level interface (connect + execute), you should
 * still call \inlinelink{execute(),::IXNMuse::execute(),execute()}
 *  to continue sending keep-alive messages.
 * If you're using \inlinelink{runAsynchronously(),::IXNMuse::runAsynchronously(),run_asynchronously()},
 * then it will take care about sending keep-alive packets. <br>
 * <B>Threading:</B> method is thread-safe. You can call it in the middle
 * of an execute operation.
 * If method is called before connection is established, the right setting
 * will be passed to device during connection routine.
 * \param enable \c true to start streaming data. \c false to pause the data stream.
 */
- (void)enableDataTransmission:(BOOL)enable;

/**
 * Changes notch frequency (power line frequency). <br><br>
 * <B>Threading:</B> method is thread-safe.
 * You can call it in the middle of execute operation, but in this case
 * be aware that this operation will interrupt data streaming to set new
 * notch frequency. Data streaming will be restored after that.
 * If method is called before a connection is established, the right setting
 * will be passed to device during connection routine.
 * <br>
 *
 * When combining a call setNotchFrequency with
 * \functionlink{Muse,setPreset,set_preset}
 * setNotchFrequency can be called before or after the call to
 * \functionlink{Muse,setPreset,set_preset}
 * The notch frequency will be applied to the preset after the preset is set.
 *
 * \warning
 * This is only supported on \muse2014 headbands and then only with presets:<br>
 * \enumlink{MusePreset,PRESET_10,IXNMusePresetPreset10},
 * \enumlink{MusePreset,PRESET_12,IXNMusePresetPreset12} and
 * \enumlink{MusePreset,PRESET_14,IXNMusePresetPreset14}.
 * Under those presets, the only valid frequencies are:
 * \enumlink{NotchFrequency,NOTCH_50HZ,IXNNotchFrequencyNotch50hz}
 * \enumlink{NotchFrequency,NOTCH_60HZ,IXNNotchFrequencyNotch60hz}
 * <br>
 *
 * \warning
 * Calling this with
 * \enumlink{NotchFrequency,NOTCH_NONE,IXNNotchFrequencyNotchNone}
 * will do nothing.
 *
 * \warning
 * This does nothing on \muse2016 or later headbands and on \muse2014 headbands with presets
 * \enumlink{MusePreset,PRESET_AB,IXNMusePresetPresetAb} or
 * \enumlink{MusePreset,PRESET_AD,IXNMusePresetPresetAd}
 *
 *\caseparam{newFrequency, newFrequency, The new notch frequency.}
 */
- (void)setNotchFrequency:(IXNNotchFrequency)newFrequency;

/**
 * True if this device supports Bluetooth Low-Energy.
 * \return \c true if this %Muse supports Bluetooth Low-Energy. \c false
 * if it does not.
 */
- (BOOL)isLowEnergy;

/**
 * Returns true if the Muse is paired with the OS, false otherwise.
 * This will always return true for \muse2014.  For \muse2016 or later headbands
 * this will return false on Android and iOS.  For \muse2016 or later headbands on
 * Windows, this will return true if the headband is paired with the OS and
 * false if it is not.
 *
 * \return \c true if the Muse is paired with the OS, \c false otherwise.
 */
- (BOOL)isPaired;

/**
 * Returns true if the Muse is connectable, false otherwise.
 * This will always return true for \muse2014.  For \muse2016 or later headbands
 * this will return true on Android and iOS.  For \muse2016 or later headbands on
 * Windows, this will return true if the headband is advertising it is
 * connectable, false if it is not.
 *
 * \return \c true if the Muse is connectable, \c false otherwise.
 */
- (BOOL)isConnectable;

/**
 * Allows forwarding of license data from cloud.
 *
 * \param data The encrypted license blob.
 */
- (void)setLicenseData:(nonnull NSData *)data;

/**
 * Enable/disable libmuse to rethrow any exceptions caught in your app code
 * from the various listeners. For example, if there is a bug in your data
 * listener code that results in an exception. Libmuse will catch that and
 * it can rethrow that to cause your app to crash if enabled. Or if disabled
 * it will swallow that exception and prevent the app from crashing. It is
 * useful to enable this in development to help track down any bugs in your
 * code more easily. It is best to disable this in production code to prevent
 * your app from crashing. If this method is not called, the default is disabled.
 * \param enable \c true to enable exception to be thrown. \c false to disable.
 */
- (void)enableException:(BOOL)enable;

@end
