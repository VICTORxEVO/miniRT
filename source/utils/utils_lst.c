#include "miniRT.h"

t_node	*create_node(void *data)
{
	t_node	*new_node;

	new_node = (t_node *)galloc(sizeof(t_node));
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_node **head, void *data, char type_macro)
{
	t_node	*new_node;

	new_node = create_node(data);
	new_node->type = type_macro;
	new_node->next = *head;
	*head = new_node;
}

t_object	*create_obj(void *data)
{
	t_object	*new_obj;

	new_obj = (t_object *)galloc(sizeof(t_object));
	new_obj->data = data;
	new_obj->next = NULL;
	return (new_obj);
}

void	add_obj(t_object **head, void *data, char type_macro)
{
	t_object	*new_obj;

	new_obj = create_obj(data);
	new_obj->type = type_macro;
	new_obj->next = *head;
	*head = new_obj;
}
