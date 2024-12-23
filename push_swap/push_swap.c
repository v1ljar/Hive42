#include "./libft/libft.h"
#include "push_swap.h"

int	ft_validate_argv(int argc, char **argv);
void	free_split(char **storage);
void	fill_stack_a(s_stack *stack_a, int argc, char **argv);
int	valid_nbr(int *arr, int nbr);

int	main(int argc, char **argv)
{
  int		total_args;
  s_stack	stack_a;
  int		i;

  if (argc < 2)
    exit(0);
  total_args = ft_validate_argv(argc, argv);
  stack_a.arr = malloc(sizeof(int) * total_args);
  if (!stack_a.arr)
    return (ft_printf("Error\n"), -1);
  stack_a.size = 0;
  fill_stack_a(&stack_a, argc, argv);
  i = 0;
  while (i < stack_a.size)
  {
    ft_printf("%i\n", stack_a.arr[i]);
    i++;
  }
  ft_printf("Size: %i\n", stack_a.size);
  free(stack_a.arr);
  return (0);
}

int	ft_validate_argv(int argc, char **argv)
{
  char	**storage;
  int	res;
  int	i;
  int	j;

  res = 0;
  i = 1;
  while (i < argc)
  {
    storage = ft_split(argv[i], ' ');
    if (!storage)
    {
      free_split(storage);
      ft_printf("Error\n");
      return (-1);
    }
    j = 0;
    while (storage[j])
    {
      res++;
      j++;
    }
    free_split(storage);
    i++;
  }
  return (res);
}

void	free_split(char **storage)
{
  int	i;

  i = 0;
  while (storage[i])
    free(storage[i++]);
  free(storage);
}

void	fill_stack_a(s_stack *stack_a, int argc, char **argv)
{
  char	**buf;
  int	i;
  int	j;

  i = 1;
  while (i < argc)
  {
    buf = ft_split(argv[i], ' ');
    if (!buf)
    {
      free_split(buf);
      ft_printf("Error filling stack_a!\n");
      exit(-1);
    }
    j = 0;
    while (buf[j] && valid_nbr(stack_a->arr, ft_atoi(buf[j])))
    {
      stack_a->arr[stack_a->size++] = ft_atoi(buf[j]);
      j++;
    }
    i = 0;
    while (i < stack_a->size)
    {
      ft_printf("%d: %i\n", i, stack_a->arr[i]);
      i++;
    }
    free_split(buf);
    i++;
  }
}

int	valid_nbr(int *arr, int nbr)
{
  int	i;

  i = 0;
  while (arr[i])
  {
    if (arr[i] == nbr)
    {
      ft_printf("Error\n");
      free(arr);
      exit(-1);
    }
    i++;
  }
  return (1);
}
