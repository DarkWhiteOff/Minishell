#include "../includes/minishell.h"

void	update_oldpwd_pwd(t_main *main)
{
	int		pwd_line;
	char	*pwd;
	char	*newpwd;

	pwd_line = check_var_exists(main->env, main->env_len, "export PWD=");
	pwd = ft_strdup(&ft_strchr(main->env[pwd_line], '=')[1]);
	export(main, ft_strjoin("export OLDPWD=", pwd));
	free(pwd);

	newpwd = ft_strdup(getcwd(NULL, 0));
	export(main, ft_strjoin("export PWD=", newpwd));
	free(newpwd);
	return ;
}

char *get_actual_arg(char *arg)
{
	int i;
	char *actual_arg;

	i = 0;
	if (arg[i] == '/')
	{
		while (arg[i])
			i++;
	}
	else
	{
		while (arg[i] != '/' && arg[i])
			i++;
	}
	actual_arg = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	if (arg[i] == '/')
	{
		while (arg[i])
		{
			actual_arg[i] = arg[i];
			i++;
		}
	}
	else
	{
		while (arg[i] != '/' && arg[i])
		{
			actual_arg[i] = arg[i];
			i++;
		}
	}
	actual_arg[i] = '\0';
	return (actual_arg);
}

int	check_syntax_cd(t_main *main, char *arg)
{
	int i;
	int chdir_value;
	char *actual_arg;

	i = 0;
	chdir_value = 0;
	while (arg[i])
	{
		actual_arg = get_actual_arg(&arg[i]);
		chdir_value = chdir(actual_arg);
		if (chdir_value == -1)
		{
			int pwd_pos = check_var_exists(main->env, main->env_len, "export PWD=");
			char *pwd_value = &ft_strchr(main->env[pwd_pos], '=')[1];
			chdir(pwd_value);
			//if ((ft_strcmp(main->env[pwd_pos], "PWD=/") == 0) && (ft_strcmp(actual_arg, "..") != 0))
			printf("bash: cd: %s: No such file or directory\n", actual_arg);
			return (0);
		}
		while (arg[i] != '/' && arg[i])
			i++;
		free(actual_arg);
		i++;
	}
	return (1);
}

int	cd(t_main *main, char **split)
{
	int	chdir_value;
	int	home_pos;

	/* chdir_value = chdir("sr");
	char *pwd = getcwd(NULL, 0);
	printf("pwd : %s\n", pwd);
	printf("chdir_value : %d\n", chdir_value);
	exit(0); */
	chdir_value = 0;
	home_pos = 0;
	if (main->split_len > 2)
		return (printf("bash: cd: too many arguments\n"), 0);
	if (main->split_len == 1 && ft_strcmp("cd", split[0]) == 0)
	{
		home_pos = check_var_exists(main->env, main->env_len, "export HOME=");
		chdir_value = chdir(&ft_strchr(main->env[home_pos], '=')[1]);
		if (chdir_value == -1)
			return (0);
		if (chdir_value == 0)
			return (update_oldpwd_pwd(main), 1);
	}
	else
	{
		if (check_syntax_cd(main, split[1]) == 1)
		{
			update_oldpwd_pwd(main);
			return (1);
		}
	}
	return (0);
}