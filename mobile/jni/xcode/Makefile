########################################################################
# GlobalTranscoding demo
########################################################################

include ./make.definitions

CONFIGFILE=./default.cfg

XXFLAGS=$(XPP_FLAGS) -Xcpp --no_warnings -domain_mapping_file preserved_domain.txt

# header files for the OMP
INCLUDE_PATH= -I ../../../src
ANDROID_PATH=-I /home/irdetogame/opt/android-ndk-r9d/platforms/android-9/arch-arm/usr/include


#here we try the log flag
LOGGING_FLAG := -D_JAC_STANDALONE
ifeq ($(ANDROID_DEBUG), on)
	LOGGING_FLAG += -DLOG_OUT
endif
ifeq ($(USE_AES_CBC), on)
	LOGGING_FLAG += -DUSE_AES_CBC
endif
ifeq ($(USE_AES_ECB), on)
	LOGGING_FLAG += -DUSE_AES_ECB
endif
ifeq ($(USE_DES), on)
	LOGGING_FLAG += -DUSE_DES
endif
ifeq ($(USE_3DES), on)
	LOGGING_FLAG += -DUSE_3DES
endif
ifeq ($(USE_RC4), on)
	LOGGING_FLAG += -DUSE_RC4
endif

all: smooth cloaked 

cloaked:  ../../../src/aes.c ../../../src/des.c ../../../src/adapter.c ../../../src/rc4.c

	
ifeq ($(USE_AES_CBC), on)	
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o aes.cloak.c ../../../src/aes.c
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o adapter.cloak.c ../../../src/adapter.c
endif
ifeq ($(USE_AES_ECB), on)	
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o aes.cloak.c ../../../src/aes.c
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o adapter.cloak.c ../../../src/adapter.c
endif
ifeq ($(USE_DES), on)	
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o des.cloak.c ../../../src/des.c
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o adapter.cloak.c ../../../src/adapter.c
endif

ifeq ($(USE_3DES), on)	
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o des.cloak.c ../../../src/des.c
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o adapter.cloak.c ../../../src/adapter.c
endif
ifeq ($(USE_RC4), on)	
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o rc4.cloak.c ../../../src/rc4.c
	$(XCC) -reset $(XXFLAGS) $(ANDROID_PATH) $(INCLUDE_PATH) $(LOGGING_FLAG) -o adapter.cloak.c ../../../src/adapter.c
endif
install:
	- $(RMSIB)
	- $(RMREPORT)
