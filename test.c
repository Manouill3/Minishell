
void ft_test(char ***i)
{
    **i = "salut";
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char **str = NULL;
    char *s = "nazi";

    str = calloc(10,sizeof(char *));
    str[0] = calloc(100,sizeof(char));
    str[0] = s;
    ft_test(&str);
    printf("str = %s\n", *str);
}