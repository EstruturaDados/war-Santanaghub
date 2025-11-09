#include <stdio.h>
#include <string.h>

/*
    Programa: Cadastro de Territórios + Mapa do Mundo
    Autor: [Seu Nome]
    Descrição:
        Este programa cria uma estrutura chamada "Territorio" para armazenar
        informações sobre territórios, incluindo nome, cor do exército e
        quantidade de tropas. O sistema permite o cadastro de 5 territórios
        e exibe um "mapa do mundo" mostrando o estado atual de todos os territórios.
*/

// Definição da struct Territorio
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

int main() {
    Territorio territorios[5]; // Vetor para armazenar 5 territórios

    printf("===== SISTEMA DE CADASTRO DE TERRITORIOS =====\n\n");

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome);  // Lê até 29 caracteres com espaços

        printf("Digite a cor do exercito: ");
        scanf(" %9s", territorios[i].cor);        // Lê uma palavra (sem espaços)

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("-------------------------------------------\n");
    }

    // Exibição do estado atual do "mapa do mundo"
    printf("\n===== MAPA DO MUNDO - ESTADO ATUAL =====\n\n");
    printf("%-5s | %-25s | %-10s | %-8s\n", "ID", "Nome do Território", "Cor", "Tropas");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++) {
        printf("%-5d | %-25s | %-10s | %-8d\n",
               i + 1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas );
    }

    printf("-------------------------------------------------------------\n");
    printf("n\ Fim da listagem do mapa do mundo.\n");

    return 0;
}