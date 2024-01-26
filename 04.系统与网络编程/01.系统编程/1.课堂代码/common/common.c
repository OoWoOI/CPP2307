/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Jan 2024 09:11:23 PM CST
 ************************************************************************/

#include "head.h"

//日志系统
void log_event(int level, const char *message, const char *filename) {
    time_t now = time(NULL);
    char *level_str;
    FILE *fp;

    switch (level) {
        case LOG_LEVEL_INFO:
            level_str = "INFO";
            break;
        case LOG_LEVEL_WARNING:
            level_str = "WARNING";
            break;
        case LOG_LEVEL_ERROR:
            level_str = "ERROR";
            break;
        default :
            level_str = "UNKNOWN";
            break;
    }

    fp = fopen(filename, "a");
    //ToDO: 确认是否正常打开
    if (fp != NULL) {
        fprintf(fp, "%s [%s] :  %s \n", ctime(&now), level_str, message);
        fclose(fp);
    }
    return ; 
}
