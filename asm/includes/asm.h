/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:37:00 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 14:46:55 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <stdint.h>
# include "op.h"
# include "../../libft/libft.h"
# include <fcntl.h>

# define FILENAME lexer->filename
# define FD lexer->fd
# define LINE lexer->line
# define INDEX lexer->index
# define PREV_INDEX lexer->prev_index
# define LINE_NB lexer->line_nb

# define TOKEN lexer->current_token

# define INSTRUCTIONS infos->instructions
# define LABELS infos->labels
# define ADDR_INDEX infos->address_index

# define LST_L ((t_label *)lst->content)
# define LST_I ((t_instruction *)lst->content)

# define SWAP_UINT16(x)			(((x) >> 8) | ((x) << 8))
# define SWAP_UINT32LEFT(x)		(((x) >> 24) | (((x) & 0x00FF0000) >> 8))
# define SWAP_UINT32RIGHT(x)	((((x) & 0x0000FF00) << 8) | ((x) << 24))
# define SWAP_UINT32(x)			(SWAP_UINT32LEFT(x) | SWAP_UINT32RIGHT(x))

typedef enum		e_token_type
{
	NAME,
	COMMENT,
	DIRECT_LABEL,
	INDIRECT_LABEL,
	LABEL,
	TEXT,
	REGISTER,
	SEPARATOR,
	ENDLINE,
	END,
	ERROR
}					t_token_type;

union				u_value {
	char			*s;
	int				i;
};

typedef struct		s_token
{
	t_token_type	type;
	union u_value	value;
	char			valuetype;
}					t_token;

typedef struct		s_lexer
{
	char			*filename;
	int				fd;
	char			*line;
	int				line_nb;
	int				index;
	int				prev_index;
	t_token			*current_token;
}					t_lexer;

typedef struct		s_parameter
{
	t_arg_type		type;
	union u_value	value;
	char			valuetype;
}					t_parameter;

typedef struct		s_instruction
{
	int				address;
	int				size;
	t_op			*infos;
	t_parameter		params[3];
}					t_instruction;

typedef struct		s_label
{
	char			*name;
	int				address;
}					t_label;

typedef struct		s_infos
{
	char			*filename;
	char			*outputfilename;
	t_list			*instructions;
	t_list			*labels;
	t_header		header;
	int				address_index;
}					t_infos;

int					initialize_lexer(t_lexer *lexer, int fd, char *filename);
int					find_next_token(t_lexer *lexer);
int					eat(t_lexer *lexer, t_token_type token);
int					check(t_lexer *lexer, t_token_type token);
int					call_gnl(t_lexer *lexer);

int					is_endline(t_lexer *lexer);
int					is_separator(t_lexer *lexer);
int					is_name(t_lexer *lexer);
int					is_comment(t_lexer *lexer);
int					is_direct_label(t_lexer *lexer);
int					is_direct_label_text(t_lexer *lexer);
int					is_indirect_label(t_lexer *lexer);
int					is_indirect_label_number(t_lexer *lexer);
int					is_register(t_lexer *lexer);
int					is_text(t_lexer *lexer);
int					is_label(t_lexer *lexer);

/*
** Parser
*/

int					malloc_fail_error(t_lexer *lexer);
int					name_missing_error(t_lexer *lexer);
int					missing_closing_quote_error(t_lexer *lexer);
int					comment_missing_error(t_lexer *lexer);
int					eat_error(t_lexer *lexer, t_token_type token);
int					unknown_instruction_error(t_lexer *lexer,
															char *instruction);
int					unknown_label_error(t_infos *infos, char *label);
int					wrong_argument_error(t_lexer *lexer,
										t_instruction *instruction, int arg);
int					parse_line_error(t_lexer *lexer);
int					parse_label_error(t_lexer *lexer);

int					parse(int fd, char *filename);
int					parse_line(t_lexer *lexer, t_infos *infos);
int					parse_label(t_lexer *lexer, t_infos *infos);
int					parse_instruction(t_lexer *lexer, t_infos *infos);
char				*get_outputfilename(char *filename);

void				free_all(t_lexer *lexer, t_infos *infos);
void				free_labels(void *content, size_t content_size);
void				free_instructions(void *content, size_t content_size);
int					free_on_write_error(t_list *lst, int arg, char *buf);
int					free_on_parse_error(t_infos *infos, t_lexer *lexer);

int					parse_parameters(t_lexer *lexer, t_infos *infos,
																t_list *lst);
int					parse_reg(t_lexer *lexer, t_list *lst, int arg);
int					parse_dir_label(t_lexer *lexer, t_list *lst, int arg);
int					parse_indir_label(t_lexer *lexer, t_list *lst, int arg);

int					parse_name_comment(t_lexer *lexer, t_infos *infos);
int					parse_name(t_lexer *lexer, t_infos *infos);
int					parse_comment(t_lexer *lexer, t_infos *infos);

int					write_in_file(t_infos *infos);
int					write_in_file2(t_infos *infos, char *buf, int index);
int					write_in_file3(t_infos *infos, char *buf);
int					loop_args(t_infos *infos, char *buf, int *index,
																t_list *lst);

void				write_register(char *buf, int *index, t_list *lst, int arg);
void				write_direct_label(char *buf, int *index, t_list *lst,
																	int arg);
void				write_indirect_label(char *buf, int *index, t_list *lst,
																	int arg);
int					find_address_label(char *str, t_infos *infos);
char				get_codage(t_instruction *instruction);

char				*get_name_argtype(int n);
char				*get_name_tokentype(t_token_type token);
t_op				*get_opinfos(char *name);
char				*get_name_opcode(int n);
void				pass_spaces(t_lexer *lexer);

#endif
