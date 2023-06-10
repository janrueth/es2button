#!/bin/bash

echo "Button ${ES2_BUTTON_NUM} pressed on ${ES2_DEV} (${ES2_DEV_MODEL}) (VID:PID=${ES2_DEV_VID}:${ES2_DEV_PID})"

if [[ ! ${ES2_DOC_PRESENT} = "Yes" ]]
then
    exit
fi

echo "Starting scan"

pid_as_dec=$(echo "ibase=16; ${ES2_DEV_PID}" | bc)
    

if [[ ${ES2_CARD_SCANNING} = "No" ]]
then
    echo "Scanning A4 paper"
    # epsonscan2:Name:bus:dev:protocol:transport:model:pid_as_decimal
    # protocol=esci2 only supported by sane
    # transport=usb only supported
    scanimage -d epsonscan2:${ES2_DEV}:esci2:usb:${ES2_DEV_MODEL}:${pid_as_dec} --duplex=yes --resolution=400 --scan-area A4 --deskew=yes -b "img%d.jpeg"
else
    echo "Scanning plastic card"
    scanimage -d epsonscan2:${ES2_DEV}:esci2:usb:${ES2_DEV_MODEL}:${pid_as_dec} --duplex=yes --resolution=400 --scan-area PlasticCard --deskew=yes -b "card%d.jpeg"
fi

echo "Finished scan"