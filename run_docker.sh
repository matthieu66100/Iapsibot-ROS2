#!/bin/bash

WEBOT_FILE="./dependencies/webots_2023b_amd64.deb"

if [ -f "$WEBOT_FILE" ]; then
    echo "LE FICHIER EST DEJA EN PLACE"
else
    echo "TELECHARGEMENT DU FICHIER WEBOTS..."
    cd ./dependencies
    wget https://github.com/cyberbotics/webots/releases/download/R2023b/webots_2023b_amd64.deb
fi

docker compose up

