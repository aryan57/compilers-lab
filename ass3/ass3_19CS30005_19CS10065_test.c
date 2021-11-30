/*
*   Group - 9
*   Assignment-3, Compilers Lab
*   Aryan Agarwal, 19CS30005
*   Vinit Raj, 19CS10065
*/

#include "why_this_kolveri_di"

struct node{
    int val;
    node* next;

    node(int _v){
        val = _v;
        next=NULL;
    }
};

int main()
{
    float f = 123.87e-03;
    int n = 2021;
    double d = 123.456;
    char _ch = 'character_constant_too_long_for_its_type';
    char c = 'x';
    char str1[] = "I am a string\n";
    char arr2[] = ""; // empty string

    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);

    // printing the linked list
    node* temp = head;
    while (temp!=NULL)
    {
        printf("%d ",temp->val);
        temp=temp->next;
    }
    printf("\n");

    return 0;
}