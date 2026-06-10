#include <stdio.h>

// ========================================================
//                  CONSTANTES DO SISTEMA
// ========================================================

#define MAX_PRODUTOS 50
#define MAX_CARRINHO 100
#define MAX_NOME 50

// ========================================================
//                    ESTRUTURAS (STRUCTS)
// ========================================================

// Struct responsável por armazenar os produtos cadastrados
struct ProdutoCadastro {
    int codigo;
    char nome[MAX_NOME];
    float preco;
};

// Struct responsável pelos itens adicionados ao carrinho
struct ItemCarrinho {
    int codigo;
    char nome[MAX_NOME];
    float preco_unitario;
    int quantidade;
    float preco_total_item;
};

// ========================================================
//                      FUNÇÕES AUXILIARES
// ========================================================

// --------------------------------------------------------
// Copia caracteres manualmente de uma string para outra
// sem utilizar strcpy().
// --------------------------------------------------------
void copiar_string(char destino[MAX_NOME], char origem[MAX_NOME]) {
    int i;

    for(i = 0; i < MAX_NOME; i++) {
        destino[i] = origem[i];

        // Finaliza a cópia ao encontrar o fim da string
        if(origem[i] == '\0') {
            break;
        }
    }
}

// ========================================================
//                      OPÇÃO 01
//                     ABRIR CAIXA
// ========================================================

int abrir_caixa(char nome[MAX_NOME], int aberto) {
    int numero_caixa;

    // Verifica se já existe um caixa aberto
    if(aberto > 0) {
        printf("Caixa ja esta aberto.\n\n");
        return aberto;
    }

    // Validação do número do caixa
    do {
        printf("\nIdentificar Caixa (1 a 12): ");
        scanf("%i", &numero_caixa);

        if(numero_caixa < 1 || numero_caixa > 12) {
            printf("Caixa inexistente! Digite novamente.\n\n");
        }

    } while(numero_caixa < 1 || numero_caixa > 12);

    // Recebe o nome do operador
    printf("Identificar Operador: ");
    scanf(" %[^\n]", nome);

    printf("\nCaixa %02d aberto com sucesso pelo operador %s!\n\n",
           numero_caixa,
           nome);

    return numero_caixa;
}

// ========================================================
//                      OPÇÃO 02
//                  CADASTRAR PRODUTOS
// ========================================================

int cadastrar_produtos(struct ProdutoCadastro banco[MAX_PRODUTOS],
                       int qtd_cadastrados) {

    char resposta;

    printf("\n==============================\n");
    printf("     CADASTRO DE PRODUTOS     \n");
    printf("==============================\n");

    do {

        // Verifica limite máximo de produtos
        if(qtd_cadastrados >= MAX_PRODUTOS) {
            printf("Limite de produtos atingido!\n");
            break;
        }

        printf("\nCadastrando produto %d\n",
               qtd_cadastrados + 1);

        // Código do produto
        printf("Digite o codigo do produto: ");
        scanf("%i", &banco[qtd_cadastrados].codigo);

        // Nome do produto
        printf("Digite o nome do produto: ");
        scanf(" %[^\n]", banco[qtd_cadastrados].nome);

        // Preço do produto
        printf("Digite o preco do produto: R$ ");
        scanf("%f", &banco[qtd_cadastrados].preco);

        // Validação do preço
        if(banco[qtd_cadastrados].preco <= 0) {
            printf("Preco invalido! Produto nao cadastrado.\n");
        }
        else {
            qtd_cadastrados++;
            printf("Produto cadastrado com sucesso!\n");
        }

        // Verifica se deseja continuar cadastrando
        printf("\nDeseja cadastrar outro produto? (s/n): ");
        scanf(" %c", &resposta);

    } while(resposta == 's');

    return qtd_cadastrados;
}

// ========================================================
//                      OPÇÃO 03
//                    INICIAR COMPRA
// ========================================================

