#include <stdio.h>
#include <string.h>

#define MaxProduto 50
#define MaxCarrinho 50

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto pro;
    int quant;
} Carrinho;

Produto produtos[MaxProduto];
Carrinho carrinho[MaxCarrinho];
int numProdutos = 0;
int numCarrinho = 0;

void menu();
void cadastrarPro();
void listarPro();
void comprarPro();
void visualizarCarrinho();
void fecharPedido();
void removerPro();
Produto* pegarProdutoPorCodigo(int codigo);
int temNoCarrinho(int codigo);
void infoPro(Produto* prod);
int produtoJaCadastrado(char nome[]);

int main() {
    menu();
    return 0;
}

void menu() {
    int opcao;
    do {
        printf("\n----- Menu Supermercado -----\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Remover Produto do Carrinho\n");
        printf("6. Fechar Pedido\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarPro();
                break;
            case 2:
                listarPro();
                break;
            case 3:
                comprarPro();
                break;
            case 4:
                visualizarCarrinho();
                break;
            case 5:
                removerPro();
                break;
            case 6:
                fecharPedido();
                break;
            case 7:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 7);
}

int produtoJaCadastrado(char nome[]) {
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].nome, nome) == 0) {
            return 1;
        }
    }
    return 0;
}

void cadastrarPro(){
    if (numProdutos >= MaxProduto){
        printf("Limite de produtos atingido.\n");
        return;
    }
    
    Produto novoPro;
    printf("Nome do produto: ");
    scanf("%s", novoPro.nome);

    if (produtoJaCadastrado(novoPro.nome)){
        printf("Produto com o nome '%s' ja cadastrado.\n", novoPro.nome);
        return;
    }
    
    printf("Preco do produto: ");
    scanf("%f", &novoPro.preco);

    novoPro.codigo = numProdutos + 1;
    produtos[numProdutos] = novoPro;
    numProdutos++;

    printf("Produto cadastrado com sucesso.\n");
}

void listarPro(){
    if (numProdutos == 0){
        printf("Nenhum produto foi cadastrado.\n");
        return;
    }
    
    printf("\n----Lista dos produtos----\n");
    for (int i = 0; i < numProdutos; i++){
        infoPro(&produtos[i]);
    } 
}

void infoPro(Produto* prod){
    printf("Codigo: %d\nNome: %s\nPreco: RS%.2f\n------------------\n", (*prod).codigo, (*prod).nome, (*prod).preco);
}

void comprarPro(){
    int codigo, quantidade;
    listarPro();
    printf("Digite o codigo do produto para adicionar ao carrinho: ");
    scanf("%d", &codigo);
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
}