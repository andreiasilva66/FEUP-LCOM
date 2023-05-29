# name of the program (Minix service)
PROG=lab5

# source code files to be compiled
<<<<<<< HEAD
SRCS = timer.c lab5.c videocard.c KBC.c utils.c  keyboard.c 

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic 
=======
SRCS = lab5.c video.c keyboard.c  utils.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
