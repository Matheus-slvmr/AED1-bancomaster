#include <stdio.h>
#include <stdlib.h>

/* Constantes de controle padrao AED1 */
#define SUCESSO 1
#define FALHA -1
#define CHAVE_INVALIDA 0

/* Limites basicos do sistema */
#define MAX_CONTAS 100
#define MESES 12
#define CATEGORIAS 5

/* ================= UTILITARIOS DE INTERFACE ================= */

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void espacarTela(void) {
    int i;
    for (i = 0; i < 10; i++) {
        printf("\n");
    }
}

void pausarTela(void) {
    printf("\nPressione ENTER para voltar ao menu...");
    limparBuffer();
    espacarTela();
}

void exibirCabecalho(const char *titulo) {
    printf("\n+==========================================================+\n");
    printf("| %-56s |\n", titulo);
    printf("+==========================================================+\n");
}

void exibirMenuPrincipal(void) {
    printf("+==========================================================+\n");
    printf("|                BANCO MASTER - MENU PRINCIPAL             |\n");
    printf("|            Sistema Bancario Simplificado (AED1)          |\n");
    printf("+==========================================================+\n");
    printf("|  [1] Cadastro de Contas                  (Vetor)         |\n");
    printf("|  [2] Deposito e Saque                    (Vetor)         |\n");
    printf("|  [3] Transferencia entre Contas / Pix    (Vetor)         |\n");
    printf("|  [4] Extrato / Historico de Transacoes   (Lista)         |\n");
    printf("|  [5] Desfazer Ultima Operacao (Undo)     (Pilha)         |\n");
    printf("|  [6] Fila de Atendimento / Pix Agendado  (Fila)          |\n");
    printf("|  [7] Notificacoes do App                 (Deque)         |\n");
    printf("|  [8] Relatorio de Gastos (Mes/Categoria) (Matriz)        |\n");
    printf("+----------------------------------------------------------+\n");
    printf("|  [0] Sair                                                |\n");
    printf("+==========================================================+\n");
    printf("Escolha uma opcao: ");
}

int lerOpcaoMenu(void) {
    int opcao;
    int leitura;

    leitura = scanf("%d", &opcao);
    limparBuffer();

    if (leitura != 1) {
        return FALHA;
    }
    return opcao;
}

/* ============= ESQUELETO DAS FUNCOES PRINCIPAIS ============= */

/* 1. Cadastro de contas - Vetor de structs */
void menuCadastrarConta(void) {
    exibirCabecalho("1. CADASTRO DE CONTAS [VETOR]");
    printf("\n[TODO] Implementar cadastro de conta (id, nome, CPF, saldo)\n");
    printf("       Estrutura: Vetor de structs (Conta contas[MAX_CONTAS]).\n");
    pausarTela();
}

/* 2. Deposito e saque - Vetor de structs */
void menuDepositoSaque(void) {
    exibirCabecalho("2. DEPOSITO E SAQUE [VETOR]");
    printf("\n[TODO] Implementar deposito e saque com atualizacao de saldo\n");
    printf("       Estrutura: Vetor de structs.\n");
    pausarTela();
}

/* 3. Transferencia entre contas (Pix) - Vetor de structs */
void menuTransferenciaPix(void) {
    exibirCabecalho("3. TRANSFERENCIA / PIX [VETOR]");
    printf("\n[TODO] Implementar transferencia (debito origem / credito destino)\n");
    printf("       Estrutura: Vetor de structs.\n");
    pausarTela();
}

/* 4. Extrato / historico de transacoes - Lista encadeada */
void menuExtratoHistorico(void) {
    exibirCabecalho("4. EXTRATO E HISTORICO [LISTA ENCADEADA]");
    printf("\n[TODO] Implementar consulta de historico de transacoes da conta\n");
    printf("       Estrutura: Lista encadeada.\n");
    pausarTela();
}

/* 5. Desfazer ultima operacao (Undo) - Pilha */
void menuDesfazerOperacao(void) {
    exibirCabecalho("5. DESFAZER ULTIMA OPERACAO (UNDO) [PILHA]");
    printf("\n[TODO] Implementar pop na pilha e reversao da ultima operacao\n");
    printf("       Estrutura: Pilha (LIFO).\n");
    pausarTela();
}

/* 6. Fila de atendimento / Pix agendado - Fila */
void menuFilaAtendimento(void) {
    exibirCabecalho("6. FILA DE ATENDIMENTO / PIX AGENDADO [FILA]");
    printf("\n[TODO] Implementar enfileiramento e processamento em ordem FIFO\n");
    printf("       Estrutura: Fila (FIFO).\n");
    pausarTela();
}

/* 7. Notificacoes do app - Deque */
void menuNotificacoes(void) {
    exibirCabecalho("7. NOTIFICACOES DO APP [DEQUE]");
    printf("\n[TODO] Implementar insercao/remocao no inicio (urgente) e fim (normal)\n");
    printf("       Estrutura: Deque.\n");
    pausarTela();
}

/* 8. Relatorio de gastos por categoria/mes - Matriz */
void menuRelatorioGastos(void) {
    exibirCabecalho("8. RELATORIO DE GASTOS [MATRIZ]");
    printf("\n[TODO] Implementar lancamento e totais por mes e por categoria\n");
    printf("       Estrutura: Matriz (float gastos[MESES][CATEGORIAS]).\n");
    pausarTela();
}

/* ===================== FUNCAO PRINCIPAL ===================== */

int main(void) {
    int opcao;

    do {
        exibirMenuPrincipal();
        opcao = lerOpcaoMenu();

        switch (opcao) {
            case 1:
                menuCadastrarConta();
                break;
            case 2:
                menuDepositoSaque();
                break;
            case 3:
                menuTransferenciaPix();
                break;
            case 4:
                menuExtratoHistorico();
                break;
            case 5:
                menuDesfazerOperacao();
                break;
            case 6:
                menuFilaAtendimento();
                break;
            case 7:
                menuNotificacoes();
                break;
            case 8:
                menuRelatorioGastos();
                break;
            case 0:
                printf("\nEncerrando o Banco Master. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida! Informe um numero de 0 a 8.\n");
                pausarTela();
                break;
        }
    } while (opcao != 0);

    return 0;
}
