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
    char *patente;
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
    

    int i = 0;
    vehiculos = fopen("vehiculos.txt", "r");
    while (fgets(line, 100, vehiculos)){
        char *value = strtok(line, ",");
        car[i].patente = malloc(sizeof(value));
        strcpy(car[i].patente, value);
        value = strtok(NULL, ",");
        car[i].modelo = malloc(sizeof(value));
        strcpy(car[i].modelo, value);
        value = strtok(NULL, ",");
        car[i].tipo = malloc(sizeof(value));
        strcpy(car[i].tipo, value);
        value = strtok(NULL, ",");
        car[i].marca = malloc(sizeof(value));
        strcpy(car[i].marca, value);
        value = strtok(NULL, ",");
        car[i].color = malloc(sizeof(value));
        strcpy(car[i].color, value);
        value = strtok(NULL, ",");
        car[i].comuna = malloc(20);
        strcpy(car[i].comuna, value);
        value = strtok(NULL, ",");
        i++;
    }

    int j = 0;
    deudas = fopen("deudas.txt", "r");
    while (fgets(line2, 100, deudas)){
        char *value = strtok(line2, ",");
        mult[j].patente = malloc(sizeof(value));
        strcpy(mult[j].patente, value);
        value = strtok(NULL, ",");
        mult[j].monto = atoi(value);
        value = strtok(NULL, ",");
        mult[j].paid = malloc(sizeof(value));
        strcpy(mult[j].paid, value);
        value = strtok(NULL, ",");
        j++;
    }

    free(line);
    free(line2);

    //====================================================

    while (1)
    {   
        char *cmd = malloc(100 * sizeof(char));

        printf("\nListado de comandos:\n- deuda [patente]\n- deuda [n]\n- deudores comuna [comuna]\n- deudores patente [string]\n- salir\n");

        printf("Ingrese comando: ");
        scanf(" %[^\n]s", cmd);

        char *aux = malloc(100 * sizeof(char));
        strcpy(aux, cmd);

        char *word = strtok(aux, " ");

        int flag = 1;
        if (strcmp(word, "deuda") == 0){
            word = strtok(NULL, " ");
            int total = 0;

            for (int i = 0; i < v_lines; i++){
                if (strcmp(car[i].patente, word) == 0){
                    for (int k = 0; k < d_lines; k++){
                        if ((strcmp(mult[k].patente, word) == 0) && (strcmp(mult[k].paid, "No"))) {
                            total += mult[k].monto;
                            }
                    }
                flag = 0;
                }
            }
            if (flag == 0) printf("\nDeuda total asociada a patente %s: %d\n", word, total);
            else if (flag == 1){
                continue; //Codigo para comando deuda [n] (agregar condicion para verificar comando?)
            }
        }
        else if (strcmp(word, "deudores") == 0){

            word = strtok(NULL, " ");

            if (strcmp(word, "comuna") == 0){
                word = strtok(NULL, " "); //<----------------- arreglar caso en que comuna tiene espacio
                for (int c = 0; c < v_lines; c++){
printf("%s, %s, %d\n", word, car[c].comuna, strcmp(car[c].comuna, word)); //testeando
                    if (strcmp(car[c].comuna, word) == 0){
                        for (int k = 0; k < d_lines; k++){
                            if (strcmp(mult[k].patente, car[c].patente) == 0) printf("%s, %s, %s", mult[k].patente, car[c].comuna, word);
                        }
                    }
                }    

            }
            else if (strcmp(word, "patente") == 0){
                continue; //Codigo para comando deudores patente [patente]
            }
        }
        else if (strcmp(word, "salir") == 0) break;
        else{
            printf("\nComando no identificado, intente nuevamente.\n");
        };
    }

    //====================================================

    for(int i = 0; i < v_lines; i++){
        free(car[i].patente);
        free(car[i].modelo);
        free(car[i].tipo);
        free(car[i].marca);
        free(car[i].color);
        free(car[i].comuna);
    }

    for(int i = 0; i < d_lines; i++){
        free(mult[i].patente);
        free(mult[i].paid);
    }

    fclose(deudas);
    fclose(vehiculos);

    return 0;
}