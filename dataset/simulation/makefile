# Компилятор
CC = g++
# Флаги компиляции
CFLAGS = -std=c++11 -Wall

# Исходные файлы
SRCS = main.cpp \
       AlternativeHypotheses.cpp \
       CensoredSample.cpp \
       ConvergenceToLimitLaw.cpp \
       Distribution.cpp \
       EDF.cpp \
       HelpFucntions.cpp \
       HomogeneityTest.cpp \
       KaplanMeyerEstimate.cpp \
       Matrix.cpp \
       MP.cpp \
       mt19937boost.cpp \
       NelsonAalenSurvivalEstimate.cpp \
       Power.cpp \
       PowerFunctionResearch.cpp \
       Sample.cpp \
       SearchN.cpp \
       simulation_for_machine_learning.cpp \
       StatisticsSample.cpp \
       TestPower.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Имя исполняемого файла
TARGET = myprogram

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Правило для компиляции исходных файлов
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Правило для очистки объектных файлов и исполняемого файла
clean:
	rm -f $(OBJS) $(TARGET)
