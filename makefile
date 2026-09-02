all: main clean

GLM_VER = 1.0.3
GLFW_VER = 3.4
GLEW_VER = 2.3.1

CUR_DIR = $(shell pwd)

CXX = clang++
CXXFLAGS = -std=c++20 -stdlib=libc++ -fcolor-diagnostics -fansi-escape-codes \
			-I/opt/homebrew/Caskroom/miniforge/base/include \
			-I/opt/homebrew/Cellar/glm/$(GLM_VER)/include \
			-I/opt/homebrew/Cellar/glfw/$(GLFW_VER)/include \
			-I/opt/homebrew/Cellar/glew/$(GLEW_VER)/include \
			-I$(CUR_DIR)

LDFLAGS = -L/opt/homebrew/Caskroom/miniforge/base/lib \
			-L/opt/homebrew/Cellar/glm/$(GLM_VER)/lib \
			-L/opt/homebrew/Cellar/glfw/$(GLFW_VER)/lib \
			-L/opt/homebrew/Cellar/glew/$(GLEW_VER)/lib \
			-Wl,-rpath,/opt/homebrew/Caskroom/miniforge/base/lib \
			-Wl,-rpath,/opt/homebrew/Cellar/glm/$(GLM_VER)/lib \
			-Wl,-rpath,/opt/homebrew/Cellar/glfw/$(GLFW_VER)/lib \
			-Wl,-rpath,/opt/homebrew/Cellar/glew/$(GLEW_VER)/lib

LDLIBS = -lglew -lglfw -framework OpenGL -lgmp -lgmpxx -lmpfr -lmpc -lmp++

main:
	$(CXX) -c $(CXXFLAGS) ppm_renderer_test.cpp -o ppm_renderer_test.o
	$(CXX) $(LDFLAGS) ppm_renderer_test.o $^ $(LDLIBS) -o render_test

clean:
	rm -rf *.o