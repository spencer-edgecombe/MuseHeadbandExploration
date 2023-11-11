// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from packets.djinni

#import "Muse/api/IXNAccelerometer.h"
#import "Muse/api/IXNBattery.h"
#import "Muse/api/IXNDrlRef.h"
#import "Muse/api/IXNEeg.h"
#import "Muse/api/IXNGyro.h"
#import "Muse/api/IXNMagnetometer.h"
#import "Muse/api/IXNMuseDataPacketType.h"
#import "Muse/api/IXNPpg.h"
#import "Muse/api/IXNPressure.h"
#import "Muse/api/IXNUltraViolet.h"
#import <Foundation/Foundation.h>
@class IXNMuseDataPacket;


/**
 * Contains information received from the headband.
 * Each packet can represent different data: eeg,
 * accelerometer, quantization, etc.
 * Take a look at \classlink{MuseDataPacketType}
 * enum for all possible types
 */
@interface IXNMuseDataPacket : NSObject

/**
 * Create a new packet with reserved capacity but unspecified contents.
 * \param capacity the number of data entries to reserve.
 */
+ (nullable IXNMuseDataPacket *)makeUninitializedPacket:(int64_t)capacity;

/**
 * Create a new packet with the given contents.
 * \param type the type of packet to create
 * \param timestamp the timestamp of the packet
 * \param values the data the packet contains.
 */
+ (nullable IXNMuseDataPacket *)makePacket:(IXNMuseDataPacketType)type
                                 timestamp:(int64_t)timestamp
                                    values:(nonnull NSArray<NSNumber *> *)values;

/**
 * Specifies what kind of values are stored in the packet.
 * \return the type of packet.
 */
- (IXNMuseDataPacketType)packetType;

/**
 * Microseconds since epoch (usually Jan 1, 1970).
 * \return the timestamp of the packet expressed in microseconds since epoch.
 */
- (int64_t)timestamp;

/**
 * Raw packet data as an array. The size of this array and the meaning of
 * its elements depend on the packet type. See the documentation for
 * \classlink{MuseDataPacketType} for details.
 *
 * Note that this method causes new memory to be allocated for an array of
 * boxed double values. If this impacts your application's performance, you
 * should use get_xxx_value() methods instead.
 *
 * \deprecated Use
 * \functionlink{MuseDataPacket,getAccelerometerValue,get_accelerometer_value},
 * \functionlink{MuseDataPacket,getBatteryValue,get_battery_value},
 * \functionlink{MuseDataPacket,getDrlRefValue,get_drl_ref_value},
 * \functionlink{MuseDataPacket,getEegChannelValue,get_eeg_channel_value},
 * \functionlink{MuseDataPacket,getPpgChannelValue,get_ppg_channel_value},
 * \functionlink{MuseDataPacket,getGyroValue,get_gyro_value}
 * instead.
 */
- (nonnull NSArray<NSNumber *> *)values;

/**
 * Get the number of values in this packet.
 * \return the number of data values in this packet.
 */
- (int64_t)valuesSize;

/**
 * Get the raw EEG or EEG derived value from the packet.
 * EEG derived value are data that is calculated based on the raw EEG values.
 * Take a look at enum in \classlink{MuseDataPacketType} for values derived from EEG channel.
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 * \if ANDROID_ONLY
 * \param channelNum the EEG channel to retrieve. (ie. \link com.choosemuse.libmuse.Eeg.EEG1 Eeg.EEG1\endlink)
 * \elseif IOS_ONLY
 * \param channelNum the ::IXNEeg channel to retrieve (ie. \link IXNEeg IxnEegEEG1 \endlink)
 * \elseif WINDOWS_ONLY
 * \param channelNum the
 * \link ::interaxon::bridge::Eeg Eeg\endlink
 * channel to retrieve (ie. Eeg::EEG1)
 * \else
 * MISSING_DOCUMENTATION
 * \endif
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,EEG,IXNMuseDataPacketTypeEeg},
 * LibMuse will throw an exception. Use
 * \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this function.
 */
- (double)getEegChannelValue:(IXNEeg)channelNum;

