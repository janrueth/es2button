#!/bin/bash

modelFromPid() {
    # Is there a simpler way?
    if [[ ! -f .lut.json ]]
    then
        find /usr/lib/$(uname -m)-linux-gnu/epsonscan2/Resources/Models/ | grep -E "/ES[^/.]+\.json$" | xargs -I {} jq '{"model": "'{}'", "PID": .HardwareInfo[0].ESProductID.string}' {} > .lut.json
    fi
    cat .lut.json | jq -r 'select(.PID=="$1") | .model' | xargs basename -s.json | sort | uniq | head -n1
}

echo "Button ${ES2_BUTTON_NUM} pressed on ${ES2_DEV} (VID:PID=${ES2_DEV_VID}:${ES2_DEV_PID})"

if [[ ! ${ES2_DOC_PRESENT} = "Yes" ]]
then
    exit
fi

echo "Starting scan"

pid_as_dec=$(echo "ibase=16; ${ES2_DEV_PID}" | bc)
model=$(modelFromPid ${ES2_DEV_PID})
    

if [[ ${ES2_CARD_SCANNING} = "No" ]]
then
    echo "Scanning A4 paper"
    # epsonscan2:Name:bus:dev:protocol:transport:model_from_pid:pid_as_decimal
    # protocol=esci2 only supported by sane
    # transport=usb only supported
    # model_from_pid
    scanimage -d "epsonscan2:${ES2_DEV}:esci2:usb:ES${model}:${pid_as_dec}" --duplex=yes --resolution=400 --scan-area A4 --deskew=yes -b "img%d.jpeg"
else
    echo "Scanning plastic card"
    scanimage -d "epsonscan2:${ES2_DEV}:esci2:usb:ES${model}:${pid_as_dec}" --duplex=yes --resolution=400 --scan-area PlasticCard --deskew=yes -b "card%d.jpeg"
fi

echo "Finished scan"