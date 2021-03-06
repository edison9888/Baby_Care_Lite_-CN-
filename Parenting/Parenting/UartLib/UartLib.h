//
//  UartLib.h
//  UartLib
//
//  Created by xu jason on 12-12-14.
//  Copyright (c) 2012年 xu jason(jasonxu@vbenz.com). All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

typedef  enum {
    DISCONNECT = 0X00,
    CONNECTING,
    CONNECTED,
}ConnectStatus;

/***********************************
 Ble scan Delegate
 *************************************/
@protocol BleScanDelegate <NSObject>
- (void) peripheralItemRefresh;
- (void) peripheralStatePoweredOff;
@end


@protocol UartDelegate <NSObject>
/*!
 *  @method didScanedPeripherals:(NSMutableArray  *)foundPeripherals
 *
 *  @param foundPeripherals           A <code>foundPeripherals</code> object.
 *
 *  @discussion                 This method is invoked while scanning, upon the discovery 
 *
 */
- (void) didScanedPeripherals:(NSMutableArray  *)foundPeripherals;

/*!
 *  @method didConnectPeripheral:(CBPeripheral *)peripheral
 *
 *  @param peripheral   The <code>CBPeripheral</code> that has connected.
 *
 *  @discussion         This method is invoked when a connection initiated by @link UartLib:ConnectPeripheral: @/link has succeeded.
 *
 */
- (void) didConnectPeripheral:(CBPeripheral *)peripheral;




/*!
 *  @method didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
 *
 *  @param peripheral   The <code>CBPeripheral</code> that has disconnected.
 *  @param error        If an error occurred, the cause of the failure.
 *
 *  @discussion         This method is invoked upon the disconnection of a peripheral that was connected by @link UartLib:ConnectPeripheral: @/link. If the disconnection
 *                      was not initiated by @link UartLib:disconnectPeripheral: @/link, the cause will be detailed in the <i>error</i> parameter. 
 *
 */
- (void) didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

- (void) didReceiveData:(CBPeripheral *)peripheral recvData:(NSData *)recvData;

- (void) didWriteData:(CBPeripheral *)peripheral error:(NSError *)error;
@end


@interface UartLib : NSObject <BleScanDelegate>

@property (nonatomic, assign) id<UartDelegate> uartDelegate;

/*!
 *  @method scanStart
 *
 *  @discussion         Starts scanning for peripherals.
 *
 */
- (void) scanStart;

/*!
 *  @method scanStop
 *
 *  @discussion         Stops scanning for peripherals.
 *
 */
- (void) scanStop;

/*!
 *  @method connectPeripheral:(CBPeripheral*)peripheral
 *
 *  @param peripheral   The <code>CBPeripheral</code> to be connected.
 *
 *  @discussion         Initiates a connection to <i>peripheral</i>. Connection attempts never time out and, depending on the outcome, will result in a call to either @link UartLib:didConnectPeripheral: @/link or 
        @link UartLib:didDisconnectPeripheral:error: @/link.
 *                      Pending attempts are cancelled automatically upon deallocation of <i>peripheral</i>, and explicitly via @link cancelPeripheralConnection @/link.
 *
 *
 */
- (void) connectPeripheral:(CBPeripheral*)peripheral;


/*!
 *  @method disconnectPeripheral:(CBPeripheral*)peripheral
 *
 *  @param peripheral   A <code>CBPeripheral</code>.
 *
 *  @discussion         Cancels an active or pending connection to <i>peripheral</i>. Note that this is non-blocking, and any <code>CBPeripheral</code>
 *                      commands that are still pending to <i>peripheral</i> may or may not complete.
 *
 */
- (void) disconnectPeripheral:(CBPeripheral*)peripheral;


/*!
 *  @method sendValue:(CBPeripheral*)peripheral sendData:(NSData *)data type:(CBCharacteristicWriteType)type
 *
 *  @param peripheral   A <code>CBPeripheral</code>.
 *  @param data				The value to write.
 *  @param type				The type of write to be executed.
 *
 *  @discussion				Writes <i>value</i> to <i>CBPeripheral</i>.
 *
 */
- (void)sendValue:(CBPeripheral*)peripheral sendData:(NSData *)data type:(CBCharacteristicWriteType)type;

@end
