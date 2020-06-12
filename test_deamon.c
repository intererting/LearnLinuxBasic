//
// Created by yuliyang on 2020/6/11.
//

#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <sys/stat.h>


void testDaemon();

int main() {
    printf("start");
    testDaemon();
    return 0;
}

/**
 * 创建守护进程
 */
void testDaemon() {

    //1:创建子进程
    pid_t pid;
    pid = fork();
    if (pid > 0) {
        _exit(0);
    }

//   2: 开启回话
    setsid();
//3:设置工作目录
    chdir("/home/yuliyang/Desktop");
//    4:修改umask
    umask(0022);
//    5:修改文件描述符
    close(STDIN_FILENO);
    int fd_0 = open("/dev/null", O_RDWR);

    dup2(fd_0, STDOUT_FILENO);
    dup2(fd_0, STDERR_FILENO);

    while (1) {

    }
}