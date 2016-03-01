########################################################################
# GlobalTranscoding demo
########################################################################

include ./make.definitions

CONFIGFILE=./default.cfg

XXFLAGS=$(XPP_FLAGS) -Xcpp --no_warnings -domain_mapping_file preserved_domain.txt

INCLUDE_PATH = -I ../ \
						-I '../src'

all: smooth cloaked 

cloaked:  ../src/aes.c ../src/rc4.c ../src/des.c ../src/adapter.c
	
	$(XCC) -reset $(XXFLAGS) $(INCLUDE_PATH) -o rc4.cloak.c ../src/rc4.c
	$(XCC) -reset $(XXFLAGS) $(INCLUDE_PATH) -o aes.cloak.c ../src/aes.c
	$(XCC) -reset $(XXFLAGS) $(INCLUDE_PATH) -o des.cloak.c ../src/des.c
	$(XCC) -reset $(XXFLAGS) $(INCLUDE_PATH) -o adapter.cloak.c ../src/adapter.c

install:
	- $(RMSIB)
	- $(RMREPORT)
