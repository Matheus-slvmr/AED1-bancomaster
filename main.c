#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MESES 12
#define CATEGORIAS 5

typedef struct {
    int id;
    char nome[40];
    char cpf[15];
    float saldo;
} Conta;

typedef struct {
    Conta item[MAX];
    int prim, ult, tam;
} Lista_est;

void Limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void Espacar_tela() {
    int i;
    for (i = 0; i < 10; i++) {
        printf("\n");
    }
}

void Pausar_tela() {
    printf("\nPressione ENTER para continuar...");
    Limpar_buffer();
    Espacar_tela();
}

void Remover_quebra_linha(char texto[]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            texto[i] = '\0';
            break;
        }
    }
}

void Criar_Lista_vazia(Lista_est *L) {
    L->prim = 0;
    L->ult = 0;
    L->tam = 0;
}

int Verifica_lista_vazia(Lista_est L) {
    return (L.prim == L.ult);
}

int Verifica_lista_cheia(Lista_est L) {
    return (L.ult == MAX);
}

void Ler_conta(Conta *X) {
    printf("\nCADASTRO DE CONTA\n");
    printf("Entre com o ID da conta: ");
    scanf("%d", &X->id);
    Limpar_buffer();

    printf("Entre com o Nome do titular: ");
    fgets(X->nome, 40, stdin);
    Remover_quebra_linha(X->nome);

    printf("Entre com o CPF: ");
    fgets(X->cpf, 15, stdin);
    Remover_quebra_linha(X->cpf);

    printf("Entre com o Saldo inicial: ");
    scanf("%f", &X->saldo);
    Limpar_buffer();
}

void Exibir_conta(Conta X) {
    printf("**********************************************************\n");
    printf("ID da conta : %d\n", X.id);
    printf("Titular     : %s\n", X.nome);
    printf("CPF         : %s\n", X.cpf);
    printf("Saldo       : R$ %.2f\n", X.saldo);
    printf("**********************************************************\n");
}

void Insere_elemento_lista(Lista_est *L, Conta X) {
    int i, j;
    if (Verifica_lista_cheia(*L)) {
        printf("\nA LISTA DE CONTAS ESTA CHEIA - INSERE\n");
    } else {
        i = L->prim;
        while ((i < L->ult) && (X.id > L->item[i].id)) {
            i++;
        }
        if ((i < L->ult) && (X.id == L->item[i].id)) {
            printf("\nJA EXISTE UMA CONTA COM O ID %d\n", X.id);
        } else {
            if (i == L->ult) {
                L->item[i] = X;
            } else {
                for (j = L->ult; j > i; j--) {
                    L->item[j] = L->item[j - 1];
                }
                L->item[i] = X;
            }
            L->ult++;
            L->tam++;
            printf("\nINSERCAO REALIZADA COM SUCESSO\n");
        }
    }
}

void Remove_elemento_lista(Lista_est *L, Conta *X) {
    int i, j;
    if (Verifica_lista_vazia(*L)) {
        printf("\nA LISTA DE CONTAS ESTA VAZIA - REMOVE\n");
    } else {
        i = L->prim;
        while ((i < L->ult) && (X->id > L->item[i].id)) {
            i++;
        }
        if ((i == L->ult) || (X->id != L->item[i].id)) {
            printf("\nA CONTA COM ID %d NAO ESTA NA LISTA - REMOVE\n", X->id);
        } else {
            *X = L->item[i];
            for (j = i; j < L->ult - 1; j++) {
                L->item[j] = L->item[j + 1];
            }
            L->ult--;
            L->tam--;
            printf("\nCONTA REMOVIDA COM SUCESSO\n");
            Exibir_conta(*X);
        }
    }
}

void Consultar_conta_lista(Lista_est L, int id) {
    int i;
    if (Verifica_lista_vazia(L)) {
        printf("\nA LISTA DE CONTAS ESTA VAZIA - CONSULTA\n");
    } else {
        i = L.prim;
        while ((i < L.ult) && (id > L.item[i].id)) {
            i++;
        }
        if ((i == L.ult) || (id != L.item[i].id)) {
            printf("\nCONTA NAO ENCONTRADA - CONSULTA\n");
        } else {
            Exibir_conta(L.item[i]);
        }
    }
}

