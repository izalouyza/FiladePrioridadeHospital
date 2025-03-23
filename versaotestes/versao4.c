#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h> // Para a função isdigit

typedef struct {
    int num_ficha; // Número da ficha do paciente na sequência
    char nome[100]; 
    int idade; // Idade em anos do paciente
    int sexo; // [1]Masculino ou [2]Feminino
    int convenio; // [1] SUS [2] Particular
    int urgencia; // [1] Azul, [2] Verde, [3] Amarelo, [4] Laranja, [5] Vermelho
} paciente;

typedef struct {
    paciente *pacientes;
    int front;
    int rear;
    int capac;
} Fila;

void inicializarFila(Fila *f, int capacidade) {
    f->capac = capacidade;
    f->pacientes = malloc(capacidade * sizeof(paciente));
    f->front = 0;
    f->rear = 0;
}

int isFull(const Fila *f) {
    return (f->rear == f->capac);
}

int isEmpty(const Fila *f) {
    return (f->front == f->rear);
}

void enfileirar(Fila *f, paciente p) {
    if (isFull(f)) {
        printf("\n>> Fila cheia. Não é possível adicionar mais pacientes.\n");
        return;
    }

    // Inserir o paciente na fila
    f->pacientes[f->rear] = p;
    f->pacientes[f->rear].num_ficha = f->rear + 1; // Atribui o número da ficha
    f->rear++;
    printf("\n>> Paciente adicionado à fila com sucesso.\n");
}

void organizarFilaPorUrgencia(Fila *f) {
    for (int i = f->front; i < f->rear - 1; i++) {
        for (int j = i + 1; j < f->rear; j++) {
            if (f->pacientes[i].urgencia < f->pacientes[j].urgencia) {
                // Troca os pacientes de lugar e dá a prioridade para aquele com mais urgência
                paciente temp = f->pacientes[i];
                f->pacientes[i] = f->pacientes[j];
                f->pacientes[j] = temp;
            }
        }
    }

    // Atribui os números das fichas após a ordenação
    for (int i = f->front; i < f->rear; i++) {
        f->pacientes[i].num_ficha = i + 1; // O número da ficha começa em 1
    }
}

paciente desenfileirar(Fila *f) {
    if (isEmpty(f)) {
        printf("\n>> Fila vazia. Não há pacientes para serem removidos.\n");
        paciente vazio = {0, "", 0, 0, 0, 0}; // Retorna um paciente vazio
        return vazio;
    }
    paciente removido = f->pacientes[f->front];
    f->front++;

    // Atualiza os números das fichas dos pacientes restantes
    for (int i = f->front; i < f->rear; i++) {
        f->pacientes[i].num_ficha = i + 1; // Atualiza o número da ficha
    }

    return removido;
}

void exibirPaciente(const paciente *p) {
    printf("—---------------------------------------- Paciente Nº%d —---------------------------------------\n", p->num_ficha);
    printf("Número da Ficha: %d\n", p->num_ficha);
    printf("Nome: %s\n", p->nome);
    printf("Idade: %d\n", p->idade);
    printf("Sexo: ");
    if (p->sexo == 1) {
        printf("Masculino\n");
    } else {
        printf("Feminino\n");
    }
    
    printf("Convênio: ");
    if (p->convenio == 1) {
        printf("SUS\n");
    } else {
        printf("Particular\n");
    }
    
    switch (p->urgencia) {
        case 1: printf("Urgência: Azul (Não Urgente)\n"); break;
        case 2: printf("Urgência: Verde (Pouco Urgente)\n"); break;
        case 3: printf("Urgência: Amarelo (Urgente)\n"); break;
        case 4: printf("Urgência: Laranja (Muito Urgente)\n"); break;
        case 5: printf("Urgência: Vermelho (Emergência)\n"); break;
    }
    printf("—----------------------------------------------------------------------------------------------\n");
}

void exibirFila(const Fila *f) {
    if (isEmpty(f)) {
        printf("\n>> Fila vazia. Não há pacientes para serem exibidos.\n");
        return;
    }
    printf("\n====================================== Fila de Pacientes ======================================\n\n");
    for (int i = f->front; i < f->rear; i++) {
        exibirPaciente(&f->pacientes[i]);
    }
}

