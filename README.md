```
rm -rf build
cmake -S . -B build -DSOC=microsoc/default -DDEVICE=microsoc_sim -DTOOLCHAIN_PATH=/opt/xpack/riscv-none-elf-gcc/bin/ -DCMAKE_BUILD_TYPE=MinSizeRel
make -C build hvms

sbt "runMain vexiiriscv.soc.micro.MicroSocSim --load-elf ../VexiiFirmware/build/app/hvms/hvms.elf --xlen 64 --with-rva --with-lsu-l1 --ram-bytes 32768"
```