url_buildroot = https://github.com/buildroot/buildroot.git
dir_configs = configs
dir_buildroot = buildroot
commit_buildroot = e2e57d56787b7a7d24ed3f9a97902d2bbd58c190
dir_publish = /srv/tftp/stm32f769/

bootstrap:
	git clone $(url_buildroot)
	cd $(dir_buildroot) && git reset --hard $(commit_buildroot)
	cd ..
	cp $(dir_configs)/buildroot $(dir_buildroot)/.config

build:
	make -C $(dir_buildroot)
	cp $(dir_buildroot)/output/images/zImage ${dir_publish}/
	cp $(dir_buildroot)/output/build/linux-5.4.10/arch/arm/boot/dts/stm32f769-disco.dtb ${dir_publish}/

flash_bootloader:
	cd $(dir_buildroot)/output/build/host-openocd-0.10.0/tcl && ../../../host/usr/bin/openocd \
		-f board/stm32f7discovery.cfg \
		-c "program ../../../images/u-boot-spl.bin 0x08000000" \
		-c "program ../../../images/u-boot.bin 0x08008000" \
		-c "reset run" -c shutdown

clean:
	rm -rf $(dir_buildroot)
