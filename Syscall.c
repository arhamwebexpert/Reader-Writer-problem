#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/semaphore.h>

asmlinkage long sys_RW(int mode) {
    static struct semaphore rw_mutex;
    static struct semaphore r_mutex;
    static int reader_count = 0;

    switch (mode) {
        case 0: // writer
            down(&rw_mutex);
            // critical section for writer
            up(&rw_mutex);
            break;
        case 1: // reader
            down(&r_mutex);
            if (++reader_count == 1) {
                down(&rw_mutex);
            }
            up(&r_mutex);

            // critical section for reader

            down(&r_mutex);
            if (--reader_count == 0) {
                up(&rw_mutex);
            }
            up(&r_mutex);
            break;
        default:
            return -1; // invalid mode
    }
    return 0;
}
