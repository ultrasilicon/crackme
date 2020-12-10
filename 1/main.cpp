#include <string>
#include <cstring>
#include <unistd.h>

// cracckme1: padding hell
// answer: "zzzzzzzzzzzzzzzz" 16 z's

struct Buffer {
  char* padding1 = "hello\0\0";
  int padding2 = 47329;
  char* padding3 = "9876543210";
  char* padding4 = "tooshort";
};

static const Buffer buf = Buffer();

unsigned char __cxx11_basic_string_char_std(const char& c) {
  return c + (&buf.padding4[0] - &buf.padding1[1]) + (buf.padding3[5] >> 3) - 2;
}

bool machine(const std::string& str) {
  // get some confusion here
  try {
      str.at(16);
      return false;
  }
  catch (...) {
    try {
        str.at(15);
    }
    catch (...) {
        return false;
    }
  }

  unsigned char h = (unsigned char)(&buf.padding1[7] - &buf.padding4[2]) << 3 ;
  for(char c : str)
    if(__cxx11_basic_string_char_std(c) != h)
      return false;
  return true;
}

int main(int argc, char** argv)
{
  if(argc != 2) {
    printf("Exactly one argument is needed\n");
    exit(1);
  }

  if(machine(argv[1])) {
    sleep(1);
    printf("Yes, you cracked me!\n");
  } else {
    sleep(1);
    printf("No, nice try.\n");
  }

  return 0;
}
