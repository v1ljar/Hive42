#include "libft.h"

int	ft_lstsize(t_list *lst)
{
  int	result;

  result = 0;
  while(lst != NULL)
  {
    lst = lst->next; 
    result++;
  }
  return (result);
}
