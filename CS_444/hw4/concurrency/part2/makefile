SRCS	= $(wildcard *.c)
OBJS	= $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(SRCS)))
OBJDIR	= objs
EXE 	= concurrency

all: $(OBJS) $(EXE)

$(EXE): $(OBJS)
	gcc -lpthread $(OBJS) -o $(EXE)

$(OBJDIR)/%.o : %.c 
	gcc -c -lpthread $< -o $@

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
