# Practica1_IoT
Telephone with Embedded Linux and i.MX8mini-pico-pi boards.

Command to start talking/listening on the boards:
arecord -D hw:0 -c 2 -r 48000 -f s32_LE | ./lab1 192.168.1.180 | aplay -D plughw:1 -c 2 -r 48000 -f s32_LE

arecord -D hw:0 -c 2 -r 48000 -f s32_LE | ./lab1 192.168.1.12 | aplay -D plughw:1 -c 2 -r 48000 -f s32_LE


