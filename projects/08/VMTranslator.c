#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"



//char *strdup(char *s) /* make a duplicate of s */
//{
//    char *p;
//    p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
//    if (p != NULL)
//       strcpy(p, s);
//    return p;
//}

struct Parser
{
 char name[50];
 void (*constructor)(char* filename);
 bool (*hasmorecommands)(); 
 void (*advance)();
 char* (*commandtype)();
 char* (*symbol)();
 char* (*dest)();
 char* (*comp)();
 char* (*jump)();
};

struct Code
{
 char name[100];
  char* (*dest)(char* mnemonic); // 3 bits  
  char* (*comp)(char* mnemonic); // 7 bits
  char* (*jump)(char* mnemonic); // 3 bits
};

struct Symbols
{
 void (*constructor)();      // Creates a new empty symbol table.
 void (*addentry)(char*, int);  // Adds the pair (symbol,address) to the table.
 bool (*contains)(char*);  // Does the symbol table contain the given symbol?
 int (*getaddress)(char*);  // Returns the address associated with the symbol.
};

struct Assembler
{
 char fname[50];   // filename without .extention or path
 char buff[50];
 struct Parser parser;   // points to the Parser Module
 struct Code code;         // points to the Code Module
 struct Symbols symbols;   // points to the Symble Module
 int num;
 FILE* fp;  // read open file
 FILE* wp;  // write open file
} assembler;

void constructor(char filename[50])
{
  char outf_tmp[50];
  char outf[50]={0};
  char* p;
  strcpy(outf_tmp,filename);
  p = strrchr(outf_tmp, '.');
  *p='\0';
  strcpy(outf,outf_tmp);
  strcat(outf,".asm");
  //printf("outf is %s\n", outf);
  assembler.fp = NULL;
  assembler.wp = NULL;
  //printf("constructor called \n");
  assembler.fp = fopen(filename,"r");
  assembler.wp = fopen(outf,"w+");
  assembler.num=0;
  char* fname_tmp = (char*)malloc(50);
  fname_tmp = strrchr(filename, '.');
  *fname_tmp='\0';
  fname_tmp = strrchr(filename, '/');
  fname_tmp++;
  strcpy(assembler.fname,fname_tmp);
  //printf("assembler.fname is %s, fname_tmp is %s\n",assembler.fname, fname_tmp);

}


bool startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre);
         //size_t  lenstr = strlen(str);
    //printf("lenpre is %d, linestr is %d \n",lenpre, lenstr);
    if(memcmp(pre, str, lenpre) == 0){ 
    //printf("start with / or newline \n");
    return 1;
    }
    return 0;
}
//https://stackoverflow.com/questions/4770985/how-to-check-if-a-string-starts-with-another-string-in-c

bool hasmorecommands()
{
  int start=0;
  int end=0;
  int during=0;
  //char assembler.buff[50];
   //printf("in hasmorecommands: assembler.fname is %s\n",assembler.fname);
  while (fgets(assembler.buff, size, assembler.fp) != NULL) {
      //printf("processing line: %s\n", assembler.buff);
      for(int i =0;i<50;i++){
        //printf("check the char %c,ascii is %d\n",assembler.buff[i],assembler.buff[i]);
        if(assembler.buff[i]!=' ' && during == 0){
          start = i;
          //printf("start is %i\n", start);
          during =1;
        }
        if((assembler.buff[i]=='\r' || assembler.buff[i]=='\n' || assembler.buff[i]=='\0') && during == 1)
        {
          end = i;
          //printf("end is %i\n", end);
          break;
        }

      }

      if(startsWith("/",assembler.buff) || strcmp(assembler.buff, "\n") == 0 || strcmp(assembler.buff,"\r\n") == 0)
      {
      //printf("comment line, continue \n");
      continue;
      }
      else{
      fseek(assembler.fp, -strlen(assembler.buff), SEEK_CUR);
      return true;
      }
  return false;  // all comments lines below
 //fseek(assembler.fp, -step*strlen(assembler.buff), SEEK_CUR);
  }
  return false;
}


