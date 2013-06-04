# Top level makefile for the project.
# Jason Corso (jcorso@buffalo.edu)
#
#
#


.PHONY:	src doc 

PROJ_PATH = $(shell pwd)

all:  external src 

external:

src:
	cd src && $(MAKE) && cd ..

test:
	cd src && $(MAKE) test && cd ..

doc:
	cd doc && $(MAKE) && cd ..

clean:
	-cd src && $(MAKE) clean && cd ..
	-cd doc && $(MAKE) clean && cd ..
	find . -name "*~" -delete

