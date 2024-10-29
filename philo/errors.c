/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:28:35 by tialbert          #+#    #+#             */
/*   Updated: 2024/07/10 22:02:10 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philo.h"

void	argument_error(int type)
{
	if (type == 0)
		printf("Wrong number of arguments. Please insert 4 or 5 integers.\n");
	else if (type == 1)
		printf("Invalid argument. Please insert 4 or 5 integers.\n");
	printf("1. Number of philosophers \(number has to be > 0)\n");
	printf("2. Time to die\n");
	printf("3. Time to eat\n");
	printf("4. Time to sleep\n");
	printf("5. Number of times each has to eat \(optional)\n");
}
