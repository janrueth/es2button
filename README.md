# es2button
This projects provides means to make use of buttons on epson scanners.

## Requirements
You need to install [epsonscan2](https://support.epson.net/linux/en/epsonscan2.php). If,like me, you want to use this on an arm64 and can't find a suitable package, please see [my epsonscan2 builder](https://github.com/janrueth/epsonscan2).

## Why
I could not seem to get `scanbd` and friends working on my Epson (DS-310) scanner. After looking through the driver code I figured I will never as the buttons are just not exposed.

## How does this work?
It uses the official EPSON [epsonscan2](https://support.epson.net/linux/en/epsonscan2.php) libraries to connect to the scanner and listen for the buttons.

When it detects a button press, it will:
* Disconnect from the scanner (allowing other programs to access it)
* Call a program that is passed to `es2button` with a series of environment variables that describe the scanner's state and buttons (see `example/example-epsonscan2.sh`)
* When the program exists, reconnect to the scanner and repeat
* When the scanner disconnects, the program exists

# Build

## Requirements
You need [Rust](https://rustup.rs/) (tested on 1.77). In addition, you will need to install a couple of dependencies that we need during building: `pkg-config`, a C compiler (e.g., `clang`), `libusb` (library and headers), and `make` if you decide to build with make.

On a debian system you'll just need to install:
```
pkg-config
make
clang
libusb-1.0-0
libusb-1.0-0-dev
```

See also [Dockerfile](./Dockerfile) or run `make enter-docker` to get into a build environment that can build `es2button`.


## Building
To build a debian package, simply run `make`.
The final deb file is placed in `target/debian/`.

Alternatively, you can also build using cargo. See the [Makefile](./Makefile) how `cargo` should be invoked.


## Installation
You can install the generated deb file using `dpkg -i`.

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

This project itself links to [libusb](https://github.com/libusb/libusb) which is licensed under the [LGPL-2.1](https://opensource.org/license/lgpl-2-1/).

This project itself uses headers from [epsonscan2](https://support.epson.net/linux/en/epsonscan2.php) as it dynamically loads (`dlopen`) a one of its libraries during runtime. `epsonscan2` itself is licensed under [LGPL-2.1](https://opensource.org/license/lgpl-2-1/).
The headers are bundled with this source and are located in `es2command-sys/cinterface`.
