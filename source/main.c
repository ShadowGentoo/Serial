#include "stdlib.h"
#include "stdio.h"
#include "termios.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"

int main(int argc, char const *argv[])
{
    int fd;
    char buffer;
    char msg[255];

    fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
        printf("can't open device\n");
        return 1;
    }

    struct termios terminal;

    tcgetattr(fd, &terminal);

    cfsetispeed(&terminal, B9600);
    cfsetospeed(&terminal, B9600);
    //set it to local, so we will not own port and we will read it
    terminal.c_cflag |= (CLOCAL | CREAD);
    //set data to 8 bit
    terminal.c_cflag &= ~CSIZE; /* Mask the character size bits */
    terminal.c_cflag |= CS8;    /* Select 8 data bits */
    tcsetattr(fd, TCSANOW, &terminal);

    printf("ready to receive data!\n");
    while (1)
    {
        if (read(fd, &buffer, 1) > 0)
        {
            strcat(msg, &buffer);
            if (buffer == '\0')
            {
                printf("%s\n", msg);
                memset(msg, 0, 255);
            }
        }
    }

    close(fd);

    return 0;
}
