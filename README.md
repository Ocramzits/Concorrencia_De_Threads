# Simulação de Estacionamento com Threads

Simulação em C de um estacionamento com vagas limitadas, onde múltiplos carros disputam acesso concorrente usando **threads POSIX** e **semáforos**, feita para a disciplina de **Sistemas Operacionais**.

## Sobre o projeto

O programa cria **15 carros** (threads), cada um tentando entrar em um estacionamento com apenas **4 vagas**. Cada carro espera um tempo aleatório antes de tentar entrar, ocupa uma vaga por um tempo aleatório e depois sai, liberando a vaga para o próximo carro na fila.

O objetivo é demonstrar, na prática, como um **semáforo contador** resolve um problema clássico de concorrência: garantir que nunca mais threads acessem um recurso do que a capacidade permitida, sem uso de locks manuais.

## Conceitos aplicados

- **Threads POSIX (`pthread`)**: cada carro é executado como uma thread independente (`pthread_create`), simulando concorrência real
- **Semáforo contador (`sem_t`)**: inicializado com o número de vagas (`sem_init(&vagas, 0, VAGAS)`), controla quantos carros podem estar estacionados ao mesmo tempo
- **Seção crítica**: `sem_wait`/`sem_post` delimitam a entrada e saída do recurso compartilhado (a vaga), evitando que mais de `VAGAS` carros ocupem o estacionamento simultaneamente
- **Sincronização com `pthread_join`**: a thread principal aguarda todos os carros terminarem antes de oferecer uma nova rodada de simulação
- **Condição de corrida evitada por design**: mesmo com múltiplas threads lendo/alterando o estado do semáforo concorrentemente, o acesso é seguro porque toda a exclusão passa pelas primitivas do semáforo, não por variáveis compartilhadas sem proteção
- **Aleatoriedade thread-safe**: uso de `rand_r` com seed própria por thread (em vez de `rand`), evitando condição de corrida no gerador de números aleatórios
- **Validação de entrada do usuário** em loop (`validar`), tratando caracteres inválidos na leitura com `scanf`

## Como compilar e executar

Requer um compilador C com suporte a `pthread` (padrão em Linux/gcc).

```bash
gcc estacionamento.c -o estacionamento -lpthread
./estacionamento
```

Ao rodar, o programa pergunta se deseja iniciar a simulação (`S`/`N`). Cada execução dispara os 15 carros simultaneamente e mostra em tempo real quem está entrando, esperando ou saindo, além da ocupação atual das vagas. Ao final de cada rodada, é possível simular novamente sem reiniciar o programa.

## Parâmetros ajustáveis

No topo do arquivo:

```c
#define TOTAL_CARROS 15   // quantidade de carros simulados
#define VAGAS 4           // capacidade do estacionamento
```

## Autor

Marco Antônio — Sistemas de Informação, UFPI.