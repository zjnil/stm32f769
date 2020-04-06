#!/bin/sh
# Deploy image and dtb to tftp

dir_publish="/srv/tftp/stm32f769/"

echo "Copy zImage to tftp"
cp ${BINARIES_DIR}/zImage ${dir_publish}
echo "Copy dtb to tftp"
cp ${BUILD_DIR}/linux-5.4.10/arch/arm/boot/dts/stm32f769-disco.dtb ${dir_publish}
