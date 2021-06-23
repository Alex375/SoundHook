//
// Created by Noé Bonne on 6/20/21.
//

#ifndef SOUNDHOOK_MEDIATOR_H
#define SOUNDHOOK_MEDIATOR_H

//Customize for your data Item type
typedef double Item;
#define ItemLess(a,b)  ((a)<(b))
#define ItemMean(a,b)  (((a)+(b))/2)

typedef struct Mediator_t
{
    Item* data;  //circular queue of values
    int*  pos;   //index into `heap` for each value
    int*  heap;  //max/median/min heap holding indexes into `data`.
    int   N;     //allocated size.
    int   idx;   //position in circular queue
    int   ct;    //count of items in queue
} Mediator;


Mediator* MediatorNew(int nItems);

void MediatorInsert(Mediator* m, Item v);

Item MediatorMedian(Mediator* m);

void ShowTree(Mediator* m);



/*--- Helper Functions ---*/

#define minCt(m) (((m)->ct-1)/2) //count of items in minheap
#define maxCt(m) (((m)->ct)/2)   //count of items in maxheap

#endif //SOUNDHOOK_MEDIATOR_H
