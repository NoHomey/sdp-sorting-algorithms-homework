.PHONY: all clean test chrome-open-coverage

Objects = ExamDate StudentExam

mainFile = trieTest.cc

all: $(addsuffix .o,$(Objects))
	$(COMPILER) $(mainFile) $^

clean:
	rm -f *.o

CXXFLAGS = -g -std=c++14 -Wall -Wextra -Wpedantic 

COMPILER = $(CXX) $(CPPFLAGS) $(CXXFLAGS)

SRC_DIR = .

dirDeps = $(SRC_DIR)/$(1)/$(2)/$(2).h $(SRC_DIR)/$(1)/$(2)/$(2).cc

define endl


endef

define obj
$(2).o: $(call dirDeps,$(1),$(2)) $(addsuffix .o,$(3))
	$(COMPILER) -c ./$(1)/$(2)/$(2).cc
endef

$(eval $(call obj,.,ExamDate))
$(eval $(call obj,.,StudentExam,ExamDate))