void coletarUrgencia(paciente *p) {
    printf("\n>> Classificação de urgência:\n");
    printf("[1] Azul (Não Urgente)\n");
    printf("[2] Verde (Pouco Urgente)\n");
    printf("[3] Amarelo (Urgente)\n");
    printf("[4] Laranja (Muito Urgente)\n");
    printf("[5] Vermelho (Emergência)\n");
    printf("\nInforme a urgência do paciente: ");
    
    while (1) {
        // Verifica se a entrada é um número
        if (scanf("%d", &p->urgencia) != 1) {
            printf("\n>> Entrada inválida. Por favor, insira um número entre 1 e 5.\n");
            // Limpa o buffer de entrada
            while (getchar() != '\n'); // Consome até a nova linha
            printf("Informe a urgência do paciente: ");
            continue; // Volta para o início do loop
        }

        // Verifica se o número está dentro do intervalo permitido
        if (p->urgencia >= 1 && p->urgencia <= 5) {
            break; // Urgência válida, sai do loop
        } else {
            printf("\n>> Opção inválida. Por favor, tente novamente.\n");
            printf("Informe a urgência do paciente: ");
        }
    }
    setbuf(stdin, NULL);
}

int nomeValido(const char *nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (isdigit(nome[i])) {
            return 0; // Nome inválido se contém números
        }
    }
    return 1; // Nome válido
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001");
    
    Fila fila;
    inicializarFila(&fila, 10);
    int opc = 0;

    while (1) {
        printf("\n============================== Sistema de atendimento hospitalar ==============================\n\n");
        printf("[1] Adicionar paciente à fila \n[2] Exibir fila de pacientes \n[3] Remover paciente da fila \n[4] Sair \n");
        printf("\n>> Escolha uma opção: ");
        
        // Verifica se a entrada é um número
        if (scanf("%d", &opc) != 1) {
            printf("\n>> Entrada inválida. Por favor, insira um número entre 1 e 4.\n");
            // Limpa o buffer de entrada
            while (getchar() != '\n'); // Consome até a nova linha
            continue; // Volta para o início do loop
        }
        setbuf(stdin, NULL);

        switch (opc) {
            case 1: {
                printf("\n>> Preencha com as informações do paciente:\n");
                paciente p;
                printf("Nome: ");
                fgets(p.nome, sizeof(p.nome), stdin);
                p.nome[strcspn(p.nome, "\n")] = 0;

                // Validação do nome
                while (!nomeValido(p.nome)) {
                    printf("\n>> Nome inválido. O nome não pode conter números. Por favor, tente novamente.\n");
                    printf("Nome: ");
                    fgets(p.nome, sizeof(p.nome), stdin);
                    p.nome[strcspn(p.nome, "\n")] = 0;
                }

                printf("Idade: ");
                while (scanf("%d", &p.idade) != 1 || p.idade < 0) {
                    printf("\n>> Idade inválida. Por favor, tente novamente.\n");
                    printf("Idade: ");
                    setbuf(stdin, NULL);
                }
                setbuf(stdin, NULL);

                printf("\nSexo: \n[1] Masculino \n[2] Feminino \n");
                printf("\nEscolha uma opção: ");
                while (scanf("%d", &p.sexo) != 1 || (p.sexo != 1 && p.sexo != 2)) {
                    printf("\n>> Opção inválida. Por favor, tente novamente.\n");
                    printf("Escolha uma opção: ");
                    setbuf(stdin, NULL);
                }
                setbuf(stdin, NULL);

                printf("\nConvênio: \n[1] SUS \n[2] Particular\n");
                printf("\nEscolha uma opção: ");
                while (scanf("%d", &p.convenio) != 1 || (p.convenio != 1 && p.convenio != 2)) {
                    printf("\n>> Opção inválida. Por favor, tente novamente.\n");
                    printf("Escolha uma opção: ");
                    setbuf(stdin, NULL);
                }
                setbuf(stdin, NULL);

                coletarUrgencia(&p);
                enfileirar(&fila, p);
                break;
            }
            case 2:
                // Organizar a fila por urgência antes de exibir
                organizarFilaPorUrgencia(&fila); // Organiza a sequência da lista antes de exibi-la
                exibirFila(&fila); // Exibe a lista
                break;
            case 3: {
                paciente removido = desenfileirar(&fila);
                if (removido.idade != 0) {
                    printf("\n>> Paciente %s removido com sucesso.\n", removido.nome);
                }
                break;
            }
            case 4:
                printf("\n>> Sistema encerrado. Agradecemos pela utilização!\n");
                free(fila.pacientes);
                return 0;
            default:
                printf("\n>> Opção inválida. Por favor, tente novamente.\n");
                break;
        }
    }
}