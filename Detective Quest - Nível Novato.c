#include <stdio.h>
#include <stdlib.h> // Essencial para malloc
#include <string.h> // Para manipulação de strings

// ----------------------------------------------------------------------------
// Conceitos Trabalhados: Structs, Árvore Binária, Alocação Dinâmica
// ----------------------------------------------------------------------------

// Structs: Criação de um tipo personalizado (Sala)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda; // Filho esquerdo
    struct Sala *direita;  // Filho direito
} Sala;

// --- Protótipos das Funções (Modularização) ---
Sala* criarSala(const char* nome);
void explorarMansao(Sala* raiz);
void limparBufferEntrada();

// ----------------------------------------------------------------------------
// --- Implementação das Funções Auxiliares ---
// ----------------------------------------------------------------------------

void limparBufferEntrada() {
    // Modularização: Limpeza de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// criarSala():
// Função utilitária para criar e alocar memória para um novo nó da árvore.
Sala* criarSala(const char* nome) {
    // Alocação dinâmica: uso de malloc para criação de nós da árvore.
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        perror("Falha na alocação de memória para nova sala.");
        exit(EXIT_FAILURE);
    }
    
    // Inicialização
    strncpy(novaSala->nome, nome, sizeof(novaSala->nome) - 1);
    novaSala->nome[sizeof(novaSala->nome) - 1] = '\0';
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// ----------------------------------------------------------------------------
// --- Implementação da Lógica de Exploração ---
// ----------------------------------------------------------------------------

// explorarMansao():
// Permite a exploração interativa da mansão até o nó-folha.
void explorarMansao(Sala* raiz) {
    Sala* atual = raiz;
    char escolha;
    int salasVisitadas = 0;
    
    printf("\n--- Início da Exploração ---\n");
    printf("Comandos: (e) para esquerda, (d) para direita, (s) para sair.\n");
    
    // Loop principal da exploração
    while (atual != NULL) {
        salasVisitadas++;
        printf("\nVocê está em: %s\n", atual->nome);

        // Verifica se é um nó-folha (não possui caminhos à esquerda nem à direita)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n[FIM] CÔMODO SEM SAÍDAS. A exploração terminou aqui!\n");
            break; // Sai do loop
        }

        // Apresenta as opções disponíveis
        printf("Caminhos disponíveis: ");
        if (atual->esquerda) printf("(e) Esquerda ");
        if (atual->direita) printf("(d) Direita ");
        printf("> ");
        
        // Leitura e controle de fluxo
        if (scanf(" %c", &escolha) != 1) {
            limparBufferEntrada();
            continue; // Tenta novamente
        }

        // Operadores condicionais: controle das decisões do jogador
        Sala* proximaSala = NULL;
        if (escolha == 'e' || escolha == 'E') {
            proximaSala = atual->esquerda;
        } else if (escolha == 'd' || escolha == 'D') {
            proximaSala = atual->direita;
        } else if (escolha == 's' || escolha == 'S') {
            printf("\n[SAÍDA] Você abandonou a exploração.\n");
            break; // Sai do loop
        } else {
            printf("[ERRO] Comando inválido. Tente 'e', 'd', ou 's'.\n");
            continue;
        }

        // Navegação
        if (proximaSala != NULL) {
            atual = proximaSala;
        } else {
            printf("[ALERTA] Caminho inexistente ou bloqueado. Escolha novamente.\n");
        }
    }
    
    printf("\n--- FIM DO REGISTRO ---\n");
    printf("Total de %d sala(s) visitada(s).\n", salasVisitadas);
    printf("---------------------------\n");
}


// ----------------------------------------------------------------------------
// --- Função Principal (main) ---
// ----------------------------------------------------------------------------

int main() {
    // --------------------------------------------------------------------
    // Criação da Árvore Binária (Estrutura definida manualmente no código-fonte)
    // Árvore Binária: estrutura de dados hierárquica com dois filhos por nó.
    // --------------------------------------------------------------------

    // Raiz: Hall de entrada
    Sala* hall = criarSala("Hall de Entrada");

    // Nível 1
    Sala* sala_estar = criarSala("Sala de Estar");
    Sala* biblioteca = criarSala("Biblioteca");
    hall->esquerda = sala_estar;
    hall->direita = biblioteca;

    // Nível 2
    Sala* cozinha = criarSala("Cozinha");
    Sala* escritorio = criarSala("Escritorio");
    sala_estar->esquerda = cozinha;
    sala_estar->direita = criarSala("Jantar"); // Folha 1
    
    biblioteca->esquerda = criarSala("Quarto Mestre"); // Folha 2
    biblioteca->direita = escritorio;

    // Nível 3 (Nós Folha)
    cozinha->esquerda = escritorio; // Caminho cruzado (Opcional)
    cozinha->direita = criarSala("Jardim"); // Folha 3

    escritorio->esquerda = criarSala("Quarto de Hospedes"); // Folha 4
    // escritorio->direita é NULL (Folha)
    
    // Permite a exploração interativa da mansão a partir do Hall de entrada
    explorarMansao(hall);

    // Nota: Em um programa real, a memória deveria ser liberada aqui
    // (ex: free(hall); free(sala_estar); ...), mas para este Nível Novato,
    // o foco é apenas na alocação, structs e navegação.

    return 0;
}