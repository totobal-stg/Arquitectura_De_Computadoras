#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Inserte el numero de numeros que desea conocer de la serie fibonacci: ");
    scanf("%d", &n);

    int uno = 0, dos = 1, sig = 0;
    for (int i = 0; i < n; i++) {
        printf("%d ", uno);
        sig = uno + dos;
        uno = dos;
        dos = sig;
    }
    printf("\n");

    return 0;
}
