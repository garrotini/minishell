/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:50 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:28:52 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env	t_env;

typedef enum e_tk_mode	t_tk_mode;

int	is_builtin(char *str);
int	execute_builtin(char **args, t_env **env);
int	ft_echo(char **arg, t_tk_mode *arg_mode, t_env **env);
int	ft_pwd(char **args);
int	ft_env(char **args, t_env *env);
int	ft_cd(char **args, t_env **env);
int	print_export(t_env *env);
int	ft_export(char **args, t_env **env);
int	ft_unset(char **args, t_env **env);
int	ft_exit(char **args, t_env **env);

#endif
