/* Ordenación en Arreglos - Por Solución Ingenieril*/
#include <stdio.h> /* Declaración librerías*/
#include <stdlib.h>
#include <string.h>

void debt_bubble_sort(int *arr, int n){
    
    int sorted = -1;
    
    for (int i = 0; i < n - 1; i++){
        if (arr[i] > arr[i+1]){
            int aux;

            aux = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = aux;

            sorted = 0;
        }
    }

    if (sorted == 0) debt_bubble_sort(arr, n);
}

int main(){

	int arr[] = {1, 5, 3, 2, 8, 6};
	debt_bubble_sort(arr, (sizeof(arr) / sizeof(arr[0])));

	for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++) printf("%d\n", arr[i]);

	int x = 5, y = 6;
	printf("\n%d\n", x);
	x = y;
	printf("%d\n", x);

	return 0;		
}