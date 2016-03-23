CFLAGS = -lsqlite3
TARGETS = example_sqlite_open example_sqlite_create example_sqlite_insert example_sqlite_select example_sqlite_update example_sqlite_delete
RM = rm 
all: $(TARGETS)
clean: 
	$(RM) $(TARGETS) *.db
