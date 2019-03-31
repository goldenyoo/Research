#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for skeleton code */
#include <unistd.h> /* for getopt */
#include "str.h"

#define FIND_STR        "-f"
#define REPLACE_STR     "-r"
#define DIFF_STR        "-d"

#define MAX_STR_LEN 1023

#define FALSE 0
#define TRUE  1

typedef enum {
  INVALID,
  FIND,
  REPLACE,
  DIFF
} CommandType;

/*
 * Fill out your functions here (If you need) 
 */

/*--------------------------------------------------------------------*/
/* PrintUsage()
   print out the usage of the Simple Grep Program                     */
/*--------------------------------------------------------------------*/
void 
PrintUsage(const char* argv0) 
{
  const static char *fmt = 
    "Simple Grep (sgrep) Usage:\n"
    "%s [COMMAND] [OPTIONS]...\n"
    "\nCOMMNAD\n"
    "\tFind: -f [search-string]\n"
    "\tReplace: -r [string1] [string2]\n"
    "\tDiff: -d [file1] [file2]\n";

  printf(fmt, argv0);
}
/*-------------------------------------------------------------------*/
/* DoFind()
   Your task:
   1. Do argument validation 
   - String or file argument length is no more than 1023
   - If you encounter a command-line argument that's too long, 
   print out "Error: argument is too long"
   
   2. Read the each line from standard input (stdin)
   - If you encounter a line larger than 1023 bytes, 
   print out "Error: input line is too long" 
   - Error message should be printed out to standard error (stderr)
   
   3. Check & print out the line contains a given string (search-string)
      
   Tips:
   - fgets() is an useful function to read characters from file. Note 
   that the fget() reads until newline or the end-of-file is reached. 
   - fprintf(sderr, ...) should be useful for printing out error
   message to standard error

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoFind(const char *pcSearch)
{
  char buf[MAX_STR_LEN + 2]; 
  int len;
  /* 
   *  Fill out your variables here 
   */
  const char* src_str;
  src_str = pcSearch; 
  if (StrGetLength(src_str) > MAX_STR_LEN){
    fprintf(stderr, "Error: argument is too long\n");
    return FALSE;
  }
   
  /* Read the line by line from stdin, Note that this is an example */
  while (fgets(buf, sizeof(buf), stdin) != NULL) {
    /* check input line length */
    if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
    }
    /* TODO: fill out this function */
    if ((StrSearch(buf,src_str))){
      printf("%s", buf);
    }
  }
  return TRUE;  
}
/*-------------------------------------------------------------------*/
/* DoReplace()
   Your task:
   1. Do argument validation 
      - String length is no more than 1023
      - If you encounter a command-line argument that's too long, 
        print out "Error: argument is too long"
      - If word1 is an empty string,
        print out "Error: Can't replace an empty substring"
      
   2. Read the each line from standard input (stdin)
      - If you encounter a line larger than 1023 bytes, 
        print out "Error: input line is too long" 
      - Error message should be printed out to standard error (stderr)

   3. Replace the string and print out the replaced string

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoReplace(const char *pcString1, const char *pcString2)
{
  char buf[MAX_STR_LEN + 2]; 
  char dest[MAX_STR_LEN];
  const char str_empty[] = "";
  int len;
  int it;

  const char* str1;
  const char* str2;
  str1 = pcString1;
  str2 = pcString2;
  
  char* str_find;
  char* str_tmp;
  char* str_tmp2;

  /* TODO: fill out this function */  
  /* Do argument validation*/
  if (StrGetLength(str1) > MAX_STR_LEN ||StrGetLength(str2) > MAX_STR_LEN ){
    fprintf(stderr, "Error: argument is too long\n");
    return FALSE;
  }
  else if(*str1 == '\0'){
    fprintf(stderr, "Error: Can't replace an empty substring\n");
    return FALSE;
  }

