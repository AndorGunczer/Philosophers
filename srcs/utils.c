# include "../inc/philosophers.h"

static	int	ft_isspace(char c);

int	ft_atoi(const char *str)
{
	int		i;
	int		j;
	int		num;

	i = 0;
	j = 0;
	num = 0;
	while (ft_isspace(*(str + i)) == 1 && str[i] != '\0')
	{
		i++;
		j++;
	}
	if (str[i] == '\0')
		return (0);
	if (*(str + j) == '-' || *(str + j) == '+')
		i++;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
	{
		num = num * 10 + (*(str + i) - '0');
		i++;
	}
	if (*(str + j) == '-')
		num *= -1;
	return (num);
}

static	int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	else if ((c == '\n' || c == '\t' || c == '\v' || c == '\t' || c == '\r'
			|| c == '\f'))
		return (1);
	else
		return (0);
}