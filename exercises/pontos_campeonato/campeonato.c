    #include <stdio.h>
    #include <stdlib.h>

    int main (void)
    {
        //Declarar variáveis
        int placar[11][3];
        int pontos = 0;
        int jogos = 1;

        //Gerar resultados aleatoriamente
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                placar[i][j] = rand() % 5;

        //Mostrar resultados
                if (j == 0)
                {
                    printf("Placar %i - %i:", jogos, placar[i][j]);
                    jogos++;
                }
                else
                {
                    printf("%i\n", placar[i][j]);

                    //Contar pontos
                    if (placar[i][j] > placar[i][j + 1])
                    {
                        pontos += 3;
                    }
                    else if (placar[i][j] == placar[i][j + 1])
                    {
                        pontos += 1;
                    }
                }
            }
        }

        //Retornar resultados
        printf("Pontos da nossa equipe = %i\n", pontos);
        return 0;
    }