# AED1 - Banco Master

Sistema bancario simplificado em C (interface de terminal 100% ASCII) desenvolvido no estilo didatico da disciplina de **Algoritmos e Estruturas de Dados I (AED1)**, com todo o codigo concentrado em um unico arquivo (`main.c`), sem prototipos e sem comentarios no codigo-fonte.

---

## Como compilar e executar

```bash
gcc main.c -o bancomaster.exe
./bancomaster.exe
```

---

## Padrao de escrita adotado

O codigo em `main.c` segue diretamente o padrao dos codigos-exemplo da disciplina:

- **Arquivo unico (`main.c`)**, sem prototipos: todas as funcoes auxiliares e de estrutura de dados sao declaradas antes da `main()`.
- **Structs com `typedef`**: tipos definidos no topo (`Conta` e `Lista_est`), seguindo o mesmo modelo de `Pessoa` e `Lista_est` do exemplo de lista linear estatica.
- **Passagem de parametros**:
  - Funcoes que **alteram** a estrutura recebem ponteiro (`Lista_est *L`, `Conta *X`) e acessam os campos com `->`.
  - Funcoes que **apenas leem/exibem** recebem por valor (`Lista_est L`, `Conta X`) e acessam os campos com `.`.
- **Nomenclatura simples**: `Criar_Lista_vazia`, `Verifica_lista_vazia`, `Verifica_lista_cheia`, `Insere_elemento_lista`, `Remove_elemento_lista`, `Exibir_lista_estatica`, variaveis curtas (`L`, `X`, `op`, `i`, `j`).
- **Interface ASCII pura**: sem acentos ou caracteres especiais, com espacamento de 10 quebras de linha (`Espacar_tela`) ao voltar ao menu.

---

## Estruturas de dados usadas ate agora

### 1. `Conta` (`main.c`, linhas 7-12)
Representa um cliente/conta do banco:

```c
typedef struct {
    int id;
    char nome[40];
    char cpf[15];
    float saldo;
} Conta;
```

- `id`: identificador numerico unico da conta (usado como chave de ordenacao e busca).
- `nome`: nome do titular (ate 39 caracteres + `\0`).
- `cpf`: CPF do titular em formato texto.
- `saldo`: saldo atual da conta em reais.

### 2. `Lista_est` (`main.c`, linhas 14-17) — **Vetor de structs (Lista Linear Estatica)**
Armazena todas as contas cadastradas em um vetor fixo de tamanho `MAX` (`100`):

```c
typedef struct {
    Conta item[MAX];
    int prim, ult, tam;
} Lista_est;
```

- `item[MAX]`: vetor estatico onde cada posicao guarda uma struct `Conta`.
- `prim`: indice do primeiro elemento (sempre `0`).
- `ult`: indice da proxima posicao livre (tambem indica o limite final da lista).
- `tam`: quantidade atual de contas cadastradas.

---

## Como funciona a Funcionalidade 1 (Cadastro de Contas)

A funcionalidade 1 usa a estrutura **Lista Linear Estatica ordenada por `id`**. Todas as contas ficam guardadas em ordem crescente de `id` dentro do vetor `L.item[]`.

### Onde esta cada funcao no `main.c` e por que funciona

