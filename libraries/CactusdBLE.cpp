/*
 * Bluetooth Low Energy library for cactusd
 */

#include "BLEDevice.h"
#include "CactusdBLE.h"

#ifdef CLIENT

// The remote service we wish to connect to.
static BLEUUID serviceUUID(SERVICE_UUID);
// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID(CHARACTERISTIC_UUID);

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;

static void notifyCallback(
    BLERemoteCharacteristic* pBLERemoteCharacteristic,
    uint8_t* pData,
    size_t length,
    bool isNotify) {
  Serial.print("Notify callback for characteristic ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
  Serial.print("data: ");
  Serial.println((char*)pData);
}


class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
    connected = true;
    Serial.println("Connected");
  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("Disconnected");
  }
};

/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;

    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks

bool connectToServer(
    BLEClient** pClient,
    BLERemoteService** pRemoteService,
    BLERemoteCharacteristic** pRemoteCharacteristic) {
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());

  (*pClient) = BLEDevice::createClient();
  Serial.println(" - Created client");

  (*pClient)->setClientCallbacks(new MyClientCallback());

  // Connect to the remove BLE Server.
  (*pClient)->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");

  // Obtain a reference to the service we are after in the remote BLE server.
  (*pRemoteService) = (*pClient)->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    (*pClient)->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

  // Obtain a reference to the characteristic in the service of the remote BLE server.
  (*pRemoteCharacteristic) = (*pRemoteService)->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID.toString().c_str());
    (*pClient)->disconnect();
    return false;
  }
  Serial.println(" - Found our characteristic");

  // Read the value of the characteristic.
  if((*pRemoteCharacteristic)->canRead()) {
    std::string value = (*pRemoteCharacteristic)->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());
  }

  if((*pRemoteCharacteristic)->canNotify()) {
    (*pRemoteCharacteristic)->registerForNotify(notifyCallback);
    Serial.println(" - Registered for notifications");
  }

  connected = true;
}
#endif

void bleTest() {
  Serial.println("ble included");
  return;
}

BLEConnection::BLEConnection() {
  Serial.println("Initializing BLE...");
#ifdef SERVER
  Serial.println("I'm server");
  BLEDevice::init("CACTUSD");
  this->server = BLEDevice::createServer();
  this->service = this->server->createService(SERVICE_UUID);
  this->characteristic = (MyBLECharacteristic*) this->service->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY |
      BLECharacteristic::PROPERTY_INDICATE
      );

  this->characteristic->setNotifyProperty(true);
  this->characteristic->setValue("1");
  this->service->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();
#endif

#ifdef CLIENT
  Serial.println("I'm client");

  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);

  while(!connectToServer(&this->client, &this->service, &this->characteristic)) {
    Serial.println("Trying to connect...");
  }
#endif
}

int BLEConnection::getStatus() {
#ifdef CLIENT
  return connected;
#else
  return -1;
#endif
}

