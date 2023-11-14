# Trabalho de Projeto e Análise de  Algoritmos de Esther e Thuanny
## Proposta

Propomos, neste trabalho, entregar uma implementação de um algoritmo exato utilizando algumas das técnicas aprendidas ao longo das aulas que resolva problemas de coloração de grafos, modelados especificamente para resolver o problema de timetabling. A técnica escolhida pelas autoras foi o BackTracking. Ele lê arquivos .col, que descrevem grafos, e gera uma tabela que aloque os recursos de modo a obedecer às restrições especificadas no problema. Assumimos, em particular, que os vértices são aulas e que as arestas são restrições - aulas que não podem ocorrer na mesma sala. Ao colorir este grafo, o resultado será uma tabela de salas e horários organizando cada aula em uma sala e horário. Cada cor será uma sala.

## Compilar

Para compilar, utilizamos o comando 

```g++ -Wall -std=c++14 src/main.cpp src/manager.cpp src/parser.cpp -o exec```.

E, para executar,

```./exec```.

## Testes

Todos os casos de teste foram tirados de https://mat.tepper.cmu.edu/COLOR/instances.html; em particular, pegamos todos os testes de formato .col. Cada teste foi executado uma única vez na medição de tempo. Todos os arquivos com os testes podem ser encontrados em src/test_lib neste repositório. Para executar os testes, basta seguir os comandos dados ao executar o código como descrito acima. Os testes estão indexados na mesma ordem em que aparecem na pasta. Ao executar um teste, a solução, o tempo gasto e o número de cores utilizadas aparecerão na tela e em um novo arquivo chamado result.txt. Todos os testes que fizemos estão disponíveis neste repositório.

## Saída

A saída será dada por uma sequência de linhas não-vazias. Cada linha representa uma cor (ou sala) alocada para aquelas aulas. A linha será composta por vários números, que serão o código daquela aula. As aulas que ocorrerão na mesma sala estarão em horários distintos. Já cada coluna representará um horário, ou seja, todas as aulas de uma coluna ocorrerão simultaneamente. Assim, a saída representa uma tabela em que cada aula tem uma combinação única de sala e horário, de modo que não haverá outra aula alocada para a mesma sala no mesmo horário. Todas as saídas geradas são colocadas na pasta "results", contendo as partições, o tempo gasto em milissegundos e a quantidade de cores utilizada.

## Metodologia

Para a solução deste problema, lemos um grafo com arestas de restrição de um arquivo .col e, nele, executamos o novo algoritmo sugerido pelas autoras, gerando partições do conjunto de vértices. Cada vértice estará em exatamente uma partição, então todos os vértices estarão coloridos. Não haverá dois vértices adjacentes na mesma partição, garantindo que aulas que não podem ocorrer na mesma sala estarão em salas distintas. Ao fim, mostramos estas partições em cada linha.

## Relatório
O relatório desse Projeto se encontra aqui: [Relatório do Projeto](https://www.overleaf.com/read/pkwvdkptnhyj#96c53d). Nele, foi especificado o tipo do problema, apresentamos alguins algoritmos exatos que  são encontradoss na literatura, sugerimos uma outra solução, implementamos e comparamos com os resultados obtidos na implementação do algoritmo de Zykov.


## Slides 
Os slides de apresentação se encontram aqui: [Slides](https://www.canva.com/design/DAF0GEjCgcQ/Xtd2q-vUyLxAxfCLUq011Q/edit?utm_content=DAF0GEjCgcQ&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton).

## Vídeo

O vídeo com a apresentação das autoras sobre o projeto se encontra aqui: [Vídeo](https://drive.google.com/file/d/1lUIavJJgSRRGATlbX3u_X1LKC9E5INi8/view?usp=drive_link).

## Agradecimentos

Esse projeto foi feito por Esther Wanderley & Thuanny Albuquerque.

Esperamos que gostem e toda sugestão/crítica é bem-vinda :smiley:

Agradecemos pela atenção!
