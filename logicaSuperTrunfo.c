#include<stdio.h>
#include<string.h>
#include<stdlib.h>


// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.
//Teste larissa

int main() {
    // Sugestão: Defina variáveis separadas para cada atributo da cidade.
    // Exemplos de atributos: código da cidade, nome, população, área, PIB, número de pontos turísticos.
    char estado1[100], estado2[100];
    char codigo1[10], codigo2[10];
    char cidade1[100], cidade2[100];
    char temporario[25];
    int populacao1, populacao2;
    float area1, area2;
    float pib1, pib2;
    int pontos_turisticos1, pontos_turisticos2;
    float densidade_populacional1, densidade_populacional2;
    float pib_per_capita1, pib_per_capita2;

    float pib1_reais;
    float pib2_reais;

    float super_poder1, super_poder2;
    
    // Cadastro das Cartas:
    // Sugestão: Utilize a função scanf para capturar as entradas do usuário para cada atributo.
    // Solicite ao usuário que insira as informações de cada cidade, como o código, nome, população, área, etc.
    // Registrando Primeira Carta
    printf("Estado: ");
    fgets(estado1, sizeof(estado1), stdin);
    estado1[strcspn(estado1, "\n")] = '\0';

    printf("Código da Carta: ");
    fgets(codigo1, sizeof(codigo1), stdin);
    codigo1[strcspn(codigo1, "\n")] = '\0';

    printf("Nome da Cidade: ");
    fgets(cidade1, sizeof(cidade1), stdin);    
    cidade1[strcspn(cidade1, "\n")] = '\0';

    printf("População: ");
    fgets(temporario, sizeof(temporario), stdin);
    populacao1 = atoi(temporario);

    printf("Área: ");
    fgets(temporario, sizeof(temporario), stdin);
    area1 = atof(temporario);

    printf("PIB: ");
    fgets(temporario, sizeof(temporario), stdin);
    pib1 = atof(temporario);
    pib1_reais = pib1 * 1e9;
    
    printf("Numero de Pontos Turísticos: ");
    fgets(temporario, sizeof(temporario), stdin);
    pontos_turisticos1 = atoi(temporario);

    printf("\n");
    
    // Registrando Segunda Carta
    printf("Estado: ");
    fgets(estado2, sizeof(estado2), stdin);
    estado2[strcspn(estado2, "\n")] = '\0';

    printf("Código da Carta: ");
    fgets(codigo2, sizeof(codigo2), stdin);
    codigo2[strcspn(codigo2, "\n")] = '\0';

    printf("Nome da Cidade: ");
    fgets(cidade2, sizeof(cidade2), stdin);    
    cidade2[strcspn(cidade2, "\n")] = '\0';

    printf("População: ");
    fgets(temporario, sizeof(temporario), stdin);
    populacao2 = atoi(temporario);

    printf("Área: ");
    fgets(temporario, sizeof(temporario), stdin);
    area2 = atof(temporario);

    printf("PIB: ");
    fgets(temporario, sizeof(temporario), stdin);
    pib2 = atof(temporario);
    pib2_reais = pib2 * 1e9;
    
    printf("Numero de Pontos Turísticos: ");
    fgets(temporario, sizeof(temporario), stdin);
    pontos_turisticos2 = atoi(temporario);

    // Exibição dos Dados das Cartas:
    // Sugestão: Utilize a função printf para exibir as informações das cartas cadastradas de forma clara e organizada.
    // Exiba os valores inseridos para cada atributo da cidade, um por linha.
    
    // Exibindo Dados da Primeira Carta
    printf("\nCarta 1: \n");

    printf("Estado: %s\n", estado1);

    printf("Código da Carta: %s\n", codigo1);

    printf("Nome da Cidade: %s\n", cidade1);

    printf("População: %d\n", populacao1);

    printf("Área: %.2f km²\n", area1);

    printf("PIB: %.2f bilhões de reais\n", pib1);

    printf("Numero de Pontos Turísticos: %d\n", pontos_turisticos1);

    // PIB per capita e densidade populacional
    densidade_populacional1 = (float)populacao1 / area1;
    printf("Densidade Populacional: %.2f hab/km²\n", densidade_populacional1);
    
    pib_per_capita1 = pib1_reais / (float)populacao1;
    printf("PIB per capita: %.2f reais\n", pib_per_capita1);
    
    // Exibindo Dados da Segunda carta:
    printf("\nCarta 2: \n");

    printf("Estado: %s\n", estado2);

    printf("Código da Carta: %s\n", codigo2);

    printf("Nome da Cidade: %s\n", cidade2);

    printf("População: %d\n", populacao2);

    printf("Área: %.2f km²\n", area2);

    printf("PIB: %.2f bilhões de reais\n", pib2);

    printf("Numero de Pontos Turísticos: %d\n", pontos_turisticos2);

    // Densidade populacional e PIB per capita
    densidade_populacional2 = (float)populacao2 / area2;
    printf("Densidade Populacional: %.2f hab/km²\n", densidade_populacional2);

    pib_per_capita2 = pib2_reais / (float)populacao2;
    printf("PIB per capita: %.2f reais\n", pib_per_capita2);

    // Calculando Super Poder das cartas
    super_poder1 = ((float)pontos_turisticos1 + (float)populacao1 + area1 
                    + pib1 + pib_per_capita1 + (1.0 / densidade_populacional1));

    super_poder2 = ((float)pontos_turisticos2 + (float)populacao2 + area2 
                    + pib2 + pib_per_capita2 + (1.0 / densidade_populacional2));

    //Comparando o atributo População
    printf("\n**Comparação de cartas(Atributo: População): \n");
    if(populacao1 > populacao2)
    {
        printf("Resultado: Carta 1(%s) venceu!\n", cidade1);
    }
    else if(populacao2 > populacao1)
    {
        printf("Resultado: Carta 2(%s) venceu!\n", cidade2);
    }
    else
    {    
        printf("Resultado: Empate!");
    }

    return 0;
}
