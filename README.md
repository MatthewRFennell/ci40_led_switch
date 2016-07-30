# Creator Ci40 - LED Switch Control
This project controls the LEDs on the Ci40 using the switches on the board. For more information and detailed instructions, [go to the Instructables guide](http://www.instructables.com/id/Creator-Ci40-LED-Switch/).

## Quickstart guide:
### Installing openwrt and LetMeCreate library
[Follow these steps to install openwrt and the LetMeCreate library](https://github.com/francois-berder/LetMeCreate)
Then, to transfer openwrt to the USB:
```
df
```
The USB appears as /dev/sdb[x] (replace x with the number given by the `df` command). If necessary, unplug the USB and run df again to see which device disappears
```
umount /dev/sdb[x]
```
```
sudo mkfs.ext4 /dev/sdb[x]
```
This formats the USB as ext4 format, which is used by the CreatorBoard. Check the USB is empty. If not, re-enter these commands.
```
sudo nautilus
```
This opens a root file explorer. Copy the contents of /path/to/openwrt/bin/pistachio/openwrt-pistachio-marduk-marduk-cc2520-rootfs to the root folder of the USB
```
sync
```
## Adding the LED Switch program

```
git clone https://github.com/MatthewRFennell/ci40_led_switch.git
```

Transfer the file to custom/letmecreate/LetMeCreate/tests/

Open CMakeLists.txt in /custom/letmecreate/LetMeCreate/tests, and append:

```
add_executable(test_led_switch test_led_switch.c $<TARGET_OBJECTS:common>)
target_link_libraries(test_led_switch letmecreate_core)
install(TARGETS test_led_switch RUNTIME DESTINATION bin)
```

to the bottom of the file.

```
openwrt$ make package/letmecreate/compile V=s
```
```
openwrt $ scp /path/to/openwrt/bin/pistachio/packages/custom/letmecreate_0.1_pistachio.ipk root@PASTE THE IP ADDRESS HERE:~/
```

Then, on the board:

```
opkg install ~/letmecreate_0.1_pistachio.ipk
```

```
/usr/bin/letmecreate_tests/test_led_switch
```
