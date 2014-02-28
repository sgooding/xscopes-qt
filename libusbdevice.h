#ifndef LIBUSBDEVICE_H
#define LIBUSBDEVICE_H
#include <QObject>
#include <QFuture>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtConcurrent/QtConcurrent>
#define NOMINMAX
#else
#include <QtConcurrentRun>
#endif
#include "libusb.h"
#include "libusbdeviceinfo.h"
#include <QDebug>

typedef uint8_t byte;


class LibUsbDevice : public QObject
{
    Q_OBJECT
public:
    explicit LibUsbDevice(QObject *parent = 0);
    void initializeDevice();
    void openDevice();
    void closeDevice();
    void eventThread();
    bool controlReadTransfer(uint8_t command, uint16_t value = 0, uint16_t index = 0 );
    void asyncBulkReadTransfer();
    void awgBulkWriteTransfer();
    void controlWriteTransfer(uint16_t index, uint8_t value);
    QString requestFirmwareVersion();
    void stopScope();
    void startScope();
    void forceTrigger();
    void autoSetup();
    void saveAWG();
    void saveDeviceSettings();
    void restoreSettings();


    QString getStringFromUnsignedChar( unsigned char *,int);

public:
    bool isDeviceConnected,isInitialiazed;
    QString cstatus;
    libusb_device **devs;
    libusb_device *deviceFound;
    libusb_device *dev;
    libusb_device_descriptor deviceDesc;
    libusb_device_handle *deviceHandle;
    libusb_context *context;
    libusb_hotplug_callback_handle hotplugHandle[2];
    struct libusb_transfer *pcToUsbDeviceTransfer;
    struct libusb_transfer *usbDeviceToPcTransfer;
    bool dataAvailable;
    int count, dataLength;
    uint8_t chData[LEN_BULK_IN_BUFFER];
    byte inBuffer[LEN_CONTROL_BUFFER];
    byte awgBuffer[256];
    bool enableEventThread,hasHotPlugSupport;
    QFuture<void> future;
    
signals:
    
public slots:
    
};

#endif // LIBUSBDEVICE_H
