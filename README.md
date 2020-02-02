####Build Linux for STM32F769I-DISCO using Buildroot

I forked `https://github.com/fdu/STM32F769I-disco_Buildroot`, and used the latest buildroot (`e2e57d56787b7a7d24ed3f9a97902d2bbd58c190` on `master`), latest kernel (5.4), latest u-boot (2020.01), latest busybox (1.31).

After cloning `git@github.com:adrianalin/STM32F769I-disco_Buildroot.git`, you need to setup a `tftp` server for hosting the image.

<br>
####`tftp` server setup:
- `apt install tftpd-hpa`
- edit `/etc/default/tftpd-hpa`:
```
TFTP_USERNAME="<username>"
TFTP_DIRECTORY="/srv/tftp/"
TFTP_ADDRESS=":69"
TFTP_OPTIONS="--ipv4 --secure"
```

These files should be provided by tftp server:
```
$ ls /srv/tftp/stm32f769/
stm32f769-disco.dtb  zImage
```

<br>
####Build the image
- `make bootstrap`: clones buildroot, and copies buildroot config
- `make build`: builds the image; copies uboot-spl, uboot, kernel image and dtb to `/srv/tftp/stm32f769/`
- `make flash_bootloader`, connect your board (ST-LINK micro USB connector) to PC before running this
- `sudo screen /dev/ttyACM0 115200` serial via STLINK connector, you should see the u-boot prompt:

```
Trying to boot from XIP


U-Boot 2020.01 (Feb 02 2020 - 17:36:10 +0200)

Model: STMicroelectronics STM32F769-DISCO board
DRAM:  16 MiB
set_rate not implemented for clock index 4
set_rate not implemented for clock index 4
set_rate not implemented for clock index 4
Flash: 1 MiB
MMC:   sdio2@40011c00: 0
In:    serial
Out:   serial
Err:   serial
usr button is at LOW LEVEL
Net:
Warning: ethernet@40028000 (eth0) using random MAC address - 56:a7:f4:77:e5:97
eth0: ethernet@40028000
Hit SPACE in 3 seconds to stop autoboot.
Card did not respond to voltage select!
U-Boot >
```

<br>
####Booting Linux
After successfully getting to u-boot console, make sure tftp server is accessible , connect your board to ethernet and run:
```
U-Boot > dhcp
U-Boot > setenv serverip 192.168.0.122
U-Boot > tftp 0xc0700000 stm32f769/stm32f769-disco.dtb && tftp 0xc0008000 stm32f769/zImage && bootz 0xc0008000 - 0xc0700000
```
And you should see linux kernel booting.