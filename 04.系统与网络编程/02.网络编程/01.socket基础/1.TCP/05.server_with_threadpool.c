/*************************************************************************
	> File Name: 05.servre_with_threadpool.c
	> Author: 
	> Mail: 
	> Created Time: Mon 26 Feb 2024 02:00:48 PM CST
 ************************************************************************/

#include "./common/head.h"

#define MAXUSR 512
#define THREAD_NUM 10
#define QUEUE_SIZE 1000

//子线程业务
void *thread_worker(void *arg) {
    pthread_detach(pthread_self());//分离线程
    struct task_queue *tq = (struct task_queue *)arg;
    //printf("<%d> is ready!\n", fd[i]);
    while (1) {
        int *fd = (int *)task_queue_pop(tq);
        //printf("Total <%d : %d>\n", tq->size, tq->total);
        char buff[4096] = {0};
        ssize_t rsize = recv(*fd, buff, sizeof(buff) - 1, 0);
        if (rsize < 0) {
            if (errno == EAGAIN) {
                continue;
            }
        
        //        fprintf(stderr, "%d : 连接中断！\n", *fd)
            fprintf(stderr, " %d : 连接中断！\n", *fd);
            close(*fd);
            *fd = 0;
            continue;
        }
        if (rsize == 0) {
            close(*fd);
            *fd = 0;
            continue;
        }
        if (rsize > 0) {
            printf("%d send a msg : ", *fd);
            printf("%s\n", buff);
            send(*fd, buff, rsize, 0);
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2) {//判断是否参数传递合法
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }

    int server_listen, port = 0;
    port = atoi(argv[1]);
    if ((server_listen = socket_create(port)) < 0) {//获取监听连接
        perror("socket_create");
        exit(1);
    }

    //创建任务队列
    struct task_queue *tq = (struct task_queue *)calloc(1, sizeof(struct task_queue));
    task_queue_init(tq, QUEUE_SIZE);//初始化任务队列
    pthread_t *tid = calloc(sizeof(pthread_t) , (THREAD_NUM + 5));//申请线程列表
    for (int i = 0; i < THREAD_NUM; i++) {
        pthread_create(&tid[i], NULL, thread_worker, (void *)tq);
    }

    //使用select 监控实现网络并发服务;
    int sockfd;
    fd_set rfds, efds;
    int fd[MAXUSR] = {0};
    fd[server_listen] = server_listen;//将server_listen加入到数组中去待监控
    int maxfd = server_listen;
    while (1) {
        //清空监控fd集合
        FD_ZERO(&rfds);
        FD_ZERO(&efds);
        for (int i = 3; i < MAXUSR; i++) {//将存在的fd放入rfds中
            if (!fd[i]) continue;
            FD_SET(fd[i], &rfds);
            FD_SET(fd[i], &efds);
        }
        int ret = select(maxfd + 1, &rfds, NULL, &efds, NULL);
        
        if (FD_ISSET(server_listen, &rfds)) {//开始监控有没有连接服务器的请求
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            bzero(&client, len);
            if ((sockfd = accept(server_listen, (struct sockaddr *)&client, &len)) < 0) {//获取连接，三次握手过程发生
                perror("accept"); 
                exit(1); 
            }
            printf(" %s : <%d> login seccessful!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            if (sockfd >= MAXUSR - 5) { 
                fprintf(stderr, "Too many User!\n");
                close(sockfd);
            } else {
                if (sockfd > maxfd) maxfd = sockfd;
                make_nonblock(sockfd);
                fd[sockfd] = sockfd;
            }
        }
        
        for (int i = 3; i < MAXUSR; i++) {
            if (!fd[i] || server_listen == fd[i]) continue;
            if (FD_ISSET(fd[i], &efds)) {
                close(fd[i]);
                fd[i] = 0;
                continue;
            }
            if (FD_ISSET(fd[i], &rfds)) {
                //fd[i]的连接处于就绪状态
                task_queue_push(tq, &fd[i]);
            }
        }
}
    
    return 0;
}
