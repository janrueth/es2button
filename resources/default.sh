#!/bin/bash

echo "Button ${ES2_BUTTON_NUM} pressed on ${ES2_DEV} (VID:PID=${ES2_DEV_VID}:${ES2_DEV_PID})"
echo "Document preset: ${ES2_DOC_PRESENT}"
if [[ ${ES2_DOC_PRESENT} = "Yes" ]]
then
    echo "Card scanning: ${ES2_CARD_SCANNING}"
fi

echo "BYE!"
