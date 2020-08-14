#include <u.h>
#include <libc.h>
#include <plumb.h>

void
usage(void)
{
	fprint(2, "usage: plumbmon channel ...\n");
	exits("usage");
}

void
checkchan(char *port)
{
	int fd;
	Plumbmsg *m;

	if((fd = plumbopen(port, OREAD)) < 0)
		sysfatal("plumbopen: %r");

	for(;;){
		if((m = plumbrecv(fd)) == nil)
			sysfatal("plumbrecv: %r");
		print("%s %s\n", port, m->data);
		plumbfree(m);
	}
}

void
main(int argc, char **argv)
{
	int pid;
	if(argc < 2)
		usage();

	while(argc-- > 1){
		print("arg: %s\n", argv[argc]);
		switch(pid = fork()){
		case -1:
			sysfatal("fork: %r");
			break;
		case 0:
			break;
		default:
			checkchan(argv[argc]);
			return;
		}
	}
}
