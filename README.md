# Fila de Prioridade de Hospital

Este repositório refere-se ao trabalho da terceira unidade da disciplina de Estruturas de Dados I. O projeto tem como objetivo a implementação de um sistema de gerenciamento de prioridade de atendimento hospitalar, visando otimizar o fluxo de atendimento por meio de uma fila de prioridades.

O sistema permitirá o cadastramento de pacientes e a organização do atendimento com base em critérios de urgência, garantindo que aqueles com maior necessidade sejam atendidos primeiro. Dessa forma, busca-se tornar o processo de atendimento mais eficiente, reduzindo o tempo de espera para casos prioritários e contribuindo para uma melhor administração hospitalar.

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue)
![Ambiente](https://img.shields.io/badge/Ambiente-VSCode-blue)
![Último commit](https://img.shields.io/github/last-commit/izalouyza/FiladePrioridadeHospital)

---
## 👨‍👧‍👧 Autores

👨‍🏫 **Professor:** George Felipe Fernandes Vieira

👩‍🎓 **Discentes:**  
🔹 **Izadora Louyza Silva Figueiredo**  
🔹 **João Victor Carvalho Alves**  
🔹 **João Victor Ferreira**  
🔹 **Lívian Maria Lucena Gomes Pinheiro**  
🔹 **Maria Vitória Fernandes Rocha**  
🔹 **Renato Vitor Juvêncio Leite**  
🔹 **Victor Hugo de Oliveira**

---

## 1. Funcionalidades

O sistema de Fila de Prioridade de Hospital terá as seguintes funcionalidades:

| Funcionalidade                 | Descrição                                                   |  
|---------------------------------|-------------------------------------------------------------|  
| **Adicionar paciente à fila**   | Permite cadastrar um novo paciente na fila de atendimento. |  
| **Exibir fila de pacientes**    | Exibe todos os pacientes atualmente na fila de espera.     |  
| **Remover paciente da fila**    | Remove um paciente da fila com base na ordem de prioridade.|  
| **Alterar dados de paciente**   | Permite modificar informações de um paciente já cadastrado na fila. |  
| **Sair**                        | Encerra a execução do sistema.   

## 2. Como o sistema funciona?

O usuário terá acesso a uma interface interativa onde poderá visualizar as funcionalidades disponíveis e interagir com o sistema. Dessa forma, o sistema de Fila de Prioridade de Hospital permite que o usuário realize as seguintes ações:

```
============================== Sistema de atendimento hospitalar ==============================

[1] Adicionar paciente à fila
[2] Exibir fila de pacientes
[3] Remover paciente da fila
[4] Alterar dados de paciente
[5] Sair

>> Escolha uma opção:

```
#### Menu principal do sistema:
- **Adicionar paciente à fila**: o sistema permite cadastrar um novo paciente na fila de atendimento.  
- **Exibir fila de pacientes**: o sistema exibe todos os pacientes atualmente na fila de espera.  
- **Remover paciente da fila**: o sistema permite remover um paciente da fila com base na ordem de prioridade.
- **Alterar dados de paciente**: o sistema permite modificar informações de um paciente já cadastrado na fila.
- **Sair**: o usuário encerra a execução do sistema.
  
### 2.1 Exemplo de Fluxo de Uso

- **Cadastre alguns pacientes na fila** (opção 1).  
- **Exiba a fila de pacientes** para verificar quais pacientes estão aguardando atendimento (opção 2).  
-  **Remova um paciente da fila** após o atendimento (opção 3).  
- **Acompanhe a fila de pacientes e verifique a ordem de atendimento** (opção 2).
- **Se necessário, atualize o cadastro de um paciente** (opção 4).
- **Ao finalizar, saia do sistema** (opção 4).

### 2.2 Estrutura de pastas

```
FiladePrioridadeHospital/
src/
│
├── codigo-fonte/
│   ├── output/
│   └── codigo-fonte.c
│
└── README.md

```

### 3. Como compilar e executar o sistema

Para compilar e executar o sistema, siga os passos abaixo:

1. Primeiramente, certifique-se de ter um ambiente que suporte a linguagem C e um compilador (por exemplo, GCC).
   
2. Clone o repositório do projeto:

```
git clone https://github.com/izalouyza/FiladePrioridadeHospital
```

3. Acesse a pasta onde o código está:
   
```
cd FiladePrioridadeHospital/src
```
```
cd codigo-fonte
```

4. Compile o programa:

```
gcc -o sistemahospital codigo-fonte.c
```

5. Execute o programa:
   
```
.\sistemahospital
```
