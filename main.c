#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM 100

typedef struct produto {
    int codigo;
    char nome[TAM];
    float preco;
} tp_produto;

typedef struct nodo {
    tp_produto produto;
    struct nodo *prox;
} tp_nodo;

tp_nodo *criarNodo(tp_produto produto) {
    tp_nodo *novoNodo = (tp_nodo *)malloc(sizeof(tp_nodo));
    if (novoNodo == NULL) {
        printf("Erro: Nao foi possivel alocar memoria para o novo noh.\n");
        exit(1);
    }
    novoNodo->produto = produto;
    novoNodo->prox = NULL;
    return novoNodo;
}

int lerInteiro() {
    int numero;
    char buffer[20];
    scanf("%s", buffer);

    int i = 0;
    while (buffer[i] != '\0') {
        if (!isdigit(buffer[i])) {
            printf("Entrada invalida. Digite um numero inteiro: ");
            scanf("%s", buffer);
            i = 0;
        } else {
            i++;
        }
    }

    sscanf(buffer, "%d", &numero);
    return numero;
}

int produtoComCodigoJaExistente(tp_nodo *lista, int codigo) {
    while (lista != NULL) {
        if (lista->produto.codigo == codigo) {
            return 1;
        }
        lista = lista->prox;
    }
    return 0;
}

void inserirProduto(tp_nodo **lista, tp_produto produto) {
    tp_nodo *novoNodo = criarNodo(produto);
    novoNodo->prox = *lista;
    *lista = novoNodo;
}

void removerProduto(tp_nodo **lista, int codigo) {
    tp_nodo *atual = *lista;
    tp_nodo *anterior = NULL;

    while (atual != NULL && atual->produto.codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Produto com codigo %d nao encontrado na lista.\n", codigo);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Produto com codigo %d removido da lista.\n", codigo);
}

void listarProdutos(tp_nodo *lista) {
    printf("Lista de Produtos:\n");
    while (lista != NULL) {
        printf("Codigo: %d\n", lista->produto.codigo);
        printf("Nome: %s\n", lista->produto.nome);
        printf("Preco: %.2f\n", lista->produto.preco);
        printf("-----------------------------\n");
        lista = lista->prox;
    }
}

int main() {
    tp_nodo *lista = NULL;
    int opcao;
    tp_produto produto;

    do {
        printf("\nOPCOES DO MENU:\n");
        printf("(1) Para inserir um produto na lista.\n");
        printf("(2) Para excluir um elemento da lista.\n");
        printf("(3) Para listar todos os campos dos elementos da lista.\n");
        printf("(0) Para finalizar o programa.\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o codigo do produto: ");
                produto.codigo = lerInteiro();

                if (produtoComCodigoJaExistente(lista, produto.codigo)) {
                    printf("Produto com o mesmo codigo ja existe na lista, favor verificar.\n");
                } else {
                    printf("Digite o nome do produto: ");
                    scanf("%s", produto.nome);
                    printf("Digite o preco do produto: ");
                    scanf("%f", &produto.preco);
                    inserirProduto(&lista, produto);
                }
                break;
            case 2:
                printf("Digite o codigo do produto a ser removido: ");
                produto.codigo = lerInteiro();
                removerProduto(&lista, produto.codigo);
                break;
            case 3:
                listarProdutos(lista);
                break;
            case 0:
                printf("Programa finalizado.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    while (lista != NULL) {
        tp_nodo *temp = lista;
        lista = lista->prox;
        free(temp);
    }

    return 0;
}
