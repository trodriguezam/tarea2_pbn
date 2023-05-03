#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cars{
    char *patente;
    char *modelo;
    char *tipo;
    char *marca;
    char *color;
    char *comuna;
};

struct mults {
    char patente[7];
    int monto;
    char *paid;
};

//NO CAMBIAR NOMBRE DE VARIABLE LINEA
int count_lines(FILE *file) {
    char linea[100];
    int n = 0;

    while (fgets(linea, 100, file)) {
        n++;
    }

    fclose(file);
    return n;
}

int main(){
    FILE *vehiculos = fopen("vehiculos.txt", "r");
    FILE *deudas = fopen("deudas.txt", "r");
    int v_lines = count_lines(vehiculos);
    int d_lines = count_lines(deudas);
    struct cars car[v_lines];
    struct mults mult[d_lines];
    char *line = malloc(100);
    char *line2 = malloc(100);
    
    int num = 0;
    // fopen("vehiculos.txt", "r");
    // while(fgets(line, 500, vehiculos)){
    //     char *value = strtok(line, ",");
    //     char *plate;
    //     for (int i = 0; i < 6; i++){
    //         if (i == 0) plate = value;
    //         value = strtok(NULL, ",");
    //     }
    //     car[num].patente = plate;
    //     num++;
    // }

printf("%s ", mult[2].patente);
    struct mults mults;

    int k = 0;
    deudas = fopen("deudas.txt", "r");
    while(k < d_lines){
        // char *value2 = strtok(line2, ",");
        // for (int j = 0; j < 3; j++){
        fscanf(deudas, "%[^,],%[^,],%[^\n]\n", mult[k].patente, mult[k].monto, mult[k].paid);
        // strcpy(mult[k].patente,mults.patente);
        //     // printf("%s ", value2);
        //     if (j == 0) mult[k].patente = value2;
        //     else if (j == 1) mult[k].monto = atoi(value2);
        //     else if (j == 2) mult[k].paid = value2;
        //     value2 = strtok(NULL, ",");
            // printf("%s ", mult[i].patente);
        // printf("%s\n", mult[k].patente);
        k ++;
        }

    // for (int i = 0; i < 190; i++) car[i].patente = "hola";
    // for (int i = 190; i < 200; i++) car[i].patente = "chao";

    for (int i = 0; i < d_lines; i++) printf("%s %d\n", mult[i].patente, mult[i].monto);// mult[i].paid);
    // for(int i = 0; i < v_lines; i++){
    //     printf("Auto %d:\npatente: %s | modelo: %s | tipo: %s | marca: %s | color: %s | comuna: %s======================== \n", i + 1, car[i].patente, car[i].modelo, car[i].tipo, car[i].marca, car[i].color, car[i].comuna);
    // }

    //printf("%d ", d_lines); 
    // for(int i = 0; i < d_lines; i++){
    //    printf("Multas %d:\npatente: %s | monto: %s | pagado: %s\n======================== \n", i + 1, mult[i].patente, mult[i].monto, mult[i].paid);
    // }
    fclose(deudas);
    fclose(vehiculos);
    return 0;
}