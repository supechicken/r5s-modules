#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#define TEMP_POLICY_FILE  "/sys/class/thermal/thermal_zone0/policy"
#define CUR_TEMP_FILE     "/sys/class/thermal/thermal_zone0/temp"
#define FAN_LEVEL_FILE    "/sys/class/thermal/cooling_device0/cur_state"

time_t cur_time;
int temp_policy, temp_file, fan_level, kmsg;
char msg_buf[256];

void print_log(void) {
  write(kmsg, msg_buf, strlen(msg_buf) + 1);
  fwrite(msg_buf, strlen(msg_buf) + 1, 1, stderr);
}

void init_file_ptrs(void) {
  temp_policy = open(TEMP_POLICY_FILE, O_WRONLY);
  temp_file   = open(CUR_TEMP_FILE, O_RDONLY);
  fan_level   = open(FAN_LEVEL_FILE, O_RDWR);
  kmsg        = open("/dev/kmsg", O_WRONLY);
}

void rewind_fds(void) {
  lseek(temp_policy, 0, SEEK_SET);
  lseek(temp_file, 0, SEEK_SET);
  lseek(fan_level, 0, SEEK_SET);
}

int get_value(int fd) {
  char buf[64];

  rewind_fds();
  read(fd, buf, sizeof(buf));

  return atoi(buf);
}

int main(int argc, char **argv) {
  init_file_ptrs();

  int prev_level = 0, cur_level;

  while (1) {
    cur_level = get_value(fan_level);

    if (prev_level != cur_level) {
      time(&cur_time);
      snprintf(msg_buf, sizeof(msg_buf), "[%s] pwmfan: Fan level changed from %i to %i\n", ctime(&cur_time), prev_level, cur_level);
      print_log();

      prev_level = cur_level;
    }

    sleep(5);
  }

  return 0;
}
