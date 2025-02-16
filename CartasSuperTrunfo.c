/*

#include <stdio.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.
//Teste larissa

int main() {
    // Sugestão: Defina variáveis separadas para cada atributo da cidade.
    // Exemplos de atributos: código da cidade, nome, população, área, PIB, número de pontos turísticos.
    
    // Cadastro das Cartas:
    // Sugestão: Utilize a função scanf para capturar as entradas do usuário para cada atributo.
    // Solicite ao usuário que insira as informações de cada cidade, como o código, nome, população, área, etc.
    
    // Exibição dos Dados das Cartas:
    // Sugestão: Utilize a função printf para exibir as informações das cartas cadastradas de forma clara e organizada.
    // Exiba os valores inseridos para cada atributo da cidade, um por linha.

    return 0;
}
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // "#include <stdlib.h>" ---> Necessário para ATOI/ATOL funcionar

// Funções
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

// Info para cidade
void registroCidade(struct Cidade *cidade) {
    char buffer[100];

    printf("Digite o nome do pais: (por exemplo, 'Brasil') ");
    fgets(cidade->pais, sizeof(cidade->pais), stdin);
    cidade->pais[strcspn(cidade->pais, "\n")] = '\0';

    printf("Digite o codigo ou nome do estado: (por exemplo, 'PR' ou 'Parana') ");
    fgets(cidade->estado_codigo_ou_nome, sizeof(cidade->estado_codigo_ou_nome), stdin);
    cidade->estado_codigo_ou_nome[strcspn(cidade->estado_codigo_ou_nome, "\n")] = '\0';

    printf("Digite o codigo da cidade: (por exemplo, '01') ");
    fgets(cidade->cidade_codigo, sizeof(cidade->cidade_codigo), stdin);
    cidade->cidade_codigo[strcspn(cidade->cidade_codigo, "\n")] = '\0';

    printf("Digite o nome da cidade: (por exemplo, 'Curitiba') ");
    fgets(cidade->cidade_nome, sizeof(cidade->cidade_nome), stdin);
    cidade->cidade_nome[strcspn(cidade->cidade_nome, "\n")] = '\0';

    printf("Digite a populacao da cidade: (por exemplo, '1774000') ");
    fgets(buffer, sizeof(buffer), stdin);
    cidade->populacao = atol(buffer); // Converter 'string' para 'long integer'

    printf("Digite a area da cidade em quilometros quadrados: (por exemplo, '432') ");
    fgets(buffer, sizeof(buffer), stdin);
    cidade->area = atof(buffer); // Converter 'string' para 'double'

    printf("Digite o PIB da cidade em bilhoes de reais: (por exemplo, '98') ");
    fgets(buffer, sizeof(buffer), stdin);
    cidade->pib = atof(buffer); // Converter 'string' para 'double'

    printf("Digite o número de pontos turisticos da cidade: (por exemplo, '20') ");
    fgets(buffer, sizeof(buffer), stdin);
    cidade->pontos_turisticos = atoi(buffer); // Converter 'string' para 'int'

    // Calcular densidade populacional
    cidade->densidade = cidade->populacao / cidade->area;

    // Calcular PIB per capita (converter PIB)
    cidade->pib_per_capita = (cidade->pib * 1e9) / cidade->populacao;
}

/*
O CÓDIGO A SEGUIR É OBSOLETO AQUI POIS UTILIZA O "SCANF" QUE NÃO FUNCIONA CORRETAMENTE
(ou, pelo menos neste código em específico) PARA NOMES COMPOSTOS (OU QUE POSSUEM ESPAÇAMENTO).

Exemplos: 'Rio de Janeiro', 'Rio Grande do Sul', etc.



Info para cidade
void registroCidade(struct Cidade *cidade) {
    printf("Digite o nome do pais: (por exemplo, 'Brasil') ");
    scanf("%s", cidade->pais);

    printf("Digite o codigo ou nome do estado: (por exemplo, 'PR' ou 'Parana') ");
    scanf("%s", cidade->estado_codigo_ou_nome);

    printf("Digite o codigo da cidade: (por exemplo, '01')");
    scanf("%s", cidade->cidade_codigo);

    printf("Digite o nome da cidade: (por exemplo, 'Curitiba') ");
    scanf("%s", cidade->cidade_nome);

    printf("Digite a populacao da cidade: (por exemplo, '1774000') ");
    scanf("%ld", &cidade->populacao);

    printf("Digite a area da cidade em quilometros quadrados: (por exemplo, '432') ");
    scanf("%lf", &cidade->area);

    printf("Digite o PIB da cidade em bilhoes de reais: (por exemplo, '98') ");
    scanf("%lf", &cidade->pib);

    // Calcular densidade populacional
    cidade->densidade = cidade->populacao / cidade->area;

    // Calcular PIB per capita (converter PIB)
    cidade->pib_per_capita = (cidade->pib * 1e9) / cidade->populacao;

    */

