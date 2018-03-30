/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_verbose.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:02:43 by upopee            #+#    #+#             */
/*   Updated: 2018/03/30 20:27:04 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VERBOSE_H
# define COREWAR_VERBOSE_H

# define CW_CHAMPS_ERR	"{yellow}%d{eoc} input files given, [1-%d] needed\n"
# define CW_ERR_OPEN	"Could not open '{yellow}%s{eoc}', aborting\n"
# define CW_LOAD_ERR	"Some of the input files are not valid, aborting\n"
# define CW_FILE_KO		"'{yellow}%s{eoc}' is invalid, aborting\n"
# define CW_FILE_OK		"Introducing contestant '{yellow}%s{eoc}'\n\"%s\"\n"

#endif
