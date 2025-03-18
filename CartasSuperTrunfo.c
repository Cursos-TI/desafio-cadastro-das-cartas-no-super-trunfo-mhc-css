#include <stdio.h>

#include <string.h>
#include <stdlib.h> // Necessário para o funcionamento de ATOI/ATOL/ATOF


// Definição da estrutura Cidade
struct Cidade {
    char pais[60];
    char estado_codigo_ou_nome[70];
    char cidade_codigo[10];
    char cidade_nome[80];
    long populacao;
    double area; // em km²
    double pib;  // em bi de reais
    double pontos_turisticos;
    double densidade; // população por km²
    double pib_per_capita;
};


// Função para registrar informações da cidade
void registroCidade(struct Cidade *cidade) {
    char buffer[100];

    printf("Digite o nome do pais (por exemplo, 'Brasil'): ");
    fgets(cidade->pais, sizeof(cidade->pais), stdin);           // Lê e armazena a entrada do usuário na variável 'cidade_pais' (neste caso).
    cidade->pais[strcspn(cidade->pais, "\n")] = '\0';           // Evita que a string armazenada contenha uma quebra de linha indesejada. [...]

    printf("Digite o codigo ou o nome do estado (por exemplo, 'PR' ou 'Parana'): ");
    fgets(cidade->estado_codigo_ou_nome, sizeof(cidade->estado_codigo_ou_nome), stdin);
    cidade->estado_codigo_ou_nome[strcspn(cidade->estado_codigo_ou_nome, "\n")] = '\0';         // [...]
    
    printf("Digite o codigo da cidade (por exemplo, '01'): ");
    fgets(cidade->cidade_codigo, sizeof(cidade->cidade_codigo), stdin);
    cidade->cidade_codigo[strcspn(cidade->cidade_codigo, "\n")] = '\0';         // [...]

    printf("Digite o nome da cidade (por exemplo, 'Curitiba'): ");
    fgets(cidade->cidade_nome, sizeof(cidade->cidade_nome), stdin);
    cidade->cidade_nome[strcspn(cidade->cidade_nome, "\n")] = '\0';         // [...]

    printf("Digite a populacao da cidade (por exemplo, '1774000'):");
    fgets(buffer, sizeof(buffer), stdin);
    cidade->populacao = atol(buffer);                                        // Converter 'string' para 'long integer'.

    printf("Digite a area da cidade em quilometros quadrados (por exemplo, '432'): ");
    fgets(buffer, sizeof(buffer), stdin);
    cidade->area = atof(buffer);                                             // Converter 'string' para 'double'.

    printf("Digite o PIB da cidade em bilhoes de reais (por exemplo, '98'): ");
    fgets(buffer, sizeof(buffer), stdin);
    cidade->pib = atof(buffer);                                              // Converter 'string' para 'double'.

    printf("Digite a quantidade de pontos turisticos da cidade (por exemplo, '20'): ");
    fgets(buffer, sizeof(buffer), stdin);
    cidade->pontos_turisticos = atof(buffer);                                // Converter 'string' para 'double'.

    // Calcular densidade populacional
    cidade->densidade = cidade->populacao / cidade->area;       // Densidade = População ÷ Área

    // Calcular PIB per capita (converter PIB)
    cidade->pib_per_capita = (cidade->pib * 1e9) / cidade->populacao;       // PIB per capita = PIB [Notação científica] ÷ População
}


// Função para mostrar informações da cidade
void mostrarCidade(struct Cidade cidade, int cartaCodigo) {
    printf("\nCARTA %d:\n", cartaCodigo);
    printf("Pais: %s\n", cidade.pais);
    printf("Estado: %s\n", cidade.estado_codigo_ou_nome);
    printf("Codigo: %s\n", cidade.cidade_codigo);
    printf("Nome: %s\n", cidade.cidade_nome);
    printf("Populacao: %ld\n", cidade.populacao);
    printf("Area (em quilometro quadrado): %    \n", cidade.area);
    printf("PIB: R$%.2lf bi\n", cidade.pib);
    printf("Pontos turisticos: %.2lf\n", cidade.pontos_turisticos);
    printf("Densidade populacional: %.2lf por quilometro quadrado\n", cidade.densidade);
    printf("PIB per capita: R$%.2lf\n", cidade.pib_per_capita);
}


