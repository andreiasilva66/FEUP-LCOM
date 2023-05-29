<<<<<<< HEAD
# name of the program (Minix service)
PROG=lab3

# source code files to be compiled
SRCS = lab3.c timer.c utils.c kbc_utils.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -DLAB3

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
=======
# name of the program (Minix service)
PROG = lab3 

# source code files to be compiled
SRCS = keyboard.c utils.c timer.c lab3.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic
CPPFLAGS += -D LAB3

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