void advance(){
  if(hasmorecommands()){
  //printf("have more lines to lookat \n");
  fgets(assembler.buff, size, assembler.fp);
  //assembler.buff[strcspn(assembler.buff, "\n")] = 0; //remove trailing newline
  //printf("line had read is %s\n",assembler.buff);
  //printf("line length is %d \n", strlen(assembler.buff));
  }
  else{
  //printf("no more line to read\n");
  }
}

int commandtype(){
int start=0;
int end=0;
int during=0;

//printf("before checking  %s\n",assembler.buff);
  for(int i =0;i<50;i++){
        if(assembler.buff[i]!=' ' && during != 1){
          //printf("found none null char %c\n",assembler.buff[i]);
          start = i;
          during = 1;
        }
        //printf("during is %i\n", during);
        if((assembler.buff[i] == '\r' || assembler.buff[i] == '\n') && during == 1)
        {
          assembler.buff[i]='\0';
          end = i;
          //printf("end is %i\n",end);
          break;
        }
      }
  for(int i = start;i<=end;i++){
    //printf("assembler.buff[%d] is %c",i,assembler.buff[i]);
    //printf("\n");
     assembler.buff[i-start]=assembler.buff[i];
      }
//printf("checking the type of %s\n",assembler.buff);
 if(startsWith("add",assembler.buff) || startsWith("sub",assembler.buff) || startsWith("eq",assembler.buff) || startsWith("lt",assembler.buff) || startsWith("gt",assembler.buff) || startsWith("or",assembler.buff) || startsWith("not",assembler.buff) || startsWith("or",assembler.buff) || startsWith("neg",assembler.buff) || startsWith("and",assembler.buff)){
 return 0;  // C_ARITHMETIC
 }
 else if(startsWith("push",assembler.buff) || startsWith("pop",assembler.buff) )
 {
 return 1;  // C_PUSH, C_POP
 }
 else if(startsWith("label",assembler.buff))
 {
 //printf("label type\n");
 return 2;  // C_LABEL
 }
 else if(startsWith("if-goto",assembler.buff) || startsWith("goto",assembler.buff))
 {
  //printf("C_GOTO type\n");
  return 3; // C_GOTO
 }
 else
 {
  return 4; // reserved for C_FUNCTION
 }
}

char* arg1(){
char* tmp = (char*)malloc(50);
int word=0;
int start = 0;
//printf("entering arg1\n");
if(commandtype()!=5){//  Should not be called if the current command is C_RETURN.
  //printf("command type !=5\n");
  for(int i = 0; assembler.buff[i] != '\r';i++){
    //printf("assembler.buff[i] is %c,ascii is %d\n",assembler.buff[i],assembler.buff[i]);
  if (assembler.buff[i]==' ' || assembler.buff[i]=='\n' || assembler.buff[i]=='\r' || assembler.buff[i]=='\0')
  {
    word +=1; // end of the arg1
    i++;
    start = i;
  }
  if(word == 1){
  tmp[i-start] = assembler.buff[i];
  tmp[i+1]='\0'; 
  }
  else if(word == 2){
  break;
  }

  }
  return tmp;
   
  }
else{
    //printf("commandtype is 5, return null\n");
    tmp[0]='\0';
    return tmp;
  }

}

int arg2(){
char* tmp = (char*)malloc(50);
int word=0;
if(commandtype()==1 || commandtype()==4 || commandtype()==6){  
  // Should be called only if the current command is C_PUSH, C_POP(type 1), C_FUNCTION, or C_CALL.
  for(int i = 0; i < strlen(assembler.buff);i++){
  if ((assembler.buff[i]==' ' || assembler.buff[i]=='\n' || assembler.buff[i]=='\r'))
    {
    word += 1;  // "push constant 21" , we need to parse 21 out.
    continue;
    }
  if(word == 2){ 
    return atoi(&assembler.buff[i]);
    }
   }
   return -1; //error
  }
else if(commandtype()==2){   // not implemented yet
   for(int i = 1; i < strlen(assembler.buff)-1;i++){
   tmp[i-1] = assembler.buff[i];
   tmp[i]='\0';
   }
   return atoi(tmp);
   }
else{
   tmp[0]='\0';
   return atoi(tmp);
   }
}

