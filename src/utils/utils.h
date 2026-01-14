/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:50:10 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:50:11 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stddef.h>

typedef struct s_tk		t_tk;
typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

void	cmd_lstadd_end(t_cmd **lst, t_cmd *cmd);
t_cmd	*cmd_lstget_end(t_cmd *cmd);
void	cmd_lstclear(t_cmd **lst);

// cmd_utils1_helper.c
void	free_cmd_io_fds(t_cmd *cmd);
void	cmd_lstdelone(t_cmd *cmd);

// cmd_utils2.c
t_cmd	*cmd_lstnew(void);

// token_utils.c
void	tk_lstadd_back(t_tk **lst, t_tk *tk);
t_tk	*tk_lstnew(char *str, int type);
void	tk_lstdelone(t_tk *tk);
void	tk_lstclear(t_tk **lst);

// str_utils1.c
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);

// str_utils2.c
void	fd_putstr(int fd, char *s, int nl);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// str_utils3.c
void	ft_free(char **argv);
char	**ft_split(char const *s, char c);

// utils_1.c
void	*ft_memset(void *s, int c, size_t n);
int		all_spaces(char *s);
int		ft_isspace(char c);
int		skip_spaces(char *s);

// utils2.c
char	*ft_itoa(int n);
int		ft_atoi(char *s);
int		ft_isalpha(int c);
int		ft_isalnum(int c);

// utils3.c
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_isnumber(const char *str);

// env_utils.c
t_env	*init_env_list(char **envp);
int		find_key(char *str);
void	free_list(t_env *head);

// env_utils2.c
char	*get_env_value(t_env *env, const char *key);
int		set_env_value(t_env **env, const char *key, const char *value);

#endif
