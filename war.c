#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===================== ESTRUTURA DO TERRITÓRIO =====================
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

// ===================== PROTÓTIPOS =====================
void exibirMapa(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
int verificarMissao(Territorio *mapa);
void pausar();

// ===================== FUNÇÃO PRINCIPAL =====================
int main() {
    srand(time(NULL));

    // --- Criação do mapa fixo ---
    const int qtd = 5;
    Territorio mapa[5] = {
        {"America", "Verde", 5},
        {"Europa", "Azul", 3},
        {"Asia", "Vermelho", 2},
        {"Africa", "Amarelo", 4},
        {"Oceania", "Branco", 1}
    };

    int opcao, atacante, defensor;

    do {
        system("clear || cls");

        // Exibe o mapa e a missão
        exibirMapa(mapa, qtd);
        printf("- SUA MISSAO (Exercito Azul) -\n");
        printf("Destruir o exercito Verde.\n");

        // Menu de ações
        printf("MENU DE ACOES\n");
        printf("1- Atacar\n");
        printf("2- Verificar Missao\n");
        printf("0- Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("\nFASE DE ATAQUE\n");
            printf("Escolha o territorio atacante (1 a 5): ");
            scanf("%d", &atacante);
            printf("Escolha o territorio defensor (1 a 5): ");
            scanf("%d", &defensor);

            if (atacante < 1 || atacante > 5 || defensor < 1 || defensor > 5) {
                printf("Territorio invalido!\n");
                pausar();
                continue;
            }

            if (strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0) {
                printf("O ataque nao pode ser feito: ambos sao do mesmo exercito!\n");
                pausar();
                continue;
            }

            atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
            printf("SUA MISSAO (Exercito Azul) o exercito Verde.\n");

            if (verificarMissao(mapa)) {
                printf("Voce cumpriu sua missao!\n");
                pausar();
                break;
            } else {
                printf("Voce ainda nao cumpriu sua missao. Continue a lutar!\n");
                pausar();
            }
        } 
        else if (opcao == 2) {
            printf("\nSUA MISSAO (Exercito Azul) o exercito Verde.\n");
            if (verificarMissao(mapa)) {
                printf("Voce cumpriu sua missao!\n");
                pausar();
                break;
            } else {
                printf("Voce ainda nao cumpriu sua missao. Continue a lutar!\n");
                pausar();
            }
        } 
        else if (opcao == 0) {
            printf("Saindo do jogo...\n");
            break;
        } 
        else {
            printf("Opcao invalida!\n");
            pausar();
        }

    } while (opcao != 0);

    return 0;
}

// ===================== EXIBIÇÃO DO MAPA =====================
void exibirMapa(Territorio *mapa, int qtd) {
    printf("MAPA DO MUNDO\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d.\t%-10s\t(Exercito:\t%-10s\tTropas : %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ===================== FUNÇÃO DE ATAQUE =====================
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("O territorio atacante nao tem tropas suficientes para atacar!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nRESULTADO DA BATALHA\n");
    printf("Ataque (%s): %d | Defesa (%s): %d\n",
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;
        if (defensor->tropas <= 0) {
            printf("O territorio %s foi conquistado por %s!\n",
                   defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}

// ===================== VERIFICAR MISSÃO =====================
int verificarMissao(Territorio *mapa) {
    // Missão: destruir todos os territórios do exército "Verde"
    for (int i = 0; i < 5; i++) {
        if (strcmp(mapa[i].cor, "Verde") == 0)
            return 0; // ainda existe território verde
    }
    return 1; // missão cumprida
}

// ===================== PAUSAR =====================
void pausar() {
    printf("PRESSIONE ENTER para continuar.");
    getchar();
    getchar();
}
