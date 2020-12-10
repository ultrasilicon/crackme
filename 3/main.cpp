#include <cstring>
#include <map>
#include <queue>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// crackme3: process hell
// answer: ":d1r1d:w0f7f0w<0x10>B" where '<0x10>' is not printable

using namespace std;

char secret[] = "tacocat";
char* s;

void correct() {
    sleep(1);
    printf("Yes, you cracked me!\n");
}

void incorrect() {
    sleep(1);
    printf("No, nice try.\n");
}
int main(int argc, char** argv)
{
  if(argc != 2) {
    printf("Exactly one argument is needed\n");
    exit(1);
  }
  s = new char(64);
  string str = argv[1];

  int fd[2];
  pipe(fd);
  pid_t childpid;
  childpid = fork();
  if(childpid != 0)  // parent
  {
    // string len must == 17
    try {
      srand(str.at((*s >> 2) + *s % 2));
      incorrect();
      exit(0);
    }  catch (...) {}
    try {
      srand(str.at((*s >> 2) - *s % 3));
    }  catch (...) {
      incorrect();
      exit(0);
    }
    close(fd[1]);
    char result;
    read(fd[0], &result, sizeof(*s));
    close(fd[0]);
    if(result == *s)
      correct();
    else
      incorrect();
  }
  else  // child
  {
    close(fd[0]);
    string key = string(secret) + secret + (char)0x20 + (char)(*s - 1);
    for(int i = 0; i < key.length(); ++ i)
      key[i] = i % 2 == 0 ? key[i] / 2 : key[i] + 3;
//    printf("%s\n", key.c_str()); answer
    write(fd[1], key==str? s : &key[0], sizeof(*s));
    close(fd[1]);
  }

  return 0;
}
