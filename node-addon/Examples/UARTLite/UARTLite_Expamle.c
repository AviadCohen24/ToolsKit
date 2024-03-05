#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

int open_serial_port(const char* port);
void configure_serial_port(int serial_port);
void write_to_serial_port(int serial_port, const char* message);
int read_from_serial_port(int serial_port, char* buffer, size_t size);

int main() {
    int serial_port = open_serial_port("/dev/ttyUL1");
    if (serial_port < 0) return 1;

    configure_serial_port(serial_port);

    char read_buf[256];
    memset(&read_buf, '\0', sizeof(read_buf));

    while (1) {
        write_to_serial_port(serial_port, "Hi, this is a KRIA test");

        int num_bytes = read_from_serial_port(serial_port, read_buf, sizeof(read_buf));
        if (num_bytes >= 0) {
            printf("Read %i bytes. Received message: %s\n", num_bytes, read_buf);
        } else {
            printf("Error reading: %s\n", strerror(errno));
            break;
        }
    }

    close(serial_port);
    return 0;
}

int open_serial_port(const char* port) {
    int serial_port = open(port, O_RDWR);
    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }
    return serial_port;
}

void configure_serial_port(int serial_port) {
    struct termios tty;
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return;
    }

    tty.c_cflag &= ~PARENB;         // Clear parity bit, disabling parity
    tty.c_cflag &= ~CSTOPB;         // Clear stop field, only one stop bit used in communication
    tty.c_cflag |= CS8;             // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS;        // Disable RTS/CTS hardware flow control
    tty.c_cflag |= CREAD | CLOCAL;  // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;           // Disable echo
    tty.c_lflag &= ~ECHOE;          // Disable erasure
    tty.c_lflag &= ~ECHONL;         // Disable new-line echo
    tty.c_lflag &= ~ISIG;           // Disable interpretation of INTR, QUIT and SUSP

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 115200
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
}

void write_to_serial_port(int serial_port, const char* message) {
    write(serial_port, message, strlen(message));
}

int read_from_serial_port(int serial_port, char* buffer, size_t size) {
    return read(serial_port, buffer, size);
}
