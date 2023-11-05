#ifndef BIGINT_H
#define BIGINT_H
struct node
{
    int data;
    struct node *next, *prev;
};
struct node *createNewNode(int);
struct node *NumberToList(char []);
struct node *reverseList(struct node *);
struct node *add(char [], char []);
struct node *subtract(char [], char []);
struct node *multiply(char [], char []);
int lengthOfList(struct node *);
int isGreaterEqualFirstNum(struct node *, struct node *);
struct node *divide(char [], char []);
struct node *modulus(char [], char []);
void print(struct node *);
#endif