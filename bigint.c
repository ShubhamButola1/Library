#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bigint.h"

struct node *createNewNode(int value)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (!temp)
        return NULL;
    temp->data = value;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

struct node *reverseList(struct node *head)
{
    if (!head)
        return NULL;
    struct node *newList = NULL, *temp;
    while (head)
    {
        temp = createNewNode(head->data);
        if (!newList)
        {
            newList = temp;
        }
        else
        {
            temp->next = newList;
            newList->prev = temp;
            newList = temp;
        }
        head = head->next;
    }
    return newList;
}

struct node *NumberToList(char num[])
{
    struct node *head = NULL, *temp, *itr;
    int i, charToNum;

    int negative = 0;
    for (i = 0; i < strlen(num); i++)
    {
        if (num[i] == '-')
        {
            negative = 1;
            i++;
        }
        if (negative)
        {
            charToNum = -1 * ((int)num[i] - 48);
        }
        else
        {
            charToNum = (int)num[i] - 48;
        }
        temp = createNewNode(charToNum);
        if (!head)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }
    return head;
}

struct node *revertSign(struct node *head)
{
    struct node *itr = head;
    while (itr)
    {
        itr->data = -1 * itr->data;
        itr = itr->next;
    }
    return head;
}

int lengthOfList(struct node *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

int isGreaterEqualFirstNum(struct node *temp1, struct node *temp2)
{
    // to remove extra 0s in temp1
    // if temp1 = 00 and temp2 = 3 then length of temp1 is greater than temp2
    // so we have to remove leading zeros
    while(temp1->data==0 && temp1->next!=NULL) 
    {   
        temp1 = temp1->next;
    }
    if (lengthOfList(temp1) > lengthOfList(temp2))
        return 1;
    if (lengthOfList(temp1) < lengthOfList(temp2))
        return 0;
    if (lengthOfList(temp1) == lengthOfList(temp2))
    {
        while (temp1 != NULL)
        {
            if (temp1->data > temp2->data)
            {
                return 1;
            }
            if (temp1->data < temp2->data)
            {
                return 0;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    return 2; // return 2 when both are equal or temp1 has more digits i.e. temp1>temp2
}

struct node *add(char n1[], char n2[])
{
    struct node *result = NULL, *temp, *itr;
    struct node *num1 = NumberToList(n1);
    struct node *num2 = NumberToList(n2);

    int len1 = strlen(n1) - 1;
    int len2 = strlen(n2) - 1;
    if (n1[0] == '-')
        len1--;
    if (n2[0] == '-')
        len2--;

    int reverted = 0;

    if (len1 == len2)
    {
        if (n1[0] == '-' && n2[0] == '-') // if both nums are -ve
        {
            int i = 1, flag = 0;
            while (i < len1 + 1)
            {
                if (n1[i] > n2[i])
                    break;
                if (n1[i] < n2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct node *temp = num1;
                num1 = num2;
                num2 = temp;
            }
        }

        else if (n1[0] == '-' && n2[0] != '-') // if 1st is -ve & 2nd is +ve
        {
            int i = 1, flag = 0;
            while (i < len1 + 1) // or i<len2 because len1 == len2
            {
                if (n1[i] > n2[i - 1])
                    break;
                if (n1[i] < n2[i - 1])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct node *temp = num1;
                num1 = num2;
                num2 = temp;
            }
            else
            {
                num1 = revertSign(num1);
                num2 = revertSign(num2);
                reverted = 1;
            }
        }

        else if (n1[0] != '-' && n2[0] == '-') // if 1st is +ve and 2nd is -ve
        {
            int i = 1, flag = 0;
            while (i < len1 + 1)
            {
                if (n1[i - 1] > n2[i])
                    break;
                if (n1[i - 1] < n2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct node *temp = num1;
                num1 = num2;
                num2 = temp;
                num1 = revertSign(num1);
                num2 = revertSign(num2);
                reverted = 1;
            }
        }

        else if ((n1[0] < n2[0]) && (n1[0] != '-' && n2[0] != '-')) // this will only execute if both the numbers are positive
        {
            struct node *temp = num1;
            num1 = num2;
            num2 = temp;
        }
        else if ((n1[0] == n2[0]) && (n1[0] != '-' && n2[0] != '-')) // this will execute if both are positive and 1st is equal
        {
            int i = 1, flag = 0;
            while (i < len1)
            {
                if (n1[i] < n2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct node *temp = num1;
                num1 = num2;
                num2 = temp;
            }
        }
    }

    else if (len1 < len2) // if num2 is bigger than num1 swap those (ignoring -ve)
    {
        struct node *temp = num1;
        num1 = num2;
        num2 = temp;
        if (n1[0] != '-' && n2[0] == '-') // if num2 is -ve than revert the sign
        {
            num1 = revertSign(num1);
            num2 = revertSign(num2);
            reverted = 1;
        }
    }

    num1 = reverseList(num1);
    num2 = reverseList(num2);
    if (num1->data < 0)
    {
        num1 = revertSign(num1);
        num2 = revertSign(num2);
        reverted = 1;
    }
    num1 = reverseList(num1);
    num2 = reverseList(num2);

    if (!num1)
    {
        result = num2;
        return result;
    }
    if (!num2)
    {
        result = num1;
        return result;
    }
    if (!num1 && !num2)
        return NULL;

    while (num1 && num2)
    {
        // if ((num1->data + num2->data < 0) && num1->data>=0 && num2->data>=0)
        if ((num1->data + num2->data < 0) && (num1->data >= 0 || num2->data >= 0))
        {
            struct node *itr = num1->next;
            while (itr->data == 0)
                itr = itr->next;
            itr->data = itr->data - 1;
            while (itr != num1)
            {
                itr = itr->prev;
                if (itr == num1)
                    break;
                itr->data = itr->data + 10 - 1;
            }
            num1->data = num1->data + 10;
        }

        temp = createNewNode(num1->data + num2->data);
        // chceck if temp is NULL;
        if (!result)
        {
            result = temp;
            itr = result;
        }
        else
        {
            itr->next = temp;
            temp->prev = itr;
            if (itr->data > 9 || itr->data < -9)
            {
                temp->data = temp->data + itr->data / 10; // itr->next->data = itr->next->data+1;
                itr->data = itr->data % 10;
            }
            itr = itr->next;
        }
        num1 = num1->next;
        num2 = num2->next;
    }
    while (num1)
    {
        temp = createNewNode(num1->data);
        if (itr->data > 9 || itr->data < -9)
        {
            temp->data = temp->data + itr->data / 10; // temp->data + 1;
            itr->data = itr->data % 10;
        }
        temp->prev = itr;
        itr->next = temp;
        itr = itr->next;
        num1 = num1->next;
    }
    while (num2)
    {
        temp = createNewNode(num2->data);
        if (itr->data > 9 || itr->data < -9)
        {
            temp->data = temp->data + itr->data / 10; // temp->data + 1;
            itr->data = itr->data % 10;
        }
        temp->prev = itr;
        itr->next = temp;
        itr = itr->next;
        num2 = num2->next;
    }

    if (reverted)
    {
        result = revertSign(result);
    }
    return result;
}

struct node *subtract(char n1[], char n2[])
{
    struct node *result = NULL, *temp, *itr;
    struct node *num1 = NumberToList(n1);
    struct node *num2 = NumberToList(n2);

    int isAnswerNegative = 0;
    if (isGreaterEqualFirstNum(num1, num2))
    {
        isAnswerNegative = 0;
    }
    if (isGreaterEqualFirstNum(num2, num1))
    {
        isAnswerNegative = 1;
    }
    int len1 = strlen(n1) - 1;
    int len2 = strlen(n2) - 1;
    if (n1[0] == '-')
        len1--;
    if (n2[0] == '-')
        len2--;

    if (len1 == len2)
    {
        if (n1[0] == '-' && n2[0] == '-')
        {
            int i = 1, flag = 0;
            while (i < len1 + 1) // or len2 both are equal
            {
                if (n1[i] > n2[i])
                    break;
                if (n1[i] < n2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct node *temp = num1;
                num1 = num2;
                num2 = temp;
                num1 = revertSign(num1);
                num2 = revertSign(num2);
            }
        }

        else if (n1[0] == '-' && n2[0] != '-') // if 1st is -ve and 2nd is +ve
        {
            int i = 1, flag = 0;
            while (i < len1 + 1) // or len2 both are equal
            {
                if (n1[i] > n2[i - 1])
                    break;
                if (n1[i] < n2[i - 1])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct node *temp = num1;
                num1 = num2;
                num2 = temp;
            } /*  */
        }

        else if (n1[0] != '-' && n2[0] == '-') // if 1st is +ve and 2nd is -ve
        {
            int i = 1, flag = 0;
            while (i < len1 + 1)
            {
                if (n1[i - 1] > n2[i])
                    break;
                if (n1[i - 1] < n2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct node *temp = num1;
                num1 = num2;
                num2 = temp;
                num1 = revertSign(num1);
                num2 = revertSign(num2);
            }
        }

        else if ((n1[0] < n2[0]) && (n1[0] != '-' && n2[0] != '-')) // this will only execute if both the numbers are positive
        {
            struct node *temp = num1;
            num1 = num2;
            num2 = temp;
        }

        else if ((n1[0] == n2[0]) && (n1[0] != '-' && n2[0] != '-')) // this will execute if both are positive and 1st digit is equal
        {
            int i = 1, flag = 0;
            // we will iterate to check if 2nd number is greater than first or not
            while (i < len1)
            {
                if (n1[i] < n2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct node *temp = num1;
                num1 = num2;
                num2 = temp;
            }
        }
    }

    else if (len1 < len2) // if num2 is bigger than num1 swap those (ignoring -ve)
    {
        struct node *temp = num1;
        num1 = num2;
        num2 = temp;
    }

    // check if num1 is -ve then revert both numbers sign
    num1 = reverseList(num1);
    num2 = reverseList(num2);
    if (num1->data < 0)
    {
        num1 = revertSign(num1);
        num2 = revertSign(num2);
    }
    num1 = reverseList(num1);
    num2 = reverseList(num2);

    if (!num1) // if num1 is 0
    {
        result = num2;
        return result;
    }
    if (!num2) // if num2 is 0
    {
        result = num1;
        return result;
    }
    if (!num1 && !num2) // if num1 & num2 both are 0
    {
        return NULL;
    }

    while (num1 && num2)
    { // copy data in new list by performing subtraction in num1 and num2
        if (num1->data < num2->data)
        {
            struct node *itr = num1->next;
            while (itr->data == 0)
            {
                itr = itr->next;
            }
            itr->data = itr->data - 1;
            while (itr != num1)
            {
                itr = itr->prev;
                if (itr == num1)
                    break;
                itr->data = itr->data + 10 - 1;
            }
            num1->data = num1->data + 10;
        }

        temp = createNewNode(num1->data - num2->data);

        if (!result)
        {
            result = temp;
            itr = result;
        }
        else
        {
            itr->next = temp;
            temp->prev = itr;
            if (itr->data < -9 || itr->data > 9)
            {
                temp->data = temp->data + itr->data / 10;
                itr->data = itr->data % 10;
            }
            itr = itr->next;
        }
        num1 = num1->next;
        num2 = num2->next;
    }

    while (num1) // if num 2 is exhausted but num1 is not exhausted copy num1 in result
    {
        temp = createNewNode(num1->data);
        if (itr->data < -9 || itr->data > 9)
        {
            temp->data = temp->data + itr->data / 10; // temp->data + 1;
            itr->data = itr->data % 10;
        }
        temp->prev = itr;
        itr->next = temp;
        itr = itr->next;
        num1 = num1->next;
    }

    while (num2) // if num 1 is exhausted but num2 is not exhausted copy num2 in result
    {
        temp = createNewNode(num2->data);
        if (itr->data < -9 || itr->data > 9)
        {
            temp->data = temp->data + itr->data / 10;
            itr->data = itr->data % 10;
        }
        temp->prev = itr;
        itr->next = temp;
        itr = itr->next;
        num2 = num2->next;
    }

    // if (reverted) // if we have reverted sign of lists earlier then revert the sign of result
    // {
    //     printf("I've inside reverted but not reverted sign\n");
    //     // printf("I have reverted the sign\n");
    //     // result = revertSign(result);
    // }

    if (isAnswerNegative == 1)
        result = revertSign(result);
    return result;
}

struct node *multiply(char n1[], char n2[])
{
    struct node *result = NULL, *resultItr;
    struct node *num1 = NumberToList(n1); // converts n1 string into a linklist having digits
    struct node *num2 = NumberToList(n2); // converts n2 string into a linklist having digits
    struct node *num1Pointer = num1;
    struct node *num2Pointer = num2;

    // here Both list have sbeen converted to +ve for easy calculation
    // later we will convert the result according to sign of num1 and num2
    int isNegative = 0;
    if (n1[0] == '-' && n2[0] != '-')
    {
        num1 = revertSign(num1);
        isNegative = 1;
    }
    if (n1[0] != '-' && n2[0] == '-')
    {
        num2 = revertSign(num2);
        isNegative = 1;
    }
    if (n1[0] == '-' && n2[0] == '-')
    {
        num1 = revertSign(num1);
        num2 = revertSign(num2);
        isNegative = 0;
    }

    struct node *temp1 = NULL, *temp2 = NULL;
    struct node *temp1Pointer, *temp2Pointer;
    while (num2Pointer != NULL)
    {
        if (temp1 == NULL)
        {
            while (num1Pointer != NULL) // multiply num1 with first digit of num2 and store in temp1
            {
                struct node *newNode = createNewNode(num1Pointer->data * num2Pointer->data);
                if (temp1 == NULL)
                {
                    temp1 = newNode;
                    temp1Pointer = temp1;
                }
                else
                {
                    if (temp1Pointer->data > 9)
                    {
                        newNode->data = newNode->data + temp1Pointer->data / 10;
                        temp1Pointer->data = temp1Pointer->data % 10;
                    }
                    newNode->prev = temp1Pointer;
                    temp1Pointer->next = newNode;
                    temp1Pointer = temp1Pointer->next;
                }
                num1Pointer = num1Pointer->next;
            }
            if (temp1Pointer->data > 9)
            {
                struct node *newNode = createNewNode(temp1Pointer->data / 10);
                temp1Pointer->data = temp1Pointer->data % 10;
                newNode->prev = temp1Pointer;
                temp1Pointer->next = newNode;
            }

            num1Pointer = num1;
            num2Pointer = num2Pointer->next;
        }

        if (num2Pointer != NULL)
        {
            temp2 = NULL;
            while (num1Pointer != NULL)
            {
                struct node *newNode = createNewNode(num1Pointer->data * num2Pointer->data);
                if (temp2 == NULL)
                {
                    temp2 = newNode;
                    temp2Pointer = temp2;
                }
                else
                {
                    if (temp2Pointer->data > 9)
                    {
                        newNode->data = newNode->data + temp2Pointer->data / 10;
                        temp2Pointer->data = temp2Pointer->data % 10;
                    }
                    newNode->prev = temp2Pointer;
                    temp2Pointer->next = newNode;
                    temp2Pointer = temp2Pointer->next;
                }
                num1Pointer = num1Pointer->next;
            }
            if (temp2Pointer->data > 9)
            {
                struct node *newNode = createNewNode(temp2Pointer->data / 10);
                temp2Pointer->data = temp2Pointer->data % 10;
                newNode->prev = temp2Pointer;
                temp2Pointer->next = newNode;
            }
            num1Pointer = num1;
            num2Pointer = num2Pointer->next;
            // till here I've two list temp1 is the list multiply num1 with first digit of num2
            // and temp2 is multiply num1 with second digits of num2
        }

        // add first digit of temp1 in the result
        struct node *temp = createNewNode(temp1->data);
        struct node *itr = temp1;
        temp1 = temp1->next;
        free(itr);
        if (temp1 != NULL)
            temp1->prev = NULL;

        if (result == NULL)
        {
            result = temp;
            resultItr = result;
        }
        else
        {
            //  appending first digit of temp1 to the result list
            temp->prev = resultItr;
            resultItr->next = temp;
            resultItr = resultItr->next;
        }

        // swap temp1 and temp2
        if (temp2 != NULL)
        {
            struct node *forSwapping = temp1;
            temp1 = temp2;
            temp2 = forSwapping;
        }

        temp1Pointer = temp1, temp2Pointer = temp2; // pointing temp1 and temp2 pointers to the first node
        struct node *sumOfTemps = NULL, *sumItr;
        // for adding temp1 and temp2
        while (temp1Pointer != NULL && temp2Pointer != NULL)
        {
            struct node *newNode = createNewNode(temp1Pointer->data + temp2Pointer->data);
            if (sumOfTemps == NULL)
            {
                sumOfTemps = newNode;
                sumItr = sumOfTemps;
            }
            else
            {
                if (sumItr->data > 9)
                {
                    newNode->data = newNode->data + sumItr->data / 10;
                    sumItr->data = sumItr->data % 10;
                }
                newNode->prev = sumItr;
                sumItr->next = newNode;
                sumItr = sumItr->next;
            }
            temp1Pointer = temp1Pointer->next;
            temp2Pointer = temp2Pointer->next;
        }

        while (temp1Pointer != NULL) // adding remaining digits of temp1 to sumOfTemp
        {
            struct node *newNode = createNewNode(temp1Pointer->data);
            if (sumOfTemps == NULL)
            {
                sumOfTemps = newNode;
                sumItr = sumOfTemps;
            }
            else
            {
                if (sumItr->data > 9)
                {
                    newNode->data = newNode->data + sumItr->data / 10;
                    sumItr->data = sumItr->data % 10;
                }
                newNode->prev = sumItr;
                sumItr->next = newNode;
                sumItr = sumItr->next;
            }
            temp1Pointer = temp1Pointer->next;
        }

        temp1 = sumOfTemps;
    }

    while (temp1 != NULL)
    {
        struct node *newNode = createNewNode(temp1->data);
        newNode->prev = resultItr;
        resultItr->next = newNode;
        resultItr = resultItr->next;
        temp1 = temp1->next;
    }

    if (isNegative) // if answer should be negative then it will convert it to negative
        result = revertSign(result);
    return result;
}

struct node *divide(char n1[], char n2[])
{
    struct node *result = NULL;
    struct node *num1 = NumberToList(n1);
    struct node *num2 = NumberToList(n2);

    int isNegativeAnswer = 0;
    if (n1[0] == '-' && n2[0] != '-')
    {
        isNegativeAnswer = 1;
        num1 = revertSign(num1);
    }
    if (n1[0] != '-' && n2[0] == '-')
    {
        isNegativeAnswer = 1;
        num2 = revertSign(num2);
    }
    if (n1[0] == '-' && n2[0] == '-')
    {
        isNegativeAnswer = 0;
        num1 = revertSign(num1);
        num2 = revertSign(num2);
    }

    num1 = reverseList(num1);
    num2 = reverseList(num2);

    if (num1->data == 0) // if num1 is 0 then answer is 0
        return NULL;
    if (num2->data == 0)
    {
        struct node *newNode = createNewNode(999); // I'm using this as counter in print function
        result = newNode;                          // If head data would be 999 that means that is divide by 0 case
        return result;
    }

    int lenOfNum1 = lengthOfList(num1);
    int lenOfNum2 = lengthOfList(num2);

    if (lenOfNum1 < lenOfNum2) // if divisor is greater then dividend, no need to divide
    {
        return result; // or return NULL;
    }

    if (lenOfNum1 == lenOfNum2) // they have same length then check which one is greater
    {
        int isNum1Greater = 2;
        struct node *num1Pointer = num1, *num2Pointer = num2;
        while (num1Pointer != NULL) // both list are equal so we can use loop condition of any list
        {
            if (num1Pointer->data > num2Pointer->data)
            {
                isNum1Greater = 1;
                break;
            }
            if (num1Pointer->data < num2Pointer->data)
            {
                isNum1Greater = 0;
                break;
            }
            num1Pointer = num1Pointer->next;
            num2Pointer = num2Pointer->next;
        }
        if (isNum1Greater == 0) // if dividend is not greater than divisor
        {
            return result; // or return NULL;
        }
    }

    struct node *remainder = NULL, *remainderPointer;
    int extractFirstTime = 1;
    struct node *temp = NULL, *tempPointer; // we will extract digits from dividend to temp

    while (num1 != NULL)
    {
        int count = 0;
        int i = 0;
        while (i < lenOfNum2 && extractFirstTime == 1) // we have to extract more digits only once then we will extract one by one
        {
            struct node *newNode = createNewNode(num1->data);
            if (temp == NULL)
            {
                temp = newNode;
                tempPointer = temp;
            }
            else
            {
                newNode->prev = tempPointer;
                tempPointer->next = newNode;
                tempPointer = tempPointer->next;
            }
            struct node *forFreeing = num1;
            num1 = num1->next;
            free(forFreeing);
            forFreeing = NULL;
            i++;
        }

        if (extractFirstTime == 0) // it means now we have to extract one by one
        {
            struct node *newNode = createNewNode(num1->data);
            if (temp == NULL)
            {
                temp = newNode;
                tempPointer = temp;
            }
            else
            {
                while (tempPointer->next != NULL)
                {
                    tempPointer = tempPointer->next;
                }
                newNode->prev = tempPointer;
                tempPointer->next = newNode;
                tempPointer = tempPointer->next;
            }
            struct node *forFreeing = num1;
            num1 = num1->next;
            free(forFreeing);
            forFreeing = NULL;
        }

        while (isGreaterEqualFirstNum(temp, num2))
        {
            temp = reverseList(temp); // reversing list to subtract
            num2 = reverseList(num2); // reversing list to subtract

            struct node *num2Pointer = num2;
            tempPointer = temp; // points tempPointer to the first node of temp

            while (tempPointer != NULL && num2Pointer != NULL)
            {
                if (tempPointer->data < num2Pointer->data) // if carry is need for subtraction
                {
                    struct node *itr = tempPointer->next;
                    while (itr->data == 0)
                    {
                        itr = itr->next;
                    }
                    itr->data = itr->data - 1;
                    while (itr != tempPointer)
                    {
                        itr = itr->prev;
                        if (itr == tempPointer)
                        {
                            break;
                        }
                        itr->data = itr->data + 10 - 1;
                    }
                    tempPointer->data = tempPointer->data + 10;
                }

                struct node *newNode = createNewNode(tempPointer->data - num2Pointer->data);

                if (remainder == NULL)
                {
                    remainder = newNode;
                    remainderPointer = remainder;
                }
                else
                {
                    newNode->prev = remainderPointer;
                    remainderPointer->next = newNode;
                    remainderPointer = remainderPointer->next;
                }
                tempPointer = tempPointer->next;
                num2Pointer = num2Pointer->next;
            }
            while (tempPointer != NULL)
            {
                struct node *newNode = createNewNode(tempPointer->data);
                if (remainder == NULL)
                {
                    remainder = newNode;
                    remainderPointer = remainder;
                }
                else
                {
                    newNode->prev = remainderPointer;
                    remainderPointer->next = newNode;
                    remainderPointer = remainderPointer->next;
                }
                tempPointer = tempPointer->next;
            }

            remainder = reverseList(remainder);
            while (remainder->data == 0 && remainder->next != NULL)
            {
                struct node *forFreeing = remainder;
                remainder = remainder->next;
                free(forFreeing);
                forFreeing = NULL;
            }

            remainderPointer = remainder;
            temp = remainder;
            remainder = NULL;
            count++;
            tempPointer = temp; // reseting tempPointer to first node
            num2 = reverseList(num2);
            num2Pointer = num2;
        }

        if (extractFirstTime == 1 && count > 0)
        {
            struct node *newNode = createNewNode(count);
            if (result == NULL)
            {
                result = newNode;
            }
            else
            {
                result->prev = newNode;
                newNode->next = result;
                result = newNode;
            }
        }
        else if (extractFirstTime == 0)
        {
            struct node *newNode = createNewNode(count);
            if (result == NULL)
            {
                result = newNode;
            }
            else
            {
                result->prev = newNode;
                newNode->next = result;
                result = newNode;
            }
        }
        extractFirstTime = 0; // this means we have extracted more digits once
    }

    if (isNegativeAnswer == 1)
        result = revertSign(result);
    return result;
}

// modulus function is same as divide function just one change at the end of function in return
struct node *modulus(char n1[], char n2[])
{
    struct node *num1 = NumberToList(n1);
    struct node *num2 = NumberToList(n2);

    int isNegativeAnswer = 0;
    if (n1[0] == '-' && n2[0] != '-')
    {
        isNegativeAnswer = 1;
        num1 = revertSign(num1);
    }
    if (n1[0] != '-' && n2[0] == '-')
    {
        isNegativeAnswer = 0;
        num2 = revertSign(num2);
    }
    if (n1[0] == '-' && n2[0] == '-')
    {
        isNegativeAnswer = 1;
        num1 = revertSign(num1);
        num2 = revertSign(num2);
    }

    num1 = reverseList(num1);
    num2 = reverseList(num2);
    struct node *result = NULL;

    if (num2->data == 0)
    {
        struct node *newNode = createNewNode(999); // I'm using this as counter in print function
        result = newNode;                          // If head data would be 999 that means that is divide by 0 case
        return result;
    }

    // check if num2 is greater than num1 than modulus would be num1 --> 2%10 = 2
    if (isGreaterEqualFirstNum(num1, num2) == 0)
    {
        // reversing num1 again because we have reversed it earlier just above this
        num1 = reverseList(num1);
        result = num1;
        if (isNegativeAnswer == 1)
            result = revertSign(result);
        return result;
    }

    int lenOfNum1 = lengthOfList(num1);
    int lenOfNum2 = lengthOfList(num2);

    if (lenOfNum1 < lenOfNum2) // if divisor is greater then dividend, no need to divide
    {
        return result; // or return NULL;
    }

    if (lenOfNum1 == lenOfNum2) // they have same length then check which one is greater
    {
        int isNum1Greater = 2;
        struct node *num1Pointer = num1, *num2Pointer = num2;
        while (num1Pointer != NULL) // both list are equal so we can use loop condition of any list
        {
            if (num1Pointer->data > num2Pointer->data)
            {
                isNum1Greater = 1;
                break;
            }
            if (num1Pointer->data < num2Pointer->data)
            {
                isNum1Greater = 0;
                break;
            }
            num1Pointer = num1Pointer->next;
            num2Pointer = num2Pointer->next;
        }
        if (isNum1Greater == 0) // if dividend is not greater than divisor
        {
            return result; // or return NULL;
        }
    }

    struct node *remainder = NULL, *remainderPointer;
    int extractFirstTime = 1;
    struct node *temp = NULL, *tempPointer; // we will extract digits from dividend to temp

    while (num1 != NULL)
    {
        int count = 0;
        int i = 0;
        while (i < lenOfNum2 && extractFirstTime == 1) // we have to extract more digits only once then we will extract one by one
        {
            struct node *newNode = createNewNode(num1->data);
            if (temp == NULL)
            {
                temp = newNode;
                tempPointer = temp;
            }
            else
            {
                newNode->prev = tempPointer;
                tempPointer->next = newNode;
                tempPointer = tempPointer->next;
            }
            struct node *forFreeing = num1;
            num1 = num1->next;
            free(forFreeing);
            forFreeing = NULL;
            i++;
        }

        if (extractFirstTime == 0) // it means now we have to extract one by one
        {
            struct node *newNode = createNewNode(num1->data);
            if (temp == NULL)
            {
                temp = newNode;
                tempPointer = temp;
            }
            else
            {
                while (tempPointer->next != NULL)
                {
                    tempPointer = tempPointer->next;
                }
                newNode->prev = tempPointer;
                tempPointer->next = newNode;
                tempPointer = tempPointer->next;
            }
            struct node *forFreeing = num1;
            num1 = num1->next;
            free(forFreeing);
            forFreeing = NULL;
        }

        while (isGreaterEqualFirstNum(temp, num2))
        {
            temp = reverseList(temp); // reversing list to subtract
            num2 = reverseList(num2); // reversing list to subtract

            struct node *num2Pointer = num2;
            tempPointer = temp; // points tempPointer to the first node of temp

            while (tempPointer != NULL && num2Pointer != NULL)
            {
                if (tempPointer->data < num2Pointer->data) // if carry is need for subtraction
                {
                    struct node *itr = tempPointer->next;
                    while (itr->data == 0)
                    {
                        itr = itr->next;
                    }
                    itr->data = itr->data - 1;
                    while (itr != tempPointer)
                    {
                        itr = itr->prev;
                        if (itr == tempPointer)
                        {
                            break;
                        }
                        itr->data = itr->data + 10 - 1;
                    }
                    tempPointer->data = tempPointer->data + 10;
                }

                struct node *newNode = createNewNode(tempPointer->data - num2Pointer->data);

                if (remainder == NULL)
                {
                    remainder = newNode;
                    remainderPointer = remainder;
                }
                else
                {
                    newNode->prev = remainderPointer;
                    remainderPointer->next = newNode;
                    remainderPointer = remainderPointer->next;
                }
                tempPointer = tempPointer->next;
                num2Pointer = num2Pointer->next;
            }
            while (tempPointer != NULL)
            {
                struct node *newNode = createNewNode(tempPointer->data);
                if (remainder == NULL)
                {
                    remainder = newNode;
                    remainderPointer = remainder;
                }
                else
                {
                    newNode->prev = remainderPointer;
                    remainderPointer->next = newNode;
                    remainderPointer = remainderPointer->next;
                }
                tempPointer = tempPointer->next;
            }

            remainder = reverseList(remainder);
            while (remainder->data == 0 && remainder->next != NULL)
            {
                struct node *forFreeing = remainder;
                remainder = remainder->next;
                free(forFreeing);
                forFreeing = NULL;
            }

            remainderPointer = remainder;
            temp = remainder;
            remainder = NULL;
            count++;
            tempPointer = temp; // reseting tempPointer to first node
            num2 = reverseList(num2);
            num2Pointer = num2;
        }

        if (extractFirstTime == 1 && count > 0)
        {
            struct node *newNode = createNewNode(count);
            if (result == NULL)
            {
                result = newNode;
            }
            else
            {
                result->prev = newNode;
                newNode->next = result;
                result = newNode;
            }
        }
        else if (extractFirstTime == 0)
        {
            struct node *newNode = createNewNode(count);
            if (result == NULL)
            {
                result = newNode;
            }
            else
            {
                result->prev = newNode;
                newNode->next = result;
                result = newNode;
            }
        }
        extractFirstTime = 0; // this means we have extracted more digits once
    }

    // result have division result
    // temp has remainder
    // so we have assigned temp in result
    result = reverseList(temp);
    if (isNegativeAnswer == 1)
        result = revertSign(result);
    return result;
}

void print(struct node *head)
{
    if (!head)
    {
        printf("0\n");
        return;
    }
    head = reverseList(head);
    if (head->data == 0)
    {
        while (head->data == 0 && head->next != NULL)
        {
            head = head->next;
        }
    }

    if (head->data < 0)
    { // This function will make all the digits positive except the first digit for better output
        struct node *itr = head->next;
        while (itr != NULL)
        {
            if (itr->data < 0)
                itr->data = -1 * itr->data;
            itr = itr->next;
        }
    }

    if (head->data == 999)
    {
        printf("Can't divide by zero!!!\n");
        return;
    }
    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}
