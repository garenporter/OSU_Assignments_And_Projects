SRCS	= $(wildcard *.c)
OBJS	= $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(SRCS)))
OBJDIR	= objs
EXE 	= hw1

all: $(OBJS) $(EXE)

$(EXE): $(OBJS)
	gcc -lpthread $(OBJS) -o $(EXE)

$(OBJDIR)/%.o : %.c 
	gcc -c -lpthread $< -o $@

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJS)
