#include "minishell.h"

void	set_parent_sigquit(void (*handler)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_parent_sigint(void (*handler)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	if (handler == handle_sigint)
		sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
