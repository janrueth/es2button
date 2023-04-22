# ES2Button

By default `/etc/es2button/entrypoint` is executed from `es2button` via udev (detects) -> systemd (runs) -> button press (es2button) -> entrypoint.

By default, this links to `/etc/es2button/default`. You can override `/etc/es2button/entrypoint` to something else which will be preserved by updates to this package.

You can customize the file to your desire.

See also `/usr/share/es2button/example` for inspiration.