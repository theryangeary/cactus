# Cactusd: A Cheating Triggered User-friendly Speedwalking Device

## How to build
1. Install Arduino IDE
2. Install https://github.com/espressif/arduino-esp32.git
3. Add `export ESP_ROOT=/path/to/espressif/arduino-esp32` to your shell's init
   script (or specify it each time you run make)
```shell
# build
$ make
# build and flash
$ make flash
# build and flash on Windows (change COM port to match)
$ make UPLOAD_PORT=COM4 flash
# clean
$ make clean
```
