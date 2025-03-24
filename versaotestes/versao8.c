#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h> // Para a função isdigit

// Estrutura que representa um paciente
typedef struct {
    int num_ficha; // Número da ficha do paciente na sequência
    char nome[100]; // Nome do paciente
    int idade; // Idade em anos do paciente
    int sexo; // [1] Masculino ou [2] Feminino
    int convenio; // [1] SUS [2] Particular
    int urgencia; // [1] Azul, [2] Verde, [3] Amarelo, [4] Laranja, [5] Vermelho
} Paciente;

// Estrutura que representa a fila de pacientes
typedef struct {
    Paciente *pacientes; // Ponteiro para um array de pacientes
    int inicio; // Índice do início da fila
    int fim; // Índice do fim da fila
    int capacidade; // Capacidade da fila
} Fila;

// Função para inicializar a fila
void inicializarFila(Fila *f, int capacidade) {
    f->capacidade = capacidade; // Define a capacidade da fila
    f->pacientes = malloc(capacidade * sizeof(Paciente)); // Aloca memória para os pacientes
    f->inicio = 0; // Inicializa o índice de início
    f->fim = 0; // Inicializa o índice de fim
}

// Função para verificar se a fila está cheia
int estaCheia(const Fila *f) {
    return (f->fim == f->capacidade); // Retorna 1 se a fila estiver cheia
}

// Função para verificar se a fila está vazia
int estaVazia(const Fila *f) {
    return (f->inicio == f->fim); // Retorna 1 se a fila estiver vazia
}

// Função para adicionar um paciente à fila
void enfileirar(Fila *f, Paciente p) {
    if (estaCheia(f)) {
        printf("\n>> Fila cheia. Não é possível adicionar mais pacientes.\n");
        return; // Se a fila estiver cheia, não adiciona o paciente
    }

    // Inserir o paciente na fila
    f->pacientes[f->fim] = p; // Adiciona o paciente na posição 'fim'
    f->pacientes[f->fim].num_ficha = f->fim + 1; // Atribui o número da ficha
    f->fim++; // Incrementa o índice de fim
    printf("\n>> Paciente adicionado à fila com sucesso.\n");
}

// Função para organizar a fila por urgência
void organizarFilaPorUrgencia(Fila *f) {
    for (int i = f->inicio; i < f->fim - 1; i++) {
        for (int j = i + 1; j < f->fim; j++) {
            if (f->pacientes[i].urgencia < f->pacientes[j].urgencia) {
                // Troca os pacientes de lugar e dá a prioridade para aquele com mais urgência
                Paciente temp = f->pacientes[i];
                f->pacientes[i] = f->pacientes[j];
                f->pacientes[j] = temp;
            }
        }
    }
}

// Função para remover um paciente da fila
Paciente desenfileirar(Fila *f) {
    if (estaVazia(f)) {
        printf("\n>> Fila vazia. Não há pacientes para serem removidos.\n");
        Paciente vazio = {0, "", 0, 0, 0, 0}; // Retorna um paciente vazio
        return vazio;
    }
    Paciente removido = f->pacientes[f->inicio]; // Armazena o paciente a ser removido
    f->inicio++; // Incrementa o índice de início

    // Atualiza os números das fichas dos pacientes restantes
    for (int i = f->inicio; i < f->fim; i++) {
        f->pacientes[i].num_ficha = i + 1; // Atualiza o número da ficha
    }

    return removido; // Retorna o paciente removido
}

// Função para exibir os dados de um paciente
void exibirPaciente(const Paciente *p) {
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
    
    // Exibe a urgência do paciente
    switch (p->urgencia) {
        case 1: printf("Urgência: Azul (Não Urgente)\n"); break;
        case 2: printf("Urgência: Verde (Pouco Urgente)\n"); break;
        case 3: printf("Urgência: Amarelo (Urgente)\n"); break;
        case 4: printf("Urgência: Laranja (Muito Urgente)\n"); break;
        case 5: printf("Urgência: Vermelho (Emergência)\n"); break;
    }
    printf("—----------------------------------------------------------------------------------------------\n");
}

// Função para validar o nome do paciente
int nomeValido(const char *nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (isdigit(nome[i])) {
            return 0; // Nome inválido se contém números
        }
    }
    return 1; // Nome válido
}