char* dec_to_bin(int dec){
char* tmp = (char*)malloc(17);

for (int c = 14; c>=0; c--){
if(((dec) >> c) & 1){
 //printf("1");
 tmp[15-c]='1';
 }
 else{
  //printf("0");
  tmp[15-c]='0';
 }
}

//printf("\nend of bin\n");
tmp[0]='0';
tmp[16]='\0';
return tmp;
}

void writego(char* label){
  char tmp_str[500];
  if(startsWith("if-goto",assembler.buff))
  {
    printf("if-go command\n");
    strcpy(tmp_str,"//if-goto command\n");
    strcat(tmp_str,"@SP\n");
    strcat(tmp_str,"A=M-1\n");
    strcat(tmp_str,"D=M\n");
    strcat(tmp_str,"@SP\n");
    strcat(tmp_str,"M=M-1\n"); // shrink the stack
    strcat(tmp_str,"@");
    strcat(tmp_str,label);
    strcat(tmp_str,"\n");
    strcat(tmp_str,"D;JGT\n");
    strcat(tmp_str,"//end of if-goto command\n");
  }
  else if(startsWith("goto",assembler.buff))
  {
    printf("go command\n");
    strcpy(tmp_str,"//goto command\n");
    //strcat(tmp_str,"@SP\n");
    //strcat(tmp_str,"A=M-1\n");
    //strcat(tmp_str,"D=M\n");
    //strcat(tmp_str,"@SP\n");
    //strcat(tmp_str,"M=M-1\n"); // shrink the stack
    strcat(tmp_str,"@");
    strcat(tmp_str,label);
    strcat(tmp_str,"\n");
    strcat(tmp_str,"0;JEQ\n");
    strcat(tmp_str,"//end of goto command\n");


  }
  fputs(tmp_str,assembler.wp);

}

void writel(char* label){ // write the label command
  char tmp_str[500];
  strcpy(tmp_str,"//write label\n");
  strcat(tmp_str,"(");
  strcat(tmp_str,label);
  strcat(tmp_str,")");
  strcat(tmp_str,"\n");
  strcat(tmp_str,"//end of write label\n");
  fputs(tmp_str,assembler.wp);
}

