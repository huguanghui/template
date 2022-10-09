#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/prctl.h>
#include <pthread.h>

static sem_t main_run_sem;
int g_runiing = 0;

static void signal_hander(int signal)
{
    if (signal == SIGINT) {
        sem_post(&main_run_sem);
    } else if (signal == SIGKILL) {
        sem_post(&main_run_sem);
    } else if (signal == SIGSEGV) {
        SIG_DFL(signal);
    }
    return;
}

static void sig_chld(int signo)
{
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        //   printf("child %d terminated\n", pid);
    }
    return;
}

static void capture_all_signal()
{
    int i = 0;
    for (i = 0; i < 32; i++) {
        if (i == SIGCHLD) {
            // signal(i, SIG_DFL);
            signal(i, sig_chld);
        } else if ((i == SIGPIPE) || (i == SIGALRM)) {
            signal(i, SIG_IGN);
        } else {
            signal(i, signal_hander);
        }
    }
    return;
}

void *check_task(void *parm)
{
    prctl(PR_SET_NAME, __FUNCTION__);
    pthread_detach(pthread_self());

    while (g_runiing) {
        sleep(5);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    capture_all_signal();
    printf("[HGH-TEST][%s %d] test\n", __FUNCTION__, __LINE__);
    sem_init(&main_run_sem, 0, 0);

    pthread_t check_task_id;
    g_runiing = 1;
    pthread_create(&check_task_id, NULL, check_task, NULL);

    sem_wait(&main_run_sem);
    int timer = 0;
    while (1) {
        timer++;
        if (timer > 100) {
            break;
        }
        usleep(10 * 1000);
    }
    sem_destroy(&main_run_sem);

    return 0;
}
