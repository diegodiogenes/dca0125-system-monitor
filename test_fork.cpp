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
#include <signal.h>   //kill

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

void funcKill(int pid_vitima, int option_kill){
    if(option_kill == 1){
     //MATAR PROCESSO
      kill(pid_vitima, SIGKILL);
      printf("PROCESSO %d MORTO\n", pid_vitima);
    } else if(option_kill == 2){
        //PAUSAR PROCESSO
        kill(pid_vitima, SIGSTOP);        
        printf("PROCESSO %d PAUSADO\n", pid_vitima);
    } else if(option_kill == 3){
        //CONTINUAR
        kill(pid_vitima, SIGCONT);
        printf("PROCESSO %d CONTINUA\n", pid_vitima);
    } else{
        printf("Comando inválido\n");
    }
}

/*
TO-DO

1- [ ] FILTRO
2- [X] Pause/Continue/Mata processo 
3- [ ] Muda Prioridade do processo
4- [ ] Escolhe a CPU do processo
*/

int main() {

  int pid_vitima;
  int option_kill = 0;

  system("clear");
  std::cout << "\033[37;41m\t\t Bem-vindo ao Gerenciador de Processos Interativo (GPI) \t\033[0m \n ";
  int option = 0;
  std::string filter;

  do{

    interface(option, filter);
    std::cout << "1. " << "\033[30;46mfiltrar processo\033[0m" << " 2. " << "\033[30;46mPausar Processo\033[0m" << " 3. " 
    << "\033[30;46mContinuar Processo\033[0m" << " 4. " << "\033[30;46mMudar prioridade\033[0m" << " 5. " << "\033[30;46mAtualizar\033[0m"
    << " 6. " << "\033[30;46mKill\033[0m \n";
    std::cin >> option;

    if(option == 1){
      interface(0, filter);
      std::cout << "Enter " << "\033[30;46mProcurar\033[0m" << " 2." << "\033[30;46mSair\033[0m" << " Nome do processo: " 
    << "\033[30;46m\033[0m";
      std::cin >> filter;
      system("clear");
    }else if(option == 5){
      system("clear");

      //KILL
    } else if(option == 6){

      //TO-DO PARA AS DEMAIS MENSAGENS
      std::cout << "Escolha uma das MENSAGENS a ser enviada e para qual processo: \n";
      std::cout << "(1) SIGKILL      (2) SIGSTOP      (3) SIGCONT\n"; 
      std::cin >> option_kill;

      printf( "Digite o PID do processo que a mensagem deve ser enviada: ");
      scanf( "%d", &pid_vitima);

      //chamar função
      funcKill(pid_vitima, option_kill);     

    } else{

      break;
    }
  } while(1);

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