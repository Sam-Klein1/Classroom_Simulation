COURSE = cs240
SEMESTER = spring2023
CP_NUMBER = 2
LASTNAME = Klein
USER = sklein27
GITUSERID = Sam-Klein1
EXE = scheduler_cp2

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/scheduler.o $(OBJ)/student.o $(OBJ)/course.o $(OBJ)/courselist.o $(OBJ)/studentlist.o
	$(CC) $(FLAGS) $(OBJ)/scheduler.o $(OBJ)/student.o $(OBJ)/course.o $(OBJ)/courselist.o $(OBJ)/studentlist.o -o $@

$(OBJ)/scheduler.o: courselist.h studentlist.h
	$(CC) $(FLAGS) -c scheduler.cpp -o $@

$(OBJ)/student.o: student.cpp student.h
	$(CC) $(FLAGS) -c student.cpp -o $@

$(OBJ)/course.o: course.cpp course.h
	$(CC) $(FLAGS) -c course.cpp -o $@

$(OBJ)/courselist.o: courselist.cpp courselist.h
	$(CC) $(FLAGS) -c courselist.cpp -o $@
	
$(OBJ)/studentlist.o: studentlist.cpp studentlist.h
	$(CC) $(FLAGS) -c studentlist.cpp -o $@


	

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz
