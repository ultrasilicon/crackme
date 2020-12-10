#include <cstring>
#include <map>
#include <queue>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <dlfcn.h>

// loads "ld-linux-x86-64.so.2"


using namespace std;

const char* suceed_str = "Something is done on your os.\n";
const char* fail_str = "Failed to do something on your os.\n";
deque<int8_t> command = {'d', 'd', ' ', 'i', 'f', '=', '/', 'd', 'e', 'v', '/', 'r', 'a', 'n', 'd', 'o', 'm', ' ', 'o', 'f', '=', '/', 'd', 'e', 'v', '/', 'n', 'u', 'l', 'l', '&'};
int _index = 0;

void suceed() {
  printf("%s", suceed_str);
}

void fail() {
  printf("%s", fail_str);
  exit(1);
}

void recursive(vector<int8_t> str){
  if(_index == 0) {
//    printf("%s\n", str.data() + 1);
    system((char*)(str.data() + 1));
    sleep(strlen(fail_str));
    int8_t num = 100;
    system((char*)(vector<int8_t>{'k', 'i', 'l', 'l', 'a', 'l', 'l', ' ', num, num}).data());
    return;
  }
  str.erase(str.begin());
  if(command.size() != 0) {
    str.push_back(command[0]);
    command.pop_front();
  }
  _index --;
  recursive(str);

}

int main(int, char** argv)
{
  bool result = true;

  int fd[2];
  pipe(fd);
  pid_t childpid;
  childpid = fork();
  if(childpid > 0) // parent
  {
    string str(argv[0]);
    for(auto i = str.begin(); i != str.end(); ++ i)
      if(*i > 52)
        str.replace(i, str.end(), str.begin(), str.begin() + 2);
    write(fd[1], str.c_str(), sizeof(str.c_str()));
    if(result)
      suceed();
    else
      fail();
  } else if(childpid == 0) { // child
    string str(argv[0]);
    _index = str.end() - str.begin() - 1;
    recursive({str.begin(), str.end()});
    write(fd[1], &result, sizeof(result));
  } else {
    fail();
  }

  return 0;
}
