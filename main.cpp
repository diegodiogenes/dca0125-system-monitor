/*
Projeto para a disciplina Sistemas em Tempo Real do DCA - UFRN
Autores:
Diego Diógenes
Douglas Carvalho
Engenharia de Computação - 2019.2
*/

#include <time.h>
#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h> // para: sleep()
#include <stdlib.h>
#include <math.h>
#include <sys/time.h> // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#include <thread>
#include <sys/wait.h>

int show_process(int stop){
    if(!stop){
        system("ps -ao pid,user,pri,nice,pcpu,pmem,time,comm --sort=-pcpu | head -n 20");
    }
    return 0;
}

int main()
{
    int option = 0;
    std::cout << " ----- \t Bem-vindo ao Gerenciador de Processos Interativo (GPI) \t----- \n ";
    do{
        std::cout << "\033[1;41mbold red text\033[0m\n";
        std::thread second (show_process, option);
        std::cin >> option;
    }while(!option);
}