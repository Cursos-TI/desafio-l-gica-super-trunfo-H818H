#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

#define MAX_STR 150
#define MAX_CODE 10
#define MAX_CARTAS 2

// Struct para armazenar os atributos de cada carta
typedef struct 
{
    char estado[MAX_STR];
    char codigo[MAX_CODE];
    char cidade[MAX_STR];
    int populacao;
    int pontos_turisticos;
    float area;
    float pib;
    float super_poder;
    float densidade_demografica;
    float pib_per_capita;
    float pib_reais;
} CARTAS;

// Uso de enum TIPOS para auxiliar na função _input(), que precisa receber um tipo para retornar um valor valido
typedef enum 
{
    T_INT,
    T_STR,
    T_FLOAT
} TIPOS;

// Uso de enum ATRIBUTOS para auxiliar no momento de escolher um atributo
typedef enum 
{
    INVALIDO,
    POPULACAO,
    AREA,
    PIB,
    PONTOSTURISTICOS,
    DENSIDADEDEMOGRAFICA,
} ATRIBUTOS;

// Função para identificar qual atributo foi escolhido a partir de uma string
ATRIBUTOS definirAtributo(char *e) 
{
    if(strcmp(e, "populacao") == 0) return POPULACAO;
    else if(strcmp(e, "area") == 0) return AREA;
    else if(strcmp(e, "pib") == 0) return PIB;
    else if(strcmp(e, "pontos turisticos") == 0) return PONTOSTURISTICOS;
    else if(strcmp(e, "densidade demografica") == 0) return DENSIDADEDEMOGRAFICA;
    else return INVALIDO;
}

