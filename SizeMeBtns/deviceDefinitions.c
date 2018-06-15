//
//  deviceDefinitions.c
//  SizeMeBtns
//
//  Created by Jaran F on 24/05/2018.
//
#include <string.h>		/* strcpy   */
#include "deviceDefinitions.h"
#define kDevicesArrayLen            13
struct DeviceDefn* getDevices();

struct WHPixelDims {
    int width;
    int height;
};
struct DeviceDefn {
    char deviceName[15];
    struct WHPixelDims pixelDims;
    float diagonalScreenSize;
    int ppi;
};

struct DeviceDefn* getDevices() {
    struct DeviceDefn device;
    struct DeviceDefn devicesArray[kDevicesArrayLen];
    struct DeviceDefn* devPointer;
    int i = 0;
    strcpy(device.deviceName, "iPhone 5");
    device.pixelDims.width = 320;
    device.pixelDims.height = 568;
    device.diagonalScreenSize = 4;
    device.ppi = 326;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 5s");
    device.pixelDims.width = 320;
    device.pixelDims.height = 568;
    device.diagonalScreenSize = 4;
    device.ppi = 326;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 5c");
    device.pixelDims.width = 320;
    device.pixelDims.height = 568;
    device.diagonalScreenSize = 4;
    device.ppi = 326;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 5SE");
    device.pixelDims.width = 320;
    device.pixelDims.height = 568;
    device.diagonalScreenSize = 4;
    device.ppi = 326;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 6");
    device.pixelDims.width = 375;
    device.pixelDims.height = 667;
    device.diagonalScreenSize = 4.7;
    device.ppi = 326;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 6s");
    device.pixelDims.width = 375;
    device.pixelDims.height = 667;
    device.diagonalScreenSize = 4.7;
    device.ppi = 326;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 7");
    device.pixelDims.width = 375;
    device.pixelDims.height = 667;
    device.diagonalScreenSize = 4.7;
    device.ppi = 326;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 8");
    device.pixelDims.width = 375;
    device.pixelDims.height = 667;
    device.diagonalScreenSize = 4.7;
    device.ppi = 326;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 6+");
    device.pixelDims.width = 414;
    device.pixelDims.height = 736;
    device.diagonalScreenSize = 5.51;
    device.ppi = 401;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 6s+");
    device.pixelDims.width = 414;
    device.pixelDims.height = 736;
    device.diagonalScreenSize = 5.5;
    device.ppi = 401;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 7+");
    device.pixelDims.width = 414;
    device.pixelDims.height = 736;
    device.diagonalScreenSize = 5.5;
    device.ppi = 401;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone 8+");
    device.pixelDims.width = 414;
    device.pixelDims.height = 736;
    device.diagonalScreenSize = 5.5;
    device.ppi = 401;
    devicesArray[i++] = device;
    
    strcpy(device.deviceName, "iPhone X");
    device.pixelDims.width = 375;
    device.pixelDims.height = 812;
    device.diagonalScreenSize = 5.8;
    device.ppi = 458;
    devicesArray[i++] = device;
    
     printf("\n++++++++++\n%s\n~~~~~~~~\n", devicesArray[12].deviceName);
     //device.deviceName        devicesLookupPointer[0].deviceName);
    devPointer = &(devicesArray[0]);
    return devPointer;
}
