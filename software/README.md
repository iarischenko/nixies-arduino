Easy "clone and go" repository for a libopencm3 based project.

# Instructions
 1. git clone --recurse-submodules https://github.com/libopencm3/libopencm3-template.git your-project
 2. cd software
 3. make -C libopencm3 # (Only needed once)
 4. bear --append -- make -C stm32f103-nixie

bear is needed to create compile_commands.json and enable clangd

If you have an older git, or got ahead of yourself and skipped the ```--recurse-submodules```
you can fix things by running ```git submodule update --init``` (This is only needed once)

# Directories
* stm32f103-nixie contains stm32 nixie tubes application

