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

void pushEnd(Node* head, struct Point newPoint)
{
  Node* current = head;

  while (current->next != NULL)
  {
    current = current->next;
  }

  current->next = (Node*)malloc(sizeof(Node));
  current->next->point = newPoint;
  current->next->next = NULL;
}

void pushFront(Node** head, struct Point newPoint)
{
  Node* newNode;

  newNode = (Node*)malloc(sizeof(Node));

  newNode->point = newPoint;
  newNode->next = *head;
  *head = newNode;
}

bool popFront(Node** head)
{

  Node* nextNode = NULL;

  if(*head == NULL)
  {
    return false;
  }

  nextNode = (*head)->next;
  free(*head);
  *head = nextNode;

  return true;
}

bool popBack(Node* head)
{
  //no head case 
  if (head == NULL)
  {
    return false;
  }

  //only one item in list case
  if(head->next == NULL)
  {
    free(head);
    return true;
  }

  //get to second last item in the list  
  Node* current = head;
  while(current->next->next != NULL)
  {
    current = current->next;
  }

  free(current->next);
  current->next = NULL;
  return true;
}

bool removeNodeByVectorValue(Node** head, Vector3 pos)
{
  //no head case
  if (*head == NULL)
  {
    return false;
  }

  Node* current = *head;
  Node* temp = NULL;

  //one node case
  if (Vector3Equals(current->point.pos, pos))
  {
    temp = current;
    *head = current->next;
    free(temp);
    return true;
  }

  //find the node and remove
  while (current->next != NULL)
  {
    if (Vector3Equals(current->next->point.pos, pos))
    {
      temp = current->next;
      current->next = temp->next;
      free(temp);
      return true;
     }

     current = current->next;
   }

  return false;
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
