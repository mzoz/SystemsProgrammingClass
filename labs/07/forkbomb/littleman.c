#include <unistd.h>

int main(){

  while(1){ //oops!
    fork();
  }

}
