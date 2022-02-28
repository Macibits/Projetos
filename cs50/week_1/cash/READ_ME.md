# Week 1 Problem - Cash

Neste problema o programa deve retornar o mínimo de moedas necessárias 
(entre 0,25 0,10 0,05 e 0,01) para formar o troco informado pelo usuário.

Aqui utilizo a conversão de valores monetários para centavos afim de evitar
possíveis erros em operações com float. Uso também condições while para monitorar
o valor do troco durante as subtrações (enquanto valor maior que 25 subtrai-se 25 do total,
caso menor que 25 e maior que 10, subtrai-se 10 do total e assim por diante até o valor ser igual a zero)
e sempre que uma subtração é feita o valor da variável moedas que inicia zero soma 1 e retorna impresso na tela
como resultado final.
