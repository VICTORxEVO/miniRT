#include "miniRT.h"

// Create a new node
t_node* create_node(t_core *d, void *data)
{
    t_node *new_node = (t_node *)galloc(sizeof(t_node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void add_node(t_core *d, t_node **head, void *data, char type_macro)
{
    t_node *new_node = create_node(d, data);
    new_node->type = type_macro;
    new_node->next = *head;
    *head = new_node;
}

void add_float_node_sorted(t_core *d, t_node **head, double value)
{
    // Allocate heap memory for the double data
    double *data_ptr = (double *)galloc(sizeof(double));
    *data_ptr = value;

    t_node *new_node = create_node(d, data_ptr);

    // If the list is empty or the new value should be placed before head
    if (*head == NULL || *((double*)(*head)->data) >= value)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    // Otherwise find the correct position
    t_node *current = *head;
    while (current->next != NULL && *((double*)current->next->data) < value)
    {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
}

int remove_node(t_core *d, t_node **head, void *data)
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
            clear_1data(current);
            return 1; // Removal succeeded
        }
        previous = current;
        current = current->next;
    }
    return 0; // Data not found
}




t_object* create_obj(t_core *d, void *data)
{
    t_object *new_obj = (t_object *)galloc(sizeof(t_object));
    new_obj->data = data;
    new_obj->next = NULL;
    return new_obj;
}

void add_obj(t_core *d, t_object **head, void *data, char type_macro)
{
    t_object *new_obj = create_obj(d, data);
    new_obj->get_norm = get_obj_norm;
    new_obj->get_color = get_obj_color;
    new_obj->set_color = set_obj_color;
    new_obj->get_pattern = get_obj_pattern;
    new_obj->set_pattern = set_obj_pattern;
    new_obj->get_reflect = get_obj_reflect;
    new_obj->get_origin = get_obj_origin;
    new_obj->type = type_macro;
    new_obj->next = *head;
    *head = new_obj;
}

void add_float_object_sorted(t_core *d, t_object **head, double value)
{
    // Allocate heap memory for the double data
    double *data_ptr = (double *)galloc(sizeof(double));
    *data_ptr = value;

    t_object *new_obj = create_obj(d, data_ptr);

    // If the list is empty or the new value should be placed before head
    if (*head == NULL || *((double*)(*head)->data) >= value)
    {
        new_obj->next = *head;
        *head = new_obj;
        return;
    }

    // Otherwise find the correct position
    t_object *current = *head;
    while (current->next != NULL && *((double*)current->next->data) < value)
    {
        current = current->next;
    }
    new_obj->next = current->next;
    current->next = new_obj;
}

int remove_obj(t_core *d, t_object **head, void *data)
{
    t_object *current = *head;
    t_object *previous = NULL;

    while (current != NULL)
    {
        // Compare pointers directly
        if (current->data == data)
        {
            // Found the obj whose data pointer matches
            if (previous == NULL)
            {
                // Removing the head obj
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            clear_1data(current);
            return 1; // Removal succeeded
        }
        previous = current;
        current = current->next;
    }
    return 0; // Data not found
}