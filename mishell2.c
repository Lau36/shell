#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "leercadena.h"
#include <sys/types.h>
#include <signal.h>

Array process;

int lastElement(char ** arr){
    int i=0;
    while(1){
        if(arr[i]==NULL)
            return i;
        i++;
    }
}

char ** returnArr(char ** arr){

    char **command = arr;
    command[lastElement(arr)-1]= NULL;

    return command;
}

int main(int argc, char* argv[]) {
  char command[256];
  char **comando;

  while (1) {
      pid_t pid;
      printf("> ");
      leer_de_teclado(256, command);
      comando = de_cadena_a_vector(command);
      if (strcmp("salir",comando[0]) == 0) break;
      int arethere=0;
      if( strcmp("&",comando[lastElement(comando)-1])==0 ){
          arethere=1;
      }
       pid = fork();
      assert(pid >= 0); //aca asegura que no haya un error, puede ser padre o hijo 
      if( strcmp("&",comando[lastElement(comando)-1])==0  && pid==0){
          //printf("Proceso: %d", getpid());
          execvp(comando[0], returnArr(comando));

      } else if (pid == 0) { //proceso hijo 
             execvp(comando[0], comando);

      }else if (arethere == 1 && pid>0){
          insertArray(&process, pid);
          continue;

      }
      else {
            if (strcmp("tareas",comando[0])==0){
            int num_process=process.used;

             for (int x=0; x< num_process; x++){
               printf("%d\n",process.array[x]);
                }

            }
            else if(strcmp("detener",comando[0])==0){
                kill(atoi(comando[1]),9);
            }
          wait(NULL);

      }
    }
        printf("Fin del minshell\n");
        return 0;
}
