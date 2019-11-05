#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50000

typedef struct node{
   int pnum;
   int count;
}frame;

int frameSearch(frame *Fpoint,int size, int page);
int searchNext(int *Ppoint,int start,int target);

int main(int argc, char *argv[]){
   int fsize = atoi(argv[2]);
   int access=0, read=0, write=0, hit=0, fault=0;
   int i=0,j=0, max=0,loc=0,find;
   int page[MAX_SIZE];
   frame pframe[fsize];
   float rate;
   char txt[7];
   
   FILE *fp;
   fp=fopen("access.list","r");
   
   while(fscanf(fp,"%s",txt)!=-1) 
      if(!strcmp(txt,"read")) read++;
      else if(!strcmp(txt,"write")) write++;
      else
      {
         access++;
         page[j] = atoi(txt);
         j++;
      }
   
   for(j=0; j<fsize; j++)
   {
      pframe[j].pnum = -1;
      pframe[j].count = 0;
   }
   
   
   if(!strcmp(argv[1],"belady")) //Belady's algorithm
   {
      while(loc<fsize)
      {
         find = frameSearch(pframe,fsize,page[i]);
         if(find==-1)
         {
            fault++;
            pframe[loc].pnum = page[i];
            loc++;
         }
         else hit++;
         
         i++;
      }

      for(j=0;j<fsize;j++)
         pframe[j].count = searchNext(page,i,pframe[j].pnum);      
      
      while(i<MAX_SIZE)
      {
         find = frameSearch(pframe,fsize,page[i]);
         if(find==-1)
         {
            fault++;
            
            for(j=0;j<fsize;j++)
               pframe[j].count--;
               
            for(j=0;j<fsize;j++)
               if(pframe[max].count < pframe[j].count) max =j;
               
            pframe[max].pnum=page[i];
            pframe[max].count = searchNext(page,i+1,pframe[max].pnum);
         }
         else
         {
            hit++;
            for(j=0;j<fsize;j++)
               pframe[j].count--;
         }
         
         i++;
      }
   }
   
   else if(!strcmp(argv[1],"lru")) //LRU algorithm
   {   
      while(loc<fsize)
      {
         find = frameSearch(pframe,fsize,page[i]);
         if(find==-1)
         {
            fault++;
            pframe[loc].pnum = page[i];
            for(j=0; j<=loc; j++) pframe[j].count++;
            loc++;
         }
         else
         {
            hit++;
            for(j=0; j<=loc; j++) pframe[j].count++;
            pframe[find].count=1;
         }
         i++;
      }
      
      while(i<MAX_SIZE)
      {
         find = frameSearch(pframe,fsize,page[i]);
         if(find==-1)
         {
            fault++;
            for(j=0; j<fsize; j++) pframe[j].count++;
            for(j=1; j<fsize; j++)
               if(pframe[max].count<pframe[j].count) max=j;
            pframe[max].pnum=page[i];
            pframe[max].count=1;
         }
         else
         {
            hit++;
            for(j=0; j<fsize; j++) pframe[j].count++;
            pframe[find].count =1;
         }
         i++;
      }
   }
   
   rate = (float)fault/access*100;
   printf("Total number of access : %d\n",access);
   printf("Total number of read : %d\n",read);
   printf("Total number of write : %d\n",write);
   printf("Number of page hits : %d\n",hit);
   printf("Number of page faults : %d\n",fault);
   printf("Page fault rate : %d/%d = %f",fault,access,rate);
   
   fclose(fp);
   
   return 0;
}

int frameSearch(frame *Fpoint,int size, int page)
{
   int j;
   for(j=0; j<size; j++)
      if(Fpoint[j].pnum == page) return j;
   return -1;
}

int searchNext(int *Ppoint,int start,int target)
{
   int j;
   for(j=start; j<MAX_SIZE; j++)
      if(Ppoint[j]==target) break;
      
   if(j==MAX_SIZE) return MAX_SIZE;
   else return j-start;
}
