// This program creates a 5 layered skiplist
// Created By: Evan Bicher
// Date: April 1, 2015

#include <limits>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <climits>
using namespace std;

struct Data
{
    int value;
    Data *greater;
    Data *less;
    Data *above;
    Data *below;
};

class Skiplist
{	protected:
    Data *high;
    Data *low;
    int amount;
public:
    Skiplist(void);
    void SkiplistInsertion (int);
    void SkiplistDeletion (int);
    Data * search (int);
    void print (void);
    Data * doit (Data *, int);
    void coinflip (Data *);
    void rep (Data *);
    bool isInList (int);
    int amt (void);
    
};


// Builds the skiplist, the height of 5. The top left node is named "low" and the top right is named "high".

Skiplist::Skiplist()
{
    amount = 2;
    
    Data *a;
    Data *b;
    Data *c;
    Data *d;
    Data *w;
    Data *x;
    Data *y;
    Data *z;
    a = new Data;
    b = new Data;
    c = new Data;
    d = new Data;
    high = new Data;
    w = new Data;
    x = new Data;
    y = new Data;
    z = new Data;

    
    low = new Data;
    low->value = INT32_MIN;
    low->above = NULL;
    low->below = a;
    low->less = NULL;
    low->greater = high;
    
    a->above = low;
    a->below = b;
    a->value = low->value;
    a->greater = w;
    a->less = NULL;
    

    b->above = a;
    b->below = c;
    b->value = low->value;
    b->greater = x;
    b->less = NULL;
    
 
    c->above = b;
    c->below = d;
    c->value = low->value;
    c->greater = y;
    c->less = NULL;
    
  
    d->above = c;
    d->below = NULL;
    d->value = low->value;
    d->greater = z;
    d->less = NULL;
    
 
    high->value = INT32_MAX;
    high->above = NULL;
    high->below = w;
    high->less = low;
    high->greater = NULL;
    
    w->above = high;
    w->below = x;
    w->value = high->value;
    w->greater = NULL;
    w->less = a;
    w->greater = NULL;
    
    
    x->above = w;
    x->below = y;
    x->value = high->value;
    x->less = b;
    x->greater = NULL;
    
 
    y->above = x;
    y->below = z;
    y->value = high->value;
    y->less = c;
    y->greater = NULL;
    
    z->above = y;
    z->below = NULL;
    z->value = high->value;
    z->less = d;
    z->greater = NULL;
    
}

int
Skiplist::amt()
{
    return (amount - 2);
}

// Print function that prints each level of the skip list and which values are in each level. This does this by
// marching down the list from the top left (low).

void
Skiplist::print()
{
    Data *i;
    Data *q;
    i = low;
    q = i;
    
    while (i->below != NULL) {
        q = i->greater;
        cout << "     *head*     ";
        while (q->value != high->value)
        {
            cout << q->value << " ";
            q = q->greater;
        }
        cout << "     *head*     ";
        cout << endl;
        i = i->below;
    }
    
    q = i->greater;
            cout << "     *head*     ";
    while (q->value != high->value)
    {
        cout << q->value << " ";
        q = q->greater;
    }
            cout << "     *head*     ";
    
}

// Search function calls doit, which recurisively calls itself and searchs for a number and returns the
// pointer to it.
Data *
Skiplist::search(int num)
{
   Data *here = doit(low, num);
    return here;
 
    
}

// Called by the insert function which takes the data piece with a value less then the value searched for
// then sees what the value is that is closest to the searched for value, that is still less then the value,
// then it recalls itself with those. Until it reaches the bottom level.

Data *
Skiplist::doit(Data *thing, int numy)
{
    
    while (thing->value != numy) {
        
        while (thing->value <= numy)
        {
            thing = thing->greater;
        }
            thing = thing->less;
        
        if (thing->below != NULL)
        {
            thing = thing->below;
        }
        else
        {
            break;
        }
    }
    return thing;
    
}

// Function that searches for a number, if found, it returns true. Else, it returns false.

bool
Skiplist::isInList(int num)
{
    Data *a = search(num);
    if (a->value == num || a->greater->value == num) {
        return true;
    }
    else    return false;
}

