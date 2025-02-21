#include "get_next_line.h"


int ft_strlen(char *str)
{

                int idx;
                idx = 0;
                while(str[idx])
                        idx++;
                return(idx);
}

char *ft_strchr(char *str, int c)
{
        while(*str)
        {
                if(*str == c)
                    return(str);
                str++;

        }

        return(0);
}
char	*ft_strdup(char *str)
{
	int		idx;
	char	*buf;

	if (!(buf = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	idx = 0;
	while (str[idx])
	{
		buf[idx] = str[idx];
		idx++;
	}
	buf[idx] = '\0';
	return (buf);
}


char	*ft_substr(char *str, int start, int len)
{
	int				idx;
	char			*buf;

	if (!(buf = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		buf[idx] = str[start + idx];
		idx++;
	}
	buf[idx] = '\0';
	return (buf);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int				idx;
	char			*buf;

	if (!(buf = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	idx = 0;
	while (*s1)
		buf[idx++] = *s1++;
	while (*s2)
		buf[idx++] = *s2++;
	buf[idx] = '\0';
	return (buf);
}

int		get_next_line(char **line)
{
	int	len; 
	int	bytes;
	char *tmp; 
	char  buf[2]; 
	static char	*store; 

	store = (store == NULL) ? ft_strdup("") : store;
	bytes = 1; 
	while (bytes > 0 && !ft_strchr(store, '\n')) 
	{
		bytes = read(0, buf, 1); 
		buf[bytes] = '\0';
		tmp = ft_strjoin(store, buf); 
		free(store);
		store = tmp;
	}
	if (ft_strchr(store, '\n')) 
	{
		len = ft_strchr(store, '\n') - store; 
		*line = ft_substr(store, 0, len); 
		tmp = ft_substr(store, len + 1, ft_strlen(store) - len); 
		free(store);
		store = tmp;
	}
	if (bytes == 0)
	{
		*line = ft_strdup(store); 
		free(store);
		store = NULL;
	}
	return (bytes); 
}