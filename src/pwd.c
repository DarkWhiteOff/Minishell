#include "../includes/minishell.h"

int check_syntax_pwd(char *cmd)
{
    if (cmd[0] == '-')
        return (printf("bash: pwd: -%c: invalid option\n", cmd[1]), 0);
    return (1);
}

int    pwd(t_main *main, char **cmd)
{
    char *pwd;

    if (main->split_len == 2)
    {
        if (check_syntax_pwd(cmd[1]) == 0)
            return (0);
    }
    pwd = ft_strdup(getcwd(NULL, 0));
    if (pwd == NULL)
        return (free(pwd), 0);
    printf("%s\n", pwd);
    free(pwd);
    return (1);
}