/**
 * Get the PPG value from the packet.
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 * \if ANDROID_ONLY
 * \param channelNum the PPG channel to retrieve. (ie. \link com.choosemuse.libmuse.Ppg.AMBIENT Ppg.IR Ppg.RED\endlink)
 * \elseif IOS_ONLY
 * \param channelNum the ::IXNPpg channel to retrieve (ie. \link IXNPpg IxnPpgIR \endlink)
 * \elseif WINDOWS_ONLY
 * \param channelNum the
 * \link ::interaxon::bridge::Ppg Ppg\endlink
 * channel to retrieve (ie. Ppg::AMBIENT)
 * \else
 * MISSING_DOCUMENTATION
 * \endif
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,PPG,IXNMuseDataPacketTypePpg},
 * LibMuse will throw an exception. Use
 * \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this function.
 */
- (double)getPpgChannelValue:(IXNPpg)channelNum;

/**
 * Get the \classlink{Battery} value from the packet.
 *
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 *
 * \param b the \classlink{Battery} value to retrieve (ie. \enumlink{Battery,MILLIVOLTS,IXNBatteryMillivolts})
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,BATTERY,IXNMuseDataPacketTypeBattery},
 * LibMuse will throw an exception. Use \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this function.
 */
- (double)getBatteryValue:(IXNBattery)b;

/**
 * Get the \classlink{Accelerometer} value from the packet.
 *
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 *
 * \param a the \classlink{Accelerometer} value to retrieve (ie. \enumlink{Accelerometer,X,IXNAccelerometerX})
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,ACCELEROMETER,IXNMuseDataPacketTypeAccelerometer},
 * LibMuse will throw an exception. Use \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this function.
 */
- (double)getAccelerometerValue:(IXNAccelerometer)a;

/**
 * Get the \classlink{Gyro} value from the packet.
 *
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 *
 * \param g the \classlink{Gyro} value to retrieve (ie. \enumlink{Gyro,X,IXNGyroX})
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,GYRO,IXNMuseDataPacketTypeGyro},
 * LibMuse will throw an exception. Use
 * \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this
 * function.
 */
- (double)getGyroValue:(IXNGyro)g;

/**
 * Get the \classlink{Magnetometer} value from the packet.
 *
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 *
 * \param m the \classlink{Magnetometer} value to retrieve (ie. \enumlink{Magnetometer,X,IXNMagnetometerX})
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,MAGNETOMETER,IXNMuseDataPacketTypeMagnetometer},
 * LibMuse will throw an exception. Use
 * \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this
 * function.
 */
- (double)getMagnetometerValue:(IXNMagnetometer)m;

/**
 * Get the \classlink{DrlRef} value from the packet.
 *
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 * \param drl the \classlink{DrlRef} value to retrieve (ie. \enumlink{DrlRef,DRL,IXNDrlRefDrl})
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,DRL_REF,IXNMuseDataPacketTypeDrlRef},
 * LibMuse will throw an exception. Use
 * \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this
 * function.
 */
- (double)getDrlRefValue:(IXNDrlRef)drl;

/**
 * Get the \classlink{Pressure} value from the packet.
 *
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 *
 * \param pressure the \classlink{Pressure} value to retrieve (ie. \enumlink{Pressure,AVERAGED,IXNPressureAveraged})
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,PRESSURE,IXNMuseDataPacketTypePressure},
 * LibMuse will throw an exception. Use
 * \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this
 * function.
 */
- (double)getPressureValue:(IXNPressure)pressure;

/**
 * Get the temperature value from the packet.
 *
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 *
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,TEMPERATURE,IXNMuseDataPacketTypeTemperature},
 * LibMuse will throw an exception. Use
 * \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this
 * function.
 */
- (double)getTemperatureValue;

/**
 * Get the \classlink{UltraViolet} value from the packet.
 *
 * Calling this function does not perform additional allocations and is preferable to using
 * values().
 *
 * \param v the \classlink{UltraViolet} value to retrieve (ie. \enumlink{UltraViolet,UVA,IXNMagnetometerUVA})
 * \return the value requested.
 * \exception SIGABRT
 * If this function is called on a packet type that is not type
 * \enumlink{MuseDataPacketType,ULTRAVIOLET,IXNMuseDataPacketTypeUltraViolet},
 * LibMuse will throw an exception. Use
 * \inlinelink{packetType(),::IXNMuseDataPacket::packetType(),packet_type()}
 *  to check the type before calling this
 * function.
 */
- (double)getUvValue:(IXNUltraViolet)v;

@end
