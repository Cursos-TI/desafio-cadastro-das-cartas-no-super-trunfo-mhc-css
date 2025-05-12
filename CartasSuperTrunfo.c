#include <stdio.h>

#include <string.h>     // Necessário para STRCMP/STRCSPN.
#include <stdlib.h>     // Necessário para ATOI/ATOL/ATOF/STRTOUL/EXIT.


// Definição da estrutura 'Cidade'.
struct Cidade {
    char pais[60];                      // 60 caracteres.
    char estado_codigo_ou_nome[70];     // 70 caracteres.
    char cidade_codigo[50];             // 50 caracteres.
    char cidade_nome[80];               // 80 caracteres.
    int populacao;
    double area;                        // em km².
    double pib;                         // em bi de reais.
    double pontos_turisticos;
    double densidade;                   // população por km².
    double pib_per_capita;              // PIB per capita.
    float super_poder;                  // Novo atributo por causa do nível Mestre: Super Poder.
};

// Função para registrar informações da cidade.
void registroCidade(struct Cidade *cidade) {            // Alterado para receber um ponteiro para a estrutura 'Cidade'.
    char buffer[100];                                   // Buffer para armazenar temporariamente a entrada do usuário.


    printf("Digite o nome do pais (por exemplo, 'Brasil'): ");
    fgets(cidade->pais, sizeof(cidade->pais), stdin);               // Lê e armazena a entrada do usuário na variável 'cidade->pais'.
    cidade->pais[strcspn(cidade->pais, "\n")] = '\0';               // Remove a quebra de linha indesejada do final da string lida.


    printf("Digite o codigo ou o nome do estado (por exemplo, 'PR' ou 'Parana'): ");

    fgets(cidade->estado_codigo_ou_nome, sizeof(cidade->estado_codigo_ou_nome), stdin);     // Lê e armazena a entrada do usuário na variável 'cidade->estado_codigo_ou_nome'.
    cidade->estado_codigo_ou_nome[strcspn(cidade->estado_codigo_ou_nome, "\n")] = '\0';     // Remove a quebra de linha indesejada do final da string lida.


    printf("Digite o codigo da cidade (por exemplo, '01'): ");

    fgets(cidade->cidade_codigo, sizeof(cidade->cidade_codigo), stdin);     // Lê e armazena a entrada do usuário na variável 'cidade->cidade_codigo'.
    cidade->cidade_codigo[strcspn(cidade->cidade_codigo, "\n")] = '\0';     // Remove a quebra de linha indesejada do final da string lida.


    printf("Digite o nome da cidade (por exemplo, 'Curitiba'): ");

    fgets(cidade->cidade_nome, sizeof(cidade->cidade_nome), stdin);         // Lê e armazena a entrada do usuário na variável 'cidade->cidade_nome'.
    cidade->cidade_nome[strcspn(cidade->cidade_nome, "\n")] = '\0';         // Remove a quebra de linha indesejada do final da string lida.


    // Leitura da população
    printf("Digite a populacao da cidade (por exemplo, '1774000'): ");

    fgets(buffer, sizeof(buffer), stdin);               // Armazena a entrada do usuário em 'buffer'.
    cidade->populacao = strtoul(buffer, NULL, 10);      // Alterado para int para simplificar a comparação.
    
    // 'strtoul' é usado ao invés de 'atol' para evitar valores negativos.


    // Leitura da área
    printf("Digite a area da cidade em quilometros quadrados (por exemplo, '432'): ");

    fgets(buffer, sizeof(buffer), stdin);               // Armazena a entrada do usuário em 'buffer'.
    cidade->area = atof(buffer);                        // Converter 'string' para 'double'.
    

    // Leitura do PIB
    printf("Digite o PIB da cidade em bilhoes de reais (por exemplo, '98'): ");
    
    fgets(buffer, sizeof(buffer), stdin);               // Armazena a entrada do usuário em 'buffer'.
    cidade->pib = atof(buffer);                         // Converter 'string' para 'double'.
    

    // Leitura dos pontos turísticos
    printf("Digite a quantidade de pontos turisticos da cidade (por exemplo, '20'): ");

    fgets(buffer, sizeof(buffer), stdin);
    cidade->pontos_turisticos = atoi(buffer);  // Converter 'string' para 'int'.

    // Inicialização de valor primário caso o usuário insira 0 ou valor negativo (evitar 'NaN').
    cidade->densidade = 0;
    cidade->pib_per_capita = 0;
    cidade->super_poder = 0;

    // Calcular densidade populacional

    // Se o usuário não inserir 0 ou valor negativo para a área, calcula a densidade populacional.
    if (cidade->area > 0.0) {

        // Densidade = População dividida pela Área.
        cidade->densidade = (double)cidade->populacao / cidade->area;
    }

    // Calcular PIB per capita

    // Se o usuário não inserir 0 ou valor negativo para a população, calcula o PIB per capita.
    if (cidade->populacao > 0) {

        // PIB per capita = PIB dividido pela População.
        // O PIB é multiplicado por '1e9' para converter de bilhões para reais.
        cidade->pib_per_capita = (cidade->pib * 1e9) / (double)cidade->populacao;
    }

    // Calcular o Super Poder

    // O Super Poder é calculado como a soma de todos os atributos,
    // incluindo PIB, população, área, pontos turísticos e PIB per capita.

    // Se for 0 ou negativo, o Super Poder não será calculado.

    cidade->super_poder = (float)cidade->populacao + 
                          (float)cidade->area + 
                          (float)(cidade->pib * 1e9) +
                          (float)cidade->pontos_turisticos + 
                          (float)cidade->pib_per_capita;
    
    // Se for maior que 0, o Super Poder aumenta com base na densidade populacional.

    // Se a densidade for maior que 0, o Super Poder aumenta com base na densidade populacional.
    if (cidade->densidade > 0.0) {      

    // O Super Poder aumenta com base na densidade populacional, onde quanto menor a densidade, maior o aumento.
        cidade->super_poder += (float)(1.0 / cidade->densidade);
    }
}

