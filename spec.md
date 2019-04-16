# Cactusd Design Spec

## int global constants
- *something about connecting to the other arduino: MAC address??????????*
- #define CHEAT_BUZZ_LENGTH 2000

## functions

`int calibrate(int* calibrationValue)`
- set amount of force when foot is up
- returns: 0 on success

`getCheatEndTime()`
`setCheatEndTime()`

`bool footDown()`
`bool footUp()`
- return true if the foot is in that position

`bool getCurrentState()`
- return true if foot down and false if up

`bool getPreviousState()`
- return previous state (see getCurrentState)

`void updateState()`
- set STATE to getCurrentState

`bool checkStateChange()`
- return false if not changed
- return true if changed

`bool cheating(int sem)`
- return false if NOT cheating
- return true if cheating

`bool startBuzz()`
- turn on buzzer
- If already buzzing, continue
- return true on success

`bool stopBuzz()`
- turn off buzzer
- return true on success

`bool checkBuzzEnd()`
- stop buzzer if applicable
- return true on success

