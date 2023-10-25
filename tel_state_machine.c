#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>



int main() {
    printf("Start opnening\n");
    int fd = open("/dev/input/event0", O_RDONLY);

    if (fd == -1) {
        perror("Error opening input device");
        exit(1);
    }

    struct input_event ev;

    printf("Start reading\n");
    while (1) {
        
        while (read(fd, &ev, sizeof(struct input_event))) {

            //printf("Type: %d, Code: %d\n",ev.type,ev.code);

            if (ev.type == EV_KEY) {
                switch (ev.code) {
                    case KEY_PLAY:
                    //todo: send system() to initialitaze the ethernet audio communication
                        if (ev.value == 0)
                            printf("Key Play released\n");
                        else if (ev.value == 1)
                            printf("Key Play pressed\n");
                        break;

                    case KEY_UP:
                    //todo: send system() to up the volume of the ethernet audio communication
                        if (ev.value == 0)
                            printf("Key UP released\n");
                        else if (ev.value == 1)
                            printf("Key UP pressed\n");
                        break;
                    case KEY_DOWN:
                    //todo: send system() to down the volume of the ethernet audio communication
                        if (ev.value == 0)
                            printf("Key DOWN released\n");
                        else if (ev.value == 1)
                            printf("Key DOWN pressed\n");
                        break;
                    case KEY_MUTE:
                    //todo: send system() to MUTE the volume of the ethernet audio communication
                        if (ev.value == 0)
                            printf("Key MUTE released\n");
                        else if (ev.value == 1)
                            printf("Key MUTE pressed\n");
                        break;
                    case KEY_PREVIOUS:
                    //todo: send system() to stop the ethernet audio communication
                        if (ev.value == 0)
                            printf("Key PREV released\n");
                        else if (ev.value == 1)
                            printf("Key PREV pressed\n");
                        break;
                    
                    default:
                        // Handle other keys or events
                        break;
                }
            }

        }
        
    }
    close(fd);
    return 0;
}