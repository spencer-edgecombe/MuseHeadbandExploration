// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from packets.djinni

#import <Foundation/Foundation.h>

/**
 * \if IOS_ONLY
 * \file
 * \endif
 * Represents the data mapping in a Gyro data packet<br>
 *
 * The gyro data is measured as the rotation about 3 axes which  as shown in the picture below:
 * \image html MuseAxes.png
 *
 * The axes are oriented to a Right Hand Coordinate System.<br>
 * Rotation about the X axis corresponds to tilting the head side to side.
 * Positive values increase when tilting to the right.  This is also known as roll.<br>
 * Rotation about the Y axis corresponds to tilting the head up and down.
 * Positive values increase when looking up.  This is also known as pitch.<br>
 * Rotation about the Z axis corresponds to looking left and right.
 * Positive values increase when looking to the right. This is also known as yaw.<br>
 * \sa \enumlink{MuseDataPacketType,GYRO,IXNMuseDataPacketTypeGyro}
 * \sa \functionlink{MuseDataPacket,getGyroValue,get_gyro_value}
 */
typedef NS_ENUM(NSInteger, IXNGyro)
{
    /**
     * Rotation about the X axis in degrees per second.
     * Rotation about the X axis corresponds to tilting the head side to side.
     * Positive values increase when tilting to the right.  This is also known as roll.<br>
     */
    IXNGyroX,
    /**
     * Rotation about the Y axis in degrees per second.
     * Rotation about the Y axis corresponds to tilting the head up and down.
     * Positive values increase when looking up.  This is also known as pitch.<br>
     */
    IXNGyroY,
    /**
     * Rotation about the Z axis in degrees per second.
     * Rotation about the Z axis corresponds to looking left and right.
     * Positive values increase when looking to the right.  This is also known as yaw.<br>
     */
    IXNGyroZ,
};
