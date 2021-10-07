#ifndef LIST_H
#define LIST_H
#include <stddef.h>

/*
 * Simple circular doubly linked list implementation.
 *
 */

struct ListHead
{
  struct ListHead *next, *prev;
};

static void InitListHead(struct ListHead *head)
{
  head->next = head;
  head->prev = head;
}

/*
 * Insert a new entry after specified entry.
 */
static void ListAdd(struct ListHead *new, struct ListHead *entry)
{
  struct ListHead *tmp = entry->next;
  entry->next->prev = new;
  entry->next = new;
  new->prev = entry;
  new->next = tmp;
}

static void ListDel(struct ListHead *entry)
{
  entry->prev->next = entry->next;
  entry->next->prev = entry->prev;
}

#define LIST_ENTRY(ptr, type, member) \
        (type *)((char *)ptr - offsetof(type, member))

#endif
