#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
int size = 100;
struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};
/* hash: form hash value for string s */
// https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
          return np; /* found */
    return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
       return NULL;
    return np;
}

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
  printf("outf is %s\n", outf);
  assembler.fp = NULL;
  assembler.wp = NULL;
  printf("constructor called \n");
  assembler.fp = fopen(filename,"r");
  assembler.wp = fopen(outf,"ab");
  assembler.num=0;
  char* fname_tmp = (char*)malloc(50);
  fname_tmp = strrchr(filename, '.');
  *fname_tmp='\0';
  fname_tmp = strrchr(filename, '/');
  fname_tmp++;
  strcpy(assembler.fname,fname_tmp);
  printf("assembler.fname is %s, fname_tmp is %s\n",assembler.fname, fname_tmp);
  
 

}


bool startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
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
   printf("in hasmorecommands: assembler.fname is %s\n",assembler.fname);
while (fgets(assembler.buff, size, assembler.fp) != NULL) {
      printf("processing line: %s\n", assembler.buff);
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
      printf("comment line, continue \n");
      continue;
      }
      else{
      fseek(assembler.fp, -strlen(assembler.buff), SEEK_CUR);
      return true;
      }
 return false;  // all comments lines below
 //fseek(assembler.fp, -step*strlen(assembler.buff), SEEK_CUR);
}
}


void advance(){
  if(hasmorecommands()){
  //printf("have more lines to lookat \n");
  fgets(assembler.buff, size, assembler.fp);
  //assembler.buff[strcspn(assembler.buff, "\n")] = 0; //remove trailing newline
  printf("line had read is %s\n",assembler.buff);
  //printf("line length is %d \n", strlen(assembler.buff));
  }
  else{
  printf("no more line to read\n");
  }
}

int commandtype(){
int start,end,during;
during = 0;
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
 else{
 return 2;  // Not implemented yet
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
    printf("commandtype is 5, return null\n");
    tmp[0]='\0';
    return tmp;
  }

}

int arg2(){
char* tmp = (char*)malloc(50);
int word=0;

if(commandtype()==1 || commandtype()==4 || commandtype()==6){  
  // Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL.
  for(int i = 0; i < strlen(assembler.buff);i++){

  if ((assembler.buff[i]==' ' || assembler.buff[i]=='\n' || assembler.buff[i]=='\r'))
  {
    word += 1;  // "push constant 21" , we need to parse 21 out.
    
    continue;
  }
  if(word == 2){
  
    printf("assembler.buff[%i]=%s\n",i,&assembler.buff[i]);
 
  return atoi(&assembler.buff[i]);
  }
  //printf("tmp is %s\n", tmp);
  }
   
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
 printf("1");
 tmp[15-c]='1';
 }
 else{
  printf("0");
  tmp[15-c]='0';
 }
}

printf("\nend of bin\n");
tmp[0]='0';
tmp[16]='\0';
return tmp;
}

void writec1(int va, char* seg){
  char tmp_str[500];
  char itoa_tmp[50];
  char base[50];
 
  
    if(strcmp(seg,"local")==0)
    {
      printf("local seg\n");
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
      printf("assembler.fname is %s\n",assembler.fname);
      strcpy(base,assembler.fname);
      printf("assembler.fname is %s\n",assembler.fname);
      strcat(base,".");
      strcat(base,itoa_tmp);
    }
    else{
      strcpy(base,"0");
    }


  if (startsWith("push",assembler.buff))
      {
        printf("C_PUSH command\n");

        strcpy(tmp_str,"//push constant ");
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
        printf("C_POP command\n");
        strcpy(tmp_str,"//pop constant ");

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
      printf("C_ARITHMETIC commandtype: %s\n",assembler.buff);
      //strcpy(tmp_str,strcat(tmp_str,assembler.buff));
      strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"A=M-1\n");
        strcat(tmp_str,"D=M\n");
        strcat(tmp_str,"A=A-1\n");

      if(startsWith("add",assembler.buff))
      {
        printf("add commnad\n");
        strcat(tmp_str,"//add\n");
        strcat(tmp_str,"M=M+D\n");

      }
      else if(startsWith("sub",assembler.buff)){
        printf("sub commnad\n");
        strcat(tmp_str,"//sub\n");
        strcat(tmp_str,"M=M-D\n");
      }
      else if(startsWith("and",assembler.buff)){
        printf("and commnad\n");
        strcat(tmp_str,"//and\n");
        strcat(tmp_str,"M=D&M\n");        
      }
      else if(startsWith("or",assembler.buff)){
        printf("or commnad\n");
        strcat(tmp_str,"//or\n");
        strcat(tmp_str,"M=D|M\n");       
      }
      else if(startsWith("not",assembler.buff))
      {
        printf("not commnad\n");
        strcat(tmp_str,"//not\n");
        strcat(tmp_str,"A=A+1\n"); 
        strcat(tmp_str,"M=!M\n"); 
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"M=M+1\n");
      }
      else if(startsWith("neg",assembler.buff)){
        printf("neg commnad\n");
        strcat(tmp_str,"//neg\n");
        strcat(tmp_str,"A=A+1\n"); 
        strcat(tmp_str,"M=-M\n"); 
        strcat(tmp_str,"@SP\n");
        strcat(tmp_str,"M=M+1\n");
      }
      else{  // eq, lt, etc which need label
        assembler.num +=1;
        printf("eq,lt,gt commnad\n");
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
 
 int p2num=0;
 int tmp;
 char* str;
 
 char* destc;
 char* compc;
 char* jumpc;
 int sym;
 char* sym_to_num;
 char* acom;
 char cstr[50];
 struct nlist* a;
 struct nlist * pos;
 int pc = 0;
 char pc_str[50]; 
 char* key[50];
 char* value[50];
 struct nlist* p;
 int va=16;
 

 char* wstr = (char*)malloc(50);
 char* wstr2 = (char*)malloc(50);
 char* fname = (char*)malloc(50);
 char tmp_str[500];
 char tmp_str_2[50];
 char itoa_tmp[5];

 constructor(argv[1]);
  printf("after constructor: assembler.fname is %s\n",assembler.fname);

   //printf("the argv[1] is %s\n",argv[1]);

  



 
 for (int i = 0; i < 1; ++i)
 {
  if (i == 1){
   fseek(assembler.fp, 0, SEEK_SET);
   while(hasmorecommands()){
     printf("after hasmorecommands: assembler.fname is %s\n",assembler.fname);
    printf("Begin new line \n");
       advance();
   }
  }
else if(i == 0) {        // The first pass
    printf("before hasmorecommands: assembler.fname is %s\n",assembler.fname);
  while(hasmorecommands()){
    printf("before commandtype(): assembler.fname is %s\n",assembler.fname);
    if(commandtype()==1){
    printf("before arg2: assembler.fname is %s\n",assembler.fname);
    va = arg2();
    printf("arg2 is %i\n", va);
    printf("before arg1: assembler.fname is %s\n",assembler.fname);
    str = arg1();
    printf("arg1 is %s\n",str );
    printf("before writec1: assembler.fname is %s\n",assembler.fname);
    writec1(va,str);  // C_PUSH, C_POP
    }
    else if(commandtype()==0)
    {
      printf("C_ARITHMETIC commandtype: %s\n",assembler.buff);
      writec0();
    }
    advance(); 
    }
    //fseek(assembler.fp, -pc*strlen(assembler.buff), SEEK_CUR);
}
}
 
  fclose(assembler.fp);
  return 0;
}
