# Practica1_IoT
Telephone with Embedded Linux and i.MX8mini-pico-pi boards.
This implementation uses a UDP socket to transmit audio between two i.MX8mini-pico-pi boards to simulate a telephone. The lab1 code receive as a parameter the microphone's audio buffer and send it to the audio buffer os the other board.
Further this implementation will have a machine state to control the states of the telephone with the buttons, to control the volume with threads and system() calling functions.

Command to start talking/listening on the boards:
arecord -D hw:0 -c 2 -r 48000 -f s32_LE | ./lab1 192.168.1.180 | aplay -D plughw:1 -c 2 -r 48000 -f s32_LE

arecord -D hw:0 -c 2 -r 48000 -f s32_LE | ./lab1 192.168.1.12 | aplay -D plughw:1 -c 2 -r 48000 -f s32_LE


