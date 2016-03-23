CFLAGS = -lsqlite3
TARGETS = example_opendb
RM = rm 
all: $(TARGETS)
clean: 
	$(RM) $(TARGETS)
