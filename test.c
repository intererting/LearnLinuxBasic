//
// Created by yuliyang on 2020/6/9.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

//int main() {
//
//    pid_t pid;
//    int fd[2];
//    pipe(fd);
//    pid = fork();
//
//    if (pid == 0) {
//
//        close(fd[1]);
//        dup2(fd[0], STDIN_FILENO);
//        execlp("wc", "wc", "-l", NULL);
//
//    } else if (pid > 0) {
//        close(fd[0]);
//        dup2(fd[1], STDOUT_FILENO);
//        execlp("ls", "ls", NULL);
//    } else {
//        perror("error");
//    }
//    wait(NULL);
//    return 0;
//}