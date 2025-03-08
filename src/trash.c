/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:48:47 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/08 17:48:49 by dwianni          ###   ########.fr       */
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