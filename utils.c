#include "utils.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "raymath.h"

void printLinkedList(Node* head)
{
  printf("Printing Linked List");

  Node* current = head;

  while(current != NULL)
  {
    printf("\n%f %f %f\n", current->point.pos.x, current->point.pos.y, current->point.pos.z);
    current = current->next;
  }
  printf("Linked List printed\n\n");
}

void pushEnd(Node** head, struct Point newPoint)
{
  //empty list case
  if (*head == NULL)
  {
    *head = (Node*)malloc(sizeof(Node));
    (*head)->point = newPoint;
    (*head)->next = NULL;
    return;
  }

  Node* current = *head;

  while (current->next != NULL)
  {
    current = current->next;
  }

  current->next = (Node*)malloc(sizeof(Node));
  current->next->point = newPoint;
  current->next->next = NULL;
}

bool popBack(Node** head)
{
  //no head case 
  if (*head == NULL)
  {
    return false;
  }

  //only one item in list case
  if((*head)->next == NULL)
  {
    free(*head);
    *head = NULL;
    return true;
  }

  //get to second last item in the list  
  Node* current = *head;
  while(current->next->next != NULL)
  {
    current = current->next;
  }

  free(current->next);
  current->next = NULL;
  return true;
}

void deleteLinkedList(Node** head)
{
  Node* current = *head;
  Node* next = NULL;

  while(current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }

  *head = NULL;
}
