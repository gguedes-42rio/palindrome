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

int	is_prime(int n)
{
	int	i;

	if (n % 2 == 0 || n < 2)
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

char	*is_palindrome(char *str)
{
	int	i;
	int	len;

	len = strlen(str);
	len--;
	i = 0;
	while (str[i] == str[len - i] && i < len)
		i++;
	if (i < len)
		return (NULL);
	return (str);
}

char	*read_pi(int fd, int n)
{
	int		bytes_read;
	char	*str;
	char	*tmp;
	char	*buffer;

	buffer = malloc(sizeof(char) * 2);
	if (!buffer)
		exit(1);
	buffer[1] = '\0';
	str = malloc(sizeof(char) * n + 1);
	if (!str)
		exit(1);
	bytes_read = read(fd, str, n);
	str[n + 1] = '\0';
	while (bytes_read > 0)
	{
		if (is_palindrome(str))
		{
			if (str[0] == '1' || str[0] == '3'
				|| str[0] == '7' || str[0] == '9')
			{
				write(1, str, strlen(str));
				write(1, "\n", 1);
			}
		}
		bytes_read = read(fd, buffer, 1);
		tmp = strjoin(str + 1, buffer);
		free(str);
		str = tmp;
	}
	return (str);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 3)
	{
		write(2, "invalid args\n", 13);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "unable to open file\n", 20);
		return (1);
	}
	read_pi(fd, atoi(argv[2]));
	write(1, "EOF\n", 4);
	return (0);
}
