/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 03:52:42 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/21 13:34:26 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "op.h"

# define DELIMITER " \t,"
# define MAX_COR_SIZE 4096
# define T_NO 0
# define T_INT 1
# define T_SHORT 2

typedef struct				s_stab
{
	char					**s;
	int						nb;
}							t_stab;

typedef struct				s_asm_err
{
	int						line;
	int						col;
	char					*msg;
	int						paramnb;
	char					*typemsg;
	char					*typemsg2;
	int						type;
	char					*endmsg;
	char					*msg2;
}							t_asm_err;

typedef struct				s_op
{
	char					*opcode;
	int						param_number;
	int						params_type[3];
	int						opnum;
	int						cycles;
	char					*description;
	int						oct;
	int						dirsizetwo;
}							t_op;

typedef struct				s_reg_exp
{
	char					*reg_exp;
	int						value;
}							t_reg_exp;

typedef enum				e_type
{
	reg_exp,
	dir_int_exp,
	dir_lab_exp,
	ind_int_exp,
	ind_lab_exp
}							t_type;

typedef struct				s_param
{
	t_type					type;
	union
	{
		t_reg_exp			reg;
		char				*dir_lab;
		unsigned int		dir_int;
		char				*ind_lab;
		unsigned short int	ind_int;
	}						val;
}							t_param;

typedef struct				s_inst
{
	int						address;
	int						label_bool;
	char					**label;
	int						opc;
	int						code_bool;
	int						code;
	t_param					params[3];
	int						nbparams;
	struct s_inst			*next;
}							t_inst;

typedef struct				s_head
{
	enum
	{
		prog_name_exp,
		prog_comment_exp
	}						type;
	char					val[COMMENT_LENGTH + 1];
	struct s_head			*next;
}							t_head;

typedef struct				s_labcall
{
	unsigned int			addr_tow;
	unsigned int			address_inst;
	char					*name;
	int						nb;
	unsigned short int		val;
	size_t					bytes;
	struct s_labcall		*next;
}							t_labcall;

typedef struct				s_data
{
	t_head					*raw_header;
	int						head_type;
	int						nb_name_prog;
	int						nb_comment_prog;
	t_inst					*inst;
	t_inst					*first_inst;
	int						nb_bytes;
	int						size_place;
	int						start_prog;
	t_labcall				*label_call;
	int						buflen;
	int						fd;
	int						write;
	char					*fnameout;
	int						fdin;
}							t_data;

extern t_op					g_op_tab[17];

char						**ft_bstrsplit2(char const *s, char *delimiter);
char						*ft_strndup(const char *s1, size_t len);
char						*ft_basename(char *s);
long long int				ft_atolli(const char *str);
int							ft_isext(char *s, char *type);

/*
**	asm_lexer.c
*/
int							asm_is_prog_head(t_data *data, char *buffer);
int							asm_is_label(char *buffer);
int							asm_opcode(char *buffer, t_op *op_tab);
int							asm_which_param(char *buffer);

/*
**	asm_read_utils.c
*/
int							asm_init_head(t_data *data, t_head **head);
int							asm_init_instruct(t_inst **inst);
void						asm_add_head(t_head **header, t_head *head);
void						asm_add_inst(t_data *data, t_inst **raw_inst,
								t_inst *inst, t_op *op_tab);
void						asm_init_dir_types(int *dir_types);

/*
**	asm_inst_utils.c
*/
void						asm_delone_inst(t_data *data, t_inst **insts,
								t_inst *todel);

/*
**	asm_labels_utils.c
*/
void						asm_ptrcpy(char ***to, char **from);
void						asm_bigger_lab(t_data *data, char ***label, int nb);
void						asm_cpyto_nolab(t_data *data, char ***label,
								int *nb);
void						asm_cpyto_inlinelab(t_data *data, char ***label,
								int *nb);
void						asm_cpyto_tmplab(t_data *data, char ***label,
								int *nb);
void						asm_prepare_tmplab(t_data *data, char ***label,
								int nb);

/*
** asm_check
*/
void						asm_check(t_data *data, t_inst *inst,
								t_op *op_tab);
