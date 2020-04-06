PREFIX = $(shell pwd)/..
url_buildroot = https://github.com/buildroot/buildroot.git
dir_external = $(PREFIX)/STM32F769I-disco_Buildroot
dir_buildroot = $(PREFIX)/buildroot
dir_output = $(dir_buildroot)/output
commit_buildroot = e2e57d56787b7a7d24ed3f9a97902d2bbd58c190

bootstrap:
	@echo "Downloading buildroot to $(PREFIX)"
	cd .. && git clone $(url_buildroot)
	cd $(dir_buildroot) && git reset --hard $(commit_buildroot)
	make BR2_EXTERNAL=$(dir_external) menuconfig -C $(dir_buildroot)
	make custom_stm32f769_defconfig -C $(dir_buildroot)

build:
	make -C $(dir_buildroot)

flash_bootloader:
	cd $(dir_output)/build/host-openocd-0.10.0/tcl && ../../../host/usr/bin/openocd \
		-f board/stm32f7discovery.cfg \
		-c "program ../../../images/u-boot-spl.bin 0x08000000" \
		-c "program ../../../images/u-boot.bin 0x08008000" \
		-c "reset run" -c shutdown

clean:
	rm -rf $(dir_output)