int iniciar_compra(struct ProdutoCadastro banco[MAX_PRODUTOS],
                   int qtd_cadastrados,
                   struct ItemCarrinho carrinho[MAX_CARRINHO]) {

    int codigo_digitado;
    int qtd_digitada;
    int qtd_itens_carrinho = 0;

    int i;
    int achou;

    char resposta;

    printf("\n==============================\n");
    printf("       NOVA COMPRA            \n");
    printf("==============================\n");

    do {

        // Verifica limite do carrinho
        if(qtd_itens_carrinho >= MAX_CARRINHO) {
            printf("Limite de itens no carrinho atingido!\n");
            break;
        }

        // Solicita código do produto
        printf("\nDigite o codigo do produto: ");
        scanf("%i", &codigo_digitado);

        achou = 0;

        // Procura o produto no banco
        for(i = 0; i < qtd_cadastrados; i++) {

            if(banco[i].codigo == codigo_digitado) {

                achou = 1;

                printf("Produto encontrado: %s\n", banco[i].nome);
                printf("Preco unitario: R$ %.2f\n", banco[i].preco);

                // Validação da quantidade
                do {
                    printf("Digite a quantidade: ");
                    scanf("%i", &qtd_digitada);

                    if(qtd_digitada <= 0) {
                        printf("Quantidade invalida!\n");
                    }

                } while(qtd_digitada <= 0);

                // Preenchimento do carrinho
                carrinho[qtd_itens_carrinho].codigo = banco[i].codigo;

                copiar_string(
                    carrinho[qtd_itens_carrinho].nome,
                    banco[i].nome
                );

                carrinho[qtd_itens_carrinho].preco_unitario = banco[i].preco;

                carrinho[qtd_itens_carrinho].quantidade = qtd_digitada;

                carrinho[qtd_itens_carrinho].preco_total_item =
                    banco[i].preco * qtd_digitada;

                qtd_itens_carrinho++;

                break;
            }
        }

        // Caso o produto não exista
        if(!achou) {
            printf("Codigo nao encontrado no sistema!\n");
        }

        // Pergunta se deseja adicionar mais itens
        printf("\nDeseja adicionar mais produtos? (s/n): ");
        scanf(" %c", &resposta);

    } while(resposta == 's');

    return qtd_itens_carrinho;
}

// ========================================================
//                      OPÇÃO 04
//                  EMITIR CUPOM FISCAL
// ========================================================

float emitir_nota_fiscal(struct ItemCarrinho carrinho[MAX_CARRINHO],
                         int qtd_itens,
                         int num_caixa,
                         char operador[MAX_NOME]) {

    float total = 0;
    int i;

    // Verifica se existem itens no carrinho
    if(qtd_itens == 0) {
        printf("\nNenhum produto no carrinho!\n\n");
        return 0;
    }

    printf("\n========================================================================\n");
    printf("                           CUPOM FISCAL                                \n");
    printf("========================================================================\n");

    printf(" Caixa: %02d                              Operador: %-20s\n",
           num_caixa,
           operador);

    printf("========================================================================\n");

    printf("%-4s %-6s %-20s %-5s %-13s %-11s\n",
           "ITEM",
           "COD.",
           "PRODUTO",
           "QTD",
           "PRECO UN.",
           "TOTAL");

    printf("------------------------------------------------------------------------\n");

    // Exibe os itens da compra
    for(i = 0; i < qtd_itens; i++) {

        printf("%-4d %-6d %-20s %-5d %-13.2f %-11.2f\n",
               i + 1,
               carrinho[i].codigo,
               carrinho[i].nome,
               carrinho[i].quantidade,
               carrinho[i].preco_unitario,
               carrinho[i].preco_total_item);

        total += carrinho[i].preco_total_item;
    }

    printf("------------------------------------------------------------------------\n");
    printf("%-44s R$ %.2f\n", "TOTAL DA COMPRA:", total);
    printf("========================================================================\n\n");

    return total;
}

// ========================================================
//                      OPÇÃO 05
//                     FECHAR CAIXA
// ========================================================

int fechar_caixa(float faturamento,
                 int qtd_compras,
                 int num_caixa,
                 char operador[MAX_NOME]) {

    printf("\n========================================================================\n");
    printf("                        FECHAMENTO DE CAIXA                             \n");
    printf("========================================================================\n");

    printf(" Caixa: %02d                              Operador: %-20s\n",
           num_caixa,
           operador);

    printf("========================================================================\n");

    printf("%-44s %d\n",
           "Total de compras realizadas:",
           qtd_compras);

    printf("%-44s R$ %.2f\n",
           "Faturamento total do dia:",
           faturamento);

    printf("========================================================================\n");
    printf("                         CAIXA ENCERRADO                                \n");
    printf("========================================================================\n\n");

    // Retorna 0 para indicar caixa fechado
    return 0;
}

