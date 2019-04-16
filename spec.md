# Cactusd Design Spec

## int global constants
- *something about connecting to the other arduino: MAC address??????????*
- #define CHEAT_BUZZ_LENGTH 2000

## global variables
- state THIS_STATE
- state OTHER_STATE
- int CHEAT_START_TIME

## enumerations
```
state {
  UP,
  DOWN
}
```

## functions

`int initializeBLE()`
- Start BLE server/client depending on compile flags
- returns: 0 on success

`int calibrate(int &calibrationValue)`
- set amount of force when foot is up
- returns: 0 on success

`int checkBtConnection()`
- make sure that this client can reach the server
- if not connected then do some special buzz thing to warn the user
- BLOCKING
- returns: 0 on success

`bool footDown()`
`bool footUp()`
- return true if the foot is in that position

`int checkStateChange()`
- if state changed, make BT request notifying other foot (notifyStateChange())
- return 0 if not changed
- return 1 if changed

`int notifyStateChange()` //Not in current version
- send BT request with new state to other server
- return 0 if response OK

`bool cheating(int sem)`
- check if both states are up
- call notifyCheating()
- call startBuzz()
- return 0 if NOT cheating
- return 1 if cheating

`int startBuzz()`
- set CHEAT_START_TIME
- turn on buzzer
- If already buzzing, continue
- return 0

`int stopBuzz()`
- turn off buzzer
- return 0

`int notifyCheating()` //Not in current version
- send BT request to start buzzing
- return 0 on acknowledgment

`int checkBuzzEnd()`
- check cheating()
- if not cheating, check current time >= CHEAT_START_TIME + CHEAT_BUZZ_LENGTH,
- then stop

