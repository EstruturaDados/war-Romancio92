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