void Exibir_lista_estatica(Lista_est L) {
    int i;
    if (Verifica_lista_vazia(L)) {
        printf("\nA LISTA DE CONTAS ESTA VAZIA - EXIBIR LISTA\n");
    } else {
        printf("\n======= RELATORIO DE CONTAS CADASTRADAS (%d) =======\n", L.tam);
        for (i = L.prim; i < L.ult; i++) {
            Exibir_conta(L.item[i]);
        }
        printf("=================== FIM DA LISTA ===================\n");
    }
}

void Menu_cadastro_contas(Lista_est *L) {
    int op, id;
    Conta X;

    do {
        printf("+==========================================================+\n");
        printf("|             1. CADASTRO DE CONTAS [VETOR]                |\n");
        printf("+==========================================================+\n");
        printf("|  [1] Cadastrar nova conta                                |\n");
        printf("|  [2] Remover conta por ID                                |\n");
        printf("|  [3] Consultar conta por ID                              |\n");
        printf("|  [4] Listar todas as contas                              |\n");
        printf("+----------------------------------------------------------+\n");
        printf("|  [0] Voltar ao menu principal                            |\n");
        printf("+==========================================================+\n");
        printf("Opcao: ");
        if (scanf("%d", &op) != 1) {
            op = -1;
        }
        Limpar_buffer();

        switch (op) {
            case 1:
                Ler_conta(&X);
                Insere_elemento_lista(L, X);
                Pausar_tela();
                break;
            case 2:
                printf("\nEntre com o ID da conta para remover: ");
                scanf("%d", &id);
                Limpar_buffer();
                X.id = id;
                Remove_elemento_lista(L, &X);
                Pausar_tela();
                break;
            case 3:
                printf("\nEntre com o ID da conta para consultar: ");
                scanf("%d", &id);
                Limpar_buffer();
                Consultar_conta_lista(*L, id);
                Pausar_tela();
                break;
            case 4:
                Exibir_lista_estatica(*L);
                Pausar_tela();
                break;
            case 0:
                Espacar_tela();
                break;
            default:
                printf("\nENTRE COM A OPCAO CORRETA\n");
                Pausar_tela();
                break;
        }
    } while (op != 0);
}

int Buscar_posicao_conta(Lista_est L, int id) {
    int i;
    if (Verifica_lista_vazia(L)) {
        return -1;
    }
    i = L.prim;
    while ((i < L.ult) && (id > L.item[i].id)) {
        i++;
    }
    if ((i == L.ult) || (id != L.item[i].id)) {
        return -1;
    }
    return i;
}

void Depositar_conta(Lista_est *L, int id, float valor) {
    int pos;
    if (valor <= 0) {
        printf("\nVALOR INVALIDO PARA DEPOSITO\n");
    } else {
        pos = Buscar_posicao_conta(*L, id);
        if (pos == -1) {
            printf("\nCONTA COM ID %d NAO ENCONTRADA - DEPOSITO\n", id);
        } else {
            L->item[pos].saldo = L->item[pos].saldo + valor;
            printf("\nDEPOSITO REALIZADO COM SUCESSO\n");
            Exibir_conta(L->item[pos]);
        }
    }
}

void Sacar_conta(Lista_est *L, int id, float valor) {
    int pos;
    if (valor <= 0) {
        printf("\nVALOR INVALIDO PARA SAQUE\n");
    } else {
        pos = Buscar_posicao_conta(*L, id);
        if (pos == -1) {
            printf("\nCONTA COM ID %d NAO ENCONTRADA - SAQUE\n", id);
        } else {
            if (valor > L->item[pos].saldo) {
                printf("\nSALDO INSUFICIENTE - SALDO ATUAL: R$ %.2f\n", L->item[pos].saldo);
            } else {
                L->item[pos].saldo = L->item[pos].saldo - valor;
                printf("\nSAQUE REALIZADO COM SUCESSO\n");
                Exibir_conta(L->item[pos]);
            }
        }
    }
}

