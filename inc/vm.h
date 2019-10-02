/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 07:28:56 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/21 13:45:19 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "../ft_printf/ft_printf.h"
# include "./op.h"
# include "../libft/libft.h"
# include <limits.h>
# include <locale.h>
# include <curses.h>
# ifdef __linux__
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_mixer.h>
# elif __APPLE__
#  include <SDL.h>
#  include <SDL_mixer.h>
# endif
# define NEXT_IS_NBR_CYCLE		90
# define IS_NBR_CYCLE			10
# define RESET_DEFAULT			20
# define NEXT_IS_PLAYER_NUM		30
# define IS_PLAYER_NUM			40
# define NEXT_IS_ASM			50
# define IS_ASM					60
# define PARSING_OVER			70
# define DEFAULT_STATE			80
# define VISU_REQ				100
# define BRIGHT_WHITE			15

typedef struct			s_process
{
	int					id;
	unsigned	int		reg[16];
	int					pc;
	int					activation_countdown;
	int					carry;
	struct s_process	*next;
	int					player_master;
	int					player_num;
	int					alive;
}						t_process;

typedef struct			s_player
{
	int					num;
	char				name[128];
	char				comment[2048];
	int					live_count;
	char				alive;
	t_process			*process;
	t_process			*initial_process;
	int					pos;
	unsigned int		prog_size_head;
	int					first_fork;
}						t_player;

typedef struct			s_music
{
	Mix_Music			*fork;
	Mix_Music			*ready;
	Mix_Music			*death;
	Mix_Music			*win;
}						t_music;

typedef struct			s_data
{
	int					arena[MEM_SIZE];
	int					c_arena[MEM_SIZE];
	int					p_arena[MEM_SIZE];
	int					nbr_cycles;
	int					cycle_to_die_tmp;
	int					live_checker_countdown;
	int					player_num;
	int					assigned_player_nums[100];
	int					parsing_state;
	int					nbr_of_players;
	int					alive_players;
	int					last_live;
	int					nb_process_lives;
	int					max_checks;
	int					oct_c[4];
	unsigned int		param_val[4];
	int					param_size[4];
	int					params_size;
	int					next_inst_addr;
	int					c_dump;
	WINDOW				*n_arena;
	WINDOW				*b_arena;
	WINDOW				*r_arena;
	WINDOW				*rb_arena;
	int					pause;
	int					ready;
	t_music				music;
	int					xspeed;
	int					yspeed;
	int					sleep;
	int					mode;
	int					mode_death;
	t_process			*init_process[4];
	int					vis;
	t_player			*player_0;
	int					step;
}						t_data;

int						ft_itoa_base2(uintmax_t n, char *buf);
int						get_from_mem(int addr, int size, int mem[]);
int						mem_shift(short int shift, int pc, int long_addr);
int						parsing(char **argv, int argc
						, t_data *data, t_player *players);
int						mem_dump(int arena[MEM_SIZE]);
int						parse_no_asm_arg(t_data *data, t_player *player
						, char *arg, int i);
int						err(char *msg);
int						print_usage();
int						mem_dump(int arena[MEM_SIZE]);
void					define_nbr_players(t_data *data
						, int i, int argc, char **argv);
int						parse_asm_arg(char *argv, t_player *player
						, t_data *data, int players_nbr);
int						define_player_num(t_data *data, t_player *player
						, char *argv, int player_num_explicite);
int						war_time(t_data *data, t_player *player);
int						kill_every_one(t_player *player, t_data *data);
t_process				*create_process(t_process *process, int pc
						, int player_master, t_data *data);
int						ft_parsing_ins(t_data *data, int addr, int op_code);
int						parsing_ins(t_data *data, int addr, int op_code);
int						live_checker(t_data *data, t_player *player);
void					vm_err_player(char *msg, char *name);
int						check_prog_size(t_player *player, int i, char *argv);
int						is_player(int i, int buf);
int						noop(t_process *process, t_data *data, t_player *player
						, int cycle);
int						live(t_process *process, t_data *data, t_player *player
						, int cycle);
int						ld_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						st_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						add_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						sub_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						and_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						or_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						xor_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						zjump_(t_process *process, t_data *data
						, t_player *player, int cycle);
int						ldi_(t_process *process, t_data *data
						, t_player *player, int cycle);
int						sti_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						fork_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						lld_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						lldi_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						lfork_(t_process *process, t_data *data
						, t_player *player, int cycle);
int						aff_(t_process *process, t_data *data, t_player *player
						, int cycle);
int						vm_noop_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_live_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_ld_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_st_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_add_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_sub_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_and_check(t_data *data, int addr
						, int oct_c, int nb_params);
int						vm_or_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_xor_check(t_data *data, int addr
						, int oct_c, int nb_params);
int						vm_zjmp_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_ldi_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_sti_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_fork_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_lld_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_lldi_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_lfork_check(t_data *data, int addr, int oct_c
						, int nb_params);
int						vm_aff_check(t_data *data, int addr, int oct_c
						, int nb_params);
void					init_uninitialized(t_data *data, t_player *player);
void					set_aliveprocess(t_data *data, int i, int set);
void					vm_process_die(t_data *data, int i);
void					vm_init_ncurses(t_data *data);
int						vm_ncurgetch(t_data *data, t_player *players
						, char ch1);
void					vm_ncur_pause(t_data *data, t_player *players
						, int ready);
void					vm_logoput(t_data *data);
void					vm_ncurside_status(t_data *data);
void					vm_ncurside_mode(t_data *data);
void					vm_speedput(t_data *data);
void					vm_ncurside_process(t_data *data, t_player *player);
void					vm_ncursideput(t_data *data, int cycle
						, t_player *players);
void					vm_ncur_change_color(t_data *data, int color
						, int process);
int						vm_ncur_coldump(t_data *data, t_player *player);
void					vm_ncur_before_fight(t_data *data, int cycle
						, t_player *players);
void					vm_ncur_after_fight(t_data *data, int cycle
						, t_player *players);
void					vm_ncurs_end(t_data *data, int cycle
						, t_player *players);
void					vm_ncurs_quit(t_data *data, t_player *players);
long int				vm_abs(long int *nb);
void					vm_negsign(long int *nb, int neg);

int						display_winner(t_data *data, t_player *player,
						int nbr_of_players);
void					init_uninitialized(t_data *data, t_player *player);
int						live(t_process *process, t_data *data,
						t_player *player, int cycle);

#endif
