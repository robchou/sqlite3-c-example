CFLAGS = -lsqlite3
TARGETS = example_opendb example_create_table
RM = rm 
all: $(TARGETS)
clean: 
	$(RM) $(TARGETS) *.db
