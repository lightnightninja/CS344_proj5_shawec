CC = gcc
CXX = icpc
CFLAGS = -std=c99 -g
TARGET = compute
SOURCE = compute.c

default: compile

compile: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS}

client: client.c
	${CC} ${CFLAGS} client.c -o client ${LDFLAGS}

manage:
	python manage.py

report:
	python report.py

——————————————————————————————————————————————————
| Report               	 			 		|
——————————————————————————————————————————————————
| Activevprocesses		  : activeProc		 |
| Lifetime processes		: lifeProc		   |
| Numbers checked		   : numChecked		 |
| Max number checked		: maxNum		 	|
| Perfect Numbers Found	 : numFound		   |
| Average time taken		: avgTime		    |
|						 					   |
——————————————————————————————————————————————————
| Active Process Stats				 		  |
——————————————————————————————————————————————————
|PID	   |calculated   |found  |milops/second  |
——————————————————————————————————————————————————
| xxxxxxx  | calc		| found | opsSec	    |
| xxxxxxx  | calc		| found | opsSec	    |
| xxxxxxx  | calc		| found | opsSec	    |
| xxxxxxx  | calc		| found | opsSec	    |
| xxxxxxx  | calc		| found | opsSec	    |
| xxxxxxx  | calc		| found | opsSec	    |
| xxxxxxx  | calc		| found | opsSec	    |
| xxxxxxx  | calc		| found | opsSec	    |
——————————————————————————————————————————————————