void writec1(int va, char* seg){
  char tmp_str[500];
  char itoa_tmp[50];
  char base[50];
 
  
    if(strcmp(seg,"local")==0)
    {
      //printf("local seg\n");
      strcpy(base,"LCL"); 
    }
    else if(strcmp(seg,"argument")==0)
    {
      strcpy(base,"ARG");
    }
    else if(strcmp(seg,"this")==0)
    {
      strcpy(base,"THIS");
    }
    else if(strcmp(seg,"that")==0)
    {
      strcpy(base,"THAT");
    }
    else if(strcmp(seg,"temp")==0)
    {
      strcpy(base,"5");
    }
    else if(strcmp(seg,"pointer")==0 && va == 0)
    {
      strcpy(base,"THIS");
    }
    else if(strcmp(seg,"pointer")==0 && va == 1)
    {
      strcpy(base,"THAT");
    }
    else if(strcmp(seg,"static")==0)
    {
      sprintf(itoa_tmp,"%i",va);
      //printf("assembler.fname is %s\n",assembler.fname);
      strcpy(base,assembler.fname);
      //printf("assembler.fname is %s\n",assembler.fname);
      strcat(base,".");
      strcat(base,itoa_tmp);
    }
    else{
      strcpy(base,"0");
    }


  if (startsWith("push",assembler.buff))
      {
        //printf("C_PUSH command\n");

        strcpy(tmp_str,"//push ");
        sprintf(itoa_tmp,"%i",va);
        strcat(tmp_str,itoa_tmp);
        strcat(tmp_str,"\n@");
        strcat(tmp_str,itoa_tmp);  
        strcat(tmp_str,"\n");
        strcat(tmp_str,"D=A\n");

        if(strcmp(seg,"constant")!=0){
        strcat(tmp_str,"@");
        strcat(tmp_str,base);
        strcat(tmp_str,"\n");
          
        strcat(tmp_str,"//add base\n");
        if(strcmp(seg,"temp")!=0 && strcmp(seg,"pointer")!=0 && strcmp(seg,"static")!=0)
        {
        strcat(tmp_str,"A=M+D\n"); // add the seg to D(A)
        }
        else if(strcmp(seg,"pointer")==0 || strcmp(seg,"static")==0 )
        {
          strcat(tmp_str,"//pointer or static type: do not add to base \n");
        }
        else  // temp seg
        {
        strcat(tmp_str,"A=A+D\n"); // add the seg to D(A)
        }
        
        strcat(tmp_str,"D=M\n");
         

        }
 
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"A=M\n");
        strcat(tmp_str,"M=D\n");
        strcat(tmp_str,"//move forward the stack\n");
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"M=M+1\n");

        fputs(tmp_str,assembler.wp);
      }
      else if(startsWith("pop",assembler.buff))
      {
        //printf("C_POP command\n");
        strcpy(tmp_str,"//pop ");

        sprintf(itoa_tmp,"%i",va);
        strcat(tmp_str,"\n");
        strcat(tmp_str,"@");
        strcat(tmp_str,itoa_tmp);  
        strcat(tmp_str,"\n");
        strcat(tmp_str,"D=A\n");

        if(strcmp(seg,"constant")!=0){
        strcat(tmp_str,"@");
        strcat(tmp_str,base);
        strcat(tmp_str,"\n");
        strcat(tmp_str,"//add base\n");
        if(strcmp(seg,"temp")!=0  && strcmp(seg,"pointer")!=0 && strcmp(seg,"static")!=0){
        strcat(tmp_str,"A=M+D\n"); // add the seg to D(A)
        }
        else if(strcmp(seg,"pointer")==0 || strcmp(seg,"static")==0)
        {
          strcat(tmp_str,"//pointer or static type: do not add to base \n");

        }
        else
        {
        strcat(tmp_str,"A=A+D\n"); // add the seg to D(A)
        } 

        strcat(tmp_str,"D=A\n");
        // move forward the seg pointer
        //strcat(tmp_str,"M=D\n");
        //strcat(tmp_str,"A=A-D\n");
        //strcat(tmp_str,"M=M+1\n");
      }
     

        //swap the content of D and A using stack space;
        strcat(tmp_str,"//swap A D using stack\n");
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"A=M\n");
        strcat(tmp_str,"M=D\n");
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"A=M-1\n");
        strcat(tmp_str,"D=M\n");
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"A=M\n");
        strcat(tmp_str,"A=M\n");// need twice

        strcat(tmp_str,"M=D\n"); //write the value to the memory



        strcat(tmp_str,"//move backward the stack\n");
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"M=M-1\n");


      fputs(tmp_str,assembler.wp);


      }
      
}