// Função para alterar os dados de um paciente
void alterarDadosPaciente(Fila *f) {
    printf("\n================================= Alterar Dados de Paciente ===================================\n\n");
    // Verifica se a fila está vazia
    if (estaVazia(f)) {
        printf(">> A fila está vazia. Não há pacientes para alterar.\n");
        return;
    }
    int num_ficha;
    printf(">> Informe o número da ficha do paciente que deseja alterar: ");
    
    while (1) {
        // Verifica se a entrada é um número inteiro e positivo
        if (scanf("%d", &num_ficha) != 1 || num_ficha <= 0 || num_ficha > f->fim) {
            printf(">> Número de ficha inválido. Deve ser um número inteiro positivo. Por favor, tente novamente.\n");
            printf(">> Informe o número da ficha do paciente que deseja alterar: ");
            while (getchar() != '\n'); // Limpa o buffer
        } else {
            break; // A entrada é válida, sai do loop
        }
    }
    
    int index = num_ficha - 1; // Ajusta para o índice da fila (começa do 0)
    Paciente *p = &f->pacientes[index]; // Ponto para o paciente a ser alterado
    
    printf("\n>> Atualizando os dados do paciente Nº %d. Preencha com as informações do paciente:\n", p->num_ficha);

    // Atualizando os dados do paciente
    printf("Nome: ");
    getchar(); // Limpa o buffer
    fgets(p->nome, sizeof(p->nome), stdin); // Lê o nome do paciente
    p->nome[strcspn(p->nome, "\n")] = 0; // Remove a quebra de linha

    // Validação do nome
    while (!nomeValido(p->nome)) {
        printf("\n>> Nome inválido. O nome não pode conter números. Por favor, tente novamente.\n");
        printf("Nome: ");
        fgets(p->nome, sizeof(p->nome), stdin);
        p->nome[strcspn(p->nome, "\n")] = 0; // Remove a quebra de linha
    }

    // Atualiza a idade do paciente
    printf("Idade: ");
    while (scanf("%d", &p->idade) != 1 || p->idade < 0) {
        printf("\n>> Idade inválida. Tente novamente.\n");
        printf("Idade: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    // Atualiza o sexo do paciente
    printf("\nSexo: \n[1] Masculino \n[2] Feminino \nEscolha uma opção: ");
    while (scanf("%d", &p->sexo) != 1 || (p->sexo != 1 && p->sexo != 2)) {
        printf("\n>> Opção inválida. Tente novamente.\n");
        printf("Escolha uma opção: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    // Atualiza o convênio do paciente
    printf("\nConvênio: \n[1] SUS \n[2] Particular\nEscolha uma opção: ");
    while (scanf("%d", &p->convenio) != 1 || (p->convenio != 1 && p->convenio != 2)) {
        printf("\n>> Opção inválida. Tente novamente.\n");
        printf("Escolha uma opção: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    // Coletar urgência
    printf("\n>> Classificação de urgência:\n");
    printf("[1] Azul (Não Urgente)\n");
    printf("[2] Verde (Pouco Urgente)\n");
    printf("[3] Amarelo (Urgente)\n");
    printf("[4] Laranja (Muito Urgente)\n");
    printf("[5] Vermelho (Emergência)\n");
    printf("\nInforme a urgência do paciente: ");
    
    while (1) {
        if (scanf("%d", &p->urgencia) != 1 || p->urgencia < 1 || p->urgencia > 5) {
            printf("\n>> Entrada inválida. Por favor, insira um número entre 1 e 5.\n");
            while (getchar() != '\n'); // Consome até a nova linha
            printf("Informe a urgência do paciente: ");
            continue; // Volta para o início do loop
        }
        break; // Urgência válida, sai do loop
    }

    printf("\n>> Dados do paciente %s atualizados com sucesso.\n", p->nome);
}

// Função para exibir todos os pacientes na fila
void exibirFila(const Fila *f) {
    if (estaVazia(f)) {
        printf("\n>> Fila vazia. Não há pacientes para serem exibidos.\n");
        return;
    }
    printf("\n====================================== Fila de Pacientes ======================================\n\n");
    for (int i = f->inicio; i < f->fim; i++) {
        exibirPaciente(&f->pacientes[i]); // Exibe cada paciente na fila
    }
}

// Função principal
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Define a localidade para português
    system("chcp 65001"); // Configura a codificação para UTF-8
    
    Fila fila; // Declara a fila de pacientes
    inicializarFila(&fila, 10); // Inicializa a fila com capacidade para 10 pacientes
    int opc = 0; // Variável para armazenar a opção do menu

    // Loop principal do sistema
    while (1) {
        printf("\n============================== Sistema de atendimento hospitalar ==============================\n\n");
        printf("[1] Adicionar paciente à fila \n[2] Exibir fila de pacientes \n[3] Remover paciente da fila \n[4] Alterar dados de paciente \n[5] Sair \n");
        printf("\n>> Escolha uma opção: ");
        
        // Verifica se a entrada é um número inteiro
        if (scanf("%d", &opc) != 1) {
            printf("\n>> Entrada inválida. Por favor, insira um número entre 1 e 5.\n");
            while (getchar() != '\n'); // Consome até a nova linha
            continue; // Volta para o início do loop
        }

        // Switch para tratar as opções do menu
        switch (opc) {
            case 1: {
                printf("\n================================= Adicionar Pacientes à Fila ==================================\n\n");
                printf(">> Preencha com as informações do paciente:\n");
                Paciente p; // Declara um paciente
                printf("Nome: ");
                getchar(); // Limpa o buffer
                fgets(p.nome, sizeof(p.nome), stdin); // Lê o nome do paciente
                p.nome[strcspn(p.nome, "\n")] = 0; // Remove a quebra de linha

                // Validação do nome
                while (!nomeValido(p.nome)) {
                    printf("\n>> Nome inválido. O nome não pode conter números. Por favor, tente novamente.\n");
                    printf("Nome: ");
                    fgets(p.nome, sizeof(p.nome), stdin);
                    p.nome[strcspn(p.nome, "\n")] = 0; // Remove a quebra de linha
                }

                // Atualiza a idade do paciente
                printf("Idade: ");
                while (scanf("%d", &p.idade) != 1 || p.idade < 0) {
                    printf("\n>> Idade inválida. Por favor, tente novamente.\n");
                    printf("Idade: ");
                    while (getchar() != '\n'); // Limpa o buffer
                }

                // Atualiza o sexo do paciente
                printf("\nSexo: \n[1] Masculino \n[2] Feminino \nEscolha uma opção: ");
                while (scanf("%d", &p.sexo) != 1 || (p.sexo != 1 && p.sexo != 2)) {
                    printf("\n>> Opção inválida. Por favor, tente novamente.\n");
                    printf("Escolha uma opção: ");
                    while (getchar() != '\n'); // Limpa o buffer
                }

                // Atualiza o convênio do paciente
                printf("\nConvênio: \n[1] SUS \n[2] Particular\nEscolha uma opção: ");
                while (scanf("%d", &p.convenio) != 1 || (p.convenio != 1 && p.convenio != 2)) {
                    printf("\n>> Opção inválida. Por favor, tente novamente.\n");
                    printf("Escolha uma opção: ");
                    while (getchar() != '\n'); // Limpa o buffer
                }

                // Coletar urgência
                printf("\n>> Classificação de urgência:\n");
                printf("[1] Azul (Não Urgente)\n");
                printf("[2] Verde (Pouco Urgente)\n");
                printf("[3] Amarelo (Urgente)\n");
                printf("[4] Laranja (Muito Urgente)\n");
                printf("[5] Vermelho (Emergência)\n");
                printf("\nInforme a urgência do paciente: ");
                
                while (1) {
                    if (scanf("%d", &p.urgencia) != 1 || p.urgencia < 1 || p.urgencia > 5) {
                        printf("\n>> Entrada inválida. Por favor, insira um número entre 1 e 5.\n");
                        while (getchar() != '\n'); // Consome até a nova linha
                        printf("Informe a urgência do paciente: ");
                        continue; // Volta para o início do loop
                    }
                    break; // Urgência válida, sai do loop
                }

                enfileirar(&fila, p); // Adiciona o paciente à fila
                break;
            }
            case 2:
                // Organizar a fila por urgência antes de exibir
                organizarFilaPorUrgencia(&fila); // Organiza a sequência da lista antes de exibi-la
                exibirFila(&fila); // Exibe a lista
                break;
            case 3: {
                printf("\n================================== Remover Pacientes da Fila ==================================\n\n");
                Paciente removido = desenfileirar(&fila); // Remove um paciente da fila
                if (removido.idade != 0) {
                    printf(">> Paciente %s removido com sucesso.\n", removido.nome);
                }
                break;
            }
            case 4:
                alterarDadosPaciente(&fila);  // Chama a função para alterar dados do paciente
                break;
            case 5: {
                printf("\n============================================= Sair ============================================\n\n");
                printf(">> Tem certeza de que deseja sair? \n[1] Sim \n[2] Não\n");
                int opcSair; // Variável para armazenar a opção de saída
                while (1) {
                    if (scanf("%d", &opcSair) != 1 || opcSair < 1 || opcSair > 2) {
                        printf("\n>> Opção inválida, por favor tente novamente.\n");
                        while (getchar() != '\n'); // Limpa o buffer
                    } else {
                        break; // A entrada é válida, sai do loop
                    }
                }
                if (opcSair == 1) {
                    printf(">> Sistema encerrado. Agradecemos pela utilização!\n");
                    free(fila.pacientes); // Libera a memória alocada para a fila
                    return 0; // Encerra o programa
                }
                break; // Se a opção for 2, apenas sai do case e volta ao menu
            }
            default:
                printf("\n>> Opção inválida. Por favor, tente novamente.\n");
                break; // Se a opção não for válida, exibe mensagem de erro
        }
    }
}
