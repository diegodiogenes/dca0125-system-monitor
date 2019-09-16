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
#include <sys/time.h> // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#define _GNU_SOURCE
#include <sched.h> // para definir a cpu que o processo irá utilizar

void interface(int option, std::string filter = NULL)
{
  // define a lista que será exibida para o usuário
  switch (option)
  {
  case 1:
    //retorna apenas os processos com base no filtro
    system("clear");
    system((" ps -ao pid,user,pri,nice,pcpu,pmem,time,comm -U $USER | head -1; ps -ao pid,user,pri,nice,pcpu,pmem,time,comm -U $USER --sort=-pcpu | grep  '" + filter + "' --color=auto").c_str());
    break;

  default:
    //interface padrão retornando todos os processos por ordem de uso de cpu
    system("ps -ao pid,user,pri,nice,pcpu,pmem,time,comm -U $USER --sort=-pcpu | head -n 30");
    break;
  }
}

void funcKill(int pid_vitima, int option_kill)
{
  if (option_kill == 1)
  {
    //MATAR PROCESSO
    kill(pid_vitima, SIGKILL);
    std::cout << "\033[37;41mPROCESSO " << pid_vitima << " MORTO\033[0m \n";
    /*printf("PROCESSO %d MORTO\n", pid_vitima);*/
  }
  else if (option_kill == 2)
  {
    //PAUSAR PROCESSO
    kill(pid_vitima, SIGSTOP);
    std::cout << "\033[37;41mPROCESSO " << pid_vitima << " PAUSADO\033[0m \n";
    /*printf("PROCESSO %d PAUSADO\n", pid_vitima);*/
  }
  else if (option_kill == 3)
  {
    //CONTINUAR
    kill(pid_vitima, SIGCONT);
    std::cout << "\033[37;41mPROCESSO " << pid_vitima << " CONTINUA\033[0m \n";
    /*printf("PROCESSO %d CONTINUA\n", pid_vitima);*/
  }
  else
  {
    std::cout << "\033[37;41m\t\t COMANDO INVÁLIDO \t\033[0m \n ";
  }
}

/*
TO-DO
1- [X] FILTRO
2- [X] Pause/Continue/Mata processo 
3- [X] Muda Prioridade do processo
4- [X] Escolhe a CPU do processo
*/

int main()
{

  int pid_vitima;
  int option_kill = 0;
  int value = 0;
  int cpuValue = 0;

  system("clear");
  std::cout << "\033[37;41m\t\t Bem-vindo ao Gerenciador de Processos Interativo (GPI) \t\033[0m \n ";
  int option = 0;
  std::string filter;

  do
  {
    //Exibindo o menu
    interface(option, filter);
    std::cout << "1. "
              << "\033[30;46mProcurar\033[0m"
              << " 2. "
              << "\033[30;46mPriority -\033[0m"
              << " 3. "
              << "\033[30;46mPriority +\033[0m"
              << " 4. "
              << "\033[30;46mChange CPU\033[0m"
              << " 5. "
              << "\033[30;46mAtualizar\033[0m"
              << " 6. "
              << "\033[30;46mKill\033[0m \n";
    std::cin >> option;

    switch (option)
    {
    // Para cada opção seleciona uma ação
    case 1:
      // irá filtrar o processo de acordo com o nome
      system("clear");
      interface(0, filter);
      std::cout << "Enter "
                << "\033[30;46mProcurar\033[0m"
                << " 2."
                << "\033[30;46mSair\033[0m"
                << " Nome do processo: "
                << "\033[30;46m\033[0m";
      std::cin >> filter;
      if (filter.compare("2") == 0)
        option = 0;
      system("clear");
      break;
    case 2:
      //DECREMENTA PRIORIDADE
      std::cout << "\033[30;46mDigite o PID do processo para decrementar(ROOT): \033[0m";
      /*printf("Digite o PID do processo para decrementar(ROOT): ");*/
      scanf("%d", &pid_vitima);

      std::cout << "\033[30;46mValor: \033[0m";
      std::cin >> value;

      setpriority(PRIO_PROCESS, pid_vitima, (-1) * value);
      /*sleep(1);
			      system("clear");*/
    case 3:
      //INCREMENTA PRIORIDADE
      std::cout << "\033[30;46mDigite o PID do processo para incrementar: \033[0m";
      /*printf( "Digite o PID do processo para incrementar: ");*/
      scanf("%d", &pid_vitima);

      /*std::cout << "Valor: "; */
      std::cout << "\033[30;46mValor: \033[0m";
      std::cin >> value;

      setpriority(PRIO_PROCESS, pid_vitima, value);
      /*sleep(1);
      			system("clear");*/
      break;
    case 4:
      cpu_set_t mask;
      std::cout << "\033[30;46mPID do processo: \033[0m";
      std::cin >> value;
      std::cout << "\033[30;46mCPU para alocar: \033[0m";
      std::cin >> cpuValue;

      CPU_ZERO(&mask);
      CPU_SET(cpuValue, &mask);
      sched_setaffinity(value, sizeof(mask), &mask);
      std::cout << "\033[30;46mProcesso de PID " << value << " alterado para " << cpuValue << "\033[0m \n";
      sleep(1);
      system("clear");
      break;
    case 5:
      system("clear");
      break;
    case 6:
      //TO-DO PARA AS DEMAIS MENSAGENS
      std::cout << "\033[30;46mEscolha uma das MENSAGENS a ser enviada e para qual processo: \n\033[0m";
      /*std::cout << "Escolha uma das MENSAGENS a ser enviada e para qual processo: \n";*/
      std::cout << "(1) SIGKILL      (2) SIGSTOP      (3) SIGCONT\n";
      std::cin >> option_kill;

      if ((option_kill != 1) && (option_kill != 2) && (option_kill != 3))
      {
        std::cout << "\033[37;41m\t\t COMANDO INVÁLIDO \t\033[0m \n ";
        break;
      }

      std::cout << "\033[30;46mDigite o PID do processo que a mensagem deve ser enviada: \033[0m";
      /*printf("Digite o PID do processo que a mensagem deve ser enviada: ");*/
      scanf("%d", &pid_vitima);

      funcKill(pid_vitima, option_kill);
      break;
    default:
      break;
    }

  } while (1);

  return 0;
}