| Funcao | Localizacao (`main.c`) | O que faz e por que funciona |
| :--- | :--- | :--- |
| `Limpar_buffer()` | linhas 19-23 | Descarta caracteres restantes no buffer de entrada (`stdin`) ate encontrar `\n` ou `EOF`. Evita que o `\n` deixado pelo `scanf` pule o proximo `fgets` ou cause loop infinito se o usuario digitar letras no lugar de numeros. |
| `Espacar_tela()` | linhas 25-30 | Imprime 10 quebras de linha (`\n`) para dar espaco visual ao retornar para o menu sem depender de comandos do sistema operacional. |
| `Pausar_tela()` | linhas 32-36 | Pede para o usuario pressionar `ENTER`, limpa o buffer e chama `Espacar_tela()`. |
| `Remover_quebra_linha()` | linhas 38-46 | Percorre a string lida pelo `fgets` e troca o `\n` final por `\0`, evitando quebras de linha indesejadas na hora de exibir `nome` e `cpf`. |
| `Criar_Lista_vazia(Lista_est *L)` | linhas 48-52 | Inicializa `prim = 0`, `ult = 0` e `tam = 0`. E obrigatorio chamar na `main()` antes de usar a lista para eliminar lixo de memoria. |
| `Verifica_lista_vazia(Lista_est L)` | linhas 54-56 | Retorna verdadeiro (`1`) se `L.prim == L.ult` (nao ha elementos) ou falso (`0`) caso contrario. |
| `Verifica_lista_cheia(Lista_est L)` | linhas 58-60 | Retorna verdadeiro (`1`) se `L.ult == MAX` (vetor atingiu 100 contas), impedindo escrita fora dos limites da memoria (*overflow*). |
| `Ler_conta(Conta *X)` | linhas 62-79 | Le `id`, `nome`, `cpf` e `saldo` do teclado e preenche diretamente a struct apontada por `X` usando `&X->id`, `X->nome`, `X->cpf` e `&X->saldo`. |
| `Exibir_conta(Conta X)` | linhas 81-88 | Imprime os dados de uma unica `Conta` formatados em bloco ASCII. |
| `Insere_elemento_lista(Lista_est *L, Conta X)` | linhas 90-115 | 1) Verifica se a lista esta cheia. 2) Avanca `i` enquanto `i < L->ult` e `X.id > L->item[i].id` para achar a posicao ordenada correta. 3) Se `X.id == L->item[i].id`, barra a insercao para nao duplicar ID. 4) Se for no final (`i == L->ult`), grava direto; senao, desloca os elementos da direita uma casa para frente (`L->item[j] = L->item[j - 1]`) e grava `X` em `L->item[i]`. 5) Incrementa `L->ult` e `L->tam`. |
| `Remove_elemento_lista(Lista_est *L, Conta *X)` | linhas 117-139 | 1) Verifica se a lista esta vazia. 2) Procura `X->id` aproveitando a ordenacao (`while ((i < L->ult) && (X->id > L->item[i].id))`). 3) Se nao encontrar, avisa o usuario. 4) Se encontrar, copia a conta removida para `*X`, desloca todos os elementos seguintes uma posicao para a esquerda (`L->item[j] = L->item[j + 1]`) para nao deixar "buraco" no vetor, decrementa `L->ult` e `L->tam` e exibe a conta removida. |
| `Consultar_conta_lista(Lista_est L, int id)` | linhas 141-156 | Verifica se a lista esta vazia, percorre ate encontrar a posicao do `id` e chama `Exibir_conta(L.item[i])` se existir. |
| `Exibir_lista_estatica(Lista_est L)` | linhas 158-169 | Percorre o vetor de `L.prim` ate `L.ult - 1` chamando `Exibir_conta` para cada elemento cadastrado. |
| `Menu_cadastro_contas(Lista_est *L)` | linhas 171-225 | Submenu da opcao 1 com loop `do-while` oferecendo Cadastrar (`1`), Remover (`2`), Consultar (`3`), Listar (`4`) e Voltar (`0`). |

---

## Como funciona a Funcionalidade 2 (Deposito e Saque)

A funcionalidade 2 reutiliza a **mesma estrutura `Lista_est`** (vetor de structs `L.item[MAX]`) criada na `main()` e preenchida na funcionalidade 1. Em vez de criar outro vetor, ela localiza a conta pelo `id` e altera diretamente o campo `saldo` daquela posicao (`L->item[pos].saldo`).

### Onde esta cada funcao da Funcionalidade 2 no `main.c` e por que funciona

| Funcao | Localizacao (`main.c`) | O que faz e por que funciona |
| :--- | :--- | :--- |
| `Buscar_posicao_conta(Lista_est L, int id)` | linhas 228-241 | Percorre a lista ordenada (`while ((i < L.ult) && (id > L.item[i].id))`) e retorna o indice `i` onde a conta esta guardada no vetor `L.item[]`. Se a lista estiver vazia ou o `id` nao existir, retorna `-1`. Centralizar essa busca evita repetir o mesmo laco em deposito, saque e futuras transferencias. |
| `Depositar_conta(Lista_est *L, int id, float valor)` | linhas 243-257 | 1) Valida se `valor > 0` (impede deposito negativo ou zero). 2) Chama `Buscar_posicao_conta(*L, id)` para achar o indice `pos`. 3) Se encontrar (`pos != -1`), soma `valor` em `L->item[pos].saldo` e exibe a conta atualizada com `Exibir_conta`. |
| `Sacar_conta(Lista_est *L, int id, float valor)` | linhas 259-277 | 1) Valida se `valor > 0`. 2) Busca o indice `pos` com `Buscar_posicao_conta(*L, id)`. 3) Verifica se `valor <= L->item[pos].saldo` para nao permitir saldo negativo. 4) Se houver saldo suficiente, subtrai `valor` de `L->item[pos].saldo` e exibe a conta atualizada. |
| `Menu_deposito_saque(Lista_est *L)` | linhas 279-337 | Submenu da opcao 2 com loop `do-while` oferecendo Depositar (`1`), Sacar (`2`), Consultar saldo por ID (`3`, reutilizando `Consultar_conta_lista(*L, id)`) e Voltar (`0`). |

