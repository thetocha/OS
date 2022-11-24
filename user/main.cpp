#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    std::cout << "Creating killer" << std::endl;
    int status;
    if(setenv("PROC_TO_KILL", "telegram-desktop", 0) == 0){
        std::cout << "successful" << std::endl;
    }
    int pid  = fork();
    if(pid == 0){
        execv( "../../killer/cmake-build-debug/./killer",  argv);
    }else{
        waitpid(pid, &status, 0);
        std::cout << "It's not working" << std::endl;
    }
    return 0;
}
