#include <stdio.h>
#include <stdlib.h>

#include "brightness.h"

#define ROUND(EXPR) (((long double)EXPR) + 0.5F)

static const char *const brightness_file_path = "/sys/class/backlight/intel_backlight/brightness";
static const char *const max_brightness_file_path = "/sys/class/backlight/intel_backlight/max_brightness";

unsigned get_brightness(void)
{
        FILE *fp_brightness;
        unsigned brightness;

        fp_brightness = fopen(brightness_file_path, "r");

        if(fp_brightness == NULL)
        {
                printf("E: Failed to Open \"%s\" to Read", brightness_file_path);
                exit(255);
        }

        fscanf(fp_brightness, "%u", &brightness);

        fclose(fp_brightness);

        return brightness;
}

void set_brightness(unsigned brightness)
{
        FILE *fp_brightness;
        unsigned max_brightness;

        fp_brightness = fopen(brightness_file_path, "w");
        max_brightness = get_max_brightness();

        if(fp_brightness == NULL)
        {
                printf("E: Failed to Open \"%s\" to Write\n", brightness_file_path);
                exit(255);
        }

        if(brightness > max_brightness)
        {
                printf("E: '%u' is Larger then the Maximum value '%u'\n", brightness, max_brightness);
                exit(127);
        }

        fprintf(fp_brightness, "%u", brightness);

        fclose(fp_brightness);
}

unsigned get_brightness_percentage(void)
{
        unsigned brightness, max_brightness, brightness_percent;

        brightness = get_brightness();
        max_brightness = get_max_brightness();

        brightness_percent = (unsigned)ROUND(brightness * 100 / max_brightness);

        return brightness_percent;
}

void set_brightness_percentage(unsigned brightness_percent)
{
        unsigned brightness, max_brightness;

        if(brightness_percent > 100)
        {
                printf("E: '%u' is Larger then the Maximum Percentage '100'\n", brightness_percent);
                exit(127);
        }

        max_brightness = get_max_brightness();
        brightness = (unsigned)ROUND(brightness_percent * max_brightness / 100);

        set_brightness(brightness);
}

unsigned get_max_brightness(void)
{
        FILE *fp_max_brightness;
        unsigned max_brightness;

        fp_max_brightness = fopen(max_brightness_file_path, "r");
        fscanf(fp_max_brightness, "%u", &max_brightness);

        if(fp_max_brightness == NULL)
        {
                printf("E: Failed to Open \"%s\" to Read\n", max_brightness_file_path);
                exit(255);
        }

        fclose(fp_max_brightness);

        return max_brightness;
}
