.PHONY:clean all

WORKDIR=.
VPATH = ./src

CC=g++
CFLGS= -Wall -g -I$(WORKDIR)/inc/


BIN = java2cpp

all:$(BIN)

java2cpp:op.o bin_stream.o date_tool.o db_fd.o db_stat.o db_userpattern.o stat_func.o stat_func_avg.o\
	stat_func_bindist.o stat_func_bindist_rang.o stat_func_count.o   stat_func_count_equals.o stat_func_count_uniq.o stat_func_dummy.o\
	stat_func_max.o stat_func_min.o stat_func_nmdist.o stat_func_snapshot.o stat_func_status.o stat_func_sum.o\
	stat_number_encode.o stat_row.o stat_win.o stat_win_base.o stat_win_time.o tmsapp.o java2cpp_log.o
	$(CC) $(LIBFLAG) $^ -o $@ 
#-licdbapi  -lclntsh
	
		
%.o:%.cpp
	$(CC) $(CFLGS) -c $< -o $@	

clean:
	rm -f *.o $(BIN)
	
	
	




