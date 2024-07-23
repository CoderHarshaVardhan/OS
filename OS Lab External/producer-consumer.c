#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item
        sem_wait(&empty);    // Decrement the empty count
        sem_wait(&mutex);    // Enter critical section

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);    // Exit critical section
        sem_post(&full);     // Increment the full count

        sleep(1); // Sleep for a while to simulate production time
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);     // Decrement the full count
        sem_wait(&mutex);    // Enter critical section

        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);    // Exit critical section
        sem_post(&empty);    // Increment the empty count

        sleep(1); // Sleep for a while to simulate consumption time
    }
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Join threads (this program will run indefinitely)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
