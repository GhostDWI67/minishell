/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:22:39 by mpalisse          #+#    #+#             */
/*   Updated: 2025/06/23 14:27:47 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
update oldpwd dans l'env en copiant PWD si PWD n'existe pas alors OLDPWD est
créé
Return void;
******************************************************************************/
static void	cd_oldpwd(t_list *env)
{
	t_list	*temp;
	char	*oldpwd;
	int		size;

	temp = env;
	size = ft_lstsize(temp);
	oldpwd = NULL;
	while (size--)
	{
		if (ft_strncmp((char *)temp->content, "PWD=", 3) == 0)
			oldpwd = (char *)temp->content;
		temp = temp->next;
	}
	if (!oldpwd)
		export_core("OLDPWD", &env);
	else
	{
		oldpwd = ft_strjoin("OLD", oldpwd);
		if (!oldpwd)
			return ;
		export_core(oldpwd, &env);
	}
	free(oldpwd);
}

/******************************************************************************
lance cd_oldpwd puis update PWD dans l'env en copiant le retour de getcwd
Return void;
******************************************************************************/
static int	cd_core(t_list *env)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	cd_oldpwd(env);
	if (!getcwd(cwd, PATH_MAX))
		return (1);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (1);
	if (!export_core(pwd, &env))
		return (1);
	free(pwd);
	return (0);
}

/******************************************************************************
execute l'equivalent de "cd ~"
Return exit status en int;
******************************************************************************/
static int	cd_no_args(t_list *env, t_cmd_line *cmd, int in_child)
{
	int		ret;
	char	*arg;

	ret = 1;
	arg = ft_getenv("HOME", env);
	if (arg != NULL)
	{
		arg = ft_strdup(arg);
		if (arg)
			ret = chdir(arg);
	}
	else
		ret = 1;
	if (ret == 0)
		ret = cd_core(env);
	if (ret == -1)
		ret = 1;
	if (ret == 1)
		ft_perror("bash: cd: HOME not set\n");
	free(arg);
	if (in_child == 1)
		free_cmd_line_exit(cmd);
	return (ret);
}

/******************************************************************************
lance cd avec l'argument donné
Return exit status en int;
******************************************************************************/
static int	cd_args(char *arg, t_list *env, t_cmd_line *cmd, int in_child)
{
	int		ret;

	if (arg[0] == '\0')
		return (0);
	if (arg[0] == '~' && arg[1] == '\0')
		ret = cd_no_args(env, cmd, in_child);
	else
		ret = chdir(arg);
	if (ret == 0)
		ret = cd_core(env);
	if (ret == -1)
		ret = 1;
	if (ret == 1)
		perror(arg);
	if (in_child == 1)
		free_cmd_line_exit(cmd);
	return (ret);
}

/******************************************************************************
check le bon nombre d'arg et lance cd_core si chdir a reussis
Return 0 si ok sinon 1;
******************************************************************************/
int	cd(char **args, t_list *env, t_cmd_line *cmd, int in_child)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		return (cd_no_args(env, cmd, in_child));
	if (i == 2)
		return (cd_args(args[1], env, cmd, in_child));
	if (in_child == 1)
		free_cmd_line_exit(cmd);
	return (msg_inf(ERM_CD, ERN_CD));
}
