######################################################################
# Automatically generated by qmake (2.01a) ??? ?? 15 21:07:54 2013
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . \
              main \
              netapp \
              target \
              lwIP\port \
              netapp\unused \
              sdio\inc \
              sdio\src \
              STM32F10x_lib\inc \
              STM32F10x_lib\src \
              lwIP\port\include \
              lwIP\port\netif \
              lwIP\src\api \
              lwIP\src\core \
              lwIP\src\netif \
              marvel\driver\inc \
              marvel\driver\src \
              STM32F10x_lib\inc\USB \
              STM32F10x_lib\src\USB \
              lwIP\port\include\arch \
              lwIP\port\include\netif \
              lwIP\src\core\ipv4 \
              lwIP\src\core\ipv6 \
              lwIP\src\core\snmp \
              lwIP\src\include\lwip \
              lwIP\src\include\netif \
              lwIP\src\netif\ppp \
              marvel\driver\src\8686_image \
              lwIP\src\include\ipv4\lwip \
              lwIP\src\include\ipv6\lwip
INCLUDEPATH += .

# Input
HEADERS += main/parmcfg.h \
           netapp/html.h \
           netapp/netapp.h \
           netapp/sample_http.h \
           netapp/yeelink.h \
           target/system.h \
           netapp/unused/netdatapack.h \
           netapp/unused/netio.h \
           netapp/unused/sample_TTCP.h \
           netapp/unused/tcpclient.h \
           netapp/unused/tcpecho.h \
           netapp/unused/tcpmultiserver.h \
           netapp/unused/tcpserver.h \
           netapp/unused/tcpserver2.h \
           netapp/unused/udpclient.h \
           netapp/unused/udpecho.h \
           netapp/unused/udpserver.h \
           sdio/inc/card.h \
           sdio/inc/common.h \
           sdio/inc/core.h \
           sdio/inc/host.h \
           sdio/inc/mmc.h \
           sdio/inc/reg_sdio.h \
           sdio/inc/s3cmci.h \
           sdio/inc/sd.h \
           sdio/inc/sdio.h \
           sdio/inc/sdio_func.h \
           sdio/inc/type.h \
           STM32F10x_lib/inc/cortexm3_macro.h \
           STM32F10x_lib/inc/stm32f10x.h \
           STM32F10x_lib/inc/stm32f10x_adc.h \
           STM32F10x_lib/inc/stm32f10x_bkp.h \
           STM32F10x_lib/inc/stm32f10x_can.h \
           STM32F10x_lib/inc/stm32f10x_cl.h \
           STM32F10x_lib/inc/stm32f10x_conf.h \
           STM32F10x_lib/inc/stm32f10x_crc.h \
           STM32F10x_lib/inc/stm32f10x_dac.h \
           STM32F10x_lib/inc/stm32f10x_dbgmcu.h \
           STM32F10x_lib/inc/stm32f10x_dma.h \
           STM32F10x_lib/inc/stm32f10x_exti.h \
           STM32F10x_lib/inc/stm32f10x_flash.h \
           STM32F10x_lib/inc/stm32f10x_fsmc.h \
           STM32F10x_lib/inc/stm32f10x_gpio.h \
           STM32F10x_lib/inc/stm32f10x_i2c.h \
           STM32F10x_lib/inc/stm32f10x_it.h \
           STM32F10x_lib/inc/stm32f10x_iwdg.h \
           STM32F10x_lib/inc/stm32f10x_lib.h \
           STM32F10x_lib/inc/stm32f10x_map.h \
           STM32F10x_lib/inc/stm32f10x_nvic.h \
           STM32F10x_lib/inc/stm32f10x_pwr.h \
           STM32F10x_lib/inc/stm32f10x_rcc.h \
           STM32F10x_lib/inc/stm32f10x_rtc.h \
           STM32F10x_lib/inc/stm32f10x_sdio.h \
           STM32F10x_lib/inc/stm32f10x_spi.h \
           STM32F10x_lib/inc/stm32f10x_systick.h \
           STM32F10x_lib/inc/stm32f10x_tim.h \
           STM32F10x_lib/inc/stm32f10x_type.h \
           STM32F10x_lib/inc/stm32f10x_usart.h \
           STM32F10x_lib/inc/stm32f10x_wwdg.h \
           STM32F10x_lib/inc/system_stm32f10x.h \
           STM32F10x_lib/inc/system_stm32f10x_cl.h \
           lwIP/port/include/lwip.h \
           lwIP/port/include/lwipopts.h \
           lwIP/src/core/api.h \
           lwIP/src/core/api_msg.h \
           lwIP/src/core/arch.h \
           lwIP/src/core/debug.h \
           lwIP/src/core/def.h \
           lwIP/src/core/dhcp.h \
           lwIP/src/core/dns.h \
           lwIP/src/core/err.h \
           lwIP/src/core/init.h \
           lwIP/src/core/mem.h \
           lwIP/src/core/memp.h \
           lwIP/src/core/memp_std.h \
           lwIP/src/core/netbios.h \
           lwIP/src/core/netbuf.h \
           lwIP/src/core/netdb.h \
           lwIP/src/core/netif.h \
           lwIP/src/core/netifapi.h \
           lwIP/src/core/opt.h \
           lwIP/src/core/pbuf.h \
           lwIP/src/core/raw.h \
           lwIP/src/core/sio.h \
           lwIP/src/core/snmp.h \
           lwIP/src/core/snmp_asn1.h \
           lwIP/src/core/snmp_msg.h \
           lwIP/src/core/snmp_structs.h \
           lwIP/src/core/sockets.h \
           lwIP/src/core/stats.h \
           lwIP/src/core/sys.h \
           lwIP/src/core/tcp.h \
           lwIP/src/core/tcpip.h \
           lwIP/src/core/udp.h \
           marvel/driver/inc/11d.h \
           marvel/driver/inc/assoc.h \
           marvel/driver/inc/cmd.h \
           marvel/driver/inc/dev.h \
           marvel/driver/inc/host_cmd.h \
           marvel/driver/inc/hostcmd.h \
           marvel/driver/inc/hostcmdcode.h \
           marvel/driver/inc/if.h \
           marvel/driver/inc/if_sdio.h \
           marvel/driver/inc/list.h \
           marvel/driver/inc/mac80211.h \
           marvel/driver/inc/marvel_main.h \
           marvel/driver/inc/marvell_ops.h \
           marvel/driver/inc/mdef.h \
           marvel/driver/inc/rxtx.h \
           marvel/driver/inc/scan.h \
           marvel/driver/inc/sdio_ids.h \
           marvel/driver/inc/types.h \
           marvel/driver/inc/wireless.h \
           STM32F10x_lib/inc/USB/usb_core.h \
           STM32F10x_lib/inc/USB/usb_def.h \
           STM32F10x_lib/inc/USB/usb_init.h \
           STM32F10x_lib/inc/USB/usb_int.h \
           STM32F10x_lib/inc/USB/usb_lib.h \
           STM32F10x_lib/inc/USB/usb_mem.h \
           STM32F10x_lib/inc/USB/usb_regs.h \
           STM32F10x_lib/inc/USB/usb_type.h \
           lwIP/port/include/arch/bpstruct.h \
           lwIP/port/include/arch/cc.h \
           lwIP/port/include/arch/cpu.h \
           lwIP/port/include/arch/epstruct.h \
           lwIP/port/include/arch/perf.h \
           lwIP/port/include/arch/sys_arch_c.h \
           lwIP/port/include/netif/ethernetif.h \
           lwIP/src/include/lwip/api.h \
           lwIP/src/include/lwip/api_msg.h \
           lwIP/src/include/lwip/arch.h \
           lwIP/src/include/lwip/debug.h \
           lwIP/src/include/lwip/def.h \
           lwIP/src/include/lwip/dhcp.h \
           lwIP/src/include/lwip/dns.h \
           lwIP/src/include/lwip/err.h \
           lwIP/src/include/lwip/init.h \
           lwIP/src/include/lwip/mem.h \
           lwIP/src/include/lwip/memp.h \
           lwIP/src/include/lwip/memp_std.h \
           lwIP/src/include/lwip/netbios.h \
           lwIP/src/include/lwip/netbuf.h \
           lwIP/src/include/lwip/netdb.h \
           lwIP/src/include/lwip/netif.h \
           lwIP/src/include/lwip/netifapi.h \
           lwIP/src/include/lwip/opt.h \
           lwIP/src/include/lwip/pbuf.h \
           lwIP/src/include/lwip/raw.h \
           lwIP/src/include/lwip/sio.h \
           lwIP/src/include/lwip/snmp.h \
           lwIP/src/include/lwip/snmp_asn1.h \
           lwIP/src/include/lwip/snmp_msg.h \
           lwIP/src/include/lwip/snmp_structs.h \
           lwIP/src/include/lwip/sockets.h \
           lwIP/src/include/lwip/stats.h \
           lwIP/src/include/lwip/sys.h \
           lwIP/src/include/lwip/tcp.h \
           lwIP/src/include/lwip/tcpip.h \
           lwIP/src/include/lwip/udp.h \
           lwIP/src/include/netif/etharp.h \
           lwIP/src/include/netif/loopif.h \
           lwIP/src/include/netif/ppp_oe.h \
           lwIP/src/include/netif/slipif.h \
           lwIP/src/netif/ppp/auth.h \
           lwIP/src/netif/ppp/chap.h \
           lwIP/src/netif/ppp/chpms.h \
           lwIP/src/netif/ppp/fsm.h \
           lwIP/src/netif/ppp/ipcp.h \
           lwIP/src/netif/ppp/lcp.h \
           lwIP/src/netif/ppp/magic.h \
           lwIP/src/netif/ppp/md5_ppp.h \
           lwIP/src/netif/ppp/pap.h \
           lwIP/src/netif/ppp/ppp.h \
           lwIP/src/netif/ppp/pppdebug.h \
           lwIP/src/netif/ppp/randm.h \
           lwIP/src/netif/ppp/vj.h \
           lwIP/src/netif/ppp/vjbsdhdr.h \
           lwIP/src/include/ipv4/lwip/autoip.h \
           lwIP/src/include/ipv4/lwip/icmp.h \
           lwIP/src/include/ipv4/lwip/igmp.h \
           lwIP/src/include/ipv4/lwip/inet.h \
           lwIP/src/include/ipv4/lwip/inet_chksum.h \
           lwIP/src/include/ipv4/lwip/ip.h \
           lwIP/src/include/ipv4/lwip/ip_addr.h \
           lwIP/src/include/ipv4/lwip/ip_frag.h \
           lwIP/src/include/ipv6/lwip/icmp.h \
           lwIP/src/include/ipv6/lwip/inet.h \
           lwIP/src/include/ipv6/lwip/ip.h \
           lwIP/src/include/ipv6/lwip/ip_addr.h
