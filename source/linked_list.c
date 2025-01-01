#include "miniRT.h"

// Create a new node
t_node* create_node(t_data *d, void *data)
{
    t_node *new_node = (t_node *)gc_malloc(d, sizeof(t_node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void add_node(t_data *d, t_node **head, void *data)
{
    t_node *new_node = create_node(d, data);
    new_node->next = *head;
    *head = new_node;
}

void add_float_node_sorted(t_data *d, t_node **head, float value)
{
    // Allocate heap memory for the float data
    float *data_ptr = (float *)gc_malloc(d, sizeof(float));
    *data_ptr = value;

    t_node *new_node = create_node(d, data_ptr);

    // If the list is empty or the new value should be placed before head
    if (*head == NULL || *((float*)(*head)->data) >= value)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    // Otherwise find the correct position
    t_node *current = *head;
    while (current->next != NULL && *((float*)current->next->data) < value)
    {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
}

// Remove a node from the linked list using a user-defined comparison function
// Returns 1 if removal was successful, 0 if data wasn't found
int remove_node(t_data *d, t_node **head, void *data)
{
    t_node *current = *head;
    t_node *previous = NULL;

    while (current != NULL)
    {
        // Compare pointers directly
        if (current->data == data)
        {
            // Found the node whose data pointer matches
            if (previous == NULL)
            {
                // Removing the head node
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            gc_free(d, current);
            return 1; // Removal succeeded
        }
        previous = current;
        current = current->next;
    }
    return 0; // Data not found
}

