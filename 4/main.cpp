#include <cstring>
#include <map>
#include <queue>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// executes "uname -a > /tmp/uname"


using namespace std;

const char* suceed_str = "Something is done on your os.\n";
const char* fail_str = "Failed to do something on your os.\n";

void suceed() {
  printf("%s", suceed_str);
}

void fail() {
  printf("%s", fail_str);
  exit(1);
}

int main(int, char**)
{
  bool result = true;

  int fd[2];
  pipe(fd);
  pid_t childpid;
  childpid = fork();
  if(childpid > 0)  // parent
  {
    read(fd[0], &result, sizeof(result));
    if(result)
      suceed();
    else
      fail();
  } else if(childpid == 0) { // child
    vector<int8_t> command = {'p', 'r', 'i', 'n', 't', ' ', '-', 'a', ' ', '>', ' ', '/', 't', 'm', 'p', '/', 'm', 'y', 'l', 'o', 'g'};
    vector<int> indice = {28, 20, 1, 15, 16};
    for(auto it = command.begin(); it < command.end(); ++ it) {
      auto dist = distance(command.begin(), it);
      if(dist == 0 || dist == indice[3] + 1) {
        for(size_t i = 0; i < indice.size() && it != command.end(); ++ i, ++ it) {
          *it = fail_str[indice[i]];
        }
      }
    }
//    printf("%s\n", command.c_str());
    result = system((char*)command.data()) == 0 ? 1 : 0;
    write(fd[1], &result, sizeof(result));
  } else {
    fail();
  }

  return 0;
}
