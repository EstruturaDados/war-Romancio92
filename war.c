// inclusao de bibliotecas.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// criação de uma struct chamada "territ" com 3 membros.
typedef struct
{
    char nome[30];
    char cor[10];
    int quantidade;
} territ;

// declaração de função criada. limpar buffer de entrada. Evita lixo de memória.
void limparbufferentrada();
// declaração de função atacar criada.
void atacar(territ* atacante, territ* defensor);
// declaração da função liberar memória.
void liberarMemoria(territ *ptrterritorio);
// declaração da função exibir o mapa.
void exibirMapa(territ *ptrterritorio);
// declaração de cadastro de territórios.
void cadastro(territ* ptrterritorio);
// declaração de função para atribuir missão.
void atribuirMissao(char *missaoAtual, char *missoes[], int totalMissoes);
// declaração de função para verificar se a missão foi cumprida.
void verificarMissao(char *missaoAtual, territ *ptrterritorio, char *exercitoAtual) ;
// declaração de função para exibir a missão no ínicio.
void exibirMissao(char *missaoAtual, char *exercitoAtual);
// declaração da função exibir menu.
void exibirMenu();
// declaração de função para sortear um exercito para o jogador.
void atribuirExercito(char *exercitoAtual, territ *ptrterritorio, int totalExercitos);


// construção da função principal.
int main ()
{       
    // utilização de ponteiros, em vez de alocação estática.
    // ptrterritorio é um ponteiro do tipo "territ" que recebe o endereço de "territorio".
    territ *ptrterritorio;
    int opcao, indice_atacante, indice_defensor;
    char *missoes[5] = {"Destruir o exercito amarelo", "Destruir o exercito verde", "Conquistar 5 territorios", "Conquistar a America", "Conquistar a Oceania"};
    char missaoAtual[50], exercitoAtual[30]; // armazenar missão sorteada.
    const int totalMissoes = 5, totalExercitos = 5;

    srand(time(NULL));

    // calloc (casting (em regra, calloc retorna void), nº elementos, tamanho de cada elemento).
    // malloc (casting (em regra, malloc retorna void), nº elementos, tamanho de cada elemento).
    ptrterritorio = (territ *) calloc(5, sizeof(territ));
    // indicar erro de alocação de memória;
    if (ptrterritorio == NULL)     
    {
        printf("Erro: falha ao alocar memória. \n");
        return 1; 
    }
    
    cadastro(ptrterritorio);
    exibirMapa(ptrterritorio);

    atribuirExercito(exercitoAtual, ptrterritorio, totalExercitos);
    atribuirMissao(missaoAtual, missoes, totalMissoes);
    exibirMissao(missaoAtual, exercitoAtual);

    do
    {
        exibirMenu();
        scanf("%i", &opcao);
        limparbufferentrada();

        switch(opcao)
        {
            case 1: 
                printf("====== FASE DE ATAQUE ====== \n");
            
                printf("Escolha o territorio atacante (1-5, ou 0 para sair): ");
                scanf("%i", &indice_atacante);  
                limparbufferentrada();             
                
                printf("Escolha o territorio defesa (1-5): ");
                scanf("%i", &indice_defensor); 
                limparbufferentrada();  

                if (indice_atacante < 1 || indice_atacante > 5 || indice_defensor < 1 || indice_defensor > 5 || indice_atacante == indice_defensor)
                {
                    printf("\ntente novamente...\n");
                }
                else if (indice_atacante > 0 && indice_atacante < 6)
                {
                atacar(&ptrterritorio[indice_atacante - 1], &ptrterritorio[indice_defensor - 1]);
                exibirMapa(ptrterritorio);
                }
                break;

            case 2:
                verificarMissao(missaoAtual, ptrterritorio, exercitoAtual);
                break;

            case 0:
                printf("\nSair do sistema...\n");
                break;

            default: 
                printf("\nOpção inválida. Tente novamente...\n");
        }
    } while (opcao != 0);
    

    
    liberarMemoria(ptrterritorio);


return 0;
}

