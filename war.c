// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
// int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

//     return 0;
// }

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TROOP 5

typedef struct{
    char name[30];
    char color[10];
    int troop;
} Territorio;

void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para rolar um dado de 6 lados
int rolarDado(){
    return (rand() % 6) + 1;
}

// Função para simular ataque entre territórios
void simularAtaque(Territorio *territory, int atacante, int defensor){
    if(territory[atacante].troop <= 1){
        printf("\n❌ Erro: O território atacante precisa ter pelo menos 2 tropas!\n");
        return;
    }
    
    if(territory[defensor].troop <= 0){
        printf("\n❌ Erro: O território defensor não possui tropas!\n");
        return;
    }
    
    printf("\n⚔️  BATALHA! ⚔️\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Atacante: %s (%s) - %d tropas\n", 
           territory[atacante].name, territory[atacante].color, territory[atacante].troop);
    printf("Defensor: %s (%s) - %d tropas\n", 
           territory[defensor].name, territory[defensor].color, territory[defensor].troop);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Rolar dados
    int dadoAtaque = rolarDado();
    int dadoDefesa = rolarDado();
    
    printf("\n🎲 Dados rolados:\n");
    printf("   Ataque: %d\n", dadoAtaque);
    printf("   Defesa: %d\n", dadoDefesa);
    printf("\n");
    
    // Resolver batalha (empate favorece atacante)
    if(dadoAtaque >= dadoDefesa){
        territory[defensor].troop--;
        printf("✅ ATACANTE VENCEU!\n");
        printf("   %s perde 1 tropa!\n", territory[defensor].name);
        
        // Verificar se território foi conquistado
        if(territory[defensor].troop == 0){
            printf("\n🏆 TERRITÓRIO CONQUISTADO!\n");
            printf("   %s conquistou %s!\n", territory[atacante].name, territory[defensor].name);
            
            // Transferir 1 tropa para o território conquistado
            territory[atacante].troop--;
            territory[defensor].troop = 1;
            strcpy(territory[defensor].color, territory[atacante].color);
            printf("   1 tropa foi movida para o território conquistado.\n");
        }
    } else {
        territory[atacante].troop--;
        printf("🛡️  DEFENSOR VENCEU!\n");
        printf("   %s perde 1 tropa!\n", territory[atacante].name);
    }
    
    printf("\n📊 Resultado:\n");
    printf("   %s: %d tropas\n", territory[atacante].name, territory[atacante].troop);
    printf("   %s: %d tropas\n", territory[defensor].name, territory[defensor].troop);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

int main(){
    // Alocar memória dinamicamente com calloc
    Territorio *territory = (Territorio*) calloc(MAX_TROOP, sizeof(Territorio));
    
    if(territory == NULL){
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    int totalTerritorio = 0;
    int option;

        printf("======================\n");
        printf("    WAR GAME - Part II\n");
        printf("======================\n");

    do {     

        
        // Exibir tropas cadastradas
        if(totalTerritorio > 0) {
            printf("======================\n");
            printf("\nTROPAS CADASTRADAS:\n");
            printf("======================\n");
            for(int i = 0; i < totalTerritorio; i++) {
                printf("%s - %s - %d \n", 
                    territory[i].name, territory[i].color, territory[i].troop);
            }
            printf("\n");
        } else {
            printf("\nNenhuma tropa cadastrada ainda.\n\n");
        }
        
        printf("======================\n");
        printf("1 - Cadastrar Tropa \n");
        printf("2 - Simular Ataque\n");
        printf("0 - Para sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);
        limparBufferEntrada();

    switch (option){
        case 1:
            printf("\n=== Cadastrar Nova Tropa ===\n");

            if(totalTerritorio < MAX_TROOP) {
                printf("Digite o nome do território: ");
                fgets(territory[totalTerritorio].name, 30, stdin);
                territory[totalTerritorio].name[strcspn(territory[totalTerritorio].name, "\n")] = 0;

                printf("Digite a cor da tropa: ");
                fgets(territory[totalTerritorio].color, 10, stdin);
                territory[totalTerritorio].color[strcspn(territory[totalTerritorio].color, "\n")] = 0;

                printf("Digite o número de tropas: ");
                scanf("%d", &territory[totalTerritorio].troop);
                limparBufferEntrada();

                if(territory[totalTerritorio].troop <= 0) {
                    printf("\nErro: O número de tropas deve ser maior que zero.\n");
                } else {
                    totalTerritorio++;
                    printf("\n✓ Tropa cadastrada com sucesso!\n");
                }
            } else {
                printf("\nLimite máximo de territórios atingido.\n");
            }
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        case 2:
            printf("\n=== Simular Ataque ===\n");
            
            if(totalTerritorio < 2){
                printf("\n❌ É necessário ter pelo menos 2 territórios cadastrados!\n");
            } else {
                printf("\nTerritórios disponíveis:\n");
                for(int i = 0; i < totalTerritorio; i++){
                    printf("[%d] %s (%s) - %d tropas\n", 
                           i+1, territory[i].name, territory[i].color, territory[i].troop);
                }
                
                int atacante, defensor;
                printf("\nEscolha o território ATACANTE (1-%d): ", totalTerritorio);
                scanf("%d", &atacante);
                limparBufferEntrada();
                
                printf("Escolha o território DEFENSOR (1-%d): ", totalTerritorio);
                scanf("%d", &defensor);
                limparBufferEntrada();
                
                // Validar entrada
                if(atacante < 1 || atacante > totalTerritorio || 
                   defensor < 1 || defensor > totalTerritorio){
                    printf("\n❌ Territórios inválidos!\n");
                } else if(atacante == defensor){
                    printf("\n❌ Um território não pode atacar a si mesmo!\n");
                } else {
                    // Converter para índice do array (0-based)
                    simularAtaque(territory, atacante-1, defensor-1);
                }
            }
            
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        case 0:
            printf("Saindo do programa...\n");
            break;

        default:
            printf("\nOpção inválida. Tente novamente.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            break;
    }

    } while (option != 0);

    // Liberar memória alocada
    free(territory);
    
    printf("\n👋 Obrigado por jogar WAR GAME!\n");
    
    return 0;
}
