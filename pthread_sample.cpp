#include <pthread.h>
#include <unistd.h>
#include <cstdio>

int r1 = 0,r2 = 0,r3 = 0;
pthread_mutex_t r3_mutex;

void* do_one_thing(void *);
void* do_another_thing(void *);
void do_wrap_up(int,int);

int main(void) {
  pthread_t thread1,thread2;
  pthread_mutex_init(&r3_mutex, NULL);

  pthread_create(&thread1, NULL, do_one_thing,     (void *) &r1);
  pthread_create(&thread2, NULL, do_another_thing, (void *) &r2);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  do_wrap_up(r1, r2);

  return 0;
}

void* do_one_thing(void *pnum_times) {
  int i,x;

  pthread_mutex_lock(&r3_mutex);

  if (r3 > 3) {
    x = r3;
    r3--; 
  } else {
    x = 1;
  } 

  pthread_mutex_unlock(&r3_mutex);

  for (i = 0; i < 4; i++) { 
    sleep(1);
    printf("doing one thing¥n");
    int* pn = (int*)pnum_times;
    (*pn)++;
  }
}

void* do_another_thing(void *pnum_times) {
  int i, j, x;

  for (i = 0; i < 4; i++) {
    printf("doing another ¥n");
    for (j = 0; j < 10000; j++){ x = x + 1;}
      int* pn = (int*)pnum_times;
      (*pn)++;
  }
}

void do_wrap_up(int one_times,int another_times) {
  int total;

  total = one_times + another_times;
  printf("All done, one thing % d , another % d for a total of %d \n",
    one_times, another_times,total);
}

