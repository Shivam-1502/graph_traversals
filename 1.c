#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX_SIZE 100

typedef struct{
    int item[MAX_SIZE];
    int top;
}Stack;

typedef struct Node{
    int vertex;
    struct Node** next;
}Node;

typedef struct{
    int num_ver;
    Node **adj_lists;
}GraphList;

Stack* create_stack(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;

    return stack;
}

int is_empty(Stack* stack){
    return stack->top == -1;
}

int is_full(Stack* stack){
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int item){
    if (is_full(stack)){
        printf("Stack is full. Cannot push %d.\n", item);
        return;
    }
    stack->item[++stack->top] = item;
}

int pop(Stack* stack){
    if (is_empty(stack)){
        printf("Stack is empty. Cannot po.\n");
        return -1;
    }
    return stack->item[stack->top--];
}

int peek(Stack* stack){
    if (is_empty(stack)){
        printf("Stack is empty. Cannot peek.\n");
        return -1;
    }
    return stack->item[stack->top];
}

void destroy_stack(Stack* stack){
    free(stack);
}

GraphList* create_graph_list(int vertices){

    GraphList* graph = malloc(sizeof(GraphList));
    graph->num_ver = vertices;
    graph->adj_lists = malloc(sizeof(Node*)* vertices);

    for(int i = 0; i < graph->num_ver; i++){
        graph->adj_lists[i] = NULL;
    }
    return graph;
}

int add_edge_list(GraphList* graph, int src, int dest){

    Node* new_node = malloc(sizeof(Node));
    new_node->vertex = dest;
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;

    new_node = malloc(sizeof(Node));
    new_node->vertex = src;
    new_node->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = new_node;

    return 0;
}

int print_graph_list(GraphList* graph){

    for(int i=0; i<graph->num_ver; i++){
        Node* temp = graph->adj_lists[i];
        printf("\n Adjacency list of vetex %d\n head",i);
        while(temp){
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
    return 0;
}

int dfs_iterative(GraphList* graph, int start_vertex){
    int curr_vertex;
    int visited[graph->num_ver];

    for(int i = 0; i<graph->num_ver; i++){
        visited[i] = 0;
    }

    Stack* stack = create_stack();
    push(stack, start_vertex);

    while(!is_empty(stack)){
        curr_vertex= pop(stack);
        if(!visited[curr_vertex]){
            visited[curr_vertex] = 1;
            printf("Visited %d \n", curr_vertex);
        }

        Node* temp = graph->adj_lists[curr_vertex];
        while(temp != NULL){
            int adj_vertex = temp->vertex;
            if(!visited[adj_vertex]){
                push(stack, adj_vertex);
            }
            temp == temp->next;

        }
    }

    destroy_stack(stack);

    return 0;
}

int main(){
    GraphList* graph = create_graph_list(5);
    add_edge_list(graph, 0, 1);
    add_edge_list(graph, 0, 2);
    add_edge_list(graph, 0, 3);
    add_edge_list(graph, 1, 2);
    add_edge_list(graph, 3, 4);

    dfs_iterative(graph, 0);

    return 0;
}