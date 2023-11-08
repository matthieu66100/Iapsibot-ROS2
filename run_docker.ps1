$WEBOT_FILE = ".\dependencies\webots_2023b_amd64.deb"

if (Test-Path $WEBOT_FILE) {
    Write-Host "[INFO] : LE FICHIER EST DEJA EN PLACE"
} else {
    Write-Host "[INFO] : FICHIER NON EXISTANT, TELECHARGEMENT DE WEBOTS..."
    Set-Location -Path .\dependencies
    Invoke-WebRequest -Uri "https://github.com/cyberbotics/webots/releases/download/R2023b/webots_2023b_amd64.deb" -OutFile "webots_2023b_amd64.deb"
}

docker-compose up

