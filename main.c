#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#define SYS_reader_writer 335

void *writer(void *arg) {
    int *id=(int*)arg;
    int i;
    for (i = 0; i < 5; i++) {
        syscall(SYS_reader_writer, 0); // writer mode
        printf("Person %d is writing...\n",*id);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *reader(void *arg) {
    int *id=(int*)arg;
    int i;
    for (i = 0; i < 5; i++) {
        syscall(SYS_reader_writer, 1); // reader mode
        printf("Person %d is reading...\n",*id);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int id1=1,id2=2;

    syscall(SYS_reader_writer, -1);

    pthread_create(&thread1, NULL, writer, (void*)&id1);
    pthread_create(&thread2, NULL, reader, (void*)&id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
