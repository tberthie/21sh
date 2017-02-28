OBJ=$(addprefix obj/,$(addsuffix .o,main setup quit signal path get_env input parse treat_char prompt func_0 func_1 termcap term builtins error input_f retrieve_input history source echo alias unalias env source func_2 completion completion_parse completion_simple_0 replace_parameters completion_simple_1 completion_ls operator globbing set_env env_check unset_env cd exec exec_path exec_pipes split_pipeline parse_exec parse_pipeline parse_redirs check_parsing exec_launch heredoc exec_redirs process_operators exec_conf split_args exec_pipes_crash restore_redirs locales set_locales hash_table))
NAME=42sh

all: obj $(NAME)

obj:
	mkdir obj

$(NAME): $(OBJ)
	make -Clibft
	gcc $^ -o $@ -Llibft -lft -ltermcap

obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinclude -Ilibft -Weverything

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re:fclean all