// procedimentos:
// definir função atribuir missao.
void atribuirExercito(char *exercitoAtual, territ *ptrterritorio, int totalExercitos)
{
    int indice_sorteioe = rand () % totalExercitos;
    strcpy(exercitoAtual, ptrterritorio[indice_sorteioe].cor);
}
void atribuirMissao(char *missaoAtual, char *missoes[], int totalMissoes)
{
    int indice_sorteio = rand () % totalMissoes;
    strcpy(missaoAtual, missoes[indice_sorteio]);     
}
// definir função para verificar missão.
void verificarMissao(char *missaoAtual, territ *ptrterritorio, char *exercitoAtual) 
{
    int i;
    int territoriosConquistados = 0;
    int exercitoDestruido = 0;
    int americaConquistada = 0;
    int oceaniaConquistada = 0;

    // Conquista de 5 territórios
    if (strcmp(missaoAtual, "Conquistar 5 territorios") == 0) {
        for (i = 0; i < 5; i++) {
            if (strcmp(ptrterritorio[i].cor, exercitoAtual) == 0) {
                territoriosConquistados++;
            }
        }
        if (territoriosConquistados >= 5) {
            printf("\nObjetivo concluído! Você conquistou 5 ou mais territórios.\n");
        } else {
            printf("\nObjetivo ainda não concluído. Você tem %d territórios. Continue a atacar!\n", territoriosConquistados);
        }
    }
    // Conquistar a América
    else if (strcmp(missaoAtual, "Conquistar a America") == 0) {
        for (i = 0; i < 5; i++) {
            if (strcmp(ptrterritorio[i].nome, "America") == 0 && strcmp(ptrterritorio[i].cor, exercitoAtual) == 0) {
                americaConquistada = 1;
                break;
            }
        }
        if (americaConquistada) {
            printf("\nParabéns! Você conquistou a América e cumpriu sua missão.\n");
        } else {
            printf("\nObjetivo ainda não concluído. Conquiste a América para vencer!\n");
        }
    }
    // Conquistar a Oceania
    else if (strcmp(missaoAtual, "Conquistar a Oceania") == 0) {
        for (i = 0; i < 5; i++) {
            if (strcmp(ptrterritorio[i].nome, "Oceania") == 0 && strcmp(ptrterritorio[i].cor, exercitoAtual) == 0) {
                oceaniaConquistada = 1;
                break;
            }
        }
        if (oceaniaConquistada) {
            printf("\nParabéns! Você conquistou a Oceania e cumpriu sua missão.\n");
        } else {
            printf("\nObjetivo ainda não concluído. Conquiste a Oceania para vencer!\n");
        }
    }
    // Destruir exército amarelo
    else if (strcmp(missaoAtual, "Destruir o exercito amarelo") == 0) {
        for (i = 0; i < 5; i++) {
            if (strcmp(ptrterritorio[i].cor, "Amarelo") == 0 && ptrterritorio[i].quantidade > 0) {
                exercitoDestruido = 0; // Ainda existem tropas do exército amarelo
                break;
            }
        }
        if (!exercitoDestruido) {
            printf("\nObjetivo ainda não concluído! O exército Amarelo ainda não foi completamente destruído.\n");
        } else {
            printf("\nParabéns! O exército Amarelo foi destruído! Missão concluída.\n");
        }
    }
    // Destruir exército verde
    else if (strcmp(missaoAtual, "Destruir o exercito verde") == 0) {
        for (i = 0; i < 5; i++) {
            if (strcmp(ptrterritorio[i].cor, "Verde") == 0 && ptrterritorio[i].quantidade > 0) {
                exercitoDestruido = 0; // Ainda existem tropas do exército verde
                break;
            }
        }
        if (!exercitoDestruido) {
            printf("\nObjetivo ainda não concluído! O exército Verde ainda não foi completamente destruído.\n");
        } else {
            printf("\nParabéns! O exército Verde foi destruído! Missão concluída.\n");
        }
    }
}
// definir função para exibir missão.
void exibirMissao(char *missaoAtual, char *exercitoAtual)
{
    printf("\nSeu exercito é: %s\n", exercitoAtual);
    printf("\nSua missão no jogo é: %s\n", missaoAtual);
    printf("\nBoa Sorte!\n");
}
// definir função para limpeza de buffer.
void limparbufferentrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// definir função para exibir mapa do mundo
void exibirMapa(territ *ptrterritorio)
{
    int i;

    printf("MAPA DO MUNDO - ESTADO ATUAL \n");
    printf("################################## \n");
    
    for(i = 0; i < 5; i++)
    {   
        printf(" %i. %s (Exercito %s, Tropas: %i) \n", i +1, ptrterritorio[i].nome, ptrterritorio[i].cor, ptrterritorio[i].quantidade);
    }

    printf("\n\n");
}
// definir função para liberar memória.
void liberarMemoria(territ *ptrterritorio)
{
    // evita memory leaks (vazamento de memoria).
    free (ptrterritorio);
    printf("memoria liberada com sucesso! \n");
}
// definir função de combate.
void atacar(territ* atacante, territ* defensor)
{
    int i;
    //para gerar numerios aleatorios.
        srand(time(NULL)); 
               
        int resultado_dadoataque = rand() % 6 + 1;
        
        int resultado_dadodefesa = rand() % 6 + 1;  

        printf("O atacante %s rolou o dado: %i \n", atacante -> nome, resultado_dadoataque);
        printf("O defensor %s rolou o dado: %i \n", defensor -> nome, resultado_dadodefesa);

        if (resultado_dadoataque > resultado_dadodefesa)
        {
            printf("Vitoria do ataque! O territorio defensor perde 1 tropa. \n");
            defensor -> quantidade--;

            if (defensor -> quantidade < 0)
            {
                printf("\nConquista! O exército %s conquistou o territorio %s.\n", atacante -> cor, defensor -> nome);    
                atacante-> quantidade--;
                defensor-> quantidade++;
                strcpy(defensor -> cor, atacante -> cor);
            }
        }
        else 
        {
            printf("O territorio defensor venceu! O territorio atacante perde um territorio. \n");
            atacante -> quantidade--;
        }
        
        printf("\nPressione Enter para continuar para o proximo turno... \n");
        getchar();            
    }      

