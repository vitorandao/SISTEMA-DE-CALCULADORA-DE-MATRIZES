# Calculadora de Matrizes em C
 
## Objetivo
 
Sistema interativo em linguagem C que permite cadastrar **duas ou mais matrizes** e realizar operações matemáticas entre elas: adição, subtração, multiplicação e divisão matricial. Pensado para aplicações de engenharia, análise de dados e processamento numérico.
 
## Funcionalidades
 
- Cadastro de 2 a 10 matrizes (quantidade informada pelo usuário).
- Para cada matriz: número de linhas, número de colunas (1 a 10) e cada elemento informado individualmente.
- Menu interativo com as operações: adição, subtração, multiplicação e divisão matricial.
- Operações aplicadas **em sequência, da esquerda para a direita**, na ordem de cadastro, com validação a cada etapa.
- Exibição da matriz resultante organizada em linhas e colunas.
- Mensagens claras quando a operação é impossível (dimensões incompatíveis ou matriz divisora singular).
- Validação de todas as entradas (letras, valores fora do intervalo, opções inexistentes).
- Permite realizar novas operações ou encerrar o programa.
## Regras matemáticas
 
| Operação | Regra |
|---|---|
| Adição / Subtração | Matrizes com as mesmas dimensões |
| Multiplicação | Colunas da matriz da esquerda = linhas da matriz da direita (a cada etapa) |
| Divisão | `A / B = A × B⁻¹`. B deve ser quadrada, invertível (determinante ≠ 0) e com linhas = colunas de A |
 
Com 3 ou mais matrizes, `A op B op C` é calculado como `(A op B) op C`.
 
## Compilação e execução
 
Requisito: compilador GCC.
 
```bash
gcc main.c -o matrizes -lm
./matrizes
```
 
A flag `-lm` liga a biblioteca matemática (`fabs`).
 
## Funções implementadas
 
| Função | Responsabilidade |
|---|---|
| `main()` | Coordena o fluxo: lê a quantidade, cadastra as matrizes e repete o menu |
| `limparBuffer()` | Descarta caracteres restantes da entrada |
| `lerInteiro()` | Lê e valida um inteiro dentro de um intervalo |
| `lerDouble()` | Lê e valida um número real |
| `lerMatriz()` | Lê dimensões e elementos de uma matriz |
| `exibirMatriz()` | Mostra uma matriz em linhas e colunas |
| `exibirMenu()` | Mostra o menu e retorna a opção validada |
| `mesmaDimensao()` | Valida dimensões para adição/subtração |
| `podeMultiplicar()` | Valida colunas da esquerda = linhas da direita |
| `podeDividir()` | Valida divisor quadrado e dimensões compatíveis |
| `somar()` / `subtrair()` | Operações elemento a elemento |
| `multiplicar()` | Multiplicação matricial |
| `inverter()` | Inversa por Gauss-Jordan; retorna 0 se a matriz for singular (sem pivô, determinante zero) |
| `dividir()` | Calcula `A × B⁻¹` |
| `executarOperacao()` | Aplica a operação sobre todas as matrizes, da esquerda para a direita, validando cada etapa |
 
## Exemplos de utilização
 
**Adição de duas matrizes 2x2**
 
Entradas: 2 matrizes; A = [[1,2],[3,4]]; B = [[5,6],[7,8]]; opção `1`.
 
```
Resultado (2x2):
     6.00      8.00
    10.00     12.00
```
 
**Multiplicação de A (2x3) por B (3x2)**
 
A = [[1,2,3],[4,5,6]]; B = [[7,8],[9,10],[11,12]]; opção `3`.
 
```
Resultado (2x2):
    58.00     64.00
   139.00    154.00
```
 
**Divisão A / B** com A = [[1,0],[0,1]] e B = [[4,7],[2,6]]; opção `4`.
 
```
Resultado (2x2):
     0.60     -0.70
    -0.20      0.40
```
 
**Dimensões incompatíveis** (soma de 2x3 com 3x2)
 
```
Erro: dimensoes diferentes (2x3 e 3x2).
```
 
**Divisor singular** (B = [[1,2],[2,4]])
 
```
Erro: matriz divisora singular, sem inversa.
```
 
## Testes realizados
 
Soma com dimensões iguais e diferentes, multiplicação compatível e incompatível, divisão por matriz invertível e singular, divisão em cadeia com 3 matrizes, entrada inválida (letras, dimensão 11, opção 9) e encerramento pelo menu.
 
