#include <cstring>
#include <map>
#include <queue>
#include <string>
#include <unistd.h>

// crackme2: data structure hell
// answer: "ooooottoccaattocc" where first five bytes can be any char in string "taco"

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

bool check(string str) {
  map<char, int> myMap;
  priority_queue<char> myQue;
  for(char c : secret) {
    myMap.insert({c, rand()});
    myQue.push(c);
  }
  for(char c: str) {
    if(myMap.find(c) == myMap.end()) {
      return false;
    }
  }
  for(size_t i = 0; i < strlen(secret); ++ i) {
    secret[i] = myQue.top();
    myQue.pop();
  }
  for(size_t i = myMap.size(); i < str.size(); ++ i) {
    if(str[i] != secret[(i-myMap.size()) % strlen(secret)]) {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv)
{
  if(argc != 2) {
    printf("Exactly one argument is needed\n");
    exit(1);
  }

  string str = argv[1];
  s = new char(67);
  // string len must == 17
  try {
    srand(str.at((*s >> 2) + *s % 2));
    incorrect();
    exit(0);
  }  catch (...) {
    try {
      srand(str.at(*s >> 2));
    }  catch (...) {
      incorrect();
      exit(0);
    }
  }

  if(check(str))
    correct();
  else
    incorrect();

  return 0;
}
