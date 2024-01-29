/*************************************************************************
	> File Name: 07.chat_shm.c
	> Author: 
	> Mail: 
	> Created Time: Mon 29 Jan 2024 02:24:28 AM CST
 ************************************************************************/

//ToDO:
    //（1）基于共享内存实现聊天室功能
    //（2）要求实现两个人的信息交互
    //（3）用户通过参数传递设置自己的房间号1和对方的房间号2进程聊天
    //（4）程序通过轮询的机制实现对对方的共享内存监听，当信息发生改变时，打印信息到屏幕
    //（5）当数据出现quit的时候就会，结束聊天

#include "./common/head.h"

struct Person {
    char name[20];
    char msg[2048];
};

int *getRoomNum(int argc, char **argv);
struct Person * getRoom(int num);//获取房间地址
int chatLoop(struct Person *sRoom, struct Person *tRoom);

int main(int argc, char **argv) {
    
    int *room_num = getRoomNum(argc, argv);//获取房间号
    struct Person *sRoom = getRoom(room_num[0]);//获取自己的房间;
    struct Person *tRoom = getRoom(room_num[1]);//获取对方的房间;
    int ret = chatLoop(sRoom, tRoom);//ret的值: 0表示一切正常、1表示对方下线、2表示对方的房间不存在
    switch (ret) {
        case 0:
            printf("与%s聊天结束\n", tRoom->name);
            break;
        case 1:
            printf("%s, 已经下线\n", tRoom->name);
            break;
        case 2:
            printf("%d, 房间不存在\n", room_num[1]);
            break;
        default :
            printf("其他异常\n");
            break;
    }
    
    return 0;
}


int *getRoomNum(int argc, char **argv) {
    


    return NULL;
}


struct Person *getRoom(int num) {
    //mma
    

    return NULL;
}
