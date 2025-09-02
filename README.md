<h1 align="center" > Dança das Cadeiras </h1>
<p align="center" ><i> Projeto Final de Sistemas Operacionais. Implementação de Dança das Cadeiras em C com conceitos de semáforo e multithreading </i></p>

## Introdução 

O que a Dança da Cadeiras?

O jogo/brincadeira no qual é necessário um grupo de pessoas para jogar consiste em: formar um círculo com um número de cadeiras menor do que o número de participantes, assim uma música de fundo é tocada e os jogadores andam em volta das cadeiras e quando a música parar os jogadores devem sentar-se o mais rápido possível, e assim, o jogador que ficar de pé sem cadeira é eliminado do jogo e uma cadeira é retirada para a próxima rodada, deste modo, o jogo prossegue até que haja apenas uma cadeira e um participando consiga sentar nela, tornando-se assim, o vencedor. 

Deste modo, o projeto da Danças da Cadeiras é uma implementação que segue as regras da brincadeira conhecida, utilizando semáforo para representar um número limitado de cadeiras, tal qual, o jogo original em que, há um número menor de cadeiras em relação ao total de participantes. Deste modo, a cada rodada o número de cadeiras diminui até que reste apenas dois jogadores e uma cadeira para a rodada final. 

Há também, a implementação de multithread no qual os jogadores irão competir e o jogador que for mais rápido ao clicar conseguirá obter um lugar na dança e poderá partir para a próxima rodada. 

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