// Função que peguei de outro programa que havia feito e alterei alguns detalhes para funcionar melhor neste caso,
// alem de melhorar no momento de inserir os dados das cartas e a visualização do codigo
bool _input(char mensagem[MAX_STR], void *saida, TIPOS t) 
{
    char buffer[MAX_STR];
    char *endp;
    bool valido = false;

    while(!valido) 
    {
        printf("%s", mensagem);
        fgets(buffer, MAX_STR, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        switch(t) 
        {
            case T_INT: 
            {
                long n_int = strtol(buffer, &endp, 10);
                if(*endp != '\0' || n_int < 0 || n_int > INT_MAX) 
                {
                    printf("***Erro: Digite um número inteiro válido (0 a %d)!\n", INT_MAX);
                } 
                else 
                {
                    *(int*)saida = (int)n_int;
                    valido = true;
                }
                break;
            }
            case T_FLOAT: 
            {  
                float n_float = strtof(buffer, &endp);
                if(*endp != '\0' || n_float < 0.0f || n_float > FLT_MAX) 
                {
                    printf("***Erro: Digite um número real válido (>= 0.0)!\n");
                } 
                else
                {
                    *(float*)saida = n_float;
                    valido = true;
                }
                break;
            }
            case T_STR:
                if(strlen(buffer) == 0) 
                {
                    printf("***Erro: Entrada vazia. Digite novamente!\n");
                }
                else 
                {
                    strcpy((char*)saida, buffer);
                    valido = true;
                }
                break;
            default:
                printf("***Erro: Tipo de entrada inválido!\n");
                return false;
        }
    }
    return true;
}

// Funçao para exibir as cartas evitando uso de varios printf()
void exibirCartas(CARTAS *carta) 
{
    if(carta == NULL) 
    {
        printf("\n***Nenhuma carta cadastrada!***\n");
        return;
    }

    printf("\n***DADOS DAS CARTAS***\n");
    
    for(int i = 0; i < MAX_CARTAS; i++) 
    {
        printf("\nCarta %d\n", i+1);
        printf("Estado: %s\n", carta[i].estado);
        printf("Código: %s\n", carta[i].codigo);
        printf("Cidade: %s\n", carta[i].cidade);
        printf("População: %d hab.\n", carta[i].populacao);
        printf("Área: %.2f km²\n", carta[i].area);
        printf("PIB: %.2f bilhões\n", carta[i].pib);
        printf("Pontos Turísticos: %d\n", carta[i].pontos_turisticos);
        printf("Densidade Demográfica: %.2f hab/km²\n", carta[i].densidade_demografica);
        printf("PIB per capita: R$ %.2f\n", carta[i].pib_per_capita);
        printf("Super Poder: %.2f\n", carta[i].super_poder);
    }
}

// Funçoes para calculos de Densidade Demografica, PIB Per Capita e Super Poder
float calcDensidadeDemografica(int populacao, float area) 
{
    return (area <= 0.0f) ? 0.0f : ((float)populacao / area);
}

float calcPIBPerCapita(float pib_reais, int populacao) 
{
    return (populacao <= 0) ? 0.0f : (pib_reais / (float)populacao); 
}

float calcSuperPoder(int pontos_turisticos, int populacao, float area, float pib, float pib_per_capita, float densidade_demografica) 
{
    if(area <= 0.0f || densidade_demografica <= 0.0f || populacao <= 0 || pontos_turisticos < 0) 
    {return 0.0f;}
    float termo_pontos = (float)pontos_turisticos / 10.0f;
    float termo_pib = pib / 100.0f;
    float termo_pop = (float)populacao / 1e6f;
    float termo_area = area / 1e3f;
    float termo_pib_capita = pib_per_capita / 1e3f;
    float termo_densidade = 1.0f / densidade_demografica;
    
    return termo_pontos + termo_pib + termo_pop + termo_area + termo_pib_capita + termo_densidade;
}

// Função separada para comparar as cartas e exibir o resultado. Poderia ter feito dentro da main(), mas assim fica mais organizado e ajuda a entender sobre funções
void compararCartas(CARTAS *carta, ATRIBUTOS opcaoUm, ATRIBUTOS opcaoDois) 
{
    if(carta == NULL || carta[0].cidade[0] == '\0' || carta[1].cidade[0] == '\0') 
    {
        printf("***Erro: Cartas inválidas para comparação!\n");
        return;
    }

    if(opcaoUm == opcaoDois) 
    {
        printf("***Erro: Escolha atributos diferentes!\n");
        return;
    }

    int pontos_cartaUm = 0, pontos_cartaDois = 0;

    // Comparação do primeiro atributo
    printf("\n");
    switch(opcaoUm) 
    {
        case POPULACAO:
            printf("\n*Comparação por População*\n");
            printf("%s: %d hab.\n%s: %d hab.\n", 
                   carta[0].cidade, carta[0].populacao, 
                   carta[1].cidade, carta[1].populacao);
            carta[0].populacao > carta[1].populacao ? pontos_cartaUm++ : 
            carta[1].populacao > carta[0].populacao ? pontos_cartaDois++ : 0;
            break;
            
        case AREA:
            printf("\n*Comparação por Área*\n");
            printf("%s: %.2f km²\n%s: %.2f km²\n", 
                   carta[0].cidade, carta[0].area, 
                   carta[1].cidade, carta[1].area);
            carta[0].area > carta[1].area ? pontos_cartaUm++ : 
            carta[1].area > carta[0].area ? pontos_cartaDois++ : 0;
            break;
            
        case PIB:
            printf("\n*Comparação por PIB*\n");
            printf("%s: %.2f bilhões\n%s: %.2f bilhões\n", 
                   carta[0].cidade, carta[0].pib, 
                   carta[1].cidade, carta[1].pib);
            carta[0].pib > carta[1].pib ? pontos_cartaUm++ : 
            carta[1].pib > carta[0].pib ? pontos_cartaDois++ : 0;
            break;
            
        case PONTOSTURISTICOS:
            printf("\n*Comparação por Pontos Turísticos*\n");
            printf("%s: %d pontos\n%s: %d pontos\n", 
                   carta[0].cidade, carta[0].pontos_turisticos, 
                   carta[1].cidade, carta[1].pontos_turisticos);
            carta[0].pontos_turisticos > carta[1].pontos_turisticos ? pontos_cartaUm++ : 
            carta[1].pontos_turisticos > carta[0].pontos_turisticos ? pontos_cartaDois++ : 0;
            break;
            
        case DENSIDADEDEMOGRAFICA:
            printf("\n*Comparação por Densidade Demográfica*\n");
            printf("%s: %.2f hab/km²\n%s: %.2f hab/km²\n", 
                   carta[0].cidade, carta[0].densidade_demografica, 
                   carta[1].cidade, carta[1].densidade_demografica);
            carta[0].densidade_demografica < carta[1].densidade_demografica ? pontos_cartaUm++ : 
            carta[1].densidade_demografica < carta[0].densidade_demografica ? pontos_cartaDois++ : 0;
            break;
            
        default:
            printf("\n***Atributo inválido!\n");
            return;
    }

    // Comparação do segundo atributo
    switch(opcaoDois) 
    {
        case POPULACAO:
            printf("\n*Comparação por População*\n");
            printf("%s: %d hab.\n%s: %d hab.\n", 
                   carta[0].cidade, carta[0].populacao, 
                   carta[1].cidade, carta[1].populacao);
            carta[0].populacao > carta[1].populacao ? pontos_cartaUm++ : 
            carta[1].populacao > carta[0].populacao ? pontos_cartaDois++ : 0;
            break;
            
        case AREA:
            printf("\n*Comparação por Área*\n");
            printf("%s: %.2f km²\n%s: %.2f km²\n", 
                   carta[0].cidade, carta[0].area, 
                   carta[1].cidade, carta[1].area);
            carta[0].area > carta[1].area ? pontos_cartaUm++ : 
            carta[1].area > carta[0].area ? pontos_cartaDois++ : 0;
            break;
            
        case PIB:
            printf("\n*Comparação por PIB*\n");
            printf("%s: %.2f bilhões\n%s: %.2f bilhões\n", 
                   carta[0].cidade, carta[0].pib, 
                   carta[1].cidade, carta[1].pib);
            carta[0].pib > carta[1].pib ? pontos_cartaUm++ : 
            carta[1].pib > carta[0].pib ? pontos_cartaDois++ : 0;
            break;
            
        case PONTOSTURISTICOS:
            printf("\n*Comparação por Pontos Turísticos*\n");
            printf("%s: %d pontos\n%s: %d pontos\n", 
                   carta[0].cidade, carta[0].pontos_turisticos, 
                   carta[1].cidade, carta[1].pontos_turisticos);
            carta[0].pontos_turisticos > carta[1].pontos_turisticos ? pontos_cartaUm++ : 
            carta[1].pontos_turisticos > carta[0].pontos_turisticos ? pontos_cartaDois++ : 0;
            break;
            
        case DENSIDADEDEMOGRAFICA:
            printf("\n*Comparação por Densidade Demográfica*\n");
            printf("%s: %.2f hab/km²\n%s: %.2f hab/km²\n", 
                   carta[0].cidade, carta[0].densidade_demografica, 
                   carta[1].cidade, carta[1].densidade_demografica);
            // Menor densidade é melhor
            carta[0].densidade_demografica < carta[1].densidade_demografica ? pontos_cartaUm++ : 
            carta[1].densidade_demografica < carta[0].densidade_demografica ? pontos_cartaDois++ : 0;
            break;
            
        default:
            printf("\n***Atributo inválido!\n");
            return;
    }

    // Resultado final
    printf("\n***RESULTADO FINAL***\n");
    printf("%s: %d vitória(s)\n", carta[0].cidade, pontos_cartaUm);
    printf("%s: %d vitória(s)\n", carta[1].cidade, pontos_cartaDois);

    if(pontos_cartaUm == 2) 
    {
        printf("\n%s VENCEU!\n", carta[0].cidade);
    } 
    else if(pontos_cartaDois == 2) 
    {
        printf("\n%s VENCEU!\n", carta[1].cidade);
    } 
    else 
    {
        printf("\nEMPATE! As cartas venceram em um atributo cada\n");
    }
}

int main()
{
    CARTAS carta[MAX_CARTAS] = {0};
    char entrada[MAX_STR];
    char atributoUm[MAX_STR], atributoDois[MAX_STR];
    ATRIBUTOS opcaoUm, opcaoDois;

    // Cadastro das cartas utilizando loop for()
    printf("\n***Cadastro de Cartas***\n");
    for(int i = 0; i < MAX_CARTAS; i++) 
    {
        printf("\n***Carta %d***\n", i+1);
        
        if(!_input("Estado: ", carta[i].estado, T_STR)){return 1;};
        if(!_input("Código: ", carta[i].codigo, T_STR)){return 1;};
        if(!_input("Cidade: ", carta[i].cidade, T_STR)){return 1;};
        if(!_input("População: ", &carta[i].populacao, T_INT)){return 1;};
        if(!_input("Área (km²): ", &carta[i].area, T_FLOAT)){return 1;};
        if(!_input("PIB (bilhões): ", &carta[i].pib, T_FLOAT)){return 1;};
        if(!_input("Pontos Turísticos: ", &carta[i].pontos_turisticos, T_INT)){return 1;};
        carta[i].pib_reais = carta[i].pib * 1e9;
        carta[i].densidade_demografica = calcDensidadeDemografica(carta[i].populacao, carta[i].area);
        carta[i].pib_per_capita = calcPIBPerCapita(carta[i].pib_reais, carta[i].populacao);
        carta[i].super_poder = calcSuperPoder(carta[i].pontos_turisticos, carta[i].populacao, 
            carta[i].area, carta[i].pib, carta[i].pib_per_capita, carta[i].densidade_demografica);
    }

    exibirCartas(carta);

    // Inicializando os atributos para fazer a comparação
    printf("\nCOMPARAÇÃO\n");
    printf("*Atributos disponíveis:\n");
    printf("- populacao\n- area\n- pib\n- pontos turisticos\n- densidade demografica\n");

    if(!_input("\nPrimeiro atributo: ", atributoUm, T_STR)){return 1;}
    if(!_input("Segundo atributo: ", atributoDois, T_STR)){return 1;}

    opcaoUm = definirAtributo(atributoUm);
    opcaoDois = definirAtributo(atributoDois);

    if(opcaoUm == INVALIDO || opcaoDois == INVALIDO)
    {
        printf("Atributo(s) inválido(s)!\n");
        return 1;
    }

    compararCartas(carta, opcaoUm, opcaoDois);

    return 0;
}
