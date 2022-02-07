OUTPUT_EXE_BASENAME  := output.exe
OVERLAY1_BASENAME    := overlay1.bin
OVERLAY2_BASENAME    := overlay2.bin

BUILD_DIR         := build
TOOLS_DIR         := tools

OUTPUT_EXE_DIR    := $(OUTPUT_EXE_BASENAME)
OVERLAY1_DIR      := $(OVERLAY1_BASENAME)
OVERLAY2_DIR      := $(OVERLAY2_BASENAME)

OUTPUT_EXE_ASM_DIR     := asm/$(OUTPUT_EXE_DIR)
OUTPUT_EXE_ASM_DIRS    := $(OUTPUT_EXE_ASM_DIR) $(OUTPUT_EXE_ASM_DIR)/data

OVERLAY1_ASM_DIR       := asm/$(OVERLAY1_DIR)
OVERLAY1_ASM_DIRS      := $(OVERLAY1_ASM_DIR) $(OVERLAY1_ASM_DIR)/data
OVERLAY2_ASM_DIR       := asm/$(OVERLAY2_DIR)
OVERLAY2_ASM_DIRS      := $(OVERLAY2_ASM_DIR) $(OVERLAY2_ASM_DIR)/data


OUTPUT_EXE_C_DIR       := src/$(OUTPUT_EXE_DIR)
OUTPUT_EXE_C_DIRS      := $(OUTPUT_EXE_C_DIR)

OVERLAY1_C_DIR         := src/$(OVERLAY1_DIR)
OVERLAY1_C_DIRS        := $(OVERLAY1_C_DIR)
OVERLAY2_C_DIR         := src/$(OVERLAY2_DIR)
OVERLAY2_C_DIRS        := $(OVERLAY2_C_DIR)


OUTPUT_EXE_ASSETS_DIR  := assets/$(OUTPUT_EXE_DIR)
OUTPUT_EXE_BIN_DIRS    := $(OUTPUT_EXE_ASSETS_DIR)

OVERLAY1_ASSETS_DIR  := assets/$(OVERLAY1_DIR)
OVERLAY1_BIN_DIRS    := $(OVERLAY1_ASSETS_DIR)
OVERLAY2_ASSETS_DIR  := assets/$(OVERLAY2_DIR)
OVERLAY2_BIN_DIRS    := $(OVERLAY2_ASSETS_DIR)


OUTPUT_EXE_TARGET      := $(BUILD_DIR)/$(OUTPUT_EXE_BASENAME)
OVERLAY1_TARGET        := $(BUILD_DIR)/$(OVERLAY1_BASENAME)
OVERLAY2_TARGET        := $(BUILD_DIR)/$(OVERLAY2_BASENAME)

