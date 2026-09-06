# Copernic Pizza :D

A simple Linux character device driver allocating a 16-MB virtual RAM disk buffer. (contains the hottest pizza in this galaxy)

It's a fan-made Linux Character Device Driver Module, sent to LKML (Linux Kernel Mailing List).

## Build

> [!NOTE]
> You must obtain the *Linux Kernel* from torvalds/linux or your distribution's **kernel headers** must be installed.

1. Move the folder `copernic_pizza` to `linux/drivers/`:
   ```bash
   mv copernic_pizza linux/drivers/
   cd linux/drivers/copernic_pizza
   ```

2. Compile the module:
   ```bash
   make
   ```

3. Load the module, check kernel logs, and read from the device:
   ```bash
   sudo insmod copernic_pizza.ko && sudo dmesg | tail -n 3 && sudo cat /dev/copernic_pizza
   ```

4. You should see the following output:
   ```text
   ❯ sudo insmod copernic_pizza.ko && sudo dmesg | tail -n 3 && sudo cat /dev/copernic_pizza
   [ 1304.047451] Module is up.
   [ 1304.047455] Most Hot Pizza innn this galaxy, innn this galaxy!.
   [ 1304.051764] Success: Mounted 16 MB Space from RAM! Addr: 00000000c4e4ae0d
   *recep ivedik laugh*
   ```
