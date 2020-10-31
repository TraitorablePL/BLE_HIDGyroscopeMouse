PROJECT_NAME     := BLE_HID_Gyroscope_Mouse
TARGETS          := nrf51822_xxac
OUTPUT_DIRECTORY := _build

$(OUTPUT_DIRECTORY)/nrf51822_xxac.out: \
  LINKER_SCRIPT  := nrf51822_xxac.ld

# Source files common to all targets
SRC_FILES += \
  components/libraries/log/src/nrf_log_backend_serial.c \
  components/libraries/log/src/nrf_log_frontend.c \
  components/libraries/button/app_button.c \
  components/libraries/util/app_error.c \
  components/libraries/util/app_error_weak.c \
  components/libraries/scheduler/app_scheduler.c \
  components/libraries/timer/app_timer.c \
  components/libraries/timer/app_timer_appsh.c \
  components/libraries/util/app_util_platform.c \
  components/libraries/crc16/crc16.c \
  components/libraries/fds/fds.c \
  components/libraries/fstorage/fstorage.c \
  components/libraries/hardfault/hardfault_implementation.c \
  components/libraries/util/nrf_assert.c \
  components/libraries/util/sdk_errors.c \
  components/libraries/util/sdk_mapped_flags.c \
  components/boards/boards.c \
  components/drivers_nrf/clock/nrf_drv_clock.c \
  components/drivers_nrf/common/nrf_drv_common.c \
  components/drivers_nrf/gpiote/nrf_drv_gpiote.c \
  components/drivers_nrf/uart/nrf_drv_uart.c \
  components/drivers_nrf/spi_master/nrf_drv_spi.c \
  components/libraries/bsp/bsp.c \
  components/libraries/bsp/bsp_btn_ble.c \
  components/libraries/bsp/bsp_nfc.c \
  main.c \
  external/segger_rtt/RTT_Syscalls_GCC.c \
  external/segger_rtt/SEGGER_RTT.c \
  external/segger_rtt/SEGGER_RTT_printf.c \
  components/ble/common/ble_advdata.c \
  components/ble/ble_advertising/ble_advertising.c \
  components/ble/common/ble_conn_params.c \
  components/ble/common/ble_conn_state.c \
  components/ble/common/ble_srv_common.c \
  components/ble/peer_manager/gatt_cache_manager.c \
  components/ble/peer_manager/gatts_cache_manager.c \
  components/ble/peer_manager/id_manager.c \
  components/ble/peer_manager/peer_data.c \
  components/ble/peer_manager/peer_data_storage.c \
  components/ble/peer_manager/peer_database.c \
  components/ble/peer_manager/peer_id.c \
  components/ble/peer_manager/peer_manager.c \
  components/ble/peer_manager/pm_buffer.c \
  components/ble/peer_manager/pm_mutex.c \
  components/ble/peer_manager/security_dispatcher.c \
  components/ble/peer_manager/security_manager.c \
  components/toolchain/gcc/gcc_startup_nrf51.S \
  components/toolchain/system_nrf51.c \
  components/ble/ble_services/ble_bas/ble_bas.c \
  components/ble/ble_services/ble_dis/ble_dis.c \
  components/ble/ble_services/ble_hids/ble_hids.c \
  components/softdevice/common/softdevice_handler/softdevice_handler.c \
  components/softdevice/common/softdevice_handler/softdevice_handler_appsh.c \