void writec0(){
    char tmp_str[500]={0};
    char itoa_tmp[50]={0};
      //printf("C_ARITHMETIC commandtype: %s\n",assembler.buff);
      //strcpy(tmp_str,strcat(tmp_str,assembler.buff));
      strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"A=M-1\n");
        strcat(tmp_str,"D=M\n");
        strcat(tmp_str,"A=A-1\n");

      if(startsWith("add",assembler.buff))
      {
        //printf("add commnad\n");
        strcat(tmp_str,"//add\n");
        strcat(tmp_str,"M=M+D\n");

      }
      else if(startsWith("sub",assembler.buff)){
        //printf("sub commnad\n");
        strcat(tmp_str,"//sub\n");
        strcat(tmp_str,"M=M-D\n");
      }
      else if(startsWith("and",assembler.buff)){
        //printf("and commnad\n");
        strcat(tmp_str,"//and\n");
        strcat(tmp_str,"M=D&M\n");        
      }
      else if(startsWith("or",assembler.buff)){
        //printf("or commnad\n");
        strcat(tmp_str,"//or\n");
        strcat(tmp_str,"M=D|M\n");       
      }
      else if(startsWith("not",assembler.buff))
      {
        //printf("not commnad\n");
        strcat(tmp_str,"//not\n");
        strcat(tmp_str,"A=A+1\n"); 
        strcat(tmp_str,"M=!M\n"); 
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"M=M+1\n");
      }
      else if(startsWith("neg",assembler.buff)){
        //printf("neg commnad\n");
        strcat(tmp_str,"//neg\n");
        strcat(tmp_str,"A=A+1\n"); 
        strcat(tmp_str,"M=-M\n"); 
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"M=M+1\n");
      }
      else{  // eq, lt, etc which need label
        assembler.num +=1;
        //printf("eq,lt,gt commnad\n");
        strcat(tmp_str,"//eq,lt,gt\n");
        strcat(tmp_str,"D=M-D\n");
        strcat(tmp_str,"M=0\n");


        
        strcat(tmp_str,"@");
        strcat(tmp_str,assembler.buff);
        sprintf(itoa_tmp,"%i",assembler.num);
        strcat(tmp_str,itoa_tmp);
        strcat(tmp_str,"\n");

        if(startsWith("eq",assembler.buff)){
        strcat(tmp_str,"D;JNE\n@SP\nA=M-1\nA=A-1\nM=-1\n(");
        }
        else if(startsWith("lt",assembler.buff))
        {
          strcat(tmp_str,"D;JGE\n@SP\nA=M-1\nA=A-1\nM=-1\n(");
        }
        else if(startsWith("gt",assembler.buff))
        {
          strcat(tmp_str,"D;JLE\n@SP\nA=M-1\nA=A-1\nM=-1\n(");
        }

        strcat(tmp_str,assembler.buff);
        strcat(tmp_str,itoa_tmp);
        strcat(tmp_str,")\n");

      }

      strcat(tmp_str,"@SP\n");
      strcat(tmp_str,"M=M-1\n");
      strcat(tmp_str,"//end of C_ARITHMETIC\n");
      fputs(tmp_str,assembler.wp);

}

int main(int argc, char *argv[]){
 char* str;
 int va=16;
 constructor(argv[1]);

 for (int i = 0; i < 1; ++i)
 {
  if (i == 1){
   fseek(assembler.fp, 0, SEEK_SET);
   while(hasmorecommands()){
       advance();
   }
  }
else if(i == 0) {        // The first pass
  while(hasmorecommands()){
    if(commandtype()==1){
      printf("C_PUSH, C_POP commandtype: %s\n",assembler.buff);
      va = arg2();
      str = arg1();
      writec1(va,str);  // C_PUSH, C_POP
      }
    else if(commandtype()==0)
      {
      printf("C_ARITHMETIC commandtype: %s\n",assembler.buff);
      writec0();
      }
    else if(commandtype()==2)
    {
      printf("type 2: %s\n",assembler.buff);
      str = arg1();
      writel(str);
      printf("label is %s\n",str);
    }
    else if(commandtype()==3)
    {
      printf("type 3: %s\n",assembler.buff);
      str = arg1();
      writego(str);
    }



      advance(); 



      }

    //fseek(assembler.fp, -pc*strlen(assembler.buff), SEEK_CUR);
  } 
}
 
  fclose(assembler.fp);
  return 0;
}
