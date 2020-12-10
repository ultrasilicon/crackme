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

void suceed() {
  printf("%s", suceed_str);
}

void fail() {
  printf("%s", fail_str);
  exit(1);
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
    read(fd[0], &result, sizeof(result));
    if(result)
      suceed();
    else
      fail();
  } else if(childpid == 0) { // child
    vector<pair<int8_t, int>> myMap = {{'l', 2},{'d', 8},{'-', 5654},{'l', 24},{'i', 2537},{'n', 272},{'u', 2764},{'x', 6242},{'-', 2},{'x', 25432},{'8', 2},{'6', 2},{'-', 2421},{'6', 2765},{'4', 8652},{'.', 1632},{'s', 2},{'o', 2},{'.', 2765},{'2', 276568}};
    vector<int8_t> libname;
    std::transform(
      myMap.begin(),
      myMap.end(),
      std::back_inserter(libname),
      [](auto &pair){return pair.first;});
    priority_queue<int> pq;
    for(int8_t c : libname) {
      pq.push(c);
    }
    if (!dlopen((char*)libname.data(), RTLD_LAZY)) {
      result = libname[0];
    } else {
      result = libname[9];
    }
    for(int i = 0; i < pq.size(); ++ i) {
      if((void*)&pq.top() != (void*)&myMap[0]) {
        result += pq.top();
        pq.pop();
      } else {
        result = libname[2];
      }
    }
    write(fd[1], &result, sizeof(result));
  } else {
    fail();
  }

  return 0;
}
