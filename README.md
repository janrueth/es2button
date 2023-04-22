# es2button
This projects provides means to make use of buttons on epson scanners.

Please note that the code right now is just hacked together and is still the first thing that I wrote while trying to figure out how to get this working. So don't expect this to be polished, nice or be able to handle every corner case that I haven't thought of (yet).

## Why
I could not seem to get `scanbd` and friends working on my Epson (DS-310) scanner. After looking through the driver code I figured I will never as the buttons are just not exposed.

## How does this work?
It uses the official EPSON `epsonscan2` libraries to connect to the scanner and listen for the buttons.

When it detects a button press, it will:
* Disconnect from the scanner (allowing other programs to access it)
* Call a program that is passed to `es2button` with a series of environment variables that describe the scanner's state and buttons (see `example/example-epsonscan2.sh`)
* When the program exists, reconnect to the scanner and repeat
* When the scanner disconnects, the program exists

# Build

## Required libraries
This requires boost headers, libusb and [nlohman-json](https://github.com/nlohmann/json). On a debian system you'll just need to install `libboost-dev nlohmann-json3-dev libusb-1.0-0 libusb-1.0-0-dev`.

It will also require the `epsonscan2` library headers but cmake will download these during the build.

## Building
To prepare the build run
```
cmake . -B build
```
This will download the [epsonscan2](https://support.epson.net/linux/src/scanner/epsonscan2/) source and generate a Makefile in `./build`.

To then build `es2button`, run

```
make -C build
```

A debian package can be generated using
```
make -C build package
```

The final deb file is placed in `build/artifacts/`.


## Installation
You can either use
```
make -C build install
```

or install the produced deb file using `dpkg -i`.

The following section explains how `es2button` is integrated into the system.

### Integration through udev & systemd
See [udev-es2button.rules](resources/udev-es2button.rules) and [systemd.service](resources/systemd.service) for how to listen to usb events and call systemd to launch `es2button`.

* `udev-es2button.rules` will be installed to `/lib/udev/rules.d/61-es2button.rules` and act upon `epsonscan2` scanner detections that `epsonscan2` installs at `/lib/udev/rules.d/60-epsonscan2.rules`.
* udev will activate the `systemd.service` that is installed to `/lib/systemd/system/es2button@.service` when it detects a device supported by `epsonscan2`. It passes a device identifier as an instance variable to instantiate the service to systemd.
* By default, systemd's `es2button` instance will execute `/etc/es2button/entrypoint` on button press which, by default, symlinks to [/etc/es2button/default](resources/default.sh). This, in turn, just logs information about the requested button action (see `journalctl -f` while pushing the button to see the output).
* One can remove the symlink and add another **executable** file there which will not be overriden by the package installer. I've added the following entrypoint for my personal `paperless-ngx` installation:
```
#!/bin/bash

# change working dir
pushd /opt/paperless/consume
# example-epsonscan2.sh will output to $(pwd)/img%d.pdf (must be writable for root:scanner)
/usr/share/es2button/example/example-epsonscan2.sh
popd
```

## License

<img align="right" src="https://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The project is licensed under the [MIT License](https://opensource.org/licenses/mit):

Copyright &copy; 2023 Jan Rüth

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

* * *

This project itself makes use of [JSON for Modern C++](https://github.com/nlohmann/json) by [Niels Lohmann](https://nlohmann.me/) which is also licensed under the [MIT License](https://opensource.org/licenses/mit) (see above).

This project itself links to [libusb](https://github.com/libusb/libusb) which is licensed under the [LGPL-2.1](https://opensource.org/license/lgpl-2-1/).

This project itself requires headers from [epsonscan2](https://support.epson.net/linux/en/epsonscan2.php) as it dynamically loads (`dlopen`) a one of its libraries during runtime. `epsonscan2` itself is licensed under [LGPL-2.1](https://opensource.org/license/lgpl-2-1/).

This project itself requires header from the [boost library](https://www.boost.org/) which itself is licensed under the [Boost Software License - Version 1.0](https://www.boost.org/LICENSE_1_0.txt).

# TODO
* Restructure/Rewrite the code and split functionality into seperate classes and files
* Get rid of having to download the epsonscan2 data and have just a small header that describes the API without all the special epson type defs.