// Insert function that takes a number, and creates a struct for it and calls coinflip which calls itself
// recursively to build a tower
void
Skiplist::SkiplistInsertion(int num)
{
    Data *before;
    Data *after;
    Data *newone;
    newone = new Data;
    newone->value = num;
    
    before = search(num);
    amount++;
    after = before->greater;
    newone->less = before;
    newone->greater = after;
    after->less = newone;
    before->greater = newone;
    newone->below = NULL;
    
    coinflip(newone);
    
    
}



// Flips a coin and builds a new node above the node introduced. Will only run if it passes the test, then it
// calls itself recursively.
void
Skiplist::coinflip(Data *starter)
{
    
    int flip;
    flip=  rand() % 2 + 1;
    int lvls = 1;
    Data *checker;
    checker = starter;
    
    while (checker->below != NULL) {
        lvls++;
        checker = checker->below;
    }
    
    if (flip == 1 && lvls < 4)
    {
        Data *before;
        Data *after;
        after = starter->greater;
        before = starter->less;
        
        Data *newer;
        newer = new Data;
        newer->value = starter->value;
        newer->below = starter;
        starter->above = newer;
        newer->above = NULL;
        
        while (before->above == NULL)
        {
            before = before->less;
            if (before == low)
                break;
        }
        
        while (after->above == NULL)
        {
            after = after->greater;
            if (after == high)
                break;
        }
        
        newer->less = before->above;
        newer->greater = after->above;
        after = after->above;
        after->less = newer;
        before = before->above;
        before->greater = newer;
        
        coinflip(newer);
    }
    
}

// Delete function which calls the function rep, which recursivly walks down the list deleting the node and
// setting it's neighbors to each other.
void
Skiplist::SkiplistDeletion(int num)
{
    Data *d = search(num);
    if (d->value == num)
    {
        while (d->above != NULL)
        {
            d = d->above;
        }
        rep(d);
    }
}

// Recursive deleting function that calls itself until it is on the bottom level.

void
Skiplist::rep(Data *de)
{
    Data *a;
    Data *b;
    Data *c;
    
    a = de->less;
    b = de->greater;
    a->greater = b;
    b->less = a;
    
    if (de->below != NULL)
    {
        c = de->below;
        delete de;
        rep(c);
    }
}


// Main function that gives the user options of how to access and alter the skiplist

int
main()
{
    Skiplist test;
    bool check;
    char dowhat;
    int x = 3;

    
    while(dowhat != '0')
    {
        cout << "\n To input numbers, press 1";
        cout << "\n To print list, press 2";
        cout << "\n To delete numbers, press 3";
        cout << "\n To search for a number, press 4";
        cout << "\n To end the program, press 0";
        cout << "\n What do you want to do: ";
        
        cin >> dowhat;
        cout << endl;
        
        switch(dowhat)
        {
            case '1':
    
                x = 3;
                while(x!=0)
                {
                    cout << "Input number (0 to stop): ";
                    cin >> x;
                    if (x!=0)
                        test.SkiplistInsertion(x);
            
                }
                break;
                
            case '2':
                
                cout << "The numbers are : " << endl;
                test.print();
                cout <<endl;
                break;
    
            case '3':
                
                x = 3;
                while(x!=0)
                {
                    cout << "Input number to delete (0 to stop): ";
                    cin >> x;
                    if (x!=0)
                        test.SkiplistDeletion(x);
                }
                break;
                
            case '4':
                
                x = 3;
                while(x!=0)
                {
                    cout << "Input number to search for (returns True of False): ";
                    cin >> x;
                    if (x!=0)
                    {
                        check = test.isInList(x);
                        if (check == true) {
                            cout << "True" << endl;
                        }
                        else {cout << "False" << endl;}
                    }
                }
                break;
                
            case '0':
                
                dowhat = '0';
                cout << "Goodbye" <<endl;
                break;
            
            default:
                
                cout << "Incorrect value" << endl;
                break;
        }
        
    }

   cout << test.amt();
    
    
    return 1;
    
}





