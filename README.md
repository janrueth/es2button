# es2button
This projects provides means to make use of buttons on epson scanners.

## Why
I could not seem to get scanbuttond and friends working on my Epson (DS-310) scanner. After looking through the driver code I figured I will never as the buttons are just not exposed.

## How does this work?
It uses the `epsonscan2` libraries to connect to the scanner and listen for the buttons.

When it detects a button press, it will:
* Disconnect from the scanner
* Call a program that is passed to `es2button` with a series of environment variables that describe the scanner's state and buttons (see `example/test.sh`)
* When the program exists, reconnect to the scanner and repeat

