CC      := clang
CFLAGS  := -O2 -Wall -Wno-deprecated-declarations 
LDFLAGS := -flto
LIBS    := -lcurl -larchive 

SRC:=$(wildcard *.c)

TARGET := hawker

PROJECT_NAME=p4
PROJECT_SERVER="http://subutai.cs.iit.edu"
PROJECT_PORT=3000

OBJ := $(patsubst %.c, %.o, \
		$(filter %.c, $(SRC)))

all: $(TARGET)

%.o: %.c
	@echo "$@ <- $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	@echo "Linking...[$(TARGET) <- $<]"
	@$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

clean:
	@rm -f $(OBJ) $(TARGET) 

handin:
	@echo "Creating tarball and attempting submission..."
	@$(MAKE) clean
	@tar cvzf submission.tar.gz ./*
	@echo "  submission file successfully created in submission.tar.gz"
	@echo "Initiating submission..."
	python3 submit.py $(PROJECT_NAME) submission.tar.gz -s $(PROJECT_SERVER) -p $(PROJECT_PORT)
	@echo "Submission complete. Cleaning up."
	@rm -f submission.tar.gz

test:
	sudo ./hawker test /test_prog


.PHONY: all clean
