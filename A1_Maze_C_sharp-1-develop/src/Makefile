.PHONY: all install uninstall clean dvi dist test check_mk gcov_report install_lcov brew lcov style_check style clang valgrind

CC = g++ -std=c++17 -g
FLAGS = -Wall -Wextra -Werror

# PROJECT = $(shell pwd)
SOURCE_BUILD = AvaloniaApplication1
INSTALL_FOLDER = Maze_1.0

all: install dvi

install: uninstall build run

build:
	dotnet build AvaloniaApplication1/AvaloniaApplication1/AvaloniaApplication1.csproj
	mkdir ../../$(INSTALL_FOLDER)
	mv AvaloniaApplication1/AvaloniaApplication1/bin/Debug ../../$(INSTALL_FOLDER)/

run:
	./../../$(INSTALL_FOLDER)/Debug/net7.0/AvaloniaApplication1

uninstall: 
	rm -rf ../../$(INSTALL_FOLDER)

dvi:
	open -a "Google Chrome" manual.html


dist: cleandist build
	cd ../../ && tar -cvf s21_maze.tar.gz $(INSTALL_FOLDER)

cleandist:
	rm -rf ../../s21_maze.tar.gz

clean:
	rm -rf AvaloniaApplication1/AvaloniaApplication1/bin AvaloniaApplication1/Tests/bin report settings.txt

test: clean 
	dotnet test --collect:"XPlat Code Coverage" AvaloniaApplication1/Tests/Tests.csproj

# gcov_report: test
# 	reportgenerator -reports:"Path\To\TestProject\TestResults{guid}\coverage.cobertura.xml" -targetdir:"coveragereport" -reporttypes:Html 

style_check: clang
	# clang-format -n $(SOURCE_BUILD)/*.h $(SOURCE_BUILD)/*.cs
	find . -type f -name ".h" -o -name "*.cs" | xargs clang-format -style=Google -n

style: clang
	# clang-format -i $(SOURCE_BUILD)/*.h $(SOURCE_BUILD)/*.cs
	find . -type f -name ".h" -o -name "*.cs" | xargs clang-format -style=Google -i
	
clang:
ifeq ("","$(wildcard ./.clang-format)")
	cp -f ../materials/linters/.clang-format ./.clang-format
endif
