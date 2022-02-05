def apply(config, args):
    config["baseimg"] = "../psyq_sample/binaries/overlay1.bin"
    config["myimg"] = "build/overlay1.bin.bin"
    config["mapfile"] = "build/overlay1.bin.map"
    config["source_directories"] = ["."]
    config["objdump_executable"] = "mips-linux-gnu-objdump"
    # config["show_line_numbers_default"] = True
    config["arch"] = "mipsel"
    # config["map_format"] = "gnu" # gnu or mw
    # config["mw_build_dir"] = "build/" # only needed for mw map format
    # config["makeflags"] = []
    # config["objdump_executable"] = ""
