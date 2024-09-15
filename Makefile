# Nome do compilador
CXX = g++

# Nome do arquivo apos compilado
TARGET = hdc-algorithm 

# Nome do arquivo em cpp
SRCS = hdc-algorithm.cpp

# Arquivos .o gerados
OBJS = $(SRCS:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra para criar arquivos .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)