# Include folders common to all targets
INC_FOLDERS += \
  components/drivers_nrf/comp \
  components/drivers_nrf/twi_master \
  components/ble/ble_services/ble_ancs_c \
  components/ble/ble_services/ble_ias_c \
  components/softdevice/s130/headers \
  components/libraries/pwm \
  components/libraries/usbd/class/cdc/acm \
  components/libraries/usbd/class/hid/generic \
  components/libraries/usbd/class/msc \
  components/libraries/usbd/class/hid \
  components/libraries/log \
  components/ble/ble_services/ble_gls \
  components/libraries/fstorage \
  components/drivers_nrf/i2s \
  components/libraries/gpiote \
  components/drivers_nrf/gpiote \
  components/boards \
  components/drivers_nrf/common \
  components/ble/ble_advertising \
  components/drivers_nrf/adc \
  components/softdevice/s130/headers/nrf51 \
  components/ble/ble_services/ble_bas_c \
  components/ble/ble_services/ble_hrs_c \
  components/libraries/queue \
  components/ble/ble_dtm \
  components/toolchain/cmsis/include \
  components/ble/ble_services/ble_rscs_c \
  components/drivers_nrf/uart \
  components/ble/common \
  components/ble/ble_services/ble_lls \
  components/drivers_nrf/wdt \
  components/libraries/bsp \
  components/ble/ble_services/ble_bas \
  components/libraries/experimental_section_vars \
  components/ble/ble_services/ble_ans_c \
  components/libraries/slip \
  components/libraries/mem_manager \
  external/segger_rtt \
  components/libraries/csense_drv \
  components/drivers_nrf/hal \
  components/ble/ble_services/ble_nus_c \
  components/drivers_nrf/rtc \
  components/ble/ble_services/ble_ias \
  components/libraries/usbd/class/hid/mouse \
  components/drivers_nrf/ppi \
  components/ble/ble_services/ble_dfu \
  components \
  components/libraries/scheduler \
  components/ble/ble_services/ble_lbs \
  components/ble/ble_services/ble_hts \
  components/drivers_nrf/delay \
  components/libraries/crc16 \
  components/drivers_nrf/timer \
  components/libraries/util \
  components/drivers_nrf/pwm \
  config \
  components/libraries/usbd/class/cdc \
  components/libraries/csense \
  components/drivers_nrf/rng \
  components/libraries/low_power_pwm \
  components/libraries/hardfault \
  components/ble/ble_services/ble_cscs \
  components/libraries/uart \
  components/libraries/hci \
  components/libraries/usbd/class/hid/kbd \
  components/drivers_nrf/spi_slave \
  components/drivers_nrf/lpcomp \
  components/libraries/timer \
  components/drivers_nrf/power \
  components/libraries/usbd/config \
  components/toolchain \
  components/libraries/led_softblink \
  components/drivers_nrf/qdec \
  components/ble/ble_services/ble_cts_c \
  components/drivers_nrf/spi_master \
  components/ble/ble_services/ble_nus \
  components/ble/ble_services/ble_hids \
  components/drivers_nrf/pdm \
  components/libraries/crc32 \
  components/libraries/usbd/class/audio \
  components/ble/peer_manager \
  components/drivers_nrf/swi \
  components/ble/ble_services/ble_tps \
  components/ble/ble_services/ble_dis \
  components/device \
  components/ble/nrf_ble_qwr \
  components/libraries/button \
  components/libraries/usbd \
  components/drivers_nrf/saadc \
  components/ble/ble_services/ble_lbs_c \
  components/ble/ble_racp \
  components/toolchain/gcc \
  components/libraries/fds \
  components/libraries/twi \
  components/drivers_nrf/clock \
  components/ble/ble_services/ble_rscs \
  components/drivers_nrf/usbd \
  components/softdevice/common/softdevice_handler \
  components/ble/ble_services/ble_hrs \
  components/libraries/log/src \

# Libraries common to all targets
LIB_FILES += \

# C flags common to all targets
CFLAGS += -DBOARD_CUSTOM
CFLAGS += -DSOFTDEVICE_PRESENT
CFLAGS += -DNRF51
CFLAGS += -DS130
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -DSWI_DISABLE0
CFLAGS += -DNRF51822
CFLAGS += -DNRF_SD_BLE_API_VERSION=2
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs
CFLAGS +=  -Wall -O3 -g3
CFLAGS += -mfloat-abi=soft
# keep every function in separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums 

# C++ flags common to all targets
CXXFLAGS += \

# Assembler flags common to all targets
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DBOARD_CUSTOM
ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DNRF51
ASMFLAGS += -DS130
ASMFLAGS += -DBLE_STACK_SUPPORT_REQD
ASMFLAGS += -DSWI_DISABLE0
ASMFLAGS += -DNRF51822
ASMFLAGS += -DNRF_SD_BLE_API_VERSION=2

# Linker flags
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys


.PHONY: $(TARGETS) default all clean help flash flash_softdevice

# Default target - first one defined
default: nrf51822_xxac

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo 	nrf51822_xxac

TEMPLATE_PATH := components/toolchain/gcc

include $(TEMPLATE_PATH)/Makefile.common

$(foreach target, $(TARGETS), $(call define_target, $(target)))

# Flash the program
flash: $(OUTPUT_DIRECTORY)/nrf51822_xxac.hex
	@echo Flashing: $<
	nrfjprog --program $< -f nrf51 --sectorerase
	nrfjprog --reset -f nrf51

# Flash softdevice
flash_softdevice:
	@echo Flashing: s130_nrf51_2.0.1_softdevice.hex
	nrfjprog --program components/softdevice/s130/hex/s130_nrf51_2.0.1_softdevice.hex -f nrf51 --sectorerase 
	nrfjprog --reset -f nrf51

erase:
	nrfjprog --eraseall -f nrf52
