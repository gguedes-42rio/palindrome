#include "palindrome.h"

char	*strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*new_str;

	if (!s1)
		return (NULL);
	new_str = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2)
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	return (new_str);
}

char	*is_palindrome(char *str)
{
	int	i;
	int	len;

	len = strlen(str);
	len--;
	i = 0;
	while (str[i] == str[len - i] && i < len - i)
		i++;
	if (i < len - i)
		return (NULL);
	return (str);
}

char	*read_pi(int fd, int digits)
{
	int		bytes_read;
	char	*str;
	char	*tmp;
	char	buffer[2];

	str = malloc(sizeof(char) * (digits + 1));
	bytes_read = read(fd, str, digits);
	str[bytes_read] = '\0';
	while (bytes_read > 0)
	{
		if (is_palindrome(str))
		{
			write(1, str, strlen(str));
			write(1, "\n", 1);
		}
		bytes_read = read(fd, buffer, 1);
		tmp = strjoin(str + 1, buffer);
		free(str);
		str = tmp;
	}
	if (bytes_read == -1)
		write(2, "something went wrong\n", 21);
	else if (bytes_read == 0)
		write(1, "EOF\n", 4);
	return (str);
}

int	main(int argc, char **argv)
{
	int		fd;

	if (argc != 3)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	read_pi(fd, atoi(argv[2]));
	return (0);
}
