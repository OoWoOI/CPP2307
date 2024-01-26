/*************************************************************************
	> File Name: 3.ls.c
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Jan 2024 11:18:17 PM CST
 ************************************************************************/

#include "./common/head.h"

int a_flag = 0;
int l_flag = 0;
int dir_num = 0;


void do_ls(const char *pathname);//执行ls操作
void do_stat(const char *name);//获取状态信息
void showinfo(const char *name, struct stat *st);//展示信息
void mode_2_str(mode_t mode, char *modestr);//将权限从掩码转换字符串形式
char * uid_2_name(uid_t uid);//将用户id转换字符串形式
char * gid_2_name(gid_t gid);//将用户组id转换为字符串形式

int main(int argc, char **argv) {
    int opt;

    //获取参数选项
    while ( (opt = getopt(argc, argv, "al")) != -1) {
        switch (opt) {
            case 'a':
                a_flag = 1;
                break;
            case 'l':
                l_flag = 1;
                break;
            default:
                fprintf(stderr, "Usage : %s is [-al] [args...]\n", argv[0]);
                exit(1);
        }
    }

    argc -= (optind - 1);
    argv += (optind - 1);
    
   // DBG("argc = %d, argv[1] = %s\n", argc, argv[1]);
    

    dir_num = argc;

    if (argc == 1) {
     //   DBG(".");
    } else {
        for (int i = 1; i < argc; i++) {
            do_ls(argv[i]);
        }
    }

    return 0;
}

void do_ls(const char *pathname) {
   // DBG("%s\n", pathname);
    DIR *dir;
    struct dirent *direntp = NULL;

    if ((dir = opendir(pathname)) == NULL) {
        if (access(pathname, R_OK) == 0) {
            if (l_flag == 1) {
                do_stat(pathname);
            } else {
                printf("%s\n", pathname);
            }
        }
    
        //判断是不是文件，如果是文件就做相应的操作

    } else {
        DBG("Open Success!\n");
        //读取目录
        if (dir_num > 1) {
            printf("%s :\n", pathname);
        }
        
        while ((direntp = readdir(dir))) {
            if (a_flag == 0 && direntp->d_name[0] == '.') continue;
            if (l_flag == 1) {
                do_stat(direntp->d_name);
            }
        }

    }
    
    return ;
}


void do_stat(const char *name) {
   // DBG("%s\n", name);
    struct stat st;
    if ((lstat(name, &st)) < 0) {
        perror(name);
        exit(1);
    }

    //DBG("uid = %d\n", st.st_uid);
    showinfo(name, &st);
    return ;
}

void showinfo(const char *name, struct stat *st) {
   char modstr[15] = "----------";
    mode_2_str(st->st_mode, modstr);
    printf("%s", modstr);
    printf("%3ld", st->st_nlink);
    printf("%10s", uid_2_name(st->st_uid));
    printf("%10s", gid_2_name(st->st_gid));
    printf("\n");
    return ;
}

void mode_2_str(mode_t mode, char *str) {
    //判断文件类型
    if (S_ISREG(mode)) str[0] = '-';
    if (S_ISDIR(mode)) str[0] = 'd';   
    if (S_ISCHR(mode)) str[0] = 'c';   
    if (S_ISBLK(mode)) str[0] = 'b';   
    if (S_ISSOCK(mode)) str[0] = 's';   
    if (S_ISFIFO(mode)) str[0] = 'p';   
    if (S_ISLNK(mode)) str[0] = 'l';   
    //修改权限
    
    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';
    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';
    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';

    return ;
}

char *uid_2_name(uid_t uid) {
    struct passwd *pw;
    static char tmpname[20] = {0};
    if ((pw = getpwuid(uid)) == NULL) {
        sprintf(tmpname, "%d", uid);
        return tmpname;
    } 
    return pw->pw_name;
}

char *gid_2_name(gid_t gid) {
    struct group *grp;
    static char tmpname[20] = {0}; 
    if ((grp = getgrgid(gid)) == NULL) {
        sprintf(tmpname, "%d", gid);
        return tmpname;
    } else {
        return grp->gr_name;
    }
}
