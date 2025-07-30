# 📝 Laporan Tugas Akhir

**Mata Kuliah**: Sistem Operasi
**Semester**: Genap / Tahun Ajaran 2024–2025
**Nama**: `<Nunik Aulia Primadani>`
**NIM**: `<240202875>`
**Modul yang Dikerjakan**:
`Modul 4 – Subsistem Kernel Alternatif (System Call chmod dan Device /dev/random)`

---

## 📌 Deskripsi Singkat Tugas

* Modul 4 – Subsistem Kernel Alternatif:
Modul ini menambahkan dua fitur penting ke kernel xv6:
  * System Call chmod() untuk mengatur mode file (read-only atau read-write). Jika file disetel sebagai read-only, proses tidak dapat menulis ke file tersebut.
  * Pseudo-device /dev/random, yaitu sebuah driver perangkat karakter yang menghasilkan byte acak saat dibaca oleh program u

---

## 🛠️ Rincian Implementasi

* Menambahkan field short mode pada struktur inode di fs.h (hanya di memori, tidak ke disk layout).
* Membuat syscall baru chmod(path, mode) di sysfile.c yang mengatur ip->mode.
* Registrasi syscall dilakukan di:
    * syscall.h (#define SYS_chmod 27)
    * syscall.c ([SYS_chmod] = sys_chmod)
    * user.h (int chmod(char*, int);)
    * usys.S (SYSCALL(chmod))
* Memodifikasi filewrite() di file.c untuk mengecek f->ip->mode. Jika mode == 1, penulisan ditolak.
* Menambahkan file random.c yang berisi fungsi randomread() untuk menghasilkan byte acak menggunakan LCG (linear congruential generator).
* Registrasi handler random device di devsw[3] pada file.c.
* Menambahkan pemanggilan mknod("/dev/random", 1, 3); di init.c untuk membuat device node /dev/random.
* Menambahkan dua program uji:
    * chmodtest.c: menguji pembatasan akses tulis pada file read-only.
    * randomtest.c: menguji pembacaan 8 byte acak dari /dev/random.
---

## ✅ Uji Fungsionalitas

* chmodtest: menguji syscall chmod() untuk mengatur file menjadi read-only, lalu mencoba menulis ke file tersebut.
* randomtest: membuka /dev/random dan membaca 8 byte acak untuk memastikan driver berjalan.

---

## 📷 Hasil Uji

### 📍 Output chmodtest:
```
Write blocked as expected
```
### 📍 Output randomtest (acak tiap run):
```
241 6 82 99 12 201 44 73
```
### 📷 Screenshot
<img width="1087" height="408" alt="Screenshot 2025-07-28 163241" src="https://github.com/user-attachments/assets/0e5f6a75-17bd-4b05-b09b-478702d9ad78" />

<img width="1044" height="418" alt="Screenshot 2025-07-27 091905" src="https://github.com/user-attachments/assets/96e22a04-0c7a-4c59-b61c-9ce75647d2d4" />

---

## ⚠️ Kendala yang Dihadapi

* Kompilasi awal gagal karena mencoba menambahkan mode ke struktur inode disk tanpa memodifikasi layout disk (yang bisa menyebabkan panic).
* Terjadi panic ketika randomread() belum diregister di devsw[].
* Lupa membuat node /dev/random menggunakan mknod() di init.c, sehingga open() gagal di randomtest.c.
* Beberapa kali lupa menambahkan program uji di UPROGS pada Makefile, menyebabkan binary tidak muncul.

---

## 📚 Referensi

Tuliskan sumber referensi yang Anda gunakan, misalnya:

* Buku xv6 MIT: [https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
* Repositori xv6-public: [https://github.com/mit-pdos/xv6-public](https://github.com/mit-pdos/xv6-public)
* Diskusi praktikum dan dokumentasi kernel
* Stack Overflow dan GitHub Issues seputar mknod, inode, dan device driver xv6

---

