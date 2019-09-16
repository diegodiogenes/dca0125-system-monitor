/*
Projeto para a disciplina Sistemas em Tempo Real do DCA - UFRN
Autores:
Diego Diógenes
Douglas Carvalho
Engenharia de Computação - 2019.2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sys/wait.h>

void interface(int option, std::string filter = NULL){
  switch (option)
  {
  case 1:
    system( (" ps -ao pid,user,pri,nice,pcpu,pmem,time,comm -U $USER --sort=-pcpu | grep  '"+filter+"'").c_str() );
    break;
  
  default:
    system("ps -ao pid,user,pri,nice,pcpu,pmem,time,comm -U $USER --sort=-pcpu | head -n 30");
    break;
  }
}

int main() {
  system("clear");
  std::cout << "\033[37;41m\t\t Bem-vindo ao Gerenciador de Processos Interativo (GPI) \t\033[0m \n ";
  int option = 0;
  std::string filter;

  do{
    interface(option, filter);
    std::cout << "1. " << "\033[30;46mfiltrar processo\033[0m" << " 2. " << "\033[30;46mPausar Processo\033[0m" << " 3. " 
    << "\033[30;46mContinuar Processo\033[0m" << " 4. " << "\033[30;46mMudar prioridade\033[0m" << " 5. " << "\033[30;46mAtualizar\033[0m \n";
    std::cin >> option;
    if(option == 1){
      interface(0, filter);
      std::cout << "Enter " << "\033[30;46mProcurar\033[0m" << " 2." << "\033[30;46mSair\033[0m" << " Nome do processo: " 
    << "\033[30;46m\033[0m";
      std::cin >> filter;
      system("clear");
    }else if(option == 5){
      system("clear");
    }else{
      break;
    }
  }while(1);

  // printf("fora");

  //   int pid = fork();
  //   if (pid == 0) {
  //     while (1)
  //     {
  //     system("clear");
  //     system("ps -ao pid,user,pri,nice,pcpu,pmem,time,comm --sort=-pcpu | head -n 20&");
  //     sleep(1);
  //     }
  //   } else if (pid > 0) {
  //       int status;
  //       waitpid(pid, &status, 0);
  //       printf("Child exited with %d\n", WEXITSTATUS(status));
  //   }

  // while (1) {
  //   printf("> \n");
  //   std::cin >> option;
  //   printf("%d \n",option);
  // }

  return 0;
}