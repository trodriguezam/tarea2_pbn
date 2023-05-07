#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_4 1
#define MAX_CMD_2 1

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

struct plate{
    char *patente;
    int cantidad;
};

void plates_bubble_sort(char **arr, int n){
    
    int sorted = -1;
    
    for (int i = 0; i < n - 1; i++){
        if (strcmp(arr[i], arr[i + 1]) > 0){
            char *aux = malloc(strlen(arr[i]) * sizeof(char*));

            strcpy(aux, arr[i]);
            strcpy(arr[i], arr[i+1]);
            strcpy(arr[i+1], aux);

            sorted = 0;
        }
    }

    if (sorted == 0) plates_bubble_sort(arr, n);
}

void debt_desc_bubble_sort(struct plate **arr, int n){
    
    int sorted = -1;
    
    for (int i = 0; i < n - 1; i++){
        if (arr[i] -> cantidad < arr[i+1] -> cantidad){
            struct plate *aux;

            aux = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = aux;

            sorted = 0;
        }
    }

    if (sorted == 0) debt_desc_bubble_sort(arr, n);
}

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
    int max_cmd_4 = MAX_CMD_4;
    int max_cmd_2 = MAX_CMD_2;
    

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
        value = strtok(NULL, "\n");
        car[i].comuna = malloc(20);
        strcpy(car[i].comuna, value);
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
        value = strtok(NULL, "\n");
        mult[j].paid = malloc(sizeof(value));
        strcpy(mult[j].paid, value);
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

// ---------------------------------- 1) & 2)
        if (strcmp(word, "deuda") == 0){
            int flag = 1; //PROBAR CON ESTO ACA. SI NO, AFUERA DE IF
            word = strtok(NULL, "\n");
            /* printf("%s", word); // APLICAR PARA EL RESTO DE INPUTS (?)
            word = word + 1; //*ptr + 1 // APLICAR PARA EL RESTO DE INPUTS (?)
            word[strlen(word) - 1] = '\0'; // APLICAR PARA EL RESTO DE INPUTS (?)
            printf("%s", word); */ // APLICAR PARA EL RESTO DE INPUTS (?)

            int total = 0;
        // ---------------------------------- 1) DONE
            for (int i = 0; i < v_lines; i++){
                if (strcmp(car[i].patente, word) == 0){
                    for (int k = 0; k < d_lines; k++){
                        if ((strcmp(mult[k].patente, word) == 0) && (strcmp(mult[k].paid, "No") == 0)) {
                            total += mult[k].monto;
                            }
                    }
                    printf("\nDeuda total asociada a patente %s: %d\n", word, total);
                    flag = 0;
                }
            }
        // ---------------------------------- 2) DONE // Falta mejorar output
        int j = 0;
           if (flag == 1){
                int n = atoi(word);
                struct plate **nplates_arr = malloc(MAX_CMD_2 * sizeof(struct plate));

                    int pcount = 0;
                for (int p = 0; p < v_lines; p++){
                    int dcount = 0;
                    int exists = -1;
                    for (int d = 0; d < d_lines; d++){
                        if ((strcmp(car[p].patente, mult[d].patente) == 0) && (strcmp(mult[d].paid, "No") == 0)){
                            if (exists == -1){
                                nplates_arr[pcount] = malloc(sizeof(struct plate));
                                nplates_arr[pcount] -> patente = malloc(sizeof(car[p].patente));
                                strcpy(nplates_arr[pcount] -> patente, car[p].patente);
                                exists = 0;
                                pcount++;
                            }
                            dcount++;
                            nplates_arr[pcount-1] -> cantidad = dcount;

                            if (pcount >= max_cmd_2){
                                max_cmd_2 *= 2;
                                nplates_arr = realloc(nplates_arr, max_cmd_2 * sizeof(struct plate));
                            }
                        }
                    }
                    debt_desc_bubble_sort(nplates_arr, pcount);
                }
                for (int i = 0; i < n; i++) printf("%s: %d\n", nplates_arr[i] -> patente, nplates_arr[i] -> cantidad);
            }
        }
// ---------------------------------- 3) & 4)
        else if (strcmp(word, "deudores") == 0){

            word = strtok(NULL, " ");

        // ---------------------------------- 3) DONE // Falta mejorar output
            if (strcmp(word, "comuna") == 0){
                word = strtok(NULL, "\n");
                for (int c = 0; c < v_lines; c++){
                    if (strcmp(car[c].comuna, word) == 0){
                        for (int k = 0; k < d_lines; k++){
                            if (strcmp(mult[k].patente, car[c].patente) == 0) printf("%s, %s\n", mult[k].patente, car[c].comuna);
                        }
                    }
                }    

            }

        // ---------------------------------- 4) 
        // agrugue patente a vehiculos.txt y deudas.txt para probar (AMLK31)
        // Error: cunado subtstring no esta al inicio de patente (ya sea se ingresa una letra de substring o mas)
        // Error: con OL no funciona (envola no funcniona con mas patentes que no he probado)
            else if (strcmp(word, "patente") == 0){
                word = strtok(NULL, "\n");
                int x = 0;
                char **plates_arr = malloc(MAX_CMD_4 * sizeof(char*));

                for (int i = 0; i < d_lines; i++){

                    if (strcmp(mult[i].paid, "No") == 0) {
                        if (strstr(mult[i].patente, word)){
                            plates_arr[x] = malloc(sizeof(mult[i].patente));
                            strcpy(plates_arr[x], mult[i].patente);
                            x++;
                        }
                        if (x >= max_cmd_4){

                            max_cmd_4 *= 2;
                            plates_arr = realloc(plates_arr, max_cmd_4 * sizeof(char*));
                        }
                    }
                }
                plates_bubble_sort(plates_arr, x);
                for (int b = 0; b < x; b++) {
                   printf("%s\n", plates_arr[b]);
                }
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