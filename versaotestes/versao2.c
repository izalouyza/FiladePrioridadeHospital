#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char nome[100]; // nome completo do paciente
    int idade;
    int sexo; // [1]M ou [2]F
    int convenio; // [1] SUS [2] Particular
    int urgencia; // [0] Azul, [1] Verde, [2] Amarelo, [3] Laranja, [4] Vermelho
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

int isFull(Fila *f) {
    return (f->rear == f->capac);
}

int isEmpty(Fila *f) {
    return (f->front == f->rear);
}

void enfileirar(Fila *f, paciente p) {
    if (isFull(f)) {
        printf("\n>> Fila cheia, não é possível adicionar mais pacientes.\n");
        return;
    }
    
    int i;
    for (i = f->rear - 1; (i >= f->front) && (f->pacientes[i].urgencia < p.urgencia); i--) {
        f->pacientes[i + 1] = f->pacientes[i];
    }
    f->pacientes[i + 1] = p;
    f->rear++;
    printf("\n>> Paciente adicionado à fila.\n");
}

paciente desenfileirar(Fila *f) {
    if (isEmpty(f)) {
        printf("\n>> Fila vazia, não há pacientes para remover.\n");
        paciente vazio = {"", 0, 0, 0, 0}; // Retorna um paciente vazio
        return vazio;
    }
    paciente removido = f->pacientes[f->front];
    for (int i = f->front; i < f->rear - 1; i++) {
        f->pacientes[i] = f->pacientes[i + 1];
    }
    f->rear--;
    return removido;
}

void exibirFila(Fila *f) {
    if (isEmpty(f)) {
        printf("\n>> Fila vazia.\n");
        return;
    }
    printf("\n======================= Fila de Pacientes =======================\n");
    for (int i = f->front; i < f->rear; i++) {
        printf("\n----- Paciente %d -----\n", i + 1);
        printf("Nome: %s\n", f->pacientes[i].nome);
        printf("Idade: %d\n", f->pacientes[i].idade);
        printf("Sexo: ");
        if (f->pacientes[i].sexo == 1) {
            printf("Masculino\n");
        } else {
            printf("Feminino\n");
        }
        
        printf("Convênio: ");
        if (f->pacientes[i].convenio == 1) {
            printf("SUS\n");
        } else {
            printf("Particular\n");
        }
        
        switch (f->pacientes[i].urgencia) {
            case 0: printf("Urgência: Azul (Não Urgente)\n"); break;
            case 1: printf("Urgência: Verde (Pouco Urgente)\n"); break;
            case 2: printf("Urgência: Amarelo (Urgente)\n"); break;
            case 3: printf("Urgência: Laranja (Muito Urgente)\n"); break;
            case 4: printf("Urgência: Vermelho (Emergência)\n"); break;
        }
        printf("-----------------------\n");
    }
}

void coletarUrgencia(paciente *p) {
    printf("Classificação de urgência:\n");
    printf("[0] Azul (Não Urgente)\n");
    printf("[1] Verde (Pouco Urgente)\n");
    printf("[2] Amarelo (Urgente)\n");
    printf("[3] Laranja (Muito Urgente)\n");
    printf("[4] Vermelho (Emergência)\n");
    printf("Escolha a urgência do paciente: ");
    
    while (1) {
        scanf("%d", &p->urgencia);
        if (p->urgencia >= 0 && p->urgencia <= 4) {
            break;
        } else {
            printf("Opção inválida. Por favor, escolha uma urgência válida: ");
        }
    }
    setbuf(stdin, NULL);
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001");
    
    Fila fila;
    inicializarFila(&fila, 10);
    int opc = 0;

    while (1) {
        printf("\n================= Sistema de atendimento hospitalar ================= \n");
        printf("[1] Adicionar paciente à fila \n[2] Exibir fila de pacientes \n[3] Remover paciente da fila \n[4] Sair \n");
        printf(">> Opção: ");
        scanf("%d", &opc);
        setbuf(stdin, NULL);

        switch (opc) {
            case 1: {
                paciente p;
                printf(">> Nome do paciente: ");
                fgets(p.nome, sizeof(p.nome), stdin);
                p.nome[strcspn(p.nome, "\n")] = 0;

                printf(">> Idade do paciente: ");
                scanf("%d", &p.idade);
                setbuf(stdin, NULL);

                printf(">> Sexo do paciente: \n[1] Masculino \n[2] Feminino \n");
                scanf("%d", &p.sexo);
                setbuf(stdin, NULL);

                printf(">> Convênio do paciente: \n[1] SUS \n[2] Particular\n");
                scanf("%d", &p.convenio);
                setbuf(stdin, NULL);

                coletarUrgencia(&p);
                enfileirar(&fila, p);
                break;
            }
            case 2:
                exibirFila(&fila);
                break;
            case 3: {
                paciente removido = desenfileirar(&fila);
                if (removido.idade != 0) {
                    printf("Paciente removido: %s\n", removido.nome);
                }
                break;
            }
            case 4:
                printf(">> Obrigado, volte sempre.\n");
                free(fila.pacientes);
                return 0;
            default:
                printf("\n>> Opção inválida, por favor tente novamente.\n");
                break;
        }
    }
}