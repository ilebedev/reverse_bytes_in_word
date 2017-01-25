#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void fail(char* arg0, char* err) {
  printf("Reverse the order of bytes in a 32-bit word.\n");
  printf("usage: %s bytes_per_word in_file out_file\n", arg0);
  printf("or print out (watch out for binary): %s bytes_per_word in_file\n", arg0);
  printf("or use streams (watch out for EOF): %s bytes_per_word\n", arg0);
  fprintf(stderr, "%s; errno = %d\n", err, errno);
  exit(1);
}

int main(int argc, char** argv) {
  FILE *in = stdin;
  FILE *out = stdout;
  unsigned long itr = 0;
  unsigned char* stack;
  int word_size, bytes_read, i;
 
  // Fail if word size is not given
  if ((argc < 2) | (argc > 4)) fail(argv[0], "see usage");
  word_size = atoi(argv[1]);

  // Choose to read from file instead of stdin if arg1 is given
  if (argc >2) {
    in = fopen(argv[2], "rb");
    if (!in) fail(argv[0], "failed to open infile");
  }
  
  // Choose to write to file instead of stdout if arg2 is given
  if (argc > 3) {
    out = fopen(argv[3], "wb");
    if (!out) fail(argv[0], "failed to open outfile");
  }

  // Byte stack
  stack = (unsigned char*)malloc(word_size);

  // Process entire file / stream
  while (word_size == (bytes_read = fread(stack, 1, word_size, in))) {
    // Stack now contains a full word. Write it to out byte by byte
    for (i=word_size-1; i>=0; i--){
      if (1 != fwrite(stack+i, 1, 1, out)) fprintf(stderr, "Failed to write a byte :(\n");
    }
  }

  // Close the buffers used. This is safe for stdin, stdout
  fclose(in);
  fclose(out);
}