SOURCES += file2carray.c \
           main/main.c \
           main/parmcfg.c \
           netapp/netapp.c \
           netapp/sample_http.c \
           netapp/yeelink.c \
           target/stm32f10x_it.c \
           target/system.c \
           lwIP/port/lwIP.c \
           lwIP/port/sys_arch.c \
           netapp/unused/netdatapack.c \
           netapp/unused/netio.c \
           netapp/unused/sample_TTCP.c \
           netapp/unused/tcpclient.c \
           netapp/unused/tcpecho.c \
           netapp/unused/tcpmultiserver.c \
           netapp/unused/tcpserver.c \
           netapp/unused/tcpserver2.c \
           netapp/unused/udpclient.c \
           netapp/unused/udpecho.c \
           netapp/unused/udpserver.c \
           sdio/src/common.c \
           sdio/src/core.c \
           sdio/src/s3cmci.c \
           sdio/src/sdio.c \
           sdio/src/sdio_cis.c \
           STM32F10x_lib/src/stm32f10x_adc.c \
           STM32F10x_lib/src/stm32f10x_bkp.c \
           STM32F10x_lib/src/stm32f10x_can.c \
           STM32F10x_lib/src/stm32f10x_crc.c \
           STM32F10x_lib/src/stm32f10x_dac.c \
           STM32F10x_lib/src/stm32f10x_dbgmcu.c \
           STM32F10x_lib/src/stm32f10x_dma.c \
           STM32F10x_lib/src/stm32f10x_exti.c \
           STM32F10x_lib/src/stm32f10x_flash.c \
           STM32F10x_lib/src/stm32f10x_fsmc.c \
           STM32F10x_lib/src/stm32f10x_gpio.c \
           STM32F10x_lib/src/stm32f10x_i2c.c \
           STM32F10x_lib/src/stm32f10x_it.c \
           STM32F10x_lib/src/stm32f10x_iwdg.c \
           STM32F10x_lib/src/stm32f10x_lib.c \
           STM32F10x_lib/src/stm32f10x_nvic.c \
           STM32F10x_lib/src/stm32f10x_pwr.c \
           STM32F10x_lib/src/stm32f10x_rcc.c \
           STM32F10x_lib/src/stm32f10x_rtc.c \
           STM32F10x_lib/src/stm32f10x_sdio.c \
           STM32F10x_lib/src/stm32f10x_spi.c \
           STM32F10x_lib/src/stm32f10x_systick.c \
           STM32F10x_lib/src/stm32f10x_tim.c \
           STM32F10x_lib/src/stm32f10x_usart.c \
           STM32F10x_lib/src/stm32f10x_wwdg.c \
           lwIP/port/netif/ethernetif.c \
           lwIP/src/api/api_lib.c \
           lwIP/src/api/api_msg.c \
           lwIP/src/api/err.c \
           lwIP/src/api/netbuf.c \
           lwIP/src/api/netdb.c \
           lwIP/src/api/netifapi.c \
           lwIP/src/api/sockets.c \
           lwIP/src/api/tcpip.c \
           lwIP/src/core/dhcp.c \
           lwIP/src/core/dhcpsrv.c \
           lwIP/src/core/dns.c \
           lwIP/src/core/init.c \
           lwIP/src/core/mem.c \
           lwIP/src/core/memp.c \
           lwIP/src/core/netbios.c \
           lwIP/src/core/netif.c \
           lwIP/src/core/pbuf.c \
           lwIP/src/core/raw.c \
           lwIP/src/core/stats.c \
           lwIP/src/core/sys.c \
           lwIP/src/core/tcp.c \
           lwIP/src/core/tcp_in.c \
           lwIP/src/core/tcp_out.c \
           lwIP/src/core/udp.c \
           lwIP/src/netif/etharp.c \
           lwIP/src/netif/loopif.c \
           lwIP/src/netif/slipif.c \
           marvel/driver/src/assoc.c \
           marvel/driver/src/help_firmware.c \
           marvel/driver/src/if_sdio.c \
           marvel/driver/src/marvel8385_firmware.c \
           marvel/driver/src/marvell_ops.c \
           marvel/driver/src/scan.c \
           STM32F10x_lib/src/USB/usb_core.c \
           STM32F10x_lib/src/USB/usb_init.c \
           STM32F10x_lib/src/USB/usb_int.c \
           STM32F10x_lib/src/USB/usb_mem.c \
           STM32F10x_lib/src/USB/usb_regs.c \
           lwIP/src/core/ipv4/autoip.c \
           lwIP/src/core/ipv4/icmp.c \
           lwIP/src/core/ipv4/igmp.c \
           lwIP/src/core/ipv4/inet.c \
           lwIP/src/core/ipv4/inet_chksum.c \
           lwIP/src/core/ipv4/ip.c \
           lwIP/src/core/ipv4/ip_addr.c \
           lwIP/src/core/ipv4/ip_frag.c \
           lwIP/src/core/ipv6/icmp6.c \
           lwIP/src/core/ipv6/inet6.c \
           lwIP/src/core/ipv6/ip6.c \
           lwIP/src/core/ipv6/ip6_addr.c \
           lwIP/src/core/snmp/asn1_dec.c \
           lwIP/src/core/snmp/asn1_enc.c \
           lwIP/src/core/snmp/mib2.c \
           lwIP/src/core/snmp/mib_structs.c \
           lwIP/src/core/snmp/msg_in.c \
           lwIP/src/core/snmp/msg_out.c \
           lwIP/src/netif/ppp/auth.c \
           lwIP/src/netif/ppp/chap.c \
           lwIP/src/netif/ppp/chpms.c \
           lwIP/src/netif/ppp/fsm.c \
           lwIP/src/netif/ppp/ipcp.c \
           lwIP/src/netif/ppp/lcp.c \
           lwIP/src/netif/ppp/magic.c \
           lwIP/src/netif/ppp/md5.c \
           lwIP/src/netif/ppp/pap.c \
           lwIP/src/netif/ppp/ppp.c \
           lwIP/src/netif/ppp/ppp_oe.c \
           lwIP/src/netif/ppp/randm.c \
           lwIP/src/netif/ppp/vj.c \
           marvel/driver/src/8686_image/8686.c \
           marvel/driver/src/8686_image/help.c