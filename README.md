# Copernic Pizza :D

A simple Linux character device driver allocating a 16-MB virtual RAM disk buffer. (contains the hottest pizza in this galaxy)

It's a fan-made Linux Character Device Driver Module, sent to LKML (Linux Kernel Mailing List).

## Build

> [!NOTE]
> Your distribution's **kernel headers** must be installed.
> Also You can write data in it. (echo "smth u want to" > /dev/copernic_pizza)

1. **Clone this repository** to your local machine:
   ```bash
   git clone https://github.com/mehmetdemir-tr/copernic_pizza
   cd copernic_pizza
   ```

3. Compile the module:
   ```bash
   make
   ```

4. Load the module, check kernel logs, and read from the device:
   ```bash
   sudo insmod copernic_pizza.ko && sudo dmesg | tail -n 3 && sudo cat /dev/copernic_pizza
   ```

5. You should see the following output:
   ```text
   ❯ sudo insmod copernic_pizza.ko && sudo dmesg | tail -n 3 && sudo cat /dev/copernic_pizza
   [ 1304.047451] Module is up.
   [ 1304.047455] Most Hot Pizza innn this galaxy, innn this galaxy!.
   [ 1304.051764] Success: Mounted 16 MB Space from RAM! Addr: [RAM_ADDRESS]
   *recep ivedik laugh*
   ```
