# added "nuvoton-ipmi-oem" recipe
# https://github.com/Nuvoton-Israel/nuvoton-ipmi-oem
## Test the IPMI command in the BMC console: 
```
Get strap pin status
  CMD: 0x30 / NetFn:0x01

```

## Usage

|Name          | Format  | Return                                                                                                   | Note |
|:-------------:|:-------: |:--------------------------------------------------------------------------------------------------------: | :-------:     |
| Get strap pin status      | ipmitool raw 0x30 0x2 | 4 bytes are returned.  | Please refer to NPCMxx series datasheet about **PWRON** register for reference. |
| Get uart mode             | ipmitool raw 0x30 0x4 | 1 byte is returned to indicated the uart mux mode. | Please refer to NPCMxx series datasheet about **SPSWC** register for reference. |
| Get usb device status     | ipmitool raw 0x30 0x6 ${usb_id} | If **0** is returned, the usb device in query is connected. Otherwise, the usb device is not connected.  | Please refer to NPCM7xx series datasheet for the number of available usb devices. |
| Get gpio status           | ipmitool raw 0x30 0x8 ${pin_id} | 2 byte are returned to indicated the direction and level if the pin is configured as a gpio. If the return is not in 2-byte form, the pin is not configured as a gpio. | The first bye indicates the direction of the pin and the second byte indicates the level of the pin. Please refer to NPCM7xx series datasheet for the number of available pins. |
| Get BMC reboot reason     | ipmitool raw 0x30 0xa | 2 byte are returned to indicated the reboot reason. The bit which **is not** set is the reboot reason. | Please refer to NPCMxx series datasheet about **INTCR2** register for reference |
| Get image location status | ipmitool raw 0x30 0xc | If **0** is returned, the bmc boots from the first flash. If **1** is returned, the bmc boots from the second flash.  |  |







