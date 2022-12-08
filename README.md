![alt text](https://raw.githubusercontent.com/apiel/attiny-midi2cv/main/usbmidi2cv.jpg)

Install:

```
http://digistump.com/package_digistump_index.json
```

Install `Digistump AVR Boards`
Use board `Digispark (Default - 16.5mhz)`

Click upload and only then plug the board.

Fix: micronucleus: library/micronucleus_lib.c:66: micronucleus_connect

See https://www.youtube.com/watch?v=ZRI1n9KcXuE

```
sudo usermod -a -G dialout {your username}
```

if this don't work then 

Create a file named `/etc/udev/rules.d/digispark.rules`  with the following line in it:

```
SUBSYSTEM=="usb", ATTR{idVendor}=="16d0", ATTR{idProduct}=="0753", MODE="0660", GROUP="dialout"
```


For the midilib, use my fork of DigisparkMIDI: `git@github.com:apiel/DigisparkMIDI.git`
And checkout branch `ifndef-usbFunctionWriteOut` to be able to use `#define DIGIMIDI_WRITEOUT 1`
Else need to modify file `DigiMIDI.h`
