# Example

This folder contains example scripts that can be used with es2button.

Please note that the script needs to have executable permissions (`chmod +x`).

The files demonstrates the available environment variables that `es2button` populates when calling the script.

## example-epsonscan2.sh
This example scans an A4 paper using `epsonscan2` with the `a4_preset.SF2` or when the scanner reports it is in card scanning mode, it uses `card_preset.SF2`

### Presets
Just a note on the presets. These are essentially just `json` config files for `epsonscan2`. `epsonscan2` isn't very good at validating the contents of these files and will simply stop parsing on failures but not abort. This usually leads to not producing any output. I recommend running them through `jq` to see if they are valid after making an edit.

Using the `epsonscan2` commandline to create a default config resulted for me in a config that didn't work out of the box, it had some values left unset (like jpeg quality) that are required. I ended up running the QT UI tool to create a config to get an idea what is required.

The values of the differnt fields are everything but self-explanatory. I've added some comments on `card_preset_png_via_custom_size.SF2` but generally I recommend looking into the `epsonscan2` code in `src/Standalone/capitem.h` and `src/Include/Controller/EpsonScan2.h`.

## example-scanimage.sh
This is suppsed to do essentially the same as the `example-epsonscan2.sh` but using sane's `scanimage`. I haven't really tested this yet.
