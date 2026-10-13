include $(PS5_PAYLOAD_SDK)/toolchain/prospero.mk
CFLAGS = -O2 -Wall -Wextra -Isrc
LDLIBS = -lSceVideoOut -lSceSystemService -lSceUserService -lScePad
all: arctic-fluid-native-ps5.elf
src/assets.c: assets/sidebar.png assets/font.bin generate_assets.py
	python3 generate_assets.py
arctic-fluid-native-ps5.elf: src/main.c src/ui.c src/assets.c src/platform.h src/ui.h
	$(CC) $(CFLAGS) -o $@ src/main.c src/ui.c src/assets.c $(LDLIBS)
	$(STRIP) $@
