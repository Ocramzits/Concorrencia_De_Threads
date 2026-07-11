#include <stdio.h>
#include <pthread.h>

int compartilhada = 0; // variavel global compartilhada entre as threads
pthread_mutex_t lock; // variavel do tipo mutex

void* incrementar(void *arg){
    for(int i=0; i<100000; i++){
        pthread_mutex_lock(&lock); //mutex bloqueia regiao critica
        compartilhada += 1; //a ideia é que o resultado final seja 1 milhão porém com as condições de corrida o resultado não será esse
        pthread_mutex_unlock(&lock); //mutex libera regiao critica
    }
    return NULL;
}

int main() {
    pthread_t threads[10]; //phthread_t é a função para armazenar espaço para threads, nesse caso eu fiz um vetor de 10 threads
    pthread_mutex_init(&lock, NULL); // inicializar a variavel mutex
    for(int i=0; i<10; i++){
        pthread_create(&threads[i], NULL, incrementar, NULL); // Agora sim as threads foram inicializadas
    }
    for(int i=0; i<10; i++){
        pthread_join(threads[i], NULL); // Serve como uma barreira em que o main espera todas as threads terminarem para continuar
    }
    printf("Valor %d\n", compartilhada);
    return 0;
}
