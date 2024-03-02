CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic 
LDFLAGS = -lgtest -pthread
GCFLAGS = -fprofile-arcs -ftest-coverage
VG_FLAGS =	--vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
FS = -fsanitize=address -g
CHECK =	$(shell pkg-config --cflags --libs check)

SRC	= $(wildcard ./s21_*.h) 
OBJ	= $(patsubst ./s21_%.h, ./s21_%.o, ${SRC})
TEST = test
LIB = s21_container.a
FILE_TEST =	$(wildcard ./tests/s21_*.cc)

all: clean test

test:clean
# $(CC) $(CFLAGS) $(LDFLAGS) --coverage ./tests/*.cc ./s21_matrix/*.cc -o $(TEST) $(GCFLAGS)
# $(CC) $(CFLAGS) $(LDFLAGS) tests/s21_stack.cc s21_matrix/s21_matrix_oop.cc -o $(TEST) $(GCFLAGS)
	$(CC) $(CFLAGS) $(LDFLAGS) tests/s21_set.cc -o $(TEST) $(GCFLAGS)
	./$(TEST)

clean:
	@rm -f  ./*.o ./*.a ./*.gcda ./*.gcno ./*.info ./*.out $(TEST)
	@rm -rf coverage $(TEST).dSYM $(TEST)s.dSYM 
	@rm -rf googletest

gcov_report: test
	@lcov -t "containers_test" -o containers_test.info -c -d . --no-external --ignore-errors mismatch
	genhtml -o report containers_test.info
	open report/index.html


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
