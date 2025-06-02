/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:27:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/03 00:06:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// CREER UN NVEAU MAILLON
// t_philo	*ft_lstnew_tok(TOK_TYPE type, char *word, t_shell *shell)
t_philo	*ft_lstnew_philo(int index, t_data *data)
{
	t_philo	*new;
	pthread_t *thread;

	(void)data;
	thread = malloc(sizeof(pthread_t));
	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (NULL);
		// free_exit(data);
	new->index = index;
	new->fork = 1;
	new->thread = thread;
	new->next = NULL;
	return (new);
}

t_philo	*ft_lstlast_philo(t_philo *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// AJOUTE LE NVEAU MAILLON A LA FIN DE LA LISTE
void	ft_lstadd_back_philo(t_philo **philo_lst, t_philo *new)
{
	t_philo	*last;

	if (philo_lst == NULL)
		return ;
	if (*philo_lst == NULL)
	{
		*philo_lst = new;
		return ;
	}
	last = ft_lstlast_philo(*philo_lst);
	last->next = new;
}

void	create_lst_philo(t_data *data)
{
	int i;

	i = 0;
	while(i < data->nb_philo)
	{
		ft_lstadd_back_philo(&(data->philo_lst), ft_lstnew_philo(i, data));
		i++;
	}
}

void	ft_lstclear_tok(t_philo *lst)
{
	t_philo	*current;
	t_philo	*tmp;

	current = lst;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->thread);
		free(tmp);
	}
	lst = NULL;
}