void						asm_check_live(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_ld(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_st(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_add(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_sub(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_and(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_or(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_xor(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_zjmp(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_ldi(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_sti(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_fork(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_lld(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_lldi(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_lfork(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_aff(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_null(t_data *data, t_inst *inst,
								t_op *optab, t_asm_err asm_errno);
void						asm_check_labels(t_data *data);

/*
**	asm_read.c
*/
void						asm_read(int fd, t_data *data);
void						asm_parse_opcode(t_data *data, t_inst **inst,
								char *splited_line, int *i);
void						asm_parse_comment(int *i);
void						asm_check_inst(t_data *data, t_inst **inst,
								char *splited_line, int *i);

/*
**	asm_parse_header.c
*/
int							asm_parse_header(t_data *data, char *line, int nu,
								int head_type);

/*
**	asm_parse.c
*/
void						asm_parse(t_data *data, char **split_line, int nu,
								char *line);

/*
**	asm_parse_params.c
*/
void						asm_parse_params(t_data *data, t_inst **inst,
								char *splited_line, int *i);

/*
**	asm_parse_utils.c
*/
void						asm_stuck_opcode(t_data *data, t_inst **inst,
								char *sline, int *i);
void						asm_comment_afterhead(t_data *data, char *line,
								int *i);
void						asm_parse_reg(t_data *data, t_inst **inst,
								char *sline, int *i);
void						asm_catch_val_indlab(t_data *data, t_inst **inst,
								char *sline, int j);

/*
**	asm_translation.c
*/
void						asm_wtranslation(t_data *data, t_op *optab);

/*
**	asm_translate_insts
*/
void						asm_live(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_ld(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_st(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_add(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_sub(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_and(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_or(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_xor(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_zjmp(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_ldi(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_sti(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_fork(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_lld(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_lldi(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_lfork(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_aff(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);
void						asm_null(t_data *data, t_inst *inst,
								unsigned char *corfile, t_op *op_tab);

/*
**	asm_translate_buf.c
*/
void						asm_cor_uintcpy(t_data *data,
								unsigned char *corfile, unsigned int nb,
								size_t byt);
void						asm_cor_uileeks(t_data *data,
								unsigned int nb, int addr);
void						asm_cor_usileeks(t_data *data,
								unsigned short int nb, int addr);
void						asm_cor_memcpy(t_data *data,
								unsigned char *corfile, int size,
								char *to_cpy);
void						asm_cor_memcpy1(t_data *data,
								unsigned char *corfile, int size,
								unsigned char to_cpy);

/*
**	asm_translate_buf2.c
*/
void						asm_write(t_data *data, unsigned char *corfile);
unsigned char				*asm_uint_to_char(t_data *data, unsigned int nb,
								size_t byt);
void						asm_openwr(t_data *data);

/*
**	asm_translate_header.c
*/
void						asm_header_translate(t_data *data,
								unsigned char *corfile);

/*
**	asm_translate_params.c
*/
void						asm_dir_param(t_data *data, t_inst *inst,
								unsigned char *corfile, int i);
void						asm_undir_param(t_data *data, t_inst *inst,
								unsigned char *corfile, int i);
void						asm_paramcode(t_data *data, t_inst *inst,
								unsigned char *corfile);

/*
**	asm_translate_labcall.c
*/
int							asm_init_labcall(t_data *data,
								t_labcall **labcall);
void						asm_label_call(t_data *data);

/*
**	asm_usage.c
*/
void						asm_usage(void);

/*
**	asm_error.c
*/
int							asm_err_col(char *line, char *split_line);
void						asm_handle_error(t_data *data, int line,
								int col, char *msg);
void						asm_print_exit(t_asm_err asm_errno);
void						asm_handle_error2(t_data *data,
								t_asm_err asm_errno, int opcode, t_op *optab);
void						asm_print_exit2(t_asm_err asm_errno);
void						asm_handle_error3(t_data *data, char *msg);
void						asm_handle_error4(t_data *data, int type,
								char *lab);
void						asm_memerr(t_data *data);
void						asm_err(char *msg);
void						asm_memerr2(t_data *data);
void						asm_handle_error21(t_asm_err *asm_errno);
void						asm_memerr3(void);

/*
**	asm_free.c
*/
void						asm_free_header(t_head *header);
void						asm_free_insts(t_inst *inst);
void						free_label_calls(t_labcall *labcall);
void						asm_free_label(char ***label);

#endif
