#include <stdlib.h>
#include <unistd.h>
#include "lem_in.h"

t_result		ft_get_line_from_buffer(t_buf *buf, t_string **str, int fd)
{
	int was_endl;

	if (buf->pos >= buf->len && buf->len == buf->capac)
	{
		buf->len = ft_read(fd, buf->buffer, (size_t)buf->capac);
		buf->pos = 0;
		if (buf->len <= 0)
			return (buf->len == 0 ? NO_LINE : ERROR);
	}
	else if (buf->pos >= buf->len)
		return (*str == 0 ? NO_LINE : ENDL_GOT);
	if (!*str)
		if (!(*str = ft_make_string(INIT_VECT_SIZE)))
			return (ERROR);
	while (buf->pos < buf->len && buf->buffer[buf->pos] != '\n')
	{
		if (!ft_string_push_back(str, buf->buffer[buf->pos]))
			return (ERROR);
		buf->pos++;
	}
	was_endl = (buf->pos < buf->len && buf->buffer[buf->pos] == '\n') ? 1 : 0;
	buf->pos += was_endl;
	if (was_endl || (buf->pos - was_endl == buf->len && buf->len < buf->capac))
		return (ENDL_GOT);
	return (ENDL_NOT_FOUND);
}

t_result		ft_append_line(t_buf *buf, int fd, t_string *str)
{
	t_result res;

	res = ENDL_NOT_FOUND;
	while (res == ENDL_NOT_FOUND)
	{
		buf->len = ft_read(fd, buf->buffer, (size_t)buf->capac);
		buf->pos = 0;
		res = ft_get_line_from_buffer(buf, &str, fd);
		if (res == ERROR || res == NO_LINE)
			return (res);
	}
	return (ENDL_GOT);
}

void			ft_free_buf(void *buf)
{
	free(((t_buf*)buf)->buffer);
	free(buf);
}

t_result		ft_gnl_init_works(int fd, t_map **fd_bf, t_buf ***curr_buf,
		int buf_size)
{
	t_result res;

	res = fd < 0 ? ERROR : ENDL_NOT_FOUND;
	if (res == ERROR)
		return (res);
	if (!*fd_bf)
		*fd_bf = ft_make_custom_value_map(INT32_T, ft_free_buf);
	if (!*fd_bf)
		return (ERROR);
	*curr_buf = (t_buf**)ft_map_get(*fd_bf, (void*)(size_t)fd);
	if (!*curr_buf)
		return (ERROR);
	if (**(void***)curr_buf == (*fd_bf)->nil)
	{
		if (!(**curr_buf = (t_buf*)malloc(sizeof(t_buf))))
			return (ERROR);
		***curr_buf = (t_buf){(char*)ft_memalloc((size_t)buf_size), 0, 0,
						buf_size};
		if (!(**curr_buf)->buffer || ((**curr_buf)->len = ft_read(fd,
				(**curr_buf)->buffer, (size_t)(**curr_buf)->capac)) == -1)
			return (ERROR);
	}
	return (res);
}

int				ft_gnl_free_ret(t_string *str, int ret)
{
	free(str);
	return (ret);
}

int				ft_get_next_line(const int fd, char **line, int buff_size)
{
	static t_map	*fd_bf = 0;
	t_result		res;
	t_buf			**curr_buf;
	t_string		*str;

	str = 0;
	res = !line ? ERROR : ft_gnl_init_works(fd, &fd_bf, &curr_buf, buff_size);
	if (res != ERROR)
		res = ft_get_line_from_buffer(*curr_buf, &str, fd);
	if (res == ENDL_NOT_FOUND)
		res = ft_append_line(*curr_buf, fd, str);
	if (res == ERROR || !ft_string_fit(&str))
		res = ERROR;
	if (res != ERROR && line)
		*line = (str == 0) ? *line : str->data;
	else if (line)
		*line = 0;
	if (res == NO_LINE || res == ERROR ||
		(fd >= 0 && fd <= 2 && (*curr_buf)->pos == (*curr_buf)->len))
	{
		ft_map_del(fd_bf, (void*)(size_t)fd);
		if (fd_bf && fd_bf->size == 0)
			ft_free_map(&fd_bf);
	}
	return (ft_gnl_free_ret(str, res));
}
