CC=cc

%.o:%.c
	$(CC) $(CFLAGS) $< -o $@
hwk4stmake: main.c
	#module load gnu openmpi # module is a function type module
	# be sure to call "make debug" in order to see homework 3 print debug messages
	$(CC) -o hwk4st main.c 
debug:
	#module load gnu openmpi # module is a function type module
	#$(call module,load gnu openmpi)
	$(CC) -o hwk4st main.c -DDEBUG
clean:
	rm hwk4st

#$(call module,load gnu openmpi)
define module
    $(shell eval $(${LMOD_CMD} bash load gnu openmpi); [ $? = 0 ] && eval $(${LMOD_SETTARG_CMD:-:} -s sh))
endef 
