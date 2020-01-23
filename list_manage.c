/* BIG42HEADER */

#include "fillit.h"

t_list		*list_new(void)
{
	t_list	*ptr;
	ptr = (t_list *)malloc(sizeof(t_list));
	ft_bzero(ptr, sizeof(t_list));
	return (ptr);
}

void		list_push(t_list **head, t_list *new)
{
	new->next = *head;
	*head = new;
	return ;
}

t_list		*list_pop(t_list **head)
{
	t_list *ptr;
	ptr = *head;
	*head = ptr->next;
	ptr->next = NULL;
	return (ptr);
}

void		list_delete(t_list *ptr)
{
	free(ptr);
	return ;
}
