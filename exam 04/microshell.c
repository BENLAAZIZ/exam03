#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void	ft_putstr_fd2(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while(*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
}


void ft_ex(char **av, int i, int tmp, char **env)
{
    av[i] = NULL;
    dup2(tmp, 0);
    close(tmp);
    execve(av[0], av, env);
    ft_putstr_fd2("error: cannot execute ", av[0]);
    exit(1);
}

int main(int ac, char **av, char **env)
{
    int i;
    int tmp;
    int fd[2];

    (void)ac;
    i = 0;
    tmp = dup(0);
    while (av[i] && av[i + 1])
    {

        av = &av[i + 1];
        i = 0;
        while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
            i++;
        if (strcmp(av[0], "cd") == 0)
        {
            if (i != 2)
                ft_putstr_fd2("error: cd: bad arguments", NULL);
            else if (chdir(av[1]) != 0)
                ft_putstr_fd2("error: cd: cannot change directory to ", av[1]	);
        }
        else if (i != 0 && (av[i] == NULL || strcmp(av[i], ";") == 0))
        {
            if (fork() == 0)
                ft_ex(av, i , tmp, env);
            else
            {
                close(tmp);
                while(waitpid(-1, NULL, WUNTRACED) != -1)
                    ;
                tmp = dup(0);
            }
        }
        else if (i != 0 && strcmp(av[i] , "|") == 0)
        {
            pipe(fd);
            if (fork() == 0)
            {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
                ft_ex(av, i, tmp, env);
            }
            else
            {
                close(fd[1]); 
                close(tmp);
                tmp = fd[0];
            }
        }
    }
    close(tmp);
    return 0;
}