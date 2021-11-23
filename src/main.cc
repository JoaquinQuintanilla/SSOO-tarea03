#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include <global.hh>
#include <iostream>
#include <signal.h>
#include <csignal>


void signal_handler(int signal_num ){
	std::cout << "Detencion no permitida" << std::endl;
}
void signal_handler2(int signal_num){
	std::raise(SIGTERM);
}

void signal_handler3(int signal_num){
	std::raise(SIGTERM);
}

int main(int argc, char* argv[])
{	
  
	std::signal(SIGINT, signal_handler); 
	std::signal(SIGTSTP, signal_handler);
	std::signal(SIGQUIT, signal_handler);
	std::signal(SIGUSR1, signal_handler2);
	std::signal(SIGUSR2, signal_handler3);    

	int ret = fork();
	if( ret == 0) {
		int res = 1;
		for(int x=0; x<50;x++){
			std::cout << "Valor Impar: " << res <<" - PID: "<< getpid() << std::endl;
			res = res +2;
			sleep(1);
		} 
	}
	else if(ret > 0){
		int t1= 0;
		int t2 =1;
		int res = 0;
		for(int x=0; x<50;x++){
			t1 = t2;
			t2 = res;
			res = t1 + t2;
			std::cout << "Valor Fibinacci: " <<res << " - PPID: " << getpid() << std::endl;
			sleep(1);
		} 
		wait(NULL);
	}

	return EXIT_SUCCESS;
}
