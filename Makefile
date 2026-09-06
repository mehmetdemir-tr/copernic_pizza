obj-m += copernic_pizza.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) CC=clang HOSTCC=clang LD=ld.lld AR=llvm-ar NM=llvm-nm OBJCOPY=llvm-objcopy OBJDUMP=llvm-objdump READELF=llvm-readelf STRIP=llvm-strip modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
