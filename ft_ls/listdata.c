/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 20:20:36 by anowak            #+#    #+#             */
/*   Updated: 2015/01/07 20:20:37 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_link(char *full_path)
{
	char	*str;
	int		buf;
	int		ret;

	buf = 1;
	ret = 1;
	str = NULL;
	while (ret == buf)
	{
		free(str);
		if (!(str = ft_strnew(buf)))
			print_error(NULL);
		ret = readlink(full_path, str, buf);
		if (ret == -1)
			return (0);
		ret++;
		buf++;
	}
	return (str);
}

char	file_type(t_stat *s, char *full_path)
{
	char c;

	c = '?';
	((S_ISREG(s->st_mode)) ? c = '-' : c);
	((S_ISBLK(s->st_mode)) ? c = 'b' : c);
	((S_ISCHR(s->st_mode)) ? c = 'c' : c);
	((S_ISDIR(s->st_mode)) ? c = 'd' : c);
	((S_ISSOCK(s->st_mode)) ? c = 's' : c);
	((S_ISFIFO(s->st_mode)) ? c = 'p' : c);
	if (get_link(full_path))
		c = 'l';
	return (c);
}

char	*file_mode(t_stat *s, char *full_path)
{
	char *mode;

	if (!(mode = (char*)ft_memalloc(sizeof(char) * 12)))
		print_error(NULL);
	mode[0] = file_type(s, full_path);
	mode[1] = ((s->st_mode & S_IRUSR) ? 'r' : '-');
	mode[2] = ((s->st_mode & S_IWUSR) ? 'w' : '-');
	mode[3] = ((s->st_mode & S_IXUSR) ? 'x' : '-');
	if (s->st_mode & S_ISUID)
		mode[3] = ((mode[3] == 'x') ? 's' : 'S');
	mode[4] = ((s->st_mode & S_IRGRP) ? 'r' : '-');
	mode[5] = ((s->st_mode & S_IWGRP) ? 'w' : '-');
	mode[6] = ((s->st_mode & S_IXGRP) ? 'x' : '-');
	if (s->st_mode & S_ISGID)
		mode[6] = ((mode[6] == 'x') ? 's' : 'S');
	mode[7] = ((s->st_mode & S_IROTH) ? 'r' : '-');
	mode[8] = ((s->st_mode & S_IWOTH) ? 'w' : '-');
	mode[9] = ((s->st_mode & S_IXOTH) ? 'x' : '-');
	if (s->st_mode & S_ISVTX)
		mode[9] = ((mode[9] == 'x') ? 't' : 'T');
	return (mode);
}

char	*ext_attr(char *full_path, char *mode, char *link)
{
	mode[10] = ' ';
	if (mode[0] == 'l')
		if (acl_get_file(link, ACL_TYPE_EXTENDED) != NULL)
			mode[10] = '+';
	if (mode[0] != 'l')
		if (acl_get_file(full_path, ACL_TYPE_EXTENDED) != NULL)
			mode[10] = '+';
	if (listxattr(full_path, NULL, 0, 1) > 0)
		mode[10] = '@';
	return (mode);
}

void	get_list_data(char **tab, char *full_path, t_stat *s, t_dir *dir)
{
	tab[1] = file_mode(s, full_path);
	if (tab[1][0] == 'c' || tab[1][0] == 'b')
	{
		dir->special_file = 1;
		tab[7] = ft_itoa(major(s->st_rdev));
		tab[8] = ft_itoa(minor(s->st_rdev));
	}
	tab[2] = ft_itoa(s->st_nlink);
	if (getpwuid(s->st_uid))
		tab[3] = ft_strdup(getpwuid(s->st_uid)->pw_name);
	else
		tab[3] = ft_ltoa(s->st_uid);
	if (getgrgid(s->st_gid))
		tab[4] = ft_strdup(getgrgid(s->st_gid)->gr_name);
	else
		tab[4] = ft_ltoa(s->st_gid);
	tab[5] = ft_itoa(s->st_size);
	tab[6] = get_time(dir, s);
	if (tab[1][0] == 'l')
		if (!(tab[9] = get_link(full_path)))
			print_error(tab[0]);
}