void Menu_deposito_saque(Lista_est *L) {
    int op, id;
    float valor;

    do {
        printf("+==========================================================+\n");
        printf("|                2. DEPOSITO E SAQUE [VETOR]               |\n");
        printf("+==========================================================+\n");
        printf("|  [1] Depositar em uma conta                              |\n");
        printf("|  [2] Sacar de uma conta                                  |\n");
        printf("|  [3] Consultar saldo por ID                              |\n");
        printf("+----------------------------------------------------------+\n");
        printf("|  [0] Voltar ao menu principal                            |\n");
        printf("+==========================================================+\n");
        printf("Opcao: ");
        if (scanf("%d", &op) != 1) {
            op = -1;
        }
        Limpar_buffer();

        switch (op) {
            case 1:
                printf("\nEntre com o ID da conta para deposito: ");
                scanf("%d", &id);
                Limpar_buffer();
                printf("Entre com o valor do deposito: ");
                scanf("%f", &valor);
                Limpar_buffer();
                Depositar_conta(L, id, valor);
                Pausar_tela();
                break;
            case 2:
                printf("\nEntre com o ID da conta para saque: ");
                scanf("%d", &id);
                Limpar_buffer();
                printf("Entre com o valor do saque: ");
                scanf("%f", &valor);
                Limpar_buffer();
                Sacar_conta(L, id, valor);
                Pausar_tela();
                break;
            case 3:
                printf("\nEntre com o ID da conta para consultar: ");
                scanf("%d", &id);
                Limpar_buffer();
                Consultar_conta_lista(*L, id);
                Pausar_tela();
                break;
            case 0:
                Espacar_tela();
                break;
            default:
                printf("\nENTRE COM A OPCAO CORRETA\n");
                Pausar_tela();
                break;
        }
    } while (op != 0);
}

void Menu_transferencia_pix() {
    printf("\n+==========================================================+\n");
    printf("|              3. TRANSFERENCIA / PIX [VETOR]              |\n");
    printf("+==========================================================+\n");
    printf("\nFuncionalidade ainda nao implementada.\n");
    Pausar_tela();
}

void Menu_extrato_historico() {
    printf("\n+==========================================================+\n");
    printf("|        4. EXTRATO E HISTORICO [LISTA ENCADEADA]          |\n");
    printf("+==========================================================+\n");
    printf("\nFuncionalidade ainda nao implementada.\n");
    Pausar_tela();
}

void Menu_desfazer_operacao() {
    printf("\n+==========================================================+\n");
    printf("|       5. DESFAZER ULTIMA OPERACAO (UNDO) [PILHA]         |\n");
    printf("+==========================================================+\n");
    printf("\nFuncionalidade ainda nao implementada.\n");
    Pausar_tela();
}

void Menu_fila_atendimento() {
    printf("\n+==========================================================+\n");
    printf("|      6. FILA DE ATENDIMENTO / PIX AGENDADO [FILA]        |\n");
    printf("+==========================================================+\n");
    printf("\nFuncionalidade ainda nao implementada.\n");
    Pausar_tela();
}

void Menu_notificacoes() {
    printf("\n+==========================================================+\n");
    printf("|              7. NOTIFICACOES DO APP [DEQUE]              |\n");
    printf("+==========================================================+\n");
    printf("\nFuncionalidade ainda nao implementada.\n");
    Pausar_tela();
}

void Menu_relatorio_gastos() {
    printf("\n+==========================================================+\n");
    printf("|            8. RELATORIO DE GASTOS [MATRIZ]               |\n");
    printf("+==========================================================+\n");
    printf("\nFuncionalidade ainda nao implementada.\n");
    Pausar_tela();
}

void Menu_principal() {
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

int main() {
    Lista_est L;
    int op;

    Criar_Lista_vazia(&L);

    do {
        Menu_principal();
        if (scanf("%d", &op) != 1) {
            op = -1;
        }
        Limpar_buffer();

        switch (op) {
            case 1:
                Menu_cadastro_contas(&L);
                break;
            case 2:
                Menu_deposito_saque(&L);
                break;
            case 3:
                Menu_transferencia_pix();
                break;
            case 4:
                Menu_extrato_historico();
                break;
            case 5:
                Menu_desfazer_operacao();
                break;
            case 6:
                Menu_fila_atendimento();
                break;
            case 7:
                Menu_notificacoes();
                break;
            case 8:
                Menu_relatorio_gastos();
                break;
            case 0:
                printf("\nOBRIGADO POR UTILIZAR O BANCO MASTER\n");
                break;
            default:
                printf("\nENTRE COM A OPCAO CORRETA\n");
                Pausar_tela();
                break;
        }
    } while (op != 0);

    return 0;
}
