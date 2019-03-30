/*
 * Bluetooth Low Energy library for cactusd
 */

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "Arduino.h"

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void bleTest();
int initializeBLE();
bool connectToServer();

class MyAdvertisedDeviceCallbacks;

class BLEConnection {
  BLEServer* server;
  BLEClient* client;
  BLEDevice* device;
  BLEService* service;
  BLERemoteService* remoteService;
  BLERemoteCharacteristic* remoteCharacteristic;
  int status;

  public:
  BLEConnection();
  int getStatus();
};
