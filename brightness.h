#ifndef BRIGHTNESS_H_
#define BRIGHTNESS_H_

extern unsigned get_brightness(void);
extern void     set_brightness(unsigned);
extern unsigned get_brightness_percentage(void);
extern void     set_brightness_percentage(unsigned);
extern unsigned get_max_brightness(void);

#endif  /* BRIGHTNESS_H_ */
