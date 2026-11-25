#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10
#define EPS 0.000000001

typedef struct {
    int lin;
    int col;
    double v[MAX][MAX];
} Matriz;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerInteiro(char *msg, int min, int max) {
    int x;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &x) == 1 && x >= min && x <= max) {
            limparBuffer();
            return x;
        }
        if (feof(stdin)) exit(1);
        printf("Valor invalido. Digite um inteiro entre %d e %d.\n", min, max);
        limparBuffer();
    }
}

double lerDouble(char *msg) {
    double x;
    while (1) {
        printf("%s", msg);
        if (scanf("%lf", &x) == 1) {
            limparBuffer();
            return x;
        }
        if (feof(stdin)) exit(1);
        printf("Valor invalido. Digite um numero.\n");
        limparBuffer();
    }
}

void lerMatriz(Matriz *m, int numero) {
    char msg[50];
    int i, j;

    printf("\n--- Matriz %d ---\n", numero);
    m->lin = lerInteiro("Linhas: ", 1, MAX);
    m->col = lerInteiro("Colunas: ", 1, MAX);
    for (i = 0; i < m->lin; i++) {
        for (j = 0; j < m->col; j++) {
            sprintf(msg, "Elemento [%d][%d]: ", i + 1, j + 1);
            m->v[i][j] = lerDouble(msg);
        }
    }
}

void exibirMatriz(Matriz m) {
    int i, j;
    for (i = 0; i < m.lin; i++) {
        for (j = 0; j < m.col; j++) {
            if (fabs(m.v[i][j]) < 0.005) m.v[i][j] = 0;
            printf("%9.2f ", m.v[i][j]);
        }
        printf("\n");
    }
}

int exibirMenu() {
    printf("\n===== MENU =====\n");
    printf("1 - Adicao\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao\n");
    printf("0 - Sair\n");
    return lerInteiro("Opcao: ", 0, 4);
}

int mesmaDimensao(Matriz a, Matriz b) {
    return a.lin == b.lin && a.col == b.col;
}

int podeMultiplicar(Matriz a, Matriz b) {
    return a.col == b.lin;
}

int podeDividir(Matriz a, Matriz b) {
    return b.lin == b.col && a.col == b.lin;
}

Matriz somar(Matriz a, Matriz b) {
    Matriz r = a;
    int i, j;
    for (i = 0; i < r.lin; i++)
        for (j = 0; j < r.col; j++)
            r.v[i][j] = a.v[i][j] + b.v[i][j];
    return r;
}

Matriz subtrair(Matriz a, Matriz b) {
    Matriz r = a;
    int i, j;
    for (i = 0; i < r.lin; i++)
        for (j = 0; j < r.col; j++)
            r.v[i][j] = a.v[i][j] - b.v[i][j];
    return r;
}

Matriz multiplicar(Matriz a, Matriz b) {
    Matriz r;
    int i, j, k;
    r.lin = a.lin;
    r.col = b.col;
    for (i = 0; i < r.lin; i++) {
        for (j = 0; j < r.col; j++) {
            r.v[i][j] = 0;
            for (k = 0; k < a.col; k++)
                r.v[i][j] += a.v[i][k] * b.v[k][j];
        }
    }
    return r;
}

/* Gauss-Jordan em [B | I]. Retorna 0 se a matriz for singular. */
int inverter(Matriz b, Matriz *inv) {
    double a[MAX][2 * MAX], t, f;
    int n = b.lin;
    int i, j, c, p;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a[i][j] = b.v[i][j];
            a[i][j + n] = (i == j) ? 1 : 0;
        }
    }

    for (c = 0; c < n; c++) {
        p = c;
        for (i = c + 1; i < n; i++)
            if (fabs(a[i][c]) > fabs(a[p][c])) p = i;
        if (fabs(a[p][c]) < EPS) return 0;

        for (j = 0; j < 2 * n; j++) {
            t = a[c][j];
            a[c][j] = a[p][j];
            a[p][j] = t;
        }

        t = a[c][c];
        for (j = 0; j < 2 * n; j++)
            a[c][j] /= t;

        for (i = 0; i < n; i++) {
            if (i != c) {
                f = a[i][c];
                for (j = 0; j < 2 * n; j++)
                    a[i][j] -= f * a[c][j];
            }
        }
    }

    inv->lin = n;
    inv->col = n;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            inv->v[i][j] = a[i][j + n];
    return 1;
}

/* A / B = A x inversa(B). Retorna 0 se B for singular. */
int dividir(Matriz a, Matriz b, Matriz *r) {
    Matriz inv;
    if (!inverter(b, &inv)) return 0;
    *r = multiplicar(a, inv);
    return 1;
}

void executarOperacao(Matriz mats[], int qtd, int op) {
    Matriz res = mats[0];
    int i;

    for (i = 1; i < qtd; i++) {
        if (op == 1 || op == 2) {
            if (!mesmaDimensao(res, mats[i])) {
                printf("\nErro: dimensoes diferentes (%dx%d e %dx%d).\n",
                       res.lin, res.col, mats[i].lin, mats[i].col);
                return;
            }
            if (op == 1) res = somar(res, mats[i]);
            else res = subtrair(res, mats[i]);
        } else if (op == 3) {
            if (!podeMultiplicar(res, mats[i])) {
                printf("\nErro: colunas (%d) diferentes das linhas (%d).\n",
                       res.col, mats[i].lin);
                return;
            }
            res = multiplicar(res, mats[i]);
        } else {
            if (!podeDividir(res, mats[i])) {
                printf("\nErro: divisor deve ser quadrado e com %d linhas.\n", res.col);
                return;
            }
            if (!dividir(res, mats[i], &res)) {
                printf("\nErro: matriz divisora singular, sem inversa.\n");
                return;
            }
        }
    }

    printf("\nResultado (%dx%d):\n", res.lin, res.col);
    exibirMatriz(res);
}

int main() {
    Matriz mats[MAX];
    int qtd, op, i;

    qtd = lerInteiro("Quantas matrizes (minimo 2)? ", 2, MAX);
    for (i = 0; i < qtd; i++)
        lerMatriz(&mats[i], i + 1);

    do {
        op = exibirMenu();
        if (op != 0) executarOperacao(mats, qtd, op);
    } while (op != 0);

    return 0;
}
