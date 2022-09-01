#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

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

int	find_prime(char *str)
{
	int	i;
	int	n;

	n = atoi(str);
	if (n % 2 == 0)
		return (0);
	i = 3;
	while (i < n)
	{
		if (n % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}

int	find_palindrome(char *str)
{
	int	i;
	int	len;

	len = strlen(str);
	len--;
	i = 0;
	while (str[i] == str[len - i])
		i++;
	if (i < len)
		return (0);
	if (find_prime(str) == 1)
		return (1);
	return (1);
}

char	*read_pi(int fd, int n)
{
	int		bytes_read;
	char	*str;
	char	*tmp;
	char	*buffer;

	buffer = malloc(sizeof(char) * 2);
	if (!buffer)
		return (NULL);
	buffer[1] = '\0';
	str = malloc(sizeof(char) * n + 1);
	if (!str)
		return (NULL);
	bytes_read = read(fd, str, n);
	str[n + 1] = '\0';
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 1);
		if (find_palindrome(str) == 1)
			break ;
		tmp = strjoin(str + 1, buffer);
		free(str);
		str = tmp;
	}
	if (bytes_read == 0)
	{
		write(1, "EOF\n", 4);
		exit(1);
	}
	return (str);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;

	if (argc != 3)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	str = read_pi(fd, atoi(argv[2]));
	write(1, "the number is: ", 15);
	write(1, str, strlen(str));
	write(1, "\n", 1);
	return (0);
}
