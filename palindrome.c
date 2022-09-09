#include "palindrome.h"

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	putnbr(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n > 9)
		putnbr(n / 10);
	if (n >= 0)
		ft_putchar((n % 10) + '0');
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

int	read_pi(int fd, int digits)
{
	unsigned int	i;
	unsigned int	j;
	int				bytes_read;
	char			*str;
	char			buffer[2];

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (digits + 1));
	bytes_read = read(fd, str, digits);
	str[bytes_read] = '\0';
	digits--;
	while (bytes_read > 0)
	{
		if (is_palindrome(str))
		{
			write(1, str, strlen(str));
			write(1, "\n", 1);
			write(1, "j = ", 4);
			putnbr(j);
			write(1, " i = ", 5);
			putnbr(i);
			write(1, "\n", 1);
		}
		bytes_read = read(fd, buffer, 1);
		memcpy(str, str + 1, digits);
		str[digits] = buffer[0];
		i++;
		if (i == 1000000000)
		{
			j++;
			i = 0;
		}
	}
	free(str);
	if (bytes_read == -1)
		write(2, "something went wrong\n", 21);
	else if (bytes_read == 0)
		write(1, "EOF\n", 4);
	return (bytes_read);
}

int	main(int argc, char **argv)
{
	int		fd;

	if (argc != 3)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	read_pi(fd, atoi(argv[2]));
	close(fd);
	return (0);
}
