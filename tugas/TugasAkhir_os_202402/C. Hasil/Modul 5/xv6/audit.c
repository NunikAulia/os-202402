#include "types.h"
#include "stat.h"
#include "user.h"
#include "audit.h" // untuk struct audit_entry jika dipisah

int main() {
  struct audit_entry buf[128];
  int n = get_audit_log((void*)buf, 128);

  if (n < 0) {
    printf(1, "Audit log gagal diambil\n");
    exit();
  }

  for (int i = 0; i < n; i++) {
    printf(1, "[%d] PID=%d SYSCALL=%d TICK=%d\n",
           i, buf[i].pid, buf[i].syscall_num, buf[i].tick);
  }

  exit();
}
