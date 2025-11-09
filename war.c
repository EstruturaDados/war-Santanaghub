#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===================== ESTRUTURA DO TERRITÓRIO =====================
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército (jogador)
    int tropas;      // Quantidade de tropas
} Territorio;

// ===================== PROTÓTIPOS DAS FUNÇÕES =====================
Territorio* cadastrarTerritorios(int *qtd);
void exibirTerritorios(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa);

// ===================== FUNÇÃO PRINCIPAL =====================
int main() {
    srand(time(NULL)); // Garante aleatoriedade para rand()

    int qtd;
    printf("=== SISTEMA DE TERRITÓRIOS ===\n\n");
    printf("Digite o número de territórios a serem cadastrados: ");
    scanf("%d", &qtd);

    // Alocação dinâmica do vetor de territórios
    Territorio *mapa = malloc(qtd * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro dos territórios
    mapa = cadastrarTerritorios(&qtd);

    // Exibe o estado inicial do mapa
    exibirTerritorios(mapa, qtd);

    // Simulação de ataques
    int opcao;
    do {
        printf("\nDeseja realizar um ataque? (1 - Sim / 0 - Não): ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int iAtacante, iDefensor;

            printf("\nEscolha o território atacante (0 a %d): ", qtd - 1);
            scanf("%d", &iAtacante);

            printf("Escolha o território defensor (0 a %d): ", qtd - 1);
            scanf("%d", &iDefensor);

            // Validação das escolhas
            if (iAtacante < 0 || iAtacante >= qtd ||
                iDefensor < 0 || iDefensor >= qtd) {
                printf("⚠️  Índices inválidos! Tente novamente.\n");
                continue;
            }

            if (strcmp(mapa[iAtacante].cor, mapa[iDefensor].cor) == 0) {
                printf("⚠️  O ataque não é permitido: ambos pertencem ao mesmo exército!\n");
                continue;
            }

            atacar(&mapa[iAtacante], &mapa[iDefensor]);
            exibirTerritorios(mapa, qtd);
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    printf("\nSistema encerrado. Memória liberada com sucesso.\n");

    return 0;
}

// ===================== FUNÇÃO: CADASTRAR TERRITÓRIOS =====================
Territorio* cadastrarTerritorios(int *qtd) {
    Territorio *mapa = malloc(*qtd * sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    for (int i = 0; i < *qtd; i++) {
        printf("\nCadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %9s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    return mapa;
}

// ===================== FUNÇÃO: EXIBIR TERRITÓRIOS =====================
void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n===== MAPA ATUAL =====\n");
    printf("%-5s | %-25s | %-10s | %-8s\n", "ID", "Nome", "Cor", "Tropas");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < qtd; i++) {
        printf("%-5d | %-25s | %-10s | %-8d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    printf("-------------------------------------------------------------\n");
}

// ===================== FUNÇÃO: ATAQUE =====================
// Simula um ataque entre dois territórios usando dados aleatórios
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("⚠️  O território atacante não possui tropas suficientes para atacar!\n");
        return;
    }

    printf("\n🎯=== ATAQUE EM ANDAMENTO ===🎯\n");
    printf("%s (%s) ATACA %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Rolagem de dados (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado atacante: %d 🎲 | Dado defensor: %d 🎲\n", dadoAtacante, dadoDefensor);

    // Resultado da batalha
    if (dadoAtacante > dadoDefensor) {
        printf("✅ O atacante venceu a batalha!\n");

        // Atualiza o defensor: muda de dono e ganha metade das tropas do atacante
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        // O atacante perde 1 tropa
        atacante->tropas -= 1;

        printf("🏳️  O território %s foi conquistado por %s!\n",
               defensor->nome, defensor->cor);
    } else {
        printf("❌ O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }
}

// ===================== FUNÇÃO: LIBERAR MEMÓRIA =====================
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}
