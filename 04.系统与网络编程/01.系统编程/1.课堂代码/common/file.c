/*************************************************************************
	> File Name: file.c
	> Author: 
	> Mail: 
	> Created Time: Wed 28 Feb 2024 09:16:21 AM CST
 ************************************************************************/

#include "head.h"

int send_file(int sockfd, char *filename) {
    FILE *fp = NULL;
    struct file_msg filemsg;
    size_t size;
    char *p;
    
    bzero(&filemsg, sizeof(filemsg));

    if ((fp = fopen(filename, "rb")) < 0) {
        perror("fopen");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    filemsg.size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    strcpy(filemsg.name, (p = strrchr(filename, '/')) ? p + 1 : filename);
    DBG("%s\n", filemsg.name);
    while ((size = fread(filemsg.buff, 1, sizeof(filemsg.buff), fp))) {
        filemsg.msgsize = size;
        send(sockfd, (void *)&filemsg, sizeof(filemsg), 0);
        bzero(filemsg.buff, sizeof(filemsg.buff));
    }

    return filemsg.size;
}


int recv_file(int sockfd) {
    int total_size = 0;
    
    struct file_msg packet, packet_t, packet_pre;
    int packet_size = sizeof(struct file_msg);
    bzero(&packet, packet_size);
    bzero(&packet_t, packet_size);
    bzero(&packet_pre, packet_size);
    
    int offset = 0, recv_size = 0, cnt = 0;
    FILE *fp = NULL;

    while (1) {
        bzero(packet.buff, sizeof(packet.buff));
        bzero(packet_t.buff, sizeof(packet_t.buff));
        if (offset) {
            memcpy(&packet, &packet_pre, offset);
            bzero(&packet_pre, sizeof(packet_pre));
        }

        while ((recv_size = recv(sockfd, (void *)&packet_t, packet_size, 0)) > 0) {
            if (recv_size + offset == packet_size) {
                memcpy((char *)&packet + offset, (char *)&packet_t, recv_size);
                offset = 0;
                DBG("整包!\n");
                break;
            } else if (offset + recv_size < packet_size) {
                memcpy((char *)&packet + offset, (char *)&packet_t, recv_size);
                offset += recv_size;
                DBG("拆包!\n");
            } else {
                int wait = packet_size - offset;
                memcpy((char *)&packet + offset, (char *)&packet_t, wait);
                offset = recv_size - wait;
                memcpy((char *)&packet_pre, (char *)&packet_t + wait, offset);
                DBG("粘包!\n");
                break;
            }
    }
        if (!cnt) {
            DBG("FILE transfer start : %s, size of %ld ...\n", packet.name, packet.size);
            char name[1024] = {0};
            sprintf(name, "./data/%s", packet.name);
            DBG("%s\n", name);
            if ((fp = fopen(name, "wb")) == NULL) {
                perror("fopen");
                return -1;
            }
            cnt++;
        }

        if (recv_size <= 0) break;
        int wsize = fwrite(packet.buff, 1, packet.msgsize, fp);
        DBG("recv : write => %d : %d!\n", recv_size,wsize);
        total_size += wsize;
        bzero(packet.buff, sizeof(packet.buff));
    }

    fclose(fp);
    DBG("Finshed transfer file!\n");
    return total_size;
}
