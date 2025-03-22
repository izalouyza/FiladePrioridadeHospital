//Classificação de risco
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
    char nome[100]; // nome completo do paciente
    int idade;
    int sexo; // [1]M ou [2]F
    int convenio; // [1] SUS [2] Particular
} paciente;

int capac = 2; //capacidade inicial
paciente *pacientes = NULL;
int cod = 0;

void realocar(){
    capac *= 2;
    paciente *p = realloc(pacientes, capac * sizeof(paciente));
    if(p == NULL){
        printf("\n>> Erro de realocação de memória.\n");
        exit(1);
    }
    pacientes = p; //atualizar ponteiro
}

void cadastro(paciente *p){
    if(cod > capac){
        realocar();
    }
    printf("\n======================= Cadastro de pacientes =======================\n");
    printf(">> Nome do paciente: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0;
    setbuf(stdin, NULL);

    printf(">> Idade do paciente: ");
    while(1){
        if(scanf("%d", &p->idade) != 1){
            printf("\n>> Conteúdo inválido, por favor tente novamente.\n");
            while(getchar() != '\n');
        }else{break;}
    }
    setbuf(stdin, NULL);

    printf(">> Sexo do paciente: \n[1] Masculino \n[2] Feminino \n");
    while(1){
        if(scanf("%d", &p->sexo) != 1 || p->sexo < 1 || p->sexo > 2){
            printf("\n>> Conteúdo inválido, por favor tente novamente.\n");
            while(getchar() != '\n');
        }else{break;}
    }
    setbuf(stdin, NULL);

    printf(">> Convênio do paciente: \n[1] SUS \n[2] Particular\n");
    while(1){
        if(scanf("%d", &p->convenio) != 1 || p->convenio < 1 || p->convenio > 2){
            printf("\n>> Conteúdo inválido, por favor tente novamente.\n");
            while(getchar() != '\n');
        }else{break;}
    }
    setbuf(stdin, NULL);
    printf("\n>> Operação realidzada com sucesso.\n");
}

void exibir(){
    if(cod > 0){
        printf("\n======================= Listagem de Pacientes =======================\n");
        for(int i = 0; i < cod; i++){
            printf("\n----- Paciente %d -----\n", i+1);
            printf("Nome: %s\n", pacientes[i].nome);
            printf("Idade: %d\n", pacientes[i].idade);
            printf("Sexo: %s\n", (pacientes[i].sexo == 1) ? "Masculino" : "Feminino");
            printf("Convênio: %s\n", (pacientes[i].convenio == 1) ? "SUS" : "Particular");
            printf("-----------------------\n");
        }
    }else{printf("\n>> Lista de pacientes vazia.\n");}
}

void remover(){
    if(cod > 0){
        exibir();
        int num = 0;
        printf("\n>> Código do cadastro a ser removido: ");
        while(1){
            if(scanf("%d", &num) != 1 || num < 1 || num > cod){
                printf("\n>> Opção inválida, por favor tente novamente.\n");
                while(getchar() != '\n');
            }else{break;}
        }
        setbuf(stdin, NULL);
        num--;
        for(int i = num; i < cod-1; i++){
            pacientes[i] = pacientes[i+1];
        }
        cod--;
        printf("\n>> Operação realidzada com sucesso.\n");
    }else{printf("\n>> Lista de pacientes vazia.\n");}
}

int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8"); //Coloca para português automaticamente
    system("chcp 65001");
    int opc = 0;
    int num = 0;
    pacientes = malloc(capac * sizeof(paciente));
    if(pacientes == NULL){
        printf("\n>> Erro ao alocar memória.\n");
        exit(1);
    }
    while(1){
        printf("\n================= Sistema de atendimento hospitalar ================= \n");
        printf("[1] Cadastrar paciente \n[2] Exibir cadastros \n[3] Atualizar cadastro \n[4] Remover cadastro \n[5] Sair \n");
        printf(">> Opção: ");
        while(1){
            if(scanf("%d", &opc) != 1){
                printf("\n>> Opção inválida, por favor tente novamente.\n");
                while(getchar() != '\n');
            }else{break;}
        }
        setbuf(stdin, NULL);
        switch(opc){
            case 1: //cadastrar
                cadastro(&pacientes[cod]);
                cod++;
                break;
            case 2: //exibir
                exibir();
                break;
            case 3: //atualizar
                if(cod > 0){
                    printf("Digite o código do paciente que deseja atualizar: ");
                    while(1){
                        if(scanf("%d", &num) != 1 || num < 1 || num > cod){
                            printf("\n>> Opção inválida, por favor tente novamente.\n");
                            while(getchar() != '\n');
                        }else{break;}
                    }
                    setbuf(stdin, NULL);
                    cadastro(&pacientes[num-1]);
                }else{printf("\n>> Lista de pacientes vazia.\n");}
                break;
            case 4: // remover
                remover();
                break;
            case 5: //sair
                printf(">> Tem certeza de que deseja sair? \n[1] Sim \n[2] Não\n");
                while(1){
                    if(scanf("%d", &opc) != 1 || opc < 1 || opc > 2){
                        printf("\n>> Opção inválida, por favor tente novamente.\n");
                        while(getchar() != '\n');
                    }else{break;}
                }
                if(opc == 1){
                    printf("\n>> Obrigado, volte sempre.\n");
                    free(pacientes);
                    return 0;
                }
                break;
            default:
                printf("\n>> Opção inválida, por favor tente novamente.\n");
                break;
        }
    }
}
