# 📝 Laporan Tugas Akhir

**Mata Kuliah**: Sistem Operasi
**Semester**: Genap / Tahun Ajaran 2024–2025
**Nama**: `<Nunik Aulia Primadani>`
**NIM**: `<240202875>`
**Modul yang Dikerjakan**:
`Modul 5 – Audit dan Keamanan Sistem`

---

## 📌 Deskripsi Singkat Tugas

Modul ini bertujuan untuk menambahkan fitur audit log di kernel xv6. Setiap pemanggilan system call akan dicatat ke dalam log, yang hanya dapat diakses oleh proses dengan PID 1 melalui system call khusus `get_audit_log()`. Tujuan utamanya adalah memberikan dasar sistem keamanan dan monitoring aktivitas sistem.

---

## 🛠️ Rincian Implementasi

* Menambahkan struktur `audit_entry` dan `array log audit audit_log[]` di `syscall.c`
* Memodifikasi fungsi `syscall()` untuk mencatat setiap syscall yang valid
* Menambahkan system call baru `get_audit_log()`:
* Mendeklarasikan di `syscall.h`, `user.h`, `usys.S`
* Registrasi di `syscall.c`
Implementasi fungsi di `sysproc.c`
* Menambahkan validasi agar hanya proses dengan PID 1 yang bisa mengakses audit log
* Menambahkan file uji `audit.c` untuk membaca dan mencetak log audit
* Menambahkan `_audit` ke dalam `Makefile` pada bagian `UPROGS`

---

## ✅ Uji Fungsionalitas

Program uji: `audit`

Pengujian dilakukan dengan dua skenario:

* Dijalankan sebagai proses biasa
    * Output: akses ditolak (`Access denied or error.`)
* Dijalankan sebagai `init` (PID 1)
    * Mengubah `init.c` agar menjalankan `audit` terlebih dahulu
    * Audit log berhasil dibaca

---

## 📷 Hasil Uji

### 📍 Output saat audit dijalankan sebagai proses biasa:
```
Access denied or error.
```
## 📍 Output saat audit dijalankan sebagai PID 1:
```
=== Audit Log ===
[0] PID=1 SYSCALL=5 TICK=12
[1] PID=1 SYSCALL=6 TICK=13
[2] PID=1 SYSCALL=6 TICK=13
[3] PID=1 SYSCALL=6 TICK=13
[4] PID=1 SYSCALL=6 TICK=14
[5] PID=1 SYSCALL=1 TICK=15

```
### 📸 Screenshot

<img width="982" height="420" alt="Screenshot 2025-07-19 152545" src="https://github.com/user-attachments/assets/ee980d35-fe3a-4eae-8b41-4c87f173d8de" />

<img width="427" height="699" alt="Screenshot 2025-07-23 162955" src="https://github.com/user-attachments/assets/248940e3-9060-4084-863c-8b1bcb0d77a6" />

---

## ⚠️ Kendala yang Dihadapi

* Pernah terjadi error `undefined reference to 'copyout_log_to_user'` karena salah menuliskan nama fungsi dan belum menambahkan deklarasi eksternal.
* Program `audit` gagal mendapatkan log jika dijalankan oleh proses selain PID 1.
* Harus menyunting `init.c` agar bisa menjadikan `audit` sebagai proses pertama untuk pengujian log.

---

## 📚 Referensi

Tuliskan sumber referensi yang Anda gunakan, misalnya:

* Buku xv6 MIT: [https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
* Repositori xv6-public: [https://github.com/mit-pdos/xv6-public](https://github.com/mit-pdos/xv6-public)
* Diskusi praktikum, Stack Overflow, dan dokumentasi xv6

---

