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
Produto* pegarProPorCodigo(int codigo);
int temNoCarrinho(int codigo);
void infoPro(Produto* prod);
int proJaCadastrado(char nome[]);

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

int proJaCadastrado(char nome[]) {
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

    if (proJaCadastrado(novoPro.nome)){
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

    Produto* produto = pegarProPorCodigo(codigo);
    if (!produto){
        printf("Produto nao encontrado.\n");
        return;
    }

    int indCar = temNoCarrinho(codigo);
    if (indCar == -1){
        carrinho[numCarrinho++] = (Carrinho){*produto, quantidade};
    }else{
        carrinho[indCar].quant += quantidade;
    }
    printf("Produto adicionado ao carrinho.\n");
}

int temNoCarrinho(int codigo){
    for (int i = 0; i < numCarrinho; i++){
        if (carrinho[i].pro.codigo == codigo) return i;
    }
    return -1;
}

Produto* pegarProPorCodigo(int codigo){
    for (int i = 0; i < numProdutos; i++){
        if (produtos[i].codigo == codigo) return &produtos[i];
    }
    return NULL;
}

void visualizarCarrinho(){
    if (numCarrinho == 0){
        printf("O carrinho esta vazio.\n");
        return;
    }
    printf("\n----- Carrinho de compra -----\n");
    for (int i = 0; i < numCarrinho; i++){
        infoPro(&carrinho[i].pro);
        printf("Quantidade: %d\n--------------------\n", carrinho[i].quant);
    }
}

void removerPro(){
    if (numCarrinho == 0){
        printf("O carrinho esta vazio, nao ha nada para remover.\n");
        return;
    }

    int codigo;
    visualizarCarrinho();
    printf("Digite o codigo do produto que deseja remover: ");
    scanf("%d", &codigo);

    for (int i = 0; i < numCarrinho; i++){
        if (carrinho[i].pro.codigo == codigo){
            for (int j = i; j < numCarrinho - 1; j++){
                carrinho[j] = carrinho[j + 1];
            }
            numCarrinho--;
            printf("Produto removido.\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

void fecharPedido(){
    if (numCarrinho = 0){
        printf("Carrinho vazio.\n");
        return;
    }

    float total = 0;
    printf("\n ----- Fechamento de pedido -----\n");
    for (int i = 0; i < numCarrinho; i++){
        Produto* produto = &carrinho[i].pro;
        printf("%s (x%d): RS%.2f\n", (*produto).nome, carrinho[i].quant, (*produto).preco * carrinho[i].quant);
        total += (*produto).preco * carrinho[i].quant;
    }
    printf("Total do pedido: RS%.2f\n", total);
    numCarrinho = 0;
    printf("Pedido fechado com sucesso.\n");
}