// Função para determinar o vencedor
int DeterminarVencedor(struct Cidade cidade1, struct Cidade cidade2, int *placar1, int *placar2) {
    *placar1 = 0;
    *placar2 = 0;                               // Estrutura o placar das cartas, que começa em 0.

    // Comparar população (maior = vencedor)
    if (cidade1.populacao > cidade2.populacao) {            // Se a População da Carta 1 for maior que a da Carta 2,
        (*placar1)++;                                       // A Carta 1 ganha um ponto.

    } else if (cidade1.populacao < cidade2.populacao) {     // Se a População da Carta 1 for menor que a da Carta 2,
        (*placar2)++;                                       // A Carta 2 ganha um ponto. [..]
    }

    // Comparar área (maior = vencedor)
    if (cidade1.area > cidade2.area) {                      // [..]
        (*placar1)++;
    } else if (cidade1.area < cidade2.area) {
        (*placar2)++;
    }

    // Comparar PIB (maior = vencedor)
    if (cidade1.pib > cidade2.pib) {                      // [..]
        (*placar1)++;
    } else if (cidade1.pib < cidade2.pib) {
        (*placar2)++;
    }

    // Comparar pontos turísticos (maior = vencedor)
    if (cidade1.pontos_turisticos > cidade2.pontos_turisticos) {                      // [..]
        (*placar1)++;
    } else if (cidade1.pontos_turisticos < cidade2.pontos_turisticos) {
        (*placar2)++;
    }

    // Comparar densidade de população (menor = vencedor)
    if (cidade1.densidade < cidade2.densidade) {                      // [..]
        (*placar1)++;
    } else if (cidade1.densidade > cidade2.densidade) {
        (*placar2)++;
    }

    // Comparar PIB per capita (maior = vencedor)
    if (cidade1.pib_per_capita > cidade2.pib_per_capita) {                      // [..]
        (*placar1)++;
    } else if (cidade1.pib_per_capita < cidade2.pib_per_capita) {
        (*placar2)++;
    }

    // Determinar a carta que venceu mais atributos
    if (*placar1 > *placar2) {                          // Se o placar final da Carta 1 for maior que o da Carta 2,
        return 1; // A carta 1 vence.                   // ...A Carta 1 vence.

    if (*placar1 > *placar2) {                          // Se o placar final da Carta 2 for maior que o da Carta 1,
    } else if (*placar2 > *placar1) {                   // ...A Carta 2 vence.
        return 2; // A carta 2 vence.
    } else {
        return 0; // Ocorre empate entre as duas cartas.
    }
}


int main() {
    struct Cidade cidade1, cidade2;
    int placar1, placar2;
    char resposta[10];              // Char para resposta final (encerrar ou não o programa).

    // Loop principal do programa
    do {
        // Limpar o buffer do stdin para evitar leituras incorretas
        fflush(stdin);

        // Tela Inicial
        printf("\nBem vindo(a) ao Super Trunfo.\n\n");

        printf("1. A seguir, digite informacoes sobre duas cidades (identificadas como cartas) respectivamente e, no final da rodada,\n");
        printf("estes dados serao calculados para definir qual carta possui a maior quantidade de atributos superiores.\n\n");

        printf("2. Para evitar caracteres indefinidos, nao utilize acentos, sinais diacriticos ou caracteres especiais em geral (por exemplo: circunflexo, agudo, til, etc.).\n\n");

        // Primeira cidade
        printf("\nDIGITE OS DETALHES DA PRIMEIRA CARTA.\n");
        registroCidade(&cidade1);

        // Segunda cidade
        printf("\nDIGITE OS DETALHES DA SEGUNDA CARTA.\n");
        registroCidade(&cidade2);

        // Mostrar as cartas após as registrar
        mostrarCidade(cidade1, 1);
        mostrarCidade(cidade2, 2);

        // Determinar e mostrar a carta vencedora
        int vencedor = DeterminarVencedor(cidade1, cidade2, &placar1, &placar2);

        if (vencedor == 1) {           // Vence a Carta 1 se tiver obtido mais pontos no placar.
            printf("\n___________________________________________________________________________________\n\n");
            printf("\n      RESULTADO: Carta 1 vence com %d/6 pontos. Carta 2 perde com %d/6 pontos.\n", placar1, placar2);
            printf("\n___________________________________________________________________________________\n\n");

        } else if (vencedor == 2) {    // Vence a Carta 2 se tiver obtido mais pontos no placar.
            printf("\n___________________________________________________________________________________\n\n");
            printf("\n      RESULTADO: Carta 2 vence com %d/6 pontos. Carta 1 perde com %d/6 pontos.\n", placar1, placar2);
            printf("\n___________________________________________________________________________________\n\n");

        } else if (placar1 == placar2) {    // Se ambas as cartas tiverem obtido a mesma pontuação no placar, ocorre um empate.
            printf("\n___________________________________________________________________________________\n\n");
            printf("\n   RESULTADO: Houve um empate. Ambas as cartas finalizaram com %d/6 pontos cada.\n", (placar1 + placar2) / 2);
            printf("\n___________________________________________________________________________________\n\n");
        }

        // Perguntar se o usuário deseja jogar novamente
        printf("\n\n1. Deseja iniciar outra rodada? Digite 's' ou 'sim'.\n\n2. Caso deseje sair, digite qualquer coisa para encerrar o programa.\n\n");
        fgets(resposta, sizeof(resposta), stdin);           // Armazena a string no char "resposta"
        resposta[strcspn(resposta, "\n\n\n")] = '\0';       // Evita que a string armazenada contenha quebras de linhas indesejadas.
        printf("\n\n\n");                                   // Espaçamento visual.

    } while (strcmp(resposta, "s") == 0 || strcmp(resposta, "'s'") == 0 || strcmp(resposta, "'s'.") == 0 || 
            strcmp(resposta, "sim") == 0 || strcmp(resposta, "'sim'") == 0 || strcmp(resposta, "'sim'.") == 0 || 
            strcmp(resposta, "y") == 0 || strcmp(resposta, "'y'") == 0 || strcmp(resposta, "'y'.") == 0 || 
            strcmp(resposta, "yes") == 0 || strcmp(resposta, "'yes'") == 0 || strcmp(resposta, "'yes'.") == 0);     // Inputs válidos para reiniciar o jogo.


      exit(1);      // Fecha o prompt de comando caso a resposta não seja 's', 'sim' ou outras listadas acima.

    return 0;
}
}
