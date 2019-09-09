
# ビルド手順

```
git clone --recurse-submodules git@github.com:gamiyama3110/qmk_firmware.git
cd qmk_firmware
docker run -e keymap=gamiyama -e subproject=ez -e keyboard=ergodox --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware
```

# Teensy2.0
http://www.pjrc.com/teensy/loader_mac.html

