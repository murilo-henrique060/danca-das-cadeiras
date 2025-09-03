<h1 align="center" > Dança das Cadeiras </h1>
<p align="center" ><i> Projeto Final de Sistemas Operacionais. Implementação de Dança das Cadeiras em C com conceitos de semáforo e multithreading </i></p>

## Introdução 

O que é a Dança das Cadeiras?

O jogo/brincadeira no qual é necessário um grupo de pessoas para jogar consiste em: formar um círculo com um número de cadeiras menor do que o número de participantes, assim uma música de fundo é tocada e os jogadores andam em volta das cadeiras e quando a música parar os jogadores devem sentar-se o mais rápido possível, e assim, o jogador que ficar de pé sem cadeira é eliminado do jogo e uma cadeira é retirada para a próxima rodada, deste modo, o jogo prossegue até que haja apenas uma cadeira e um participando consiga sentar nela, tornando-se assim, o vencedor. 

Deste modo, o projeto da Danças da Cadeiras é uma implementação que segue as regras da brincadeira conhecida, utilizando semáforo para representar um número limitado de cadeiras, tal qual, o jogo original em que, há um número menor de cadeiras em relação ao total de participantes. Deste modo, a cada rodada o número de cadeiras diminui até que reste apenas dois jogadores e uma cadeira para a rodada final. 

Há também, a implementação de multithread no qual os jogadores irão competir e o jogador que for mais rápido ao clicar conseguirá obter um lugar na dança e poderá partir para a próxima rodada. 

O jogo tem um mínimo necessário de dois jogadores, com limite de até cinco jogadores, suas teclas de controle ficam distribuídas da seguinte forma:

• player 1: tecla "a"

• player 2: tecla "d"

• player 3: tecla "g"

• player 4: tecla "j"

• player 5: tecla "l"

O número de "cadeiras" a cada rodada é definido pelo número de jogadores menos um, dessa forma a última rodada sempre tem apenas uma "cadeira". Apenas os jogadores que conseguirem uma "cadeira" prosseguirão para a próxima rodada, até que haja um vencedor. Para conseguir uma "cadeira" os jogadores terão de clicar na sua respectiva tecla de controle após o contador da rodada dizer "APERTEM", de modo que sejam mais rápidos que outros jogadores, caso contrário não haverá "cadeiras" e, por fim,  serão eliminados da partida.

## Implementação dos Semáforos e das Threads

O jogo ocorre de forma que múltiplos jogadores competem de forma simultânea, o que faz necessário a administração entre diferentes threads, isto é, porque cada thread representa a tecla de controle de um respectivo jogador, e a forma de gerenciar essas ações concorrentes é por meio do semáforo. O semáforo funciona de forma a armazenar os jogadores que conseguiram uma "cadeira", tendo um limite igual ao número de "cadeiras" da rodada, por meio de um contador e utilizando mutex para garantir exclusão mútua nessa operação. 

As threads, utilizam máscara de bits para representar os jogadores, quando tem sua respectiva tecla pressionada enviam um sinal para o semáforo, caso ainda tenha espaço o contador será iterado e a thread correspondente é registrada como segura através de operações bit a bit. O mesmo ocorre para operações de adição de jogadores, remoção e verficação.

## Rodando o Projeto 

Clone o projeto

```bash
  git clone https://github.com/murilo-henrique060/danca-das-cadeiras
```

Entre no diretório do projeto

```bash
  cd danca-das-cadeiras 
```
Compilando

```bash
  make
```

Rodando o executável

```bash
  ./danca-das-cadeiras.o
```

## Ferramentas 
<img width="48" src="https://avatars.githubusercontent.com/u/25699522?s=200&v=4" alt="c-logo"/>

## Ambientes de Desenvolvimento
<img width="35" src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/9a/Visual_Studio_Code_1.35_icon.svg/2048px-Visual_Studio_Code_1.35_icon.svg.png" alt="vscode-logo"/>
