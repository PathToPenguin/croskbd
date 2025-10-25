#ifndef EVDEV_H
#define EVDEV_H

#include <croskbd.h>

typedef struct input_device {
	char event_name[10];
	int fd;
} input_device;

int get_keyboards(input_device *dev);
int get_touchpad(input_device *dev);
int get_tablet_switch(input_device *dev);
void close_dev_fds(KeyboardDevice *kdev, TabletSwitchDevice *tdev,
				   TouchpadDevice *pdev);
void load_kb_layout_data(KeyboardDevice *kdev);

#endif