OUTPUT_EXE_S_FILES     := $(foreach dir,$(OUTPUT_EXE_ASM_DIRS),$(wildcard $(dir)/*.s))
OUTPUT_EXE_C_FILES     := $(foreach dir,$(OUTPUT_EXE_C_DIRS),$(wildcard $(dir)/*.c))
OUTPUT_EXE_BIN_FILES   := $(foreach dir,$(OUTPUT_EXE_BIN_DIRS),$(wildcard $(dir)/*.bin))

OVERLAY1_S_FILES     := $(foreach dir,$(OVERLAY1_ASM_DIRS),$(wildcard $(dir)/*.s))
OVERLAY1_C_FILES     := $(foreach dir,$(OVERLAY1_C_DIRS),$(wildcard $(dir)/*.c))
OVERLAY1_BIN_FILES   := $(foreach dir,$(OVERLAY1_BIN_DIRS),$(wildcard $(dir)/*.bin))

OVERLAY2_S_FILES     := $(foreach dir,$(OVERLAY2_ASM_DIRS),$(wildcard $(dir)/*.s))
OVERLAY2_C_FILES     := $(foreach dir,$(OVERLAY2_C_DIRS),$(wildcard $(dir)/*.c))
OVERLAY2_BIN_FILES   := $(foreach dir,$(OVERLAY2_BIN_DIRS),$(wildcard $(dir)/*.bin))

OUTPUT_EXE_O_FILES     := $(foreach file,$(OUTPUT_EXE_S_FILES),$(BUILD_DIR)/$(file).o) \
                   $(foreach file,$(OUTPUT_EXE_C_FILES),$(BUILD_DIR)/$(file).o) \
                   $(foreach file,$(OUTPUT_EXE_BIN_FILES),$(BUILD_DIR)/$(file).o)

OVERLAY1_O_FILES     := $(foreach file,$(OVERLAY1_S_FILES),$(BUILD_DIR)/$(file).o) \
                   $(foreach file,$(OVERLAY1_C_FILES),$(BUILD_DIR)/$(file).o) \
                   $(foreach file,$(OVERLAY1_BIN_FILES),$(BUILD_DIR)/$(file).o)

OVERLAY2_O_FILES     := $(foreach file,$(OVERLAY2_S_FILES),$(BUILD_DIR)/$(file).o) \
                   $(foreach file,$(OVERLAY2_C_FILES),$(BUILD_DIR)/$(file).o) \
                   $(foreach file,$(OVERLAY2_BIN_FILES),$(BUILD_DIR)/$(file).o)

MAKE            := make
PYTHON          := python3
WINE            := wine
SED             := sed
UNIX2DOS        := unix2dos
GREP            := grep

# default noop
TRUNCATE        := echo

CPP             := cpp -P
CC              := mips-linux-gnu-gcc
CC_FLAGS        := -EL -c -O2 -march=r3000 -mfp32 -mno-abicalls

CROSS           := mips-linux-gnu-
AS              := $(CROSS)as -EL
LD              := $(CROSS)ld -EL
OBJCOPY         := $(CROSS)objcopy

SPLAT           := $(PYTHON) $(TOOLS_DIR)/splat/split.py

AS_INCLUDES     := -Iinclude
AS_FLAGS        := -march=r3000 -mtune=r3000 -no-pad-sections
AS_FLAGS        += -G0
AS_FLAGS        += $(AS_INCLUDES)

OVERLAY1_LD_FLAGS    := -Map $(OVERLAY1_TARGET).map -T $(OVERLAY1_BASENAME).ld \
                   -T undefined_syms_auto.$(OVERLAY1_BASENAME).txt -T undefined_funcs_auto.$(OVERLAY1_BASENAME).txt -T undefined_syms.$(OVERLAY1_BASENAME).txt \
                   --no-check-sections

OVERLAY2_LD_FLAGS    := -Map $(OVERLAY2_TARGET).map -T $(OVERLAY2_BASENAME).ld \
                   -T undefined_syms_auto.$(OVERLAY2_BASENAME).txt -T undefined_funcs_auto.$(OVERLAY2_BASENAME).txt -T undefined_syms.$(OVERLAY2_BASENAME).txt \
                   --no-check-sections

OUTPUT_EXE_LD_FLAGS    := -Map $(OUTPUT_EXE_TARGET).map -T $(OUTPUT_EXE_BASENAME).ld \
                   -T undefined_syms_auto.$(OUTPUT_EXE_BASENAME).txt -T undefined_funcs_auto.$(OUTPUT_EXE_BASENAME).txt -T undefined_syms.$(OUTPUT_EXE_BASENAME).txt \
                   --no-check-sections --allow-multiple-definition


OBJCOPY_FLAGS   := -O binary

# overrides
# targets

# first target to appear is "default" don't swap the order
default: output_exe overlay1 overlay2

all: output_exe overlay1 overlay2

output_exe: output_exe_dirs verify_output_exe
overlay1: overlay1_dirs verify_overlay1
overlay2: overlay2_dirs verify_overlay2

output_exe_dirs:
	$(foreach dir,$(OUTPUT_EXE_ASM_DIRS) $(OUTPUT_EXE_BIN_DIRS) $(OUTPUT_EXE_C_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

overlay1_dirs:
	$(foreach dir,$(OVERLAY1_ASM_DIRS) $(OVERLAY1_BIN_DIRS) $(OVERLAY1_C_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

overlay2_dirs:
	$(foreach dir,$(OVERLAY2_ASM_DIRS) $(OVERLAY2_BIN_DIRS) $(OVERLAY2_C_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

check: check_output_exe check_overlay1 check_overlay2
check_output_exe: $(OUTPUT_EXE_BASENAME).ok
check_overlay1: $(OVERLAY1_BASENAME).ok
check_overlay2: $(OVERLAY2_BASENAME).ok

verify: verify_output_exe verify_overlay1 verify_overlay2

verify_output_exe: $(OUTPUT_EXE_TARGET).ok
verify_overlay1: $(OVERLAY1_TARGET).ok
verify_overlay2: $(OVERLAY2_TARGET).ok

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(PSYQ_INI)

# recipes

$(OUTPUT_EXE_TARGET).elf: $(OUTPUT_EXE_O_FILES)
	$(LD) $(OUTPUT_EXE_LD_FLAGS) -o $@

$(OVERLAY1_TARGET).elf: $(OVERLAY1_O_FILES)
	$(LD) $(OVERLAY1_LD_FLAGS) -o $@

$(OVERLAY2_TARGET).elf: $(OVERLAY2_O_FILES)
	$(LD) $(OVERLAY2_LD_FLAGS) -o $@

%.bin: %.elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@
	@$(TRUNCATE) $@

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<


PROC_VERSION != uname -a
IS_WSL := $(findstring microsoft,$(PROC_VERSION)) $(findstring Microsoft,$(PROC_VERSION))
ifneq ($(IS_WSL),)
	WSL := no
else
	WSL := yes
endif

PSYQ_PATH_ABS := $(realpath ../3rdParty/psyq_sdk/psyq_4.4/bin)

export PSYQ_PATH := $(PSYQ_PATH_ABS)
export WSLENV := PSYQ_PATH/p

PSYQ_INI := $$PSYQ_PATH\\psyq.ini

$(PSYQ_INI):
	echo [ccpsx] > $(PSYQ_INI)
	echo stdlib=libgs.lib libgte.lib libgpu.lib libspu.lib libsnd.lib libetc.lib libapi.lib libsn.lib libc.lib libcd.lib libcard.lib >> $(PSYQ_INI)
	echo compiler_path=$(PSYQ_PATH_ABS)\\bin >> $(PSYQ_INI)
	echo assembler_path=$(PSYQ_PATH_ABS)\\bin >> $(PSYQ_INI)
	echo linker_path=$(PSYQ_PATH_ABS)\\bin >> $(PSYQ_INI)
	echo library_path=$(PSYQ_PATH_ABS)\\lib >> $(PSYQ_INI)
	echo c_include_path=$(PSYQ_PATH_ABS)\\include >> $(PSYQ_INI)
	echo cplus_include_path=$(PSYQ_PATH_ABS)\\include >> $(PSYQ_INI)

PSYQ_CC_FLAGS        := -O2 -G 0 -g -c -Wall

# python3 ../tools/asm-processor/asm_processor.py -O2 ../src/rocket/codeseg0/codeseg0.c > codeseg0.c
# python3 ../tools/asm-processor/asm_processor.py -O2 ../src/rocket/codeseg0/codeseg0.c --post-process codeseg0.o --assembler "mips-linux-gnu-as -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I../include -mips3" --asm-prelude ../tools/asm-processor/prelude.inc
#  $(PSYQ_INI)
$(BUILD_DIR)/%.c.o: %.c
	echo $@ $<
	@echo $$PATH
	@echo $$PSX_PATH
	@echo $$PSYQ_PATH

	python3 ../3rdParty/asm-processor/asm_processor.py -O2 $< > meh.c
	../3rdParty/psyq_sdk/psyq_4.4/bin/ccpsx.exe -O2 -G 0 -g -c -Wall meh.c "-o$@.obj"
	../3rdParty/psyq-objparser.exe $@.obj -o $@
	python3 ../3rdParty/asm-processor/asm_processor.py -O2 $< --post-process $@ --assembler "mips-linux-gnu-as -EL -march=r3000 -mtune=r3000 -no-pad-sections -G0 -I../include -mips1" --asm-prelude ../3rdParty/asm-processor/prelude.inc

#$(BUILD_DIR)/%.c.o: $(BUILD_DIR)/%.c.obj
#	echo $@ $<
#	../3rdParty/psyq-objparser.exe $< -o $@

%.ok: %.bin
	@echo "$$(cat $(notdir $(<:.bin=)).sha1)  $<" | sha1sum --check
	@touch $@

# keep .obj files
.SECONDARY:

.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