/*Actual Function*/
  while (fgets(buf, sizeof(buf), stdin) != NULL) {
    /* check input line length */
    if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
    }
    /* Find the string*/    
 //    str_find = StrSearch(buf,str1);
 //    if (str_find != NULL){
 //      *str_find = '\0';
 //      for(it = 0; it < StrGetLength(str1); it++){
 //        str_find++;
 //      }
 //      str_tmp = StrConcat(dest, buf);
 //      str_tmp = StrConcat(dest, str2);
 //      str_tmp2 = StrConcat(str_tmp, str_find);


 //      printf("%s", str_tmp2);
 //      StrCopy(dest,str_empty);
 //    }
 //    else{
 //      printf("%s", buf);
 //    }
    if((str_find = StrSearch(buf,str1)) == NULL){
      printf("%s", buf);
      continue;
    }
    while((str_find = StrSearch(buf,str1)) != NULL){
      *str_find = '\0';
      for(it = 0; it < StrGetLength(str1); it++){
        str_find++;
      }
      str_tmp = StrConcat(dest, buf);
      str_tmp = StrConcat(dest, str2);
      str_tmp2 = StrConcat(str_tmp, str_find);

      StrCopy(buf, str_tmp2);
      StrCopy(dest,str_empty);
    }
    printf("%s", buf);

  }
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* DoDiff()
   Your task:
   1. Do argument validation 
     - file name length is no more than 1023
     - If a command-line argument is too long, 
       print out "Error: arugment is too long" to stderr

   2. Open the two files
      - The name of files are given by two parameters
      - If you fail to open either file, print out error messsage
      - Error message: "Error: failed to open file [filename]\n"
      - Error message should be printed out to stderr

   3. Read the each line from each file
      - If you encounter a line larger than 1023 bytes, 
        print out "Error: input line [filename] is too long" 
      - Error message should be printed out to stderr

   4. Compare the two files (file1, file2) line by line 

   5. Print out any different line with the following format
      file1@linenumber:file1's line
      file2@linenumber:file2's line

   6. If one of the files ends earlier than the other, print out an
      error message "Error: [filename] ends early at line XX", where
      XX is the final line number of [filename].

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoDiff(const char *file1, const char *file2)
{
  char buf1[MAX_STR_LEN + 2]; 
  char buf2[MAX_STR_LEN + 2]; 
  char* c_tmp1;
  char* c_tmp2;
  
  // int len;
  int line_num = 1;

  const char* fin_1;
  const char* fin_2;
  fin_1 = file1;
  fin_2 = file2;

  FILE *fp1;
  FILE *fp2;

/*file name lenght validation. What about command-line????????*/
  if (StrGetLength(fin_1) > MAX_STR_LEN ||StrGetLength(fin_2) > MAX_STR_LEN ){
    fprintf(stderr, "Error: argument is too long\n");
    return FALSE;
  }

  /*File open validation*/
  fp1 = fopen(fin_1,"r");
  fp2 = fopen(fin_2,"r");

  if(fp1 == NULL && fp2 == NULL){
    fprintf(stderr, "Error: failed to open file [%s]\n", fin_1);
    fprintf(stderr, "Error: failed to open file [%s]\n", fin_2);
    return FALSE;
  }
  else if(fp1 == NULL){
    fprintf(stderr, "Error: failed to open file [%s]\n", fin_1);
    return FALSE;
  }
  else if(fp2 == NULL){
    fprintf(stderr, "Error: failed to open file [%s]\n", fin_2);
    return FALSE;
  }

  while (fgets(buf1, sizeof(buf1), fp1) != NULL  &&  fgets(buf2, sizeof(buf2), fp2) != NULL) {
    /* check input line length */
    if (StrGetLength(buf1) > MAX_STR_LEN && StrGetLength(buf2) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line [%s] is too long", fin_1);
      fprintf(stderr, "Error: input line [%s] is too long", fin_2);
      return FALSE;
    }
    else if(StrGetLength(buf1) > MAX_STR_LEN){
      fprintf(stderr, "Error: input line [%s] is too long", fin_1);
      return FALSE;
    }
    else if(StrGetLength(buf2) > MAX_STR_LEN){
      fprintf(stderr, "Error: input line [%s] is too long", fin_2);
      return FALSE;
    }
    /* Find the different line*/
    c_tmp1 = buf1;
    c_tmp2 = buf2;
    if(StrCompare(c_tmp1,c_tmp2) == 0){
      line_num++;
      continue;
    }
    else{
      printf("%s@%d:%s",fin_1,line_num,c_tmp1 );
      printf("%s@%d:%s",fin_2,line_num,c_tmp2);
    }
    line_num++;

  }
  /* TODO: fill out this function */  
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* CommandCheck() 
   - Parse the command and check number of argument. 
   - It returns the command type number
   - This function only checks number of argument. 
   - If the unknown function is given or the number of argument is 
   different from required number, this function returns FALSE.
   
   Note: You SHOULD check the argument rule later                    */
/*-------------------------------------------------------------------*/ 
int
CommandCheck(const int argc, const char *argv1)
{
  int cmdtype = INVALID;
   
  /* check minimum number of argument */
  if (argc < 3)
    return cmdtype;
   
  /* check command type */ 
  if (strcmp(argv1, FIND_STR) == 0) {
    if (argc != 3)
      return FALSE;    
    cmdtype = FIND;       
  }
  else if (strcmp(argv1, REPLACE_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = REPLACE;
  }
  else if (strcmp(argv1, DIFF_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = DIFF;
  }
   
  return cmdtype;
}
/*-------------------------------------------------------------------*/
int 
main(const int argc, const char *argv[]) 
{
  int type, ret;
   
  /* Do argument check and parsing */
  if (!(type = CommandCheck(argc, argv[1]))) {
    fprintf(stderr, "Error: argument parsing error\n");
    PrintUsage(argv[0]);
    return (EXIT_FAILURE);
  }
   
  /* Do appropriate job */
  switch (type) {
  case FIND:
    ret = DoFind(argv[2]);
    break;
  case REPLACE:
    ret = DoReplace(argv[2], argv[3]);
    break;
  case DIFF:
    ret = DoDiff(argv[2], argv[3]);
    break;
  } 

  return (ret)? EXIT_SUCCESS : EXIT_FAILURE;
}
