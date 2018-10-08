// http://www.cs.nuim.ie/~jpower/Courses/Previous/CS310/labs/lab7/hashtable.c

/* This code implements a fairly simple hash table.
 * (Fairly simple in that there's only one of them at any time!)
 * I've taken the hashing algorithm from the Dragon Book, and I've 
 * tried to keep the interface as close as possible to Java's 
 * HashMap class.
 * The keys are always of type char * (32 chars relevant), 
 * but the contents can be anything.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

#define PRIME 65537
#define KEY_SIZE 32

/* A hash table entry: a linked list node, with a (key,value) pair */
struct Entry {
  char key[KEY_SIZE+1];
  void * value;
  struct Entry *next; // Singly-linked list
};

/* The hash-table is an array of Entry-lists */
static struct Entry *table[PRIME];

/* Current hash table size */
static int the_size = 0;


/* Hashing function from Aho, Sethi & Ullman, Fig. 7.35 */
static int hashpjw(const char *s)
{
  const char *p;
  unsigned int h = 0, g;
  for (p=s; *p != '\0'; p++) {
    h = (h << 4) + (*p);
    g = h & 0xF0000000;
    if (g != 0) {  
      h = h ^ (g >> 24);
      h = h ^ g;
    }
  }
  return h % PRIME;
}

/* Find an entry for key in the hash table; return the entry, or NULL */
static struct Entry *find(const char *key)
{
  struct Entry *curr;
  int hval = hashpjw(key);
  for (curr=table[hval]; curr!=NULL; curr=curr->next) {
    if (strncmp(key,curr->key,KEY_SIZE)==0)
      return curr;
  }
  // Not found:
  return NULL;
}



/* Return true if the hash table hash an entry for key */
int hash_containsKey(const char *key)
{
  return (find(key) != NULL);
}


/* Return the value associated with key, or NULL if it's not found */
void *hash_get(const char *key)
{
  struct Entry *curr = find(key);
  if (curr != NULL) 
      return curr->value;
  else
    return NULL;
}

/* Add a new (key,value) pair to the hash table.
 * If there's already an entry for this key, overwrite it, and return
 * the old value.  Return NULL if there wasn't an entry for key.
 */
void *hash_put(const char *key, void *value)
{
  void *old_value = NULL;
  struct Entry *curr = find(key);
  if (curr == NULL) {  // Not found, so add it (at the head)
    int hval = hashpjw(key);
    curr = (struct Entry *)malloc(sizeof(struct Entry)); 
    strncpy(curr->key, key, KEY_SIZE);
    curr->value = NULL;
    curr->next = table[hval];
    table[hval] = curr;
    the_size++;
  }
  old_value = curr->value;
  curr->value = value;
  return old_value;
}

/* Remove the entry from the hash table that's associated with key.
 * Return the corresponding value if found, or NULL otherwise 
 */
void *hash_remove(const char *key)
{
  struct Entry *curr, *prev=NULL;
  int hval = hashpjw(key);
  for (curr=table[hval]; curr!=NULL; curr=curr->next) {
    if (strncmp(key,curr->key,KEY_SIZE)==0) {
      void *old_value = curr->value;
      if (prev != NULL)
	prev->next = curr->next;
      else if (curr == table[hval])
	table[hval] = curr->next;
      free(curr);
      the_size--;
      return old_value;
    }
    prev = curr;
  }
  // Not found, so:
  return NULL;
}

/* Delete all the entries in the hash table */
void hash_clear(void)
{
  int i;
  for (i=0; i<PRIME; i++) {
    struct Entry *curr, *next;
    for (curr=table[i]; curr!=NULL; curr=next) {
      next = curr->next;
      free(curr);
    }
    table[i] = NULL; /* Otherwise it's a dangling pointer */
  }
  the_size = 0;
}

/* Return true if the hash table is empty */
int hash_isEmpty(void)
{
  return the_size == 0;
}

/* Return the number of entries currently in the hash table */
int hash_size(void)
{
  return the_size;
}



