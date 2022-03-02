//SUNG CHAN CHOI 201824641
#include "cachelab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

struct Cache
{
   int hit;
   int evict;
   int miss;
   int time;

   int numSets;
   struct Set* sets;
};

struct Line
{
   int valid;
   int tag;
   int when;
   long long data;
};

struct Set
{
   struct Line* line;
};

void InitCache(struct Cache* cache, int s, int E);
void InitLine(struct Cache* cache, int E);
void Simulate(struct Cache* cache, unsigned long long address, int s, int b, int E);
void deleteCache(struct Cache* cache, int E);


int main(int argc, char **argv)
{
    int set, line, block;
    char* trace;
    int option = 0;
    char inst;
    unsigned long long address;
    FILE *fp = NULL;
    struct Cache cache;


    while((option = getopt(argc, argv, "s:E:b:t:"))!= EOF)
    {
        switch(option)
        {
                case 's': set = atoi(optarg); break;
                case 'E': line = atoi(optarg); break;
                case 'b': block = atoi(optarg); break;
                case 't': trace = optarg;
        }
    }

    InitCache(&cache, set, line);

    fp = fopen(trace, "r");
    if(fp != NULL)
    {
        while(fscanf(fp, " %c %llx, %*d", &inst, &address))
        {
            switch(inst)
            {
                case 'L':
                case 'S': Simulate(&cache, address, set, block, line); break;
                case 'M': Simulate(&cache, address, set, block, line); Simulate(&cache, address, set, block, line); break;

            }
        }
    }



    printSummary(cache.hit, cache.miss, cache.evict);
    deleteCache(&cache, line);
    return 0;
}

void deleteCache(struct Cache* cache, int E)
{
    int i = 0;
    int j = 0;
    for(; i < cache->numSets; ++i)
    {
        free(cache->sets[i].line);
    }
    free(cache->sets);
}

void InitCache(struct Cache* cache, int s, int E)
{
   cache->hit = 0;
   cache->evict = 0;
   cache->miss = 0;
   cache->time = 0;

   cache->numSets = (1 << s);
   cache->sets = (struct Set*)malloc(sizeof(struct Set) * cache->numSets);
   InitLine(cache, E);
}

void InitLine(struct Cache* cache, int E)
{
   int i;
   int j;
   for(i = 0; i < cache->numSets; ++i)
   {
      cache->sets[i].line = (struct Line*)malloc(sizeof(struct Line) * E);
      for(j = 0; j < E; ++j)
      {
         cache->sets[i].line[j].valid = 0;
         cache->sets[i].line[j].tag = 0;
         cache->sets[i].line[j].when = 0;
         cache->sets[i].line[j].data = 0;
      }
   }
}

void Simulate(struct Cache* cache, unsigned long long address, int s, int b, int E)
{
   int tag = address >> (s+b);
   int set_index = (address >> b) - (tag << s);
   int data = ~(~0 << b) & address;
   int i;
   int ishit = 0;
   int iscold = 1;
   int timestamp = cache->sets[set_index].line[0].when;
   int oldestidx = 0;
   cache->time += 1;

   for(i = 0; i < E; ++i)
   {
       if(cache->sets[set_index].line[i].valid)
       {
           iscold = 0;
           if(cache->sets[set_index].line[i].tag == tag && cache->sets[set_index].line[i].data == data)
           {
              cache->hit += 1;
              cache->sets[set_index].line[i].when = cache->time;
              ishit = 1;
              break;
           }
       }
       else
       {
           oldestidx = i;
           break;
       }

       if(timestamp > cache->sets[set_index].line[i].when)
       {
           timestamp = cache->sets[set_index].line[i].when;
           oldestidx = i;
       }
   }
   if(!ishit)
   {
       cache->miss += 1;

       if(!iscold)
       {
           cache->evict += 1;
       }
       cache->sets[set_index].line[oldestidx].valid = 1;
       cache->sets[set_index].line[oldestidx].tag = tag;
       cache->sets[set_index].line[oldestidx].when = cache->time;
       cache->sets[set_index].line[oldestidx].data = data;
   }

}

void printSummary(int hits, int misses, int evictions)
{
    printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
    FILE* output_fp = fopen(".csim_results", "w");
    assert(output_fp);
    fprintf(output_fp, "%d %d %d\n", hits, misses, evictions);
    fclose(output_fp);
}
