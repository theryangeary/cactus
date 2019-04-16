/*
 * Bluetooth Low Energy library for cactusd
 */

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "Common.h"
#include "Arduino.h"

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void bleTest();
int initializeBLE();
bool connectToServer();

class MyAdvertisedDeviceCallbacks;

class MyBLECharacteristic : public BLECharacteristic {
  public:
    std::string readValue() {
      return this->getValue();
    }

    void writeValue(std::string value) {
      this->setValue(value);
    }
};

class CallbackHandler: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pCharacteristic) {
    cheating(atoi(pCharacteristic->getValue().c_str()));
  }
};

class BLEConnection {
  BLEServer* server;
  BLEClient* client;
  BLEDevice* device;

  public:
  BLEConnection();
  int getStatus();
  std::string readCharacteristic(std::string charUUID);
  void writeCharacteristic(std::string charUUID, std::string newValue);
  void semInc();
  void semDec();

#ifdef SERVER
  BLEService* service;
  MyBLECharacteristic* characteristic;
#endif

#ifdef CLIENT
  BLERemoteService* service;
  BLERemoteCharacteristic* characteristic;
#endif

};
