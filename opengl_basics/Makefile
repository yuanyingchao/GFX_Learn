# OpenGL 基础示例 Makefile

# 编译器设置
CC = g++
CFLAGS = -Wall -g -finput-charset=UTF-8 -fexec-charset=UTF-8
LDFLAGS = -lglfw -lGL -lGLEW -lm

# 目标：所有示例程序
TARGETS = example01_window example02_point example03_line example04_triangle example05_color_triangle example06_vbo example07_vao example08_ebo example09_shaders example10_texture

# 默认目标：编译所有示例
all: $(TARGETS)

# 编译每个示例
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# 清理目标
clean:
	rm -f $(TARGETS)

# 运行所有示例的脚本
run_all:
	@for prog in $(TARGETS); do \
		./$prog & \
		sleep 2; \
		kill $!; \
	done

.PHONY: all clean run_all