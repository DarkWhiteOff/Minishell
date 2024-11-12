
#include "includes/minishell.h"

void    init_env(char **env, t_main *main)
{
    int i = -1;
    int j = 0;

    main->env = NULL;
    main->env_len = 0;
    while (env[++i] != NULL)
    {
        j++;
    }
    main->env_len = i;
    main->env = (char **)malloc(sizeof(char *) * main->env_len + 1);
    i = 0;
    while (i < main->env_len)
    {
        main->env[i] = ft_strdup(env[i]);
        i++;
    }
}

void    print_env(t_main *main)
{
    int i = 0;
    while (i < main->env_len)
    {
        printf("%s\n", main->env[i]);
        i++;
    }
}

void    free_old_env(char **tab)
{
    free(tab);
    tab = NULL;
}

int check_only_export(char *cmd)
{
    if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 'r' && cmd[5] == 't' && cmd[6] == '\0')
        return (1);
    return (0);
}

/* void    print_ascii_order(t_main *main) // a faire
{

} */

int check_equal(char *cmd)
{
    int i = 0;

    while (cmd[i] != ' ' && cmd[i])
        i++;
    while (cmd[i] != '=' && cmd[i])
        i++;
    if (cmd[i] == '=' && cmd[i - 1] != ' ')
        return (1);
    return (0);
}

void    add_var_to_env(t_main *main, char *cmd)
{
    int i = 0;
    int j = 0;
    char **tmp;

    if (check_only_export(cmd) == 1)
    {
        //print_ascii_order(main);
        return ;
    }
    else if (check_equal(cmd) == 0)
        return ;
    tmp = (char **)malloc(sizeof(char *) * main->env_len + 1);
    while (i < main->env_len)
    {
        tmp[i] = ft_strdup(main->env[i]);
        i++;
    }
    free_old_env(main->env);
    main->env = (char **)malloc(sizeof(char *) * (main->env_len + 1) + 1);
    i = 0;
    while (i < main->env_len)
    {
        main->env[i] = ft_strdup(tmp[i]);
        i++;
    }
    while (cmd[j] != ' ')
        j++;
    j++;
    main->env[i] = ft_strdup(&cmd[j]);
    free_old_env(tmp);
    main->env_len += 1;
}

int check_var(char **tmp, char *cmd, int tmplen)
{
    int i = 0;
    int j = 0;
    int r = 0;
    char s1[500];
    char s2[500];


    while (cmd[j] != ' ')
        j++;
    j++;
    while (cmd[j] != '\0')
    {
        s2[r] = cmd[j];
        r++;
        j++;
    }
    s2[r] = '\0';
    r = 0;
    j = 0;
    while (i < tmplen)
    {
        while (tmp[i][j] != '=')
        {
            s1[r] = tmp[i][j];
            r++;
            j++;
        }
        s1[r] = '\0';
        r = 0;
        j = 0;
        if (ft_strncmp(s1, s2) == 0)
            return (i);
        i++;
    }
    return (-1);
}

int check_only_unset(char *cmd)
{
    if (cmd[0] == 'u' && cmd[1] == 'n' && cmd[2] == 's' && cmd[3] == 'e' && cmd[4] == 't' && cmd[5] == '\0')
        return (1);
    return (0);
}

void    del_var_to_env(t_main *main, char *cmd)
{
    int i = 0;
    int j = 0;
    int var_to_unset;
    char **tmp;

    if (check_only_unset(cmd) == 1)
        return ;
    else if (check_equal(cmd) == 1)
        return ;
    tmp = (char **)malloc(sizeof(char *) * main->env_len + 1);
    while (i < main->env_len)
    {
        tmp[i] = ft_strdup(main->env[i]);
        i++;
    }
    var_to_unset = check_var(tmp, cmd, main->env_len);
    if (var_to_unset == -1)
        return ;
    free_old_env(main->env);
    main->env = (char **)malloc(sizeof(char *) * (main->env_len - 1) + 1);
    i = 0;
    while (i < main->env_len)
    {
        if (i == var_to_unset)
            i++;
        main->env[j] = ft_strdup(tmp[i]);
        i++;
        j++;
    }
    free_old_env(tmp);
    main->env_len -= 1;
}

void    update_env(t_main *main, char *cmd, int update_type) //update_env(&main, update_type); // pour export/unset, changement de pwd/oldpwd // update_type -> 1 : export, 2 : unset, 3 : pwd/oldpwd
{
    if (update_type == 1)
        add_var_to_env(main, cmd);
    if (update_type == 2)
        del_var_to_env(main, cmd);
    return ;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
    (void)env;
    char *rl;
    (void)rl;
    char *cmd;
    t_main main;

    init_env(env, &main);
	while (1)
	{
		rl = readline("Prompt >");
        cmd = ft_strdup(rl);
        if (cmd[0] == 'e' && cmd[1] == 'n' && cmd[2] == 'v' && cmd[3] == '\0')
            print_env(&main);
        if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 'r' && cmd[5] == 't')
            update_env(&main, cmd, 1);
        if (cmd[0] == 'u' && cmd[1] == 'n' && cmd[2] == 's' && cmd[3] == 'e' && cmd[4] == 't')
            update_env(&main, cmd, 2);
	}
}