// Mostra informações de uma carta
void mostrarCidade(struct Cidade cidade, int cartaCodigo) {
    printf("\nCARTA %d:\n", cartaCodigo);
    printf("Pais: %s\n", cidade.pais);
    printf("Estado: %s\n", cidade.estado_codigo_ou_nome);
    printf("Código: %s\n", cidade.cidade_codigo);
    printf("Nome: %s\n", cidade.cidade_nome);
    printf("Populacao: %ld\n", cidade.populacao);
    printf("Area (em km²): %.2lf\n", cidade.area);
    printf("PIB: %.2lf bilhões de reais\n", cidade.pib);
    printf("Pontos Turisticos: %.2lf\n", cidade.pontos_turisticos);
    printf("Densidade populacional: %.2lf por quilometro quadrado\n", cidade.densidade);
    printf("PIB per capita: R$%.2lf\n", cidade.pib_per_capita);
}

// Determinar qual carta venceu
int DeterminarVencedor(struct Cidade cidade1, struct Cidade cidade2) {
    int placar1 = 0, placar2 = 0;

    // Comparar população (maior = vencedor)
    if (cidade1.populacao > cidade2.populacao) {
        placar1++;
    } else if (cidade1.populacao < cidade2.populacao) {
        placar2++;
    }

    // Comparar área (maior = vencedor)
    if (cidade1.area > cidade2.area) {
        placar1++;
    } else if (cidade1.area < cidade2.area) {
        placar2++;
    }

    // Comparar PIB (maior = vencedor)
    if (cidade1.pib > cidade2.pib) {
        placar1++;
    } else if (cidade1.pib < cidade2.pib) {
        placar2++;
    }

    // Comparar pontos turísticos (maior = vencedor)
    if (cidade1.pontos_turisticos > cidade2.pontos_turisticos) {
        placar1++;
    } else if (cidade1.pontos_turisticos < cidade2.pontos_turisticos) {
        placar2++;
    }

    // Comparar densidade de população (menor = vencedor)
    if (cidade1.densidade < cidade2.densidade) {
        placar1++;
    } else if (cidade1.densidade > cidade2.densidade) {
        placar2++;
    }

    // Comparar PIB per capita (maior = vencedor)
    if (cidade1.pib_per_capita > cidade2.pib_per_capita) {
        placar1++;
    } else if (cidade1.pib_per_capita < cidade2.pib_per_capita) {
        placar2++;
    }

    // Determinar a carta que venceu mais atriibtos
    if (placar1 > placar2) {
        return 1; // A carta 1 vence
    } else if (placar2 > placar1) {
        return 2; // A carta 2 vence
    } else {
        return 0; // Ocorre empate entre as duas cartas
    }
}

int main() {
    struct Cidade cidade1, cidade2;

    //Tela Inicial
    printf("Bem vindo(a) ao Super Trunfo. A seguir, digite informacoes sobre duas cidades (identificadas como cartas) respectivamente e,\n no final do programa, estes dados serao calculados para definir qual carta possui melhores atributos. \n \nPara evitar caracteres indefinidos, nao utilize acentos especiais, como os presentes na lingua portuguesa.\n\n1. DIGITE OS DETALHES PARA A PRIMEIRA CARTA.\n");
    registroCidade(&cidade1);

    //Segunda cidade
    printf("\n2. DIGITE OS DETALHES PARA A SEGUNDA CARTA.\n");
    registroCidade(&cidade2);

    // Mostrar as cartas após as registrar
    mostrarCidade(cidade1, 1);
    mostrarCidade(cidade2, 2);

    // Determinar e mostrar a carta vencedora
    int vencedor = DeterminarVencedor(cidade1, cidade2);

    if (vencedor == 1) {
        printf("\nRESULTADO: CARTA 1 VENCE!\n");
    } else if (vencedor == 2) {
        printf("\nRESULTADO: CARTA 2 VENCE!\n");
    } else {
        printf("\nRESULTADO: HOUVE UM EMPATE ENTRE AS DUAS CARTAS!\n");
    }

    printf("\nPressione Enter para fechar o programa.");
    getchar(); // Remove o espaço do '\n' (?)
    getchar();  // Espera o usuario apertar Enter para fechar

    return 0;
}


