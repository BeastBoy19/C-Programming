#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int STEPSIZE=100;
char **loadfile(char *);
int main(int argc, char *argv[])
{
    if(argc==1){
        fprintf(stderr,"Must supply a filename to read.\n");
        exit(1);
    }
    char **word=loadfile(argv[1]);
    if(!word)
    {
        fprintf(stderr,"cant build data structure\n");
        exit(1);
    }
    for(int i=0;word[i]!=NULL;i++)
    {
        printf("%s\n",word[i]);
    }
    printf("Done\n");
}
char **loadfile(char *filename){
    int arrlen=0;
    FILE *f=fopen(filename,"r");
    if(!f){
        fprintf(stderr,"Cant open %s file.\n",filename);
        return NULL;
    }
    char **lines=NULL;
    // char **lines = (char **)malloc(arrlen * sizeof(char *));
    // char **lines = (char **)realloc(NULL,arrlen * sizeof(char *));
    char buf[1000];
    int i=0;
    while(fgets(buf,1000,f))
    {
        if (i == arrlen)
        {
            arrlen+=STEPSIZE;
            char **newlines = (char**)realloc(lines, arrlen * sizeof(char *));
            if(!newlines)
            {
                fprintf(stderr,"cant reallocate.\n");
                exit(1);
            }
            lines=newlines;
        }
        buf[strlen(buf)-1]='\0';
        int slen=strlen(buf);
        char *str = (char *)malloc((slen+1) * sizeof(char));
        strcpy(str,buf);
        lines[i]=str;
        i++;
    }
    if(i==arrlen)
    {
        char **newarr=(char**)realloc(lines,(arrlen+1)*sizeof(char*));
        if (!newarr)
        {
            fprintf(stderr, "cant reallocate.\n");
            exit(1);
        }
        lines = newarr;
    }
    lines[i]=NULL;
    return lines;
}