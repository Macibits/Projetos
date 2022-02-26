#include <stdio.h>
#include <math.h>

int main(void)
{
    //Declaração de variáveis
    int ano;
    int sec;

    //Inserção do ano a ser computado
    do
    {
        printf("Digite um ano: ");
        scanf("%i", &ano);
    }

    //Ano deve ser entre 1 e 9999
    while (ano < 1 || ano > 9999);

    //Cálculo e impressão do século para anos de final 00
    if (ano % 100 == 0)
    {
        sec = ano / 100;
        printf("%i\n", sec);
    }

    //Cálculo e impressão para os outros anos
    else
    {
        sec = ano / 100.0;
        sec = floor(sec) + 1;
        printf("Século %i\n", sec);
    }
    return 0;
}