// definir função de cadastro de territórios.
void cadastro(territ* ptrterritorio)
{
    // inicializando variáveis da main.
    int i;
    int indice_atacante, indice_defensor;

    // cadastro de 5 territórios.
    printf("CADASTRO INICIAL DE 5 TERRITORIOS \n");
    //outro modo de referenciar ponteiros seria: (*ptrterritorio).nome;
    for (i = 0; i < 5; i++)
    {
    printf("========================================== \n");
    printf("------- CADASTRANDO O TERRITORIO %i -------\n", i +1);    
    printf("1. indique o nome do territorio: ");
    fgets(ptrterritorio[i].nome, 30, stdin);
    ptrterritorio[i].nome[strcspn(ptrterritorio[i].nome, "\n")] = 0; // Remove o '\n'
    printf("2. indique a cor do territorio: ");
    fgets(ptrterritorio[i].cor, 10, stdin);
    ptrterritorio[i].cor[strcspn(ptrterritorio[i].cor, "\n")] = 0; // Remove o '\n'
    printf("3. indique a quantidade de exercitos: ");
    scanf(" %i", &ptrterritorio[i].quantidade);
    limparbufferentrada();
    }

    printf("\n (Cadastro inicial concluido com sucesso!)\n");
    printf("\n");
}
void exibirMenu()
{
    printf("\n--- Menu de Ações ---\n");
    printf("1. Atacar\n");
    printf("2. Verificar Missão\n");
    printf("0. Sair\n");
    printf("Escolha sua ação: \n");
}
