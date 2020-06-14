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
 char buff[50];
 struct Parser parser;   // points to the Parser Module
 struct Code code;         // points to the Code Module
 struct Symbols symbols;   // points to the Symble Module
 FILE* fp;  // read open file
 FILE* wp;  // write open file
} assembler;

void constructor(char filename[50])
{
  assembler.fp = NULL;
  assembler.wp = NULL;
  printf("constructor called \n");
  assembler.fp = fopen(filename,"r");
  assembler.wp = fopen("fileout","ab");
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
  int start,end,during;
//char assembler.buff[50];
int step = 0;
while (fgets(assembler.buff, size, assembler.fp) != NULL) {
      for(int i =0;i<50;i++){
        if(assembler.buff[i]!=' '){
          start = i;
          during =1;}
        if(assembler.buff[i]==' ' && during == 1)
        {
          end = i;
        }
      }
      for(int i = start;i<end;i++){
        assembler.buff[i-start]=assembler.buff[i];
      }
      if(startsWith("/",assembler.buff) || strcmp(assembler.buff, "\n") == 0 || strcmp(assembler.buff,"\r\n") == 0)
      {
      step += 1;
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
  printf("line had read is %s \n",assembler.buff);
  //printf("line length is %d \n", strlen(assembler.buff));
  }
  else{
  printf("no more line to read \n");
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
        if((isspace(assembler.buff[i]) || assembler.buff[i] == '\0') && during == 1)
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
 if(startsWith("@",assembler.buff)){
 return 0;
 }
 else if(startsWith("(",assembler.buff))
 {
 return 2;
 }
 else{
 return 1;
 }
}

char* symbol(){
char* tmp = (char*)malloc(50);
if(commandtype()==0){
// A command
  for(int i = 1; i < strlen(assembler.buff);i++){
  tmp[i-1] = assembler.buff[i];
  tmp[i]='\0'; 
  }
return tmp;
}
else if(commandtype()==2){
   for(int i = 1; i < strlen(assembler.buff)-1;i++){
   tmp[i-1] = assembler.buff[i];
   tmp[i]='\0';
   }
return tmp;
}
else{
tmp[0]='\0';
return tmp;
}
}

char* dest(){
char* tmp = (char*)malloc(4);
int found = 0;
tmp[3]='\0';
tmp[2]='0';
tmp[1]='0';
tmp[0]='0';
for(int i = 0 ; i < strlen(assembler.buff); i++){
 printf("dest: char is %c\n", assembler.buff[i]);
 if(assembler.buff[i]==' '){
  continue;
 }
 if(assembler.buff[i] == 'M')
 {
 tmp[2]='1';
 }
 else if(assembler.buff[i] == 'D'){
 tmp[1]='1';
 printf("set tmp[1]=1\n");
 }
 else if(assembler.buff[i] == 'A'){
 tmp[0]='1';
 }
 if(assembler.buff[i] == '='){
 printf("dest is found\n");
 found = 1; 
 break;
 }
 
 }
 if(found == 0){
 printf("dest not found\n");
 tmp="000";
 }
 //tmp[3]='\0';
return tmp;
}

char* comp(){
int found=0;
int end = 0;
char* compchar = (char*)malloc(8);
char* tmp = (char*)malloc(8);
int step = 0;
for(int i = 0 ; i < strlen(assembler.buff); i++){
 printf("comp: char is %c\n", assembler.buff[i]);
 if(assembler.buff[i]==' '){
  continue;
 }
 compchar[i]=assembler.buff[i];


 if(assembler.buff[i] == ';'){
 compchar[i]='\0';
 //tmp=compchar;
 //return tmp;
 break;
 }
 else if(assembler.buff[i] == '='){
 step = i;
 compchar[i-step]='\0';
 found = 1;
 continue; 
 }
 if(found==1){
 printf("init compchar \n");
 compchar[i-step-1]=assembler.buff[i];
 compchar[i-step]='\0';
 } 

}
printf("compchar is %s\n",compchar);
if(!strcmp(compchar,"M")){
printf("str equal\n");
 tmp="1110000";
}
else if(!strcmp(compchar,"A")){
 tmp="0110000";
}
else if(!strcmp(compchar,"!M")){
 tmp="1110001";
 }
else if(!strcmp(compchar,"!A")){
 tmp="0110001";
 }
else if(!strcmp(compchar,"M+1")){
 tmp="1110111";
 }
else if(!strcmp(compchar,"A+1")){
 tmp="0110111";
 }
else if(!strcmp(compchar,"M-1")){
 tmp="1110010";
 }
else if(!strcmp(compchar,"A-1")){
 tmp="0110010";
 }
else if(!strcmp(compchar,"D+M")){
 tmp="1000010";
}
else if(!strcmp(compchar,"D+A")){
 tmp="0000010";
}
else if(!strcmp(compchar,"D-M")){
 tmp="1010011";
}
else if(!strcmp(compchar,"D-A")){
 tmp="0010011";
}
else if(!strcmp(compchar,"M-D")){
 tmp="1000111";
}
else if(!strcmp(compchar,"A-D")){
 tmp="0000111";
}
else if(!strcmp(compchar,"D&M")){
 tmp="1000000";
}
else if(!strcmp(compchar,"D&A")){
 tmp="0000000";
}
else if(!strcmp(compchar,"D|M")){
 tmp="1010101";
}
else if(!strcmp(compchar,"D|A")){
 tmp="0010101";
}
//finished A and M, begin a=0 only
else if(!strcmp(compchar,"0")){
 tmp="0101010";
}
else if(!strcmp(compchar,"1")){
 tmp="0111111";
}
else if(!strcmp(compchar,"-1")){
 tmp="0111010";
}
else if(!strcmp(compchar,"D")){
 tmp="0001100";
}
else if(!strcmp(compchar,"!D")){
 tmp="0001101";
}
else if(!strcmp(compchar,"-D")){
 tmp="0001111";
}
else if(!strcmp(compchar,"D+1")){
 tmp="0011111";
}
else if(!strcmp(compchar,"D-1")){
 tmp="0001110";
}
//finished a=0 only items
return tmp;
}

char* jump(){
char* tmp = (char*)malloc(4);
char* tmpchar = (char*)malloc(4);
int found = 0;
int index = 0;
for(int i = 0 ; i < strlen(assembler.buff); i++){
 //printf("jump(): char is %c\n", assembler.buff[i]);
 if(assembler.buff[i]==';')
{
printf("begin jump\n");
found = 1;
continue;
}

if(found == 1)
  {
  tmpchar[index] = assembler.buff[i];
  index++;
  }

if(index==3){
 tmpchar[3]='\0';
 break;
 }
}

printf("jumpchar is %s\n",tmpchar);
if(!strcmp(tmpchar,"\0")){
 tmp="000";
}
else if(!strcmp(tmpchar,"JGT")){
 tmp="001";
}
else if(!strcmp(tmpchar,"JEQ")){
 tmp="010";
}
else if(!strcmp(tmpchar,"JGE")){
 tmp="011";
}
else if(!strcmp(tmpchar,"JLT")){
 tmp="100";
}
else if(!strcmp(tmpchar,"JNE")){
 tmp="101";
}
else if(!strcmp(tmpchar,"JLE")){
 tmp="110";
}
else if(!strcmp(tmpchar,"JMP")){
 tmp="111";
}
return tmp;
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

int main() {
 int p2num=0;
 int tmp;
 char* str;
 constructor("Max.asm");
 char* destc;
 char* compc;
 char* jumpc;
 char* sym;
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

  install("SP","0");
  install("LCL","1");
  install("ARG","2");
  install("THIS","3");
  install("THAT","4");
  install("R0","0");
  install("R1","1");
  install("R2","2");
  install("R3","3");
  install("R4","4");
  install("R5","5");
  install("R6","6");
  install("R7","7");
  install("R8","8");
  install("R9","9");
  install("R10","10");
  install("R11","11");
  install("R12","12");
  install("R13","13");
  install("R14","14");
  install("R15","15");
  install("SCREEN","16384");
  install("KBD","24579");

 for (int i = 0; i < 2; ++i)
 {
  if (i == 1){
   fseek(assembler.fp, 0, SEEK_SET);
   while(hasmorecommands()){
    printf("Begin new line \n");
    //printf("command type is %d \n", commandtype());
      if(commandtype()==1){
      destc=dest();
      printf("dest is %s\n",destc);
      compc = comp();
      printf("compc is %s\n",compc);
      jumpc=jump();
      printf("jumpc is %s\n",jumpc);
      printf("command is %s%s%s%s\n","111",compc,destc,jumpc);
      strcpy(cstr,"111");
      strcat(cstr,compc);
      strcat(cstr,destc);
      strcat(cstr,jumpc);
      fputs(cstr,assembler.wp);
      fputs("\n",assembler.wp);
      }// command type is 1, c type

       else if(commandtype()==0){
       sym = symbol();
       printf("a type, symbol is %s\ntry to lookup in the table\n",sym);
       if(lookup(sym)){
        printf("symbol found\n");

        }
        else if(isdigit(sym[0])){  // is number
        printf("atoi result is %i\n",atoi(sym));
        install(sym,sym);


        }
        else  // variable not in table
        {
        printf("not in table, assign one\n");
        sprintf(pc_str, "%i", va);
        install(sym,pc_str);
        va++;
        }
        p = lookup(sym);
        printf("p->name is %s\n",p->name);
        printf("p->defn is %s\n",p->defn);
        acom = dec_to_bin(atoi(p->defn)); 
        printf("command is %s\n",acom);
        fputs(acom,assembler.wp);
        fputs("\n",assembler.wp);   
        }
       else  
       {    
        printf("symbol command, do nothing in second pass\n");
       }
       advance();
   }
  }
else if(i == 0) {        // The first pass
  while(hasmorecommands()){

    if(commandtype()==2){
      p2num++;
      sym = symbol();
      printf("labol found: %s\n",sym);
      //*sym_to_num = pc+'0';
      sprintf(pc_str, "%i", pc-p2num+1);
      printf("pc is %i, the pc+0 is %s\n",pc,pc_str);
      install(sym,pc_str);
      }
    pc++;
    advance(); 
    
    }
    //fseek(assembler.fp, -pc*strlen(assembler.buff), SEEK_CUR);
  
}

}

  /*
  pos = lookup("key");
  printf("the addr of key is %p\n",pos);
  printf("the value of key=key is %s\n",pos->defn);
  */
  fclose(assembler.fp);
  return 0;
}
