/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:48:47 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/15 20:13:21 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* BOUT DE PROGRQMME EXECVE*/
/*
	const char *pathname = "/bin/cat";


	//cat <out1 >out2 >out3
	//cat <out1 >>out2 >>out3
    // Les arguments à passer à la commande (argv[])
    char *const argv[] = {
        "toto",    
		// Par convention, le premier argument est le nom de la commande
        "<out1",    // Option pour afficher les fichiers détaillés
		"out2",
		"out3",
		NULL     // Tableau d'arguments doit se terminer par NULL
    };

    // Les variables d'environnement (envp[])
    extern char **environ;  // L'environnement par défaut

    // Exécute le programme
    if (execve(pathname, argv, environ) == -1) {
        perror("execve toto");  // Si execve échoue
        exit(EXIT_FAILURE);
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
int main() {
    int id = fork();
	printf("Current ID %d Parent ID %d ID %d\n", getpid(), getppid(), id);

    return 0; 
}
*/

int	main()
{
	int	fd[2];
	int pid1;
	int	pid2;

	if (pipe(fd) == - 1)
		return (1);
	pid1 = fork();
	if (pid1 <0)
		return (2);
	if (pid1 ==0)
	{
		//dup2(fd[1], STDOUT_FILENO);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid2 = fork();
	if (pid2 <0)
		return (3);
	if (pid2 ==0)
	{
		//dup2(fd[0], STDIN_FILENO);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	
	return (0);
}