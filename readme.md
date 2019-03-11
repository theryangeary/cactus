# Cactusd: A Cheating Triggered User-friendly Speedwalking Device

## How to build
1. Install Arduino IDE
2. Install https://github.com/espressif/arduino-esp32.git
3. Add `export ESP_ROOT=/path/to/espressif/arduino-esp32` to your shell's init
   script (or specify it each time you run make)
4. Use either `CPP_EXTRA="-DSERVER"` or `CPP_EXTRA="-DCLIENT"` when running
   make.
```shell
# build
$ make CPP_EXTRA="-DSERVER"
# build and flash
$ make CPP_EXTRA="-DSERVER" flash
# build and flash on Windows (change COM port to match)
$ make CPP_EXTRA="-DSERVER" UPLOAD_PORT=COM4 flash
# build, flash, and connect to serial monitor
$ make CPP_EXTRA="-DSERVER" run
# clean
$ make clean
```
