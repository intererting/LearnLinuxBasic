#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <zconf.h>
#include <semaphore.h>
#include <wait.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>

void testMMAP();

void testSem();

void testFIFO();

void testReadFile();

void testTimer();

void testRef();

void testSigAction();

void testDaemon();

void testPthread();

void testPthreadJoin();

void testThreadAttr();

void test(int *data) {

}

int main() {

//    testThreadAttr();

//    dprintf(STDOUT_FILENO, "haha   %s", "haha");

//    char result[1024];
//    sprintf(result, "haha %s", "dir");
//
//    printf("%s", result);

//    testPthread();

//    testPthreadJoin();

//    testTimer();

//    testMMAP();
    testSem();

//    testFIFO();

//    testReadFile();

//    testDaemon();

//pthread_exit()可以退出主线程，所以不会影响子线程的执行，如果是
//_exit()或者return，那么进程将会被中断
//    pthread_exit(0);
    return 0;
}

/**
 * 线程属性
 */
void testThreadAttr() {

//    pthread_attr_init();
//    pthread_attr_destroy();
//    pthread_attr_setdetachstate();
}

struct Person {
    int no;
    char *name;
};


void *tfn_join(void *arg) {

    printf("pthread join \n");

//    struct Person *person = malloc(sizeof(struct Person));
    struct Person *person = arg;
    person->no = 1;
    person->name = "yuliyang";
    return person;
}


/**
 * PthreadJoin带返回值
 */
void testPthreadJoin() {

    pthread_t pthread;

    struct Person *result;

    struct Person temp = {};

    pthread_create(&pthread, NULL, tfn_join, (void *) &temp);

    pthread_join(pthread, (void **) &result);

    printf("%d,%s", result->no, result->name);


}

void *thread_fn(void *arg) {
    printf("thread  %lud", pthread_self());
    return NULL;
}


/**
 * 测试线程
 */
void testPthread() {

    pthread_t pthread;

    pthread_create(&pthread, NULL, thread_fn, NULL);


}

/**
 * 创建守护进程s
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


void handleSignal(int signo) {
    printf("time arrival");
}

void testTimer() {

    struct itimerval timerNew, timerOld;

//    signal(SIGALRM, handleSignal);

    struct sigaction newAct, oldAct;
    newAct.sa_handler = handleSignal;
    newAct.sa_flags = 0;
    sigemptyset(&(newAct.sa_mask));

    sigaction(SIGALRM, &newAct, &oldAct);


    timerNew.it_value.tv_sec = 2;
    timerNew.it_value.tv_usec = 0;

    timerNew.it_interval.tv_sec = 5;
    timerNew.it_interval.tv_usec = 0;


    int code = setitimer(ITIMER_REAL, &timerNew, &timerOld);

    printf("%d", code);

    while (1) {

    }
}

void testReadFile() {


    char buf[1024];

    int fd = open("/home/yuliyang/Desktop/haha.txt", O_RDONLY
                                                     | O_CREAT);
    int n = read(fd, buf, 1024);

    write(STDOUT_FILENO, buf, n);

    printf("read finish");
}


/**
 * 测试FIFO
 */
void testFIFO() {

}

sem_t sem;

void *semfun(void *arg) {
    sleep(1);
    sem_post(&sem);
    return NULL;
}

void testSem() {


    //初始信号量
    sem_init(&sem, 0, 0);

    pthread_t pthread;

    pthread_create(&pthread, NULL, semfun, NULL);

    sem_wait(&sem);

    printf("get sem");

    sem_destroy(&sem);
    pthread_join(pthread, NULL);
}

void testMMAP() {


    struct stat buf;

    char *path = "/home/yuliyang/Desktop/share.txt";

    int fd = open(path, O_RDWR);

    fstat(fd, &buf);

    //建立fd和ptr的内存映射
    char *ptr = mmap(NULL, 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    close(fd);

    printf("%s", ptr);

    strcpy(ptr, "changed");

    munmap(ptr, buf.st_size);

}
