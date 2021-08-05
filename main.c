/* 
 * File:   main.c
 * Author: Vitor
 *
 * Created on 7 de Julho de 2021, 20:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen

int verificaAlfabeto(char input[200], int max, char E[2]){
    for (int i = 0; i < max; i++){
        if (input[i] != E[0] && input[i] != E[1]){
            printf("\nCaractere %c NÃO foi aceito.\n", input[i]);
            return 0; //se não for nenhum das possibilidades do alfabeto, fecha imediatamente pois não é preciso
        }
    }
    return 1;
}

int AFD(char input[200], int max, int init){
    int inputPointer = 0; //primeiro valor de input
    int statePointer = init; //primeiro estado = init
    
    // Q[3] = {'0','01','012'};    
    
    while(inputPointer < max){
        printf("\nEstado atual: q%i,\nCaractere sendo lido: %c", statePointer, input[inputPointer]);
        
        switch(statePointer){ //verifica qual nó está apontando
            case 0:{ //{q0}
                if (input[inputPointer] == '0') //transição laço
                    break;
                if (input[inputPointer] == '1') //transição para {q0, q1}
                    statePointer = 1;
                break;
            }
            case 1:{ //{q0, q1}
                if (input[inputPointer] == '0') //transição laço
                    break;
                if (input[inputPointer] == '1') //transição para {q0, q1, q2}
                    statePointer = 2;
                break;
            }
            case 2:{ //{q0, q1, q2}
                if (input[inputPointer] == '0') //transição para {q0, q1}
                    statePointer = 1;
                if (input[inputPointer] == '1') //transição laço
                    break;
                break;
            }
        }
        inputPointer++; //avança 1 casa na leitura do input
    }
    
    printf("\n\nEstado FINAL: q%i", statePointer);
    
    if (statePointer == 2) //verifica se o nó é final
        return 1; //caiu em {q0, q1, q2}
    else
        return 0; //caiu em {q0} ou {q0, q1}
}



/*
 * 
 */
int main(int argc, char** argv) {
    char input[200]; //string para ser recebido como input
    
    printf("digite input: ");
    scanf("%s", &input);
    
    int max; //máximo de iterações, que é a quantidade de símbolos no input
    max = strlen(input);
    
//    printf("\nsize = %i", max);
    
/*
 * 5-upla: M=(Q,Σ,δ,Init,F)
 * Q = {q0, q1, q2}
 * Σ = {0,1}
 * δ = Q x Σ -> Q
 * Init = q0
 * F = q2
 */
    int Q[3] = {0, 1, 2}; //estados, apenas para visualização
    char E[2] = {'0', '1'}; //alfabeto
    int init = 0; //estado inicial
    int F[1] = {2}; //estado final, apenas para visualização
    
    if (verificaAlfabeto(input, max, E) == 0){ //verifica se input está dentro do alfabeto
        printf("\n\nERRO: INPUT CONTEM VALOR FORA DO ALFABETO\n");
        system("pause"); //apenas para funcionar no meu PC, sem essa linha não dá pra ver o que aparece na tela
        return(2);
    }
    
    if (AFD(input, max, init) == 1){ //executa o AFD
        printf("\n\nINPUT ACEITO\n");
    }
    else{
        printf("\n\nINPUT NÃO ACEITO\n");
    }

    
    
    
    printf("\n\nFim do codigo\n");
    system("pause");
    return (EXIT_SUCCESS);
}

