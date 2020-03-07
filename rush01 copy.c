#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void    ft_strcat(char *dest, char *src)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (dest[x] != '\0')
        x++;
    dest[x] = src[0];
    x++;
    dest[x] = '\0';
}

int		ft_atoi(char c)
{
	return(c - '0');
}

int		which_sector(int x, int y)
{
	int i;

	i = x / 3;
	i = i * 3 + y / 3;
	return (i);
}

char    **trans_to_arr_sc(char **arr)
{
    int i = 0;
    int j;
    char **arr_sc;

    arr_sc = (char**)malloc(sizeof(char*) * 9);
    while (i < 9)
    {
        arr_sc[i] = (char*)malloc(sizeof(char) * 10);
        arr_sc[i][0] = '\0';
        i++;
    }
    i = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            ft_strcat(arr_sc[which_sector(i, j)], &arr[i][j]);
            j++;
        }
        i++;
    }
    return (arr_sc);
}

char    ***fill_arr3d(void)
{
    char    ***arr;
    int     i;
    int     j;
    int     k;

    arr = (char***)malloc(sizeof(char**) * 9);
    i = 0;
    while (i < 9)
    {
        arr[i] = (char**)malloc(sizeof(char*) * 9);
        j = 0;
        while (j < 9)
        {
            arr[i][j] = (char*)malloc(sizeof(char) * 9);
            k = 0;
            while (k < 9)
            {
                arr[i][j][k] = '1' + k;
                k++;
            }
            j++;
        }
        i++;
    }
    return (arr);
}

char **fill_arr(char **str)
{
    char **arr_sc;
    int i;
    int j;
    arr_sc = (char**)malloc(sizeof(char*) * 9);
    i = 0;
    while (i < 9)
    {
        arr_sc[i] = (char*)malloc(9);
        j = 0;
        while (j < 9)
        {
            if(str[i + 1][j] == '.')
                arr_sc[i][j] = '0';
            else
                arr_sc[i][j] = str[i + 1][j];
            j++;
        }
        i++;
    }
    return (arr_sc);
}

int    see_answer_add(char *c, int *count, int k)
{
    int z;


    if (c - '0' > 0)
    {
        count++;
        z = k;
    }
    return (z);
}

void    see_answer(char **arr, char ***arr3d)
{
    int i;
    int j;
    int k;
    int count;
    int z;

    i = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            count = 0;
            k = 0;
            while (k < 9)
            {
                z = see_answer_add(&arr3d[i][j][k], &count, k);
                k++;
            }
            if (count == 1)
                arr[i][j] = arr3d[i][j][z];
            j++;
        }
        i++;
    }
}

void    del_sc(char **arr_sc, char ***arr3d)
{
    int i;
    int j;
    int k;

    i = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            k = 0;
            while (k < 0)
            {
                if (arr_sc[which_sector(i, j)][k] != '0')
                    arr3d[i][j][k - 1] = '0';
                k++;
            }
            j++;
        }
        i++;
    }
}

void    display_3d(char ***arr)
{
    int     i;
    int     j;
    int     k;
    i = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            k = 0;
            while (k < 9)
            {
                ft_putchar(arr[i][j][k]);
                ft_putchar(' ');
                k++;
            }
            ft_putchar('\n');
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

void    display_2d(char **arr)
{
    int     i;
    int     j;
    i = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            ft_putchar(arr[i][j]);
            ft_putchar(' ');
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

void    sort_3d_from_arr(char ***arr3d, char **arr)
{
    int i;
    int j;
    int k;
    i = 0;
    while(i < 9)
    {
        j = 0;
        while (j < 9)
        {
            if(arr[i][j] != '0')
            {
                k = 0;
                while (k < 9)
                {
                    if (k != arr[i][j] - 1 - '0')
                        arr3d[i][j][k] = '0';
                    k++;
                }
            }
            j++;
        }
        i++;
    }
}

int     check_del_hv(char el, int i, int j, char **arr)
{
    int x;
    int result;
    x = 0;
    result = 0;
    while (x < 9)
    {
        if (arr[i][x] == el || arr[x][i] == el)
            result = 1;
        x++;
    }
    return (result);
}

void    del_hv(char ***arr3d, char **arr)
{
    int i;
    int j;
    int k;
    i = 0;
    while(i < 9)
    {
        j = 0;
        while (j < 9)
        {
            k = 0;
            while (k < 9)
            {
                if (arr[i][j] == '0' && check_del_hv(arr3d[i][j][k], i, j, arr) == 1)
                    arr3d[i][j][k] = '0';
                k++;
            }
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    char **arr;
    char **arr_sc;
    char ***arr3d;

    arr = fill_arr(argv);
    arr_sc = trans_to_arr_sc(arr);
    arr3d = fill_arr3d();
    sort_3d_from_arr(arr3d, arr);
    del_hv(arr3d, arr);
    display_3d(arr3d);
}

