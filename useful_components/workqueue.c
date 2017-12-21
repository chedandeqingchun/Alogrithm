#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

struct msg {
  struct msg *m_next;
  int num;
};

struct msg *workq = NULL;

void process_msg(void) {

  struct msg *mp;

  for (;;) {

    pthread_mutex_lock(&qlock);

    while (!workq) {
      pthread_cond_wait(&qready, &qlock);
    }

    mp = workq;
    printf("process msg num is %d\n", mp->num);
    workq = workq->m_next;
    pthread_mutex_unlock(&qlock);
  }

}

void enqueue_msg(struct msg *mp) {

  pthread_mutex_lock(&qlock);
  mp->m_next = workq;
  workq = mp;
  printf("enqueue msg nums is %d\n", mp->num);
  pthread_mutex_unlock(&qlock);
  pthread_cond_signal(&qready);

}

void* consumer(void *data) {
    process_msg();
}

void* produce(void *data) {

    for (int i = 0; i < 5; i++) {

        struct msg *mp = (struct msg *)malloc(sizeof(struct msg));
        
        if (!mp) {
            printf("malloc msg fails");
            return NULL;
        }

        mp->num = rand() % 1000 + 1;
        enqueue_msg(mp);
    }

}

int main(void) {

    pthread_t id1, id2;

    if (pthread_create(&id1, NULL, produce, NULL) != 0) {
        printf("id1 create  fails");
        return -1;
    }

    if (pthread_create(&id2, NULL, consumer, NULL) != 0) {
        printf("id2 create fails");
        return -1;
    }

    if (pthread_join(id1, NULL) != 0) {
        printf("fails");

    }

    if (pthread_join(id2, NULL) != 0) {

    }

  return 0;
}
