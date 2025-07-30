// Di audit.h
#ifndef AUDIT_H
#define AUDIT_H

struct audit_entry {
  int pid;
  int syscall_num;
  int tick;
};

int copyout_log_to_user(char *buf, int size);  // ← tambahkan ini

#endif
