# include <stdio.h>
# include <stdlib.h>

char * ERROR_MSG = "INVALID INPUT\n"; 

// Struct to store data for each day
struct data {
    int index;
    double min_temp, max_temp;
}; 
typedef struct data data_t;

// struct for linked list
struct node {
    data_t data;
    struct node * next;
}; 
typedef struct node node_t; 


void add(node_t **, data_t);
void delete(node_t **, int);
void print_db(node_t *); 


int main (){

    node_t * db = NULL;  // Define the database

    char operation;
    double min_temp, max_temp; 
    int index;

    /* 
    Idea: 
        1. use a do-while loop and stop when operaation = 'Q'.
        2. switch statements for the different operations
     */

    
    do
    {
        printf("Enter command: ");
        scanf(" %c",&operation); 
        // Trying to explain to my self the use of " %c". If we do not use the whitespace the scanf will
        // read the newline character \n from the previous scanf. Every scanf leaves a \n in the input buffer.
        // By using this " %c" we explictly tell the scanf to consume white spaces INCLUDING the newline character.
        // and only read the next non whitespace character. 

        switch (operation)
        {
        case 'A':

            if(scanf("%d",&index) > 0 && scanf("%lf",&min_temp) > 0 && scanf("%lf",&max_temp) > 0)
            {
                 if (index < 1 || index > 31)  
                 {
                    printf("%s",ERROR_MSG);
                    break;
                 }
                 else // ADD TO DATABASE
                 {
                    data_t data = {index,min_temp,max_temp};
                    add(&db,data);
                 }    
            }
            else printf("%s",ERROR_MSG);    

            break;
        case 'D':
            if(scanf("%d",&index) > 0){
                 if (index < 1 || index > 31)  
                 {
                    printf("%s",ERROR_MSG);
                    break;
                 }
                 else // DELETE FROM DATABASE
                 {
                    delete(&db,index);
                 }
                 
            }
            break;
        case 'P':
            print_db(db); 
            break;    
        default:
            break;
        }
    
        
    } while (operation != 'Q');
    



    return 0; 

}

void add(node_t ** head, data_t newData)
{
    // Check if head is null, if null malloc memory + assign data to head
    if(*(head) == NULL){
        (*head) = (node_t *)malloc(sizeof(node_t));
        (*head)->data = newData;
        //printf("Added data to db. index %d (min_temp,max_temp) = (%lf,%lf)",(*head)->data.index,(*head)->data.min_temp,(*head)->data.max_temp);
        return; 
    }
    
    // if same index update data
    if(newData.index == (*head)->data.index) (*head)->data = newData;  

    // Sort list from low to high -> if new data has higher index try to add to the right one
    else if (newData.index > (*head)->data.index) {
    if ((*head)->next == NULL) {
        node_t *newNode;
        newNode = (node_t *)malloc(sizeof(node_t));
        newNode->data = newData;
        newNode->next = NULL;
        (*head)->next = newNode;
    } else {
        add(&(*head)->next, newData);
    }
}

    // New data has lower index (create newNode as head)
    else {
        node_t * newNode;
        newNode = (node_t *)malloc(sizeof(node_t));
        newNode->data = newData;
        newNode->next = NULL; 
        newNode->next = *head; // Make newNode->next point at the node *head is pointing to
        *head = newNode;  // updates the adress of *head to point to newNode 
    } 
}

void delete(node_t ** head, int index)
{
    if(*head == NULL) return; // To get out of recursive loop if we can't find index
    else if((*head)->data.index != index) delete(&(*head)->next, index);
    else
    {
        node_t * temp_node = (*head)->next; 
        free(*head); // free node
        *head = temp_node;
    }
}

void print_db(node_t * head)
{
    node_t * current = head;

    printf("day\tmin\tmax\n");
    while (current != NULL)
    {
        printf("%d\t%lf\t%lf\n",current->data.index,current->data.min_temp,current->data.max_temp); 
        current = current->next; 
    }

    
}