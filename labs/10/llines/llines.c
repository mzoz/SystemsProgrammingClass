#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

/* USAGE Information */
char USAGE[] = "llines [OPTIONS] [file]\n"
  "\n"
  "Will print the specified bytes to stdout.\n"
  "\n"
  "OPTIONS:\n"
  "  -s start_offset \t Specify the start offset\n"
  "  -e end_offset   \t Specify the end offset\n"
  "\n"
  "EXAMPLES:\n"
  "llines -s 10 -e 20 file : print between the bytes between offset 10 and 20\n"
  "llines -s 20 -e 10 file : ERROR: end offset can be greater than start offset\n"
  "llines -s 10 file : print bytes between offset 10 and the end of the file\n"
  "llines -e 10 file : print bytes from start of file until 10 from end\n"
  "llines file : print all bytes of file, like cat\n"
  "llines -e -10 : ERROR: cannot have negative offsets\n";


//OPTIONS
typedef struct{
  int start; //the start offset
  int end; //the end offset
  int f_index; //ignore
} opt_t;


//parsing commmand line options : DO NOT EDIT
void parse_args(int argc, char * argv[], opt_t * opts){
  int c;

  opts->start=-1;
  opts->end=-1;
  
  while((c = getopt(argc,argv, "hs:e:")) != -1){
      switch(c)
	{
	case 'h':
	  printf("%s", USAGE);
	  exit(0);
	  break;
	case 's':
	  if(sscanf(optarg,"%d",&(opts->start)) == 0){
	    fprintf(stderr, "ERROR: Invlaid value for start_offset");
	    fprintf(stderr, "USAGE");
	    exit(1);
	  }
	  break;
	case 'e':
	  if(sscanf(optarg,"%d",&(opts->end)) == 0){
	    fprintf(stderr, "ERROR: Invlaid value for end_offset");
	    fprintf(stderr, "USAGE");
	    exit(1);
	  }
	  break;
	default:
	  fprintf(stderr, "ERROR: Unknown option '%c' \n", c);
	  exit(0);
	  break;
	}
    }
  
  opts->f_index = optind;
}

int main(int argc, char * argv[]){
  
  opt_t opts;
  int fd, i;
  char c;

  parse_args(argc,argv,&opts);

  if(opts.f_index == argc){
    fprintf(stderr, "ERROR: Require a file argument\n");
    exit(1);
  }else{

    if( (fd = open(argv[opts.f_index], O_RDONLY)) < 0){
      fprintf(stderr, "ERROR: Invalid file\n");
      exit(1);
    }
  }


  //TODO: Complete the program based on the specification
  //
  //    YOU MUST USE lseek(), read(), and write()
  //
  //    command line options are stored in the opts structure
  int eof;

  i= 0;
  if((opts.start < -1) || (opts.end < -1)){
    fprintf(stderr, "ERROR: can't have negaitatve ofsets cheater");
    exit(1);
   }
  if(lseek(fd, opts.end * -1, SEEK_END) < lseek(fd, opts.start, SEEK_SET)){
    fprintf(stderr, "ERROR:Invalid start and end (end < start)");
    exit(1);
  }
  else if ((opts.start == -1) && (opts.end == -1)){
    eof = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    while(i < eof){
      read(fd, &c, 1); 
      write(1, &c, 1);
      i++;
    }
  }
  else if((opts.start > -1) && (opts.end == -1)){
    eof = lseek(fd, -1, SEEK_END);
    i = lseek(fd, opts.start, SEEK_SET);
    while(i < eof){
      read(fd, &c, 1);
      write(1, &c, 1);
      i++;
    }
    
  }
  else if((opts.start == -1) && (opts.end >= -1)){
    eof = lseek(fd, -1, SEEK_END);
    i = lseek(fd, -1 * opts.end , SEEK_END);
    while(i < eof){
      read(fd, &c, 1);
      write(1, &c, 1);
      //offset = lseek(fd, 0, SEEK_CUR);
      i++;
    }
  }
  else{
    eof = lseek(fd, -1 * opts.end -1, SEEK_END);
    i = lseek(fd, opts.start, SEEK_SET);
    while(i < eof){
      read(fd, &c, 1);
      write(1, &c, 1);
       i++;
    }
  }
  printf("\n");
  close(fd);
  return 0;
}