---

## Ligacoes entre as funcoes (fluxo de execucao)

```text
main()
  |-- Cria a variavel local: Lista_est L
  |-- Chama Criar_Lista_vazia(&L)              (passa endereco &L para inicializar)
  |-- Loop do-while:
        |-- Chama Menu_principal()
        |-- Le a opcao op
        |-- switch(op):
              |-- case 1 -> Menu_cadastro_contas(&L)   (recebe ponteiro Lista_est *L)
              |     |-- case 1 -> Ler_conta(&X) -> Insere_elemento_lista(L, X)
              |     |-- case 2 -> le id -> Remove_elemento_lista(L, &X)
              |     |-- case 3 -> le id -> Consultar_conta_lista(*L, id)
              |     |-- case 4 -> Exibir_lista_estatica(*L)
              |     |-- case 0 -> Espacar_tela() -> volta para main()
              |-- case 2 -> Menu_deposito_saque(&L)    (recebe o mesmo ponteiro &L)
              |     |-- case 1 -> le id e valor -> Depositar_conta(L, id, valor)
              |     |                                 |-- Buscar_posicao_conta(*L, id)
              |     |                                 |-- altera L->item[pos].saldo
              |     |                                 |-- Exibir_conta(L->item[pos])
              |     |-- case 2 -> le id e valor -> Sacar_conta(L, id, valor)
              |     |                                 |-- Buscar_posicao_conta(*L, id)
              |     |                                 |-- valida saldo e altera L->item[pos].saldo
              |     |                                 |-- Exibir_conta(L->item[pos])
              |     |-- case 3 -> le id -> Consultar_conta_lista(*L, id)
              |     |-- case 0 -> Espacar_tela() -> volta para main()
              |-- case 3..8 -> Funcoes esqueleto das proximas etapas
              |-- case 0 -> Encerra o programa
```

### Por que as alteracoes de saldo persistem entre a Opcao 1 e a Opcao 2?
1. A lista `L` existe uma unica vez, dentro da `main()`.
2. Tanto `Menu_cadastro_contas(&L)` quanto `Menu_deposito_saque(&L)` recebem o **endereco de memoria** (`&L`) dessa mesma lista.
3. Dentro de `Depositar_conta(L, id, valor)` e `Sacar_conta(L, id, valor)`, alterar `L->item[pos].saldo` modifica diretamente a struct original guardada na `main()`. Por isso, se voce depositar na opcao `2` e depois listar as contas na opcao `1`, o novo saldo ja aparece atualizado.
4. Ja em `Buscar_posicao_conta(*L, id)` e `Consultar_conta_lista(*L, id)`, passamos `*L` (por valor) porque essas funcoes apenas leem o vetor sem modificar nada.

---

## Mapa das 8 funcionalidades do projeto

1. **Cadastro de Contas** (`Lista_est` — Vetor de structs) — **Implementado**
2. **Deposito e Saque** (`Lista_est` — Vetor de structs) — **Implementado**
3. **Transferencia entre Contas / Pix** (Vetor de structs) — *Esqueleto pronto*
4. **Extrato / Historico de Transacoes** (Lista encadeada) — *Esqueleto pronto*
5. **Desfazer Ultima Operacao / Undo** (Pilha) — *Esqueleto pronto*
6. **Fila de Atendimento / Pix Agendado** (Fila) — *Esqueleto pronto*
7. **Notificacoes do App** (Deque) — *Esqueleto pronto*
8. **Relatorio de Gastos por Mes/Categoria** (Matriz) — *Esqueleto pronto*