// ========================================================
//                           MAIN
// ========================================================

int main() {

    // ----------------------------------------------------
    // Controle do menu e estado do caixa
    // ----------------------------------------------------

    int opcao;
    int aberto = 0;

    char nome_operador[MAX_NOME] = "";

    // ----------------------------------------------------
    // Banco de produtos
    // ----------------------------------------------------

    struct ProdutoCadastro banco_produtos[MAX_PRODUTOS];
    int qtd_cadastrados = 0;

    // ----------------------------------------------------
    // Carrinho da compra atual
    // ----------------------------------------------------

    struct ItemCarrinho carrinho_atual[MAX_CARRINHO];
    int qtd_itens_carrinho = 0;

    // ----------------------------------------------------
    // Controle financeiro do caixa
    // ----------------------------------------------------

    float faturamento_dia = 0;
    float valor_venda_atual = 0;

    int total_compras_dia = 0;

    printf("Iniciando Sistema...\n\n");

    // ====================================================
    // LOOP PRINCIPAL DO SISTEMA
    // ====================================================

    do {

        printf("=======================\n");
        printf("01 - Abrir Caixa\n");
        printf("02 - Cadastrar Produto\n");
        printf("03 - Iniciar Compra\n");
        printf("04 - Emitir Cupom Fiscal\n");
        printf("05 - Fechar Caixa\n");
        printf("06 - Sair\n");
        printf("=======================\n");

        printf("Escolha uma opcao: ");
        scanf("%i", &opcao);

        printf("\n");

        // =================================================
        // CONTROLE DAS OPÇÕES DO MENU
        // =================================================

        switch(opcao) {

            // =============================================
            // ABRIR CAIXA
            // =============================================

            case 1:

                aberto = abrir_caixa(nome_operador, aberto);

                break;

            // =============================================
            // CADASTRAR PRODUTOS
            // =============================================

            case 2:

                qtd_cadastrados = cadastrar_produtos(
                    banco_produtos,
                    qtd_cadastrados
                );

                break;

            // =============================================
            // INICIAR COMPRA
            // =============================================

            case 3:

                if(aberto == 0) {
                    printf("Erro: O caixa precisa estar aberto!\n\n");
                }
                else if(qtd_cadastrados == 0) {
                    printf("Erro: Nao existem produtos cadastrados!\n\n");
                }
                else {
                    qtd_itens_carrinho = iniciar_compra(
                        banco_produtos,
                        qtd_cadastrados,
                        carrinho_atual
                    );
                }

                break;

            // =============================================
            // EMITIR CUPOM FISCAL
            // =============================================

            case 4:

                if(aberto == 0) {
                    printf("Erro: O caixa precisa estar aberto!\n\n");
                }
                else {

                    valor_venda_atual = emitir_nota_fiscal(
                        carrinho_atual,
                        qtd_itens_carrinho,
                        aberto,
                        nome_operador
                    );

                    // Atualiza faturamento do caixa
                    if(valor_venda_atual > 0) {

                        faturamento_dia += valor_venda_atual;

                        total_compras_dia++;

                        // Limpa quantidade do carrinho
                        qtd_itens_carrinho = 0;
                    }
                }

                break;

            // =============================================
            // FECHAR CAIXA
            // =============================================

            case 5:

                if(aberto == 0) {
                    printf("Erro: O caixa ja esta fechado!\n\n");
                }
                else {

                    aberto = fechar_caixa(
                        faturamento_dia,
                        total_compras_dia,
                        aberto,
                        nome_operador
                    );

                    // Reinicia informações financeiras
                    faturamento_dia = 0;
                    total_compras_dia = 0;
                }

                break;

            // =============================================
            // ENCERRAR SISTEMA
            // =============================================

            case 6:

                printf("Encerrando o sistema com seguranca...\n");

                break;

            // =============================================
            // OPÇÃO INVÁLIDA
            // =============================================

            default:

                printf("Opcao invalida! Tente novamente.\n\n");

                break;
        }

    } while(opcao != 6);

    return 0;
}
