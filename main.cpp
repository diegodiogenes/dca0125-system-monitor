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
#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#define _GNU_SOURCE
#include <sched.h>

std::string name_key( int c ) {
  // This function takes a keycode and turns it into a string.
  // I'm pretty sure there is a curses function to do this,
  // but I'm not going to look it up right now... (sorry)
  std::string result;
  if (c < 32) {  // control keys
    result = "^";
    result += (char)c +'A' -1;
    }
  else if (c == 127) result = "^?";
  else if (c > 127) result = "FN";  // any function key (arrows, F1, Cut, etc)
  else result = c;  // normal alphanumeric key
  return result;
}

void interface(int option, std::string filter = NULL){
  switch (option)
  {
  case 1:
    system("clear");
    system( (" ps -ao pid,user,pri,nice,pcpu,pmem,time,comm -U $USER | head -1; ps -ao pid,user,pri,nice,pcpu,pmem,time,comm -U $USER --sort=-pcpu | grep  '"+filter+"' --color=auto").c_str() );
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
1- [X] FILTRO
2- [X] Pause/Continue/Mata processo 
3- [ ] Muda Prioridade do processo
4- [ ] Escolhe a CPU do processo
*/

int main() {

  int pid_vitima;
  int option_kill = 0;
  int value = 0;
  int cpuValue = 0;

  system("clear");
  std::cout << "\033[37;41m\t\t Bem-vindo ao Gerenciador de Processos Interativo (GPI) \t\033[0m \n ";
  int option = 0;
  std::string filter;

  do{
    interface(option, filter);
    std::cout << "1. " << "\033[30;46mProcurar\033[0m" << " 2. " << "\033[30;46mNice -\033[0m" << " 3. " 
    << "\033[30;46mNice +\033[0m" << " 4. " << "\033[30;46mChange CPU\033[0m" << " 5. " << "\033[30;46mAtualizar\033[0m"
    << " 6. " << "\033[30;46mKill\033[0m \n";
    std::cin >> option;

    switch(option){
        case 1:
            system("clear");  
            interface(0, filter);
            std::cout << "Enter " << "\033[30;46mProcurar\033[0m" << " 2." << "\033[30;46mSair\033[0m" << " Nome do processo: " 
            << "\033[30;46m\033[0m";
            std::cin >> filter;
            if(filter.compare("2") == 0)
                option = 0;
            system("clear");
            break;
        case 2:
            //DECREMENTA PRIORIDADE   	
			printf( "Digite o PID do processo para decrementar(ROOT): ");
			scanf( "%d", &pid_vitima);

			std::cout << "Valor: "; 
	      	std::cin >> value;

			setpriority(PRIO_PROCESS, pid_vitima, (-1)*value); 
			system("clear");
        case 3:
            //INCREMENTA PRIORIDADE   	
			printf( "Digite o PID do processo para incrementar: ");
			scanf( "%d", &pid_vitima);

			std::cout << "Valor: "; 
	      	std::cin >> value;

			setpriority(PRIO_PROCESS, pid_vitima, value); 
			system("clear");
        case 4:
            cpu_set_t  mask;
            std::cout << "\033[30;46mPID do processo: \033[0m";
            std::cin >> value;
            std::cout << "\033[30;46mCPU para alocar: \033[0m";
            std::cin >> cpuValue;

            CPU_ZERO(&mask);
            CPU_SET(cpuValue, &mask);
            sched_setaffinity(value, sizeof(mask), &mask);
            std::cout << "\033[30;46mProcesso de PID " << value <<" alterado para " << cpuValue << "\033[0m \n";
            sleep(1);
            system("clear");
            break;
        case 5:
            system("clear");
            break;
        case 6:
            //TO-DO PARA AS DEMAIS MENSAGENS
            std::cout << "Escolha uma das MENSAGENS a ser enviada e para qual processo: \n";
            std::cout << "(1) SIGKILL      (2) SIGSTOP      (3) SIGCONT\n"; 
            std::cin >> option_kill;

            printf("Digite o PID do processo que a mensagem deve ser enviada: ");
            scanf( "%d", &pid_vitima);

            //chamar função
            funcKill(pid_vitima, option_kill);     
            break;
        default:
            break;                            
    }

  } while(1);

  return 0;
}