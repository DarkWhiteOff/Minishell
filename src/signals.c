#include "../includes/minishell.h"

void    signal_manager(int sig)
{
    (void)sig;
    printf("\n");
    return ;
}

void signals()
{
    signal(SIGINT, signal_manager);
    //signal(SIG, signal_manager);
    return ;
}
