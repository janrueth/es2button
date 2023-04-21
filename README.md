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

## Todos

* Create udev rules that automatically activate and stop the service (does this require running as a daemon?)
* Restructe the code and split functionality into seperate classes and files
* Reorganize repo structure and move code into separate folder
* Add a license to the repo, can this be MIT with the epsonscan2 code, what license is their code?
* Get rid of having to download the epsonscan2 data and have just a small header that describes the API without all the special epson type defs.