#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <libsocket/libinetsocket.h>

int main(int argc, char *argv[]) {
    char hostname[100];
    strcpy(hostname, argv[1]);
    strcat(hostname, ".cs.sierracollege.edu");

    int fd = create_inet_stream_socket(hostname, "5055", LIBSOCKET_IPv4, 0);

    if (fd < 0) {
        char errmesg[100];
        sprintf(errmesg, "Cant open socket");
        perror(errmesg);
    }
    printf("Connected to %s\n", hostname);

    struct timeval now;
    FILE *s = fdopen(fd, "r+");

// ---------------------------------------------
    //sleep(1);

    // fetch time
    gettimeofday(&now, NULL);
    double epoch1 = now.tv_sec*1000.0 + now.tv_usec/1000.0; 

    // send data
    fprintf(s, "HELO\n");

    // recive data
    char line[100];
    fgets(line, 100, s);

    // fetch time again
    gettimeofday(&now, NULL);
    double epoch2 = now.tv_sec*1000.0 + now.tv_usec/1000.0; 

    // get the diffrence
    double diff1 = epoch2 - epoch1;
    printf("Sending data 1\n");
    printf("Received data 1: %.2f ms\n", diff1);

// -------------------------------------------------------------
    // next set of data
    // fetch time
    gettimeofday(&now, NULL);
    double epoch3 = now.tv_sec*1000.0 + now.tv_usec/1000.0; 

    // send data
    fprintf(s, "DATE\n");

    // recive data
    fgets(line, 100, s);

    // fetch time again
    gettimeofday(&now, NULL);
    double epoch4 = now.tv_sec*1000.0 + now.tv_usec/1000.0; 

    // get the diffrence
    double diff2 = epoch4 - epoch3;
    printf("Sending data 2\n");
    printf("Received data 2: %.2f ms\n", diff2);

// -----------------------------------------------------
    // next set of data
    // fetch time
    gettimeofday(&now, NULL);
    double epoch5 = now.tv_sec*1000.0 + now.tv_usec/1000.0; 

    // send data
    fprintf(s, "DATE\n");

    // recive
    fgets(line, 100, s);
    //usleep(100);

    // fetch time again
    gettimeofday(&now, NULL);
    double epoch6 = now.tv_sec*1000.0 + now.tv_usec/1000.0; 

    // get the diffrence
    double diff3 = epoch6 - epoch5;
    printf("Sending data 3\n");
    printf("Received data 3: %.2f ms\n", diff3);

// ----------------------------------------------
    // get average
    double avg = (diff1 + diff2 + diff3) / 3;
    printf("closing connection\n");
    printf("Average RTT: %.2f ms\n", avg);

    // close
    close(fd);
    return 0;
}
