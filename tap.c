#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <linux/if_tun.h>
#include<stdlib.h>
#include<stdio.h>

int tun_alloc(int flags)
{
    struct ifreq ifr;
    int fd, err;
    char *clonedev = "/dev/net/tun";
    if ((fd = open(clonedev, O_RDWR)) < 0) {
        return fd;
    }
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = flags;
    if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
        close(fd);
        return err;
    }
    printf("Open tun/tap device: %s for reading...n", ifr.ifr_name);
    return fd;
}

int main()
{
    int tun_fd, nread;
    int nwrite;
    int fd;
    char buffer[1500];
    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *        IFF_NO_PI - Do not provide packet information
     */
    tun_fd = tun_alloc(IFF_TAP| IFF_NO_PI);
    fd = tun_alloc(IFF_TAP| IFF_NO_PI);
    if (tun_fd < 0 || fd < 0) {
        perror("Allocating interface");
        exit(1);
    }
    printf("tap fd %d\n", tun_fd);

    while (1) {  
        memset(buffer, 0, sizeof(buffer)); 
        nread = read(tun_fd, buffer, sizeof(buffer));
        if (nread < 0) {
            perror("Reading from interface");
            close(tun_fd);
            exit(1);
        }
        printf("Read %d bytes from tun/tap devicen\n", nread);

     	nwrite = write(fd, buffer, nread);
	printf("fd %d nwrite %d\n", fd, nwrite);

     }
    return 0;
}


