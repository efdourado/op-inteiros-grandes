//soma, subtração e multiplicação de inteiros grandes.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//remover os zeros da esquerda.
void rmze (char r []) {

    int i, j = 0, encontrou = 0;
    int tam = strlen (r);

//encontraremos o primeiro caractere diferente de zero.
    for (i =0; i < tam; i ++) {

        if (r [i] != '0') {
            encontrou = 1;
            break;
        }
    }

//pegar os caracteres restantes para a nova string.
    if (encontrou) {

        for (; i < tam; i ++) {
            r [j ++] = r [i];
        }
        r [j] = '\0'; //válidar a string.
    } else {
//else para strings que apresentem somente zeros.
        r [0] = '\0';
    }
}

//soma.
void soma (char a [], char b [], char resposta []) {
    
    rmze (a);
    rmze (b);
    int tam_a = strlen (a);
    int tam_b = strlen (b);

//pegar o maior tamanho (tam_m).
    int tam_m = (tam_a > tam_b) ? tam_a : tam_b;

    int c = 0; //carry

    for (int i = 0; i < tam_m; i ++) {
/*da direita para a esquerda igual no papel,
transformaremos o caracter em número inteiro e, caso ultrapassar o comprimento da string, atribuiremos 0. */
        int da = (i < tam_a) ? a[tam_a - i - 1] - '0' : 0;
        int db = (i < tam_b) ? b[tam_b - i - 1] - '0' : 0;

//faremos a soma dígito por dígito (armazenando na string 'resposta'), considerando o 'c' (carry) caso necessário.
        int s = da + db + c;
        c = s / 10;
        resposta [tam_m - i - 1] = (s % 10) + '0'; //coloca na string 'resposta' o valor do dígito (entre 0 e 9).
    }
//caso sobre valor em 'c'.
    if (c > 0) {
//deslocando os dígitos para a esquerda, adicionaremos o 'c' que sobrou.
        for (int i = tam_m; i > 0; i --) {
            resposta [i] = resposta [i - 1];
        }
        resposta [0] = c + '0';
        tam_m ++;
    }
//válidar a string.
    resposta [tam_m] = '\0';
}

//subtração.
void subt (char a [], char b [], char resposta []) {
    
    rmze (a);
    rmze (b);
    int tam_a = strlen (a);
    int tam_b = strlen (b);

    if (tam_a == tam_b && strcmp (a, b) == 0) { //com 2 strings iguais, subtração =0.
        resposta [0] = '0';
        resposta [1] = '\0';
        return; //retorna imediatamente com a resposta =0.
    }

//se a string 'a' for o menor valor, o número será negativo.
    int negativo =0;
    if (tam_a < tam_b || (tam_a == tam_b && strcmp (a, b) <0)) negativo =1;

    int tam_m = (tam_a > tam_b) ? tam_a : tam_b;

    int c =0; //empréstimo.
    int s =0; //armazenar a subtração.

    for (int i =0; i < tam_m; i ++) {

        int da = (i < tam_a) ? a[tam_a - i - 1] - '0' : 0;
        int db = (i < tam_b) ? b[tam_b - i - 1] - '0' : 0;

        if (negativo) //caso a string 'b' seja um número maior, colocaremos os dígitos dela como os primeiros.
        {
            int s = db - da - c; //subtração, dígito por dígito, considerando o empréstimo 'c' caso necessário.

//se a subtração db (1ª dígito) - c for menor que o 2º dígito (resposta negativa), faremos o empréstimo e adicionaremos 10 na conta.
            if (db - c < da) c =1; //empréstimo.
            else c =0;

            if (s <0) {
                s +=10;
                c =1;
            }

            resposta [tam_m -i -1] = s + '0';
        }
        
        else
        {
            int s = da - db - c;

            if (da - c < db) c =1;
            else c =0;

            if (s <0) {
                s +=10;
                c =1;
            }
            resposta [tam_m -i -1] = s + '0';
        }
        rmze (resposta);
        resposta [tam_m] = '\0';      
    }

//adicionaremos o sinal.
    if (negativo) {

        int tam_r = strlen (resposta);
        tam_r ++; //tamanho da string 'resposta' +1, liberando espaço para o sinal.
        for (int i = tam_r; i > 0; i --) {
            resposta [i] = resposta [i -1];
        }
        resposta [0] = '-';
    }
}

//multiplicação.
void mtpc (char a [], char b [], char resposta []) {
    
    rmze (a);
    rmze (b);

    int tam_a = strlen (a);
    int tam_b = strlen (b);

    int tam_m = tam_a + tam_b; //tamanho máximo da string 'resposta'.

    int rt [tam_m]; //vetor rt (resposta temporária).
    for (int i =0; i < tam_m; i ++) { //vetor inicializado com zeros.
        rt[i] =0;
    }

    for (int i =0; i < tam_a; i ++) {
        int c =0; //carry.
        int da = a [tam_a -i -1] - '0';

        for (int j =0; j < tam_b; j ++) {
            int db = b [tam_b -j -1] - '0';

            int p = da * db + c + rt [i + j]; //produto entre dígitos, considerando o 'c' (carry) e atualizando o valor da resposta temporária.

            c = p/10; //próximo carry.
            rt [i + j] = p % 10; //coloca no vetor 'rt' o valor do dígito (entre 0 e 9).
        }

        rt [i + tam_b] += c; //adiciona o carry no próximo dígito do vetor 'rt'.
    }

//verificar multiplicações por 0 e transformar o vetor em string.
    int i = tam_m - 1;
    while (i >=0 && rt [i] ==0) {
        i --;
    }

    if (i == -1) {
        resposta [0] = '0';
        resposta [1] = '\0';
    } else {
        int j =0;

//copiar a resposta temporária (rt) para a definitiva e válidar a string.
        while (i >= 0) {
            resposta [j ++] = rt [i] + '0';
            i --;
        }

        resposta [j] = '\0';
    }

}

int main () {
    
    int n, c;

    scanf ("%d", &n); //quantas casos.
    
    char a [501], b [501], resposta [1002], respostas [1002][1002];

    for (int i =0; i < n; i ++) { //loop para processar cada caso.

        scanf (" %s %s", a, b);
        scanf (" %d", &c); //operação a ser realizada.

        if (c ==1) {
            soma (a, b, resposta);
            rmze (resposta); //remover os zeros da esquerda.
            strcpy (respostas [i], resposta); //armazenar a resposta.
        } else if (c ==2) {
            subt (a, b, resposta);
            strcpy (respostas [i], resposta);
        } else if (c ==3) {
            mtpc (a, b, resposta);
            strcpy (respostas [i], resposta);
        }
    }

    for (int i =0; i < n; i ++) { //loop para imprimir as respostas armazenadas.
        printf ("%s\n", respostas [i]);
    }

return 0; }
