// see linux/tools/testing/selftests/rtc/ for more examples

#include "rtc.h"

#include <linux/rtc.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <assert.h>

#define ALARM_DELTA 3
static char *rtc_file = "/dev/rtc0";

bool readDateTime()
{
    struct rtc_time rtc_tm;

    int fd = open(rtc_file, O_RDONLY);
    if (fd == -1) {
        printf("Failed to open %s\n", rtc_file);
        close(fd);
        return false;
    }

    if (ioctl(fd, RTC_RD_TIME, &rtc_tm) == -1) {
        printf("RTC_RD_TIME ioctl failed!\n");
        close(fd);
        return false;
    }
    printf("Current RTC date/time is %02d/%02d/%02d %02d:%02d:%02d.\n",
           rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
           rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

    close(fd);
    return true;
}

//bool setDateTime()
//{
//    struct rtc_time new_time;

//    new_time.tm_mday = 15;
//    new_time.tm_mon = 5;
//    new_time.tm_year = 2020;
//    new_time.tm_hour = 15;
//    new_time.tm_min = 5;
//    new_time.tm_sec = 5;

//    new_time.tm_mon -= 1;
//    new_time.tm_year -= 1900;

//    int fd = open(rtc_file, O_RDONLY);
//    if (fd <= -1) {
//        printf("Failed to open %s\n", rtc_file);
//        close(fd);
//        return false;
//    }

//    printf("Set RTC date/time to %d-%d-%d, %02d:%02d:%02d.\n",
//        new_time.tm_mday, new_time.tm_mon + 1, new_time.tm_year + 1900,
//        new_time.tm_hour, new_time.tm_min, new_time.tm_sec);

//    if (ioctl(fd, RTC_SET_TIME, &new_time) == -1) {
//        printf("RTC_SET_TIME ioctl failed!\n");
//        close(fd);
//        return false;
//    }

//    close(fd);
//    return true;
//}

//bool updateInterrupts()
//{
//    int i, rc, irq = 0;
//    unsigned long data;

//    printf("%s %d\n", __FUNCTION__, __LINE__);

//    int fd = open(rtc_file, O_RDONLY);
//    if (fd <= -1) {
//        printf("Failed to open %s\n", rtc_file);
//        close(fd);
//        return false;
//    }
//    printf("%s %d\n", __FUNCTION__, __LINE__);
//    /* Turn on update interrupts */
//    if (ioctl(fd, RTC_UIE_ON, 0) == -1) {
//        printf("IRQs not supported!\n");
//        close(fd);
//        return false;
//    }

//    for (i = 0; i < 3; i++) {
//        /* This read will block */
//        printf("%s %d\n", __FUNCTION__, __LINE__);
//        rc = read(fd, &data, sizeof(data));
//        assert(-1 != rc);
//        irq++;
//        printf("%s %d\n", __FUNCTION__, __LINE__);
//    }
//    printf("%s %d\n", __FUNCTION__, __LINE__);
//    assert(3 == irq);
//    printf("%s %d\n", __FUNCTION__, __LINE__);
//    rc = ioctl(fd, RTC_UIE_OFF, 0);
//    assert(-1 != rc);
//    close(fd);
//    return true;
//}

//void alarmSet()
//{
//    struct timeval tv = { .tv_sec = ALARM_DELTA + 2 };
//    unsigned long data;
//    struct rtc_time tm;
//    fd_set readfds;
//    time_t secs, new_t;
//    int rc;

//    int fd = open(rtc_file, O_RDONLY);
//    if (fd <= -1) {
//        printf("Failed to open %s\n", rtc_file);
//        close(fd);
//        return;
//    }

//    rc = ioctl(fd, RTC_RD_TIME, &tm);
//    assert(-1 != rc);
//    printf("Current RTC time is %02d:%02d:%02d.\n",
//           tm.tm_hour, tm.tm_min, tm.tm_sec);

//    secs = timegm((struct tm *)&tm) + ALARM_DELTA;
//    gmtime_r(&secs, (struct tm *)&tm);

//    rc = ioctl(fd, RTC_ALM_SET, &tm);
//    if (rc == -1) {
//        printf("alarms are not supported!\n");
//        return;
//    }

//    rc = ioctl(fd, RTC_ALM_READ, &tm);
//    assert(-1 != rc);

//    printf("Alarm time now set to %02d:%02d:%02d.\n",
//           tm.tm_hour, tm.tm_min, tm.tm_sec);

//    /* Enable alarm interrupts */
//    rc = ioctl(fd, RTC_AIE_ON, 0);
//    assert(-1 != rc);

//    FD_ZERO(&readfds);
//    FD_SET(fd, &readfds);

//    /* The select will wait until an RTC interrupt happens. */
//    rc = select(fd + 1, &readfds, NULL, NULL, &tv);
//    assert(-1 != rc);
//    assert(0 != rc);

//    /* Disable alarm interrupts */
//    rc = ioctl(fd, RTC_AIE_OFF, 0);
//    assert(-1 != rc);

//    rc = read(fd, &data, sizeof(unsigned long));
//    assert(-1 != rc);
//    printf("data: %lx\n", data);

//    rc = ioctl(fd, RTC_RD_TIME, &tm);
//    assert(-1 != rc);

//    printf("Time after alarm %02d:%02d:%02d.\n",
//           tm.tm_hour, tm.tm_min, tm.tm_sec);

//    new_t = timegm((struct tm *)&tm);
//    assert(new_t == secs);
//}
