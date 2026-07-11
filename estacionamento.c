#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 

#define TOTAL_CARROS 15
#define VAGAS 4

pthread_t carros[TOTAL_CARROS]; 
sem_t vagas;

char validar(char loop){
    while (loop != 'S' && loop != 's' && loop != 'N' && loop != 'n'){
        printf("Erro! Digite um caractere válido: ");
        scanf("%c", &loop);
        getchar();
    }
    
    return loop;
}

void* estacionamento(void *id){
    int vagas_disponiveis;
    int id_carro = *(int*)id;
    unsigned int seed = time(NULL) + id_carro; 

    sleep(rand_r(&seed) % 10 + 3); 

    printf("O carro %d está tentando entrar no estacionamento.\n", id_carro);
    sem_getvalue(&vagas, &vagas_disponiveis);
    
    if(vagas_disponiveis == 0){
        printf("O carro %d está aguardando uma vaga.\n", id_carro);
    }

    sem_wait(&vagas); 
    sem_getvalue(&vagas, &vagas_disponiveis);
    printf("O carro %d entrou no estacionamento. (Vagas: %d/%d)\n", id_carro, vagas_disponiveis, VAGAS);
    sleep(rand_r(&seed) % 9 + 7);
    
    sem_getvalue(&vagas, &vagas_disponiveis);
    printf("O carro %d saiu do estacionamento. (Vagas: %d/%d)\n", id_carro, vagas_disponiveis+1, VAGAS);
    sem_post(&vagas);
    
    return NULL;
}

int main(){
    char loop;
    sem_init(&vagas, 0, VAGAS); 
    int id[TOTAL_CARROS]; 

    printf("=== Implementação de concorrência de Threads ===\n"
    "Deseja iniciar? (S/n): ");
    scanf("%c", &loop);
    getchar();      
    loop = validar(loop);
        
    while(loop == 'S' || loop == 's'){
        for(int i=0; i<TOTAL_CARROS; i++){
            id[i] = i+1;
            pthread_create(&carros[i], NULL, estacionamento, &id[i]);
        }
        
        for(int i=0; i<TOTAL_CARROS; i++){
        pthread_join(carros[i], NULL); 
        }
        
        printf("Deseja continuar a simulação? (S/n): ");
        scanf("%c", &loop);
        getchar();
        loop = validar(loop);
    }

    sem_destroy(&vagas);
    return 0;
}