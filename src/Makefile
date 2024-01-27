CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic -g 
LDFLAGS = -lgtest -pthread
GCFLAGS = -fprofile-arcs -ftest-coverage
VG_FLAGS =	--vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
FS = -fsanitize=address -g
CHECK =	$(shell pkg-config --cflags --libs check)

SRC	= $(wildcard ./s21_*.h) 
OBJ	= $(patsubst ./s21_%.h, ./s21_%.o, ${SRC})
TEST = tests
LIB = s21_container.a
FILE_TEST =	$(wildcard ./tests/s21_*.cc)

all: clean test

test:
	g++ -Wall -Wextra -Werror -std=c++17 -pedantic -lgtest -pthread tests/s21_stack.cc s21_matrix/s21_matrix_oop.cc && ./a.out

clean:
	@rm -f  ./*.o ./*.a ./*.gcda ./*.gcno ./*.info ./*.out ./$(TEST)/$(TEST)
	@rm -rf coverage $(TEST).dSYM $(TEST)s.dSYM 
	@rm -rf googletest

# $(LIB):
# 	@echo "+-------------------+"
# 	@echo "|     MAKE_LIB      |"
# 	@echo "+-------------------+"
# 	@$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRC)  
# 	@ar -rcs $@ $(OBJ)

# $(TEST): clean $(LIB)
# 	@echo "+-------------------+"
# 	@echo "|     UNIT_TEST     |"
# 	@echo "+-------------------+"
# 	@$(CC) $(CFLAGS) $(FILE_TEST) $(LIB) -o $@ $(LDFLAGS)
# 	@./$(TEST)/$(TEST)

# gcov_report: $(TEST)
# 	@echo "+-------------------+"
# 	@echo "|    GCOV_REPORT    |"
# 	@echo "+-------------------+"
# 	@$(CC) --coverage $(GCFLAGS) $(CFLAGS) $(LDFLAGS) $(FILE_TEST) $(LIB) $(SRC) -o test 
# 	@./$(TEST)
# 	@rm -f *test.gcno *test.gcda 
# 	@lcov -t lcov_branch_coverage=1 --ignore-errors  mismatch -t "tests" -o tests.info \
# 				-c -d . --no-external 
# 	@genhtml -o coverage tests.info 
# 	@open coverage/index.html

# valgrind_check: test
# 	@CK_FORK=no valgrind  $(VG_FLAGS) ./$(TEST)

# check:
# 	@echo "+-------------------+"
# 	@echo "|    STYLE_CHECK    |"
# 	@echo "+-------------------+"
# 	@clang-format -style=Google -n *.cc *.h
# 	@clang-format -style=Google -n */*.cc 

# clang:
# 	clang-format -style=Google -i *.cc *.h
# 	clang-format -style=Google -i */*.cc 
# 	clang-format -style=Google -n *.cc *.h
# 	clang-format -style=Google -n */*.cc

rebuild: clean $(LIB)
