#!/bin/bash

if [[ "${HOME:-unset}" = "unset" ]]; then
    # epsonscan2 will fail if HOME env is unset, so just set it
    export HOME="/tmp/"
fi

echo "Button ${ES2_BUTTON_NUM} pressed on ${ES2_DEV} (${ES2_DEV_MODEL}) (VID:PID=${ES2_DEV_VID}:${ES2_DEV_PID})"

if [[ ! ${ES2_DOC_PRESENT} = "Yes" ]]
then
    exit
fi

echo "Starting scan"
if [[ ${ES2_CARD_SCANNING} = "No" ]]; then
    echo "Scanning A4 paper"
    epsonscan2 -s ${ES2_DEV} $(dirname $0)/a4_preset.SF2
else
    echo "Scanning plastic card"
    epsonscan2 -s ${ES2_DEV} $(dirname $0)/card_preset.SF2
fi

echo "Finished scan"