// Função para mostrar informações da cidade no final do jogo.
void mostrarCidade(struct Cidade cidade, int cartaCodigo) {

    // Título para a respectiva carta (1 e 2).
    printf("\nCARTA %d:\n", cartaCodigo);

    // Mostrar o Nome do País, Código ou Nome do Estado, Código da Cidade e Nome da Cidade com %s, pois são strings.
    printf("Pais: %s\n", cidade.pais);
    printf("Estado: %s\n", cidade.estado_codigo_ou_nome);
    printf("Codigo: %s\n", cidade.cidade_codigo);
    printf("Nome: %s\n", cidade.cidade_nome);

    // "%d" para int, pois a população deve ser inteira.
    printf("Populacao: %d\n", cidade.populacao);

    // Mostrar a área e PIB com 2 casas decimais. (.2lf)
    printf("Area (em quilometros quadrados): %.2lf\n", cidade.area);
    printf("PIB: R$%.2lf bi\n", cidade.pib);              

    // %d para int, pois a quantidade de pontos turísticos deve ser inteira.
    printf("Pontos turisticos: %d\n", (int)cidade.pontos_turisticos);

    // Mostrar a densidade populacional, PIB e Super Poder com 2 casas decimais. (.2lf)
    printf("Densidade populacional: %.2lf por quilometro quadrado\n", cidade.densidade);
    printf("PIB per capita: R$%.2lf\n", cidade.pib_per_capita);
    printf("Super Poder: %.2f\n", cidade.super_poder);
}

// Função para comparar os atributos e atualizar o placar.
// 7 atributos (com Super Poder do nível Mestre)

// Função para determinar o vencedor com base em um atributo específico
int DeterminarVencedor(struct Cidade cidade1, struct Cidade cidade2, int *placar1, int *placar2) {
    // Alterado para receber ponteiros para os placares.

    *placar1 = 0;   // Inicializar o placar da Carta 1.
    *placar2 = 0;   // Inicializar o placar da Carta 2.


    // Comparar População (maior vence)

    // Se a População da Carta 1 for maior que a da Carta 2,
    if (cidade1.populacao > cidade2.populacao)

        // A Carta 1 ganha um ponto.
        (*placar1)++;


    // Do contrário,

    //// Se a População da Carta 1 for menor que a da Carta 2,
    else if (cidade1.populacao < cidade2.populacao)

        // A Carta 2 ganha um ponto.
        (*placar2)++;



    // Comparar Área (maior vence)

    if (cidade1.area > cidade2.area)        // Se a Área da Carta 1 for maior que a da Carta 2,
        (*placar1)++;                       // A Carta 1 ganha um ponto.

    // Do contrário,

    else if (cidade1.area < cidade2.area)   // Se a Área da Carta 1 for menor que a da Carta 2,
        (*placar2)++;                       // A Carta 2 ganha um ponto.



    // Comparar PIB (maior vence)

    if (cidade1.pib > cidade2.pib)          // Se o PIB da Carta 1 for maior que o da Carta 2,
        (*placar1)++;                       // A Carta 1 ganha um ponto.

    // Do contrário,

    else if (cidade1.pib < cidade2.pib)     // Se o PIB da Carta 1 for menor que o da Carta 2,
        (*placar2)++;                       // A Carta 2 ganha um ponto.



    // Comparar Pontos Turísticos (maior vence)

    // Se houverem mais Pontos Turísticos na Carta 1 do que na da Carta 2,
    if (cidade1.pontos_turisticos > cidade2.pontos_turisticos)

        (*placar1)++;       // A Carta 1 ganha um ponto.

    // Do contrário,

    // Se houverem mais Pontos Turísticos na Carta 2 do que na da Carta 1,    
    else if (cidade1.pontos_turisticos < cidade2.pontos_turisticos)

        (*placar2)++;       // A Carta 2 ganha um ponto.



    // Comparar Densidade Populacional (menor vence)

    if (cidade1.densidade < cidade2.densidade)      // Se a Densidade Populacional da Carta 1 for menor que a da Carta 2,
        (*placar1)++;                               // A Carta 1 ganha um ponto.

    // Do contrário,

    else if (cidade1.densidade > cidade2.densidade)     // Se a Densidade Populacional da Carta 1 for maior que a da Carta 2,
        (*placar2)++;                                   // A Carta 2 ganha um ponto.



    // Comparar PIB per Capita (maior vence)
    if (cidade1.pib_per_capita > cidade2.pib_per_capita)        // Se o PIB per Capita da Carta 1 for maior que o da Carta 2,
        (*placar1)++;                                           // A Carta 1 ganha um ponto.

    // Do contrário,

    else if (cidade1.pib_per_capita < cidade2.pib_per_capita)   // Se o PIB per Capita da Carta 1 for menor que o da Carta 2,
        (*placar2)++;                                           // A Carta 2 ganha um ponto.



    // Comparar Super Poder (soma de todos os atributos) (maior vence)

    if (cidade1.super_poder > cidade2.super_poder)              // Se o Super Poder da Carta 1 for maior que o da Carta 2,
        (*placar1)++;                                           // A Carta 1 ganha um ponto.

    // Do contrário,

    else if (cidade1.super_poder < cidade2.super_poder)         // Se o Super Poder da Carta 1 for menor que o da Carta 2,
        (*placar2)++;                                           // A Carta 2 ganha um ponto.



    // Retornar a carta vencedora: 1 se a Carta 1 vencer, 2 se a Carta 2 vencer ou 0 se houver empate entre as duas cartas.

    // Se o placar final da Carta 1 for maior que o da Carta 2,
    if (*placar1 > *placar2)

        // A Carta 1 vence, retornando '1'.
        return 1;


    // Se o placar final da Carta 2 for maior que o da Carta 1,
    else if (*placar2 > *placar1)

        // A Carta 2 vence, retornando '2'.
        return 2;                   // A Carta 2 vence, retornando '2'.


    // Se não 'retornou 1' e nem '2',  significa que ocorreu um empate entre as duas cartas,
    else
        return 0;                   // retornando assim '0'.

}


// Função para mostrar a comparação de cada atributo.
// Feita apenas para visualização, sem impacto no verdadeiro placar do jogo.

// Com isto, o jogador pode ver uma 'simulação' do que ocorreu em cada comparação de atributo a medida em que a rodada aconteceu.

void compararAtributos(struct Cidade c1, struct Cidade c2) {

    // Título para a comparação de cartas.
    printf("\nCOMPARACAO DE CARTAS:\n");
    printf("O numero entre parenteses indica a pontuacao que a carta obteve a medida em que a comparação foi ocorrendo.\n\n");

    int exibicao_C1;        // Variável para armazenar a pontuação da Carta 1.
    exibicao_C1 = 0;        // Inicializa a pontuação da Carta 1 com 0.

    int exibicao_C2;        // Variável para armazenar a pontuação da Carta 2.
    exibicao_C2 = 0;        // Inicializa a pontuação da Carta 2 com 0.


// POPULAÇÃO
// (maior vence)

    if (c1.populacao > c2.populacao) {    // Se a População da Carta 1 for maior que a da Carta 2,

        exibicao_C1++;        // A Carta 1 ganha um ponto.

        printf("Populacao: Carta 1 (%s) vence (%d)\n", exibicao_C1);        // Mostrar a pontuação da Carta 1 até o momento.
    }


    // Do contrário,

    else if (c1.populacao < c2.populacao) {    // Se a População da Carta 1 for menor que a da Carta 2,

        exibicao_C2++;        // A Carta 2 ganha um ponto.

        printf("Populacao: Carta 2 vence (%d)\n", exibicao_C2);        // Mostrar a pontuação da Carta 2 até o momento.
    }


    // No caso de empate entre as duas cartas,

    else {
        printf("Populacao: Empate (Nenhum ponto adicionado)\n");    // Mostrar que não houve pontuação.
    }


// ÁREA
// (maior vence)

    if (c1.area > c2.area) {    // Se a Área da Carta 1 for maior que a da Carta 2,

        exibicao_C1++;        // A Carta 1 ganha um ponto.

        printf("Area: Carta 1 vence (%d)\n", exibicao_C1);        // Mostrar a pontuação da Carta 1 até o momento.
    }


    // Do contrário,

    else if (c1.area < c2.area) {        // Se a Área da Carta 1 for menor que a da Carta 2, 

        exibicao_C2++;        // A Carta 2 ganha um ponto.

        printf("Area: Carta 2 vence (%d)\n", exibicao_C2);        // Mostrar a pontuação da Carta 2 até o momento.
    }


    // No caso de empate entre as duas cartas,

    else {
        printf("Area: Empate (Nenhum ponto adicionado)\n");    // Mostrar que não houve pontuação.
    }


// PIB
// (maior vence)

    if (c1.pib > c2.pib) {    // Se o PIB da Carta 1 for maior que o da Carta 2,

        exibicao_C1++;        // A Carta 1 ganha um ponto.

        printf("PIB: Carta 1 vence (%d)\n", exibicao_C1);        // Mostrar a pontuação da Carta 1 até o momento.
    }


    // Do contrário,

    else if (c1.pib < c2.pib) {    // Se o PIB da Carta 1 for menor que o da Carta 2,

        exibicao_C2++;        // A Carta 2 ganha um ponto.

        printf("PIB: Carta 2 vence (%d)\n", exibicao_C2);        // Mostrar a pontuação da Carta 2 até o momento.

    }


    // No caso de empate entre as duas cartas,

    else {
        printf("PIB: Empate (Nenhum ponto adicionado)\n");    // Mostrar que não houve pontuação.
    }


// PONTOS TURÍSTICOS
// (maior vence)

    if (c1.pontos_turisticos > c2.pontos_turisticos) {    // Se houverem mais Pontos Turísticos na Carta 1 do que na da Carta 2,

        exibicao_C1++;        // A Carta 1 ganha um ponto.

        printf("Pontos Turisticos: Carta 1 vence (%d)\n", exibicao_C1);        // Mostrar a pontuação da Carta 1 até o momento.
    }


    // Do contrário,

    else if (c1.pontos_turisticos < c2.pontos_turisticos) {    // Se houverem mais Pontos Turísticos na Carta 2 do que na da Carta 1,

        exibicao_C2++;        // A Carta 2 ganha um ponto.

        printf("Pontos Turisticos: Carta 2 vence (%d)\n", exibicao_C2);        // Mostrar a pontuação da Carta 2 até o momento.
    }


    // No caso de empate entre as duas cartas,

    else {
        printf("Pontos Turisticos: Empate (Nenhum ponto adicionado)\n");    // Mostrar que não houve pontuação.
    }
    

// DENSIDADE POPULACIONAL
// (menor vence)

    if (c1.densidade < c2.densidade) {    // Se a Densidade Populacional da Carta 1 for menor que a da Carta 2,

        exibicao_C1++;        // A Carta 1 ganha um ponto.

        printf("Densidade Populacional: Carta 1 vence (%d)\n", exibicao_C1);        // Mostrar a pontuação da Carta 1 até o momento.
    }


    // Do contrário,

    else if (c1.densidade > c2.densidade) {    // Se a Densidade Populacional da Carta 1 for maior que a da Carta 2,

        exibicao_C2++;        // A Carta 2 ganha um ponto.

        printf("Densidade Populacional: Carta 2 vence (%d)\n", exibicao_C2);        // Mostrar a pontuação da Carta 2 até o momento.
    }


    // No caso de empate entre as duas cartas,

    else {
        printf("Densidade Populacional: Empate (Nenhum ponto adicionado)\n");    // Mostrar que não houve pontuação.
    }
    

// PIB PER CAPITA
// (maior vence)

    // Se o PIB per Capita da Carta 1 for maior que o da Carta 2,
    if (c1.pib_per_capita > c2.pib_per_capita) {

        // A Carta 1 ganha um ponto.
        exibicao_C1++;

        // Mostrar a pontuação da Carta 1 até o momento.
        printf("PIB per Capita: Carta 1 vence (%d)\n", exibicao_C1);
    }


    // Do contrário,

    else if (c1.pib_per_capita < c2.pib_per_capita) {    // Se o PIB per Capita da Carta 1 for menor que o da Carta 2,

        exibicao_C2++;        // A Carta 2 ganha um ponto.

        printf("PIB per Capita: Carta 2 vence (%d)\n", exibicao_C2);        // Mostrar a pontuação da Carta 2 até o momento.
    }


    // No caso de empate entre as duas cartas,

    else {
        printf("PIB per Capita: Empate (Nenhum ponto adicionado)\n");    // Mostrar que não houve pontuação.
    }



// SUPER PODER
// (maior vence)

    if (c1.super_poder > c2.super_poder) {    // Se o Super Poder da Carta 1 for maior que o da Carta 2,

        exibicao_C1++;        // A Carta 1 ganha um ponto.

        printf("Super Poder: Carta 1 vence (%d)\n", exibicao_C1);        // Mostrar a pontuação da Carta 1 até o momento.
    }


    // Do contrário,

    else if (c1.super_poder < c2.super_poder) {    // Se o Super Poder da Carta 1 for menor que o da Carta 2,

        exibicao_C2++;        // A Carta 2 ganha um ponto.

        printf("Super Poder: Carta 2 vence (%d)\n", exibicao_C2);        // Mostrar a pontuação da Carta 2 até o momento.
    }


    // No caso de empate entre as duas cartas,

    else {
        printf("Super Poder: Empate (Nenhum ponto adicionado)\n");    // Mostrar que não houve pontuação.
    }
}


// Função principal
int main() {

    struct Cidade cidade1, cidade2;     // Declaração das cartas (struct para armazenar as informações das cidades).
    int placar1, placar2;               // Placares das cartas
    char resposta[110];                  // Resposta do usuário

    do {
        setbuf(stdin, NULL);        // Limpa o buffer de entrada para evitar leituras incorretas.

        // Exibição da tela inicial do jogo
        printf("\nBem vindo(a) ao Super Trunfo.\n\n");
        printf("1. A seguir, digite informacoes sobre duas cidades (cartas) e, no final da rodada,\n");
        printf("estes dados serao calculados para definir qual carta possui a maior quantidade de atributos superiores.\n\n");
        printf("2. Evite acentos e caracteres especiais.\n\n");

        // Leitura da primeira cidade
        printf("\nDIGITE OS DETALHES DA PRIMEIRA CARTA.\n");
        registroCidade(&cidade1);                               // Registro das informações da Carta 1

        // Leitura da segunda cidade
        printf("\nDIGITE OS DETALHES DA SEGUNDA CARTA.\n");
        registroCidade(&cidade2);                               // Registro das informações da Carta 2

        // Exibição das cartas
        mostrarCidade(cidade1, 1);
        mostrarCidade(cidade2, 2);                              // Exibir as cartas após registrar as informações

        // Exibir comparações individualizadas dos atributos
        compararAtributos(cidade1, cidade2);                    // Exibe a comparação de cada atributo

        // Determinar e mostrar o vencedor geral
        int vencedor = DeterminarVencedor(cidade1, cidade2, &placar1, &placar2);    // Determina o vencedor e atualiza os placares.

        printf("\n___________________________________________________________________________________\n\n\n");      // Separador Visual 1


        if (vencedor == 1) {                // Se a Carta 1 vencer, exibe o placar final vencedor da Carta 1 e o placar final da Carta 2.
            printf("      RESULTADO: Carta 1 vence com %d/7 pontos. Carta 2 perde com %d/7 pontos.\n", placar1, placar2);
        }

        else if (vencedor == 2) {           // Se a Carta 2 vencer, exibe o placar final vencedor da Carta 2 e o placar final da Carta 1.
            printf("      RESULTADO: Carta 2 vence com %d/7 pontos. Carta 1 perde com %d/7 pontos.\n", placar2, placar1);
        }

        else if (placar1 == placar2) {      // Se houver um empate, mostra que ambas as cartas finalizaram com o mesmo placar.

            // Visto que neste caso ambas terão o mesmo valor, podemos usar qualquer um dos dois placares para exibir o resultado.
            // Neste caso, 'placar1' está sendo usado. Porém, 'placar2' também funcionaria.

            printf("      RESULTADO: Empate. Ambas as cartas finalizaram com %d/7 pontos.\n", placar1);
        }

        else {                              // Se nenhuma das condições acima for atendida, exibe um erro inesperado.
            printf("      ATENCAO: Erro de logica inesperado. Por favor, reinicie o programa e tente novamente.\n\n");

            setbuf(stdin, NULL);        // Limpa o buffer de entrada para evitar leituras incorretas.

            printf("      Pressione qualquer tecla para encerrar o programa.\n");
            getchar();     // Espera o usuário pressionar uma tecla antes de encerrar o programa.
        }

        printf("\n___________________________________________________________________________________\n\n");        // Separador Visual 2

        // Pergunta se o usuário deseja realizar outra rodada
        printf("\n1. Deseja iniciar outra rodada? Digite 's' ou 'sim'.\n");
        printf("2. Caso deseje sair, digite qualquer outra coisa para encerrar o programa.\n");

        setbuf(stdin, NULL);                            // Limpa o buffer de entrada para evitar leituras incorretas.
        fgets(resposta, sizeof(resposta), stdin);       // Armazena a resposta
        resposta[strcspn(resposta, "\n")] = '\0';       // Remove qualquer espaçamento não desejado inserido pelo usuário

        printf("\n\n\n");       // Espaçamento de 3 linhas

         // Verifica se a resposta é 's', 'sim' ou variações com aspas simples ou ponto no final.
    } while (strcmp(resposta, "'s'") == 0 || strcmp(resposta, "s") == 0 || strcmp(resposta, "'sim'.") == 0 ||
             strcmp(resposta, "'sim'") == 0 || strcmp(resposta, "sim") == 0);
        // 'strcmp' compara strings e retorna '0' ou '!= 0', dependendo se são iguais ou não.

    exit(1);            // Se a resposta NÃO for uma das acima, retorna '1' e encerra o programa.

    return 0;           // Se a resposta FOR uma das acima, retorna '0' e reinicia o programa.
}
