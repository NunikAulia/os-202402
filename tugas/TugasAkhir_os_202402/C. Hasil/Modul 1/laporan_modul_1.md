# 📝 Laporan Tugas Akhir

**Mata Kuliah**: Sistem Operasi
**Semester**: Genap / Tahun Ajaran 2024–2025
**Nama**: `<Nunik Aulia Primadani>`
**NIM**: `<240202875>`
**Modul yang Dikerjakan**:
Modul 1-System Call dan Instrumentasi Kernel

---

## 📌 Deskripsi Singkat Tugas

**Modul 1 – System Call dan Instrumentasi Kernel**:
  Modul ini berfokus pada penambahan dua system call baru ke sistem operasi xv6 (x86) dan melakukan instrumentasi kernel. System call yang diimplementasikan adalah getpinfo() untuk mendapatkan informasi proses aktif (PID, ukuran memori, dan nama proses) dan getReadCount() untuk mengembalikan total jumlah pemanggilan fungsi read() sejak sistem boot.
  
## 🛠️ Rincian Implementasi

berikut adalah langkah-langkah implementasi yang dilakukan:
- Menambahkan dua system call baru (sys_getpinfo dan sys_getreadcount) di     file sysproc.c.
- Mengedit syscall.c untuk mendeklarasikan dan meregistrasikan system call    baru ke dalam dispatch table kernel.
- Mengubah user.h untuk menambahkan forward declaration struct pinfo dan      deklarasi fungsi user-level getpinfo() serta getreadcount().
- Mengedit usys.S untuk menambahkan entri stub assembly untuk system call     getpinfo dan getreadcount.
- Menambahkan definisi struktur struct pinfo di proc.h untuk menampung        informasi proses.
- Menambahkan variabel global readcount di sysproc.c sebagai counter untuk    panggilan read().
- Memodifikasi fungsi sys_read() di sysfile.c untuk mengincrement readcount   setiap kali dipanggil.
- Membuat dua program uji user-level: ptest.c untuk menguji getpinfo() dan    rtest.c untuk menguji getreadcount().
- Mendaftarkan program uji _ptest dan _rtest ke dalam Makefile agar dapat     di-build dan dijalankan di xv6.
  
### Contoh untuk Modul 1:

* Menambahkan dua system call baru di file `sysproc.c` dan `syscall.c`
* Mengedit `user.h`, `usys.S`, dan `syscall.h` untuk mendaftarkan syscall
* Menambahkan struktur `struct pinfo` di `proc.h`
* Menambahkan counter `readcount` di kernel
* Membuat dua program uji: `ptest.c` dan `rtest.c`
---

## ✅ Uji Fungsionalitas
Program uji yang digunakan untuk memverifikasi fungsionalitas system call    baru adalah:
- ptest: Digunakan untuk menguji system call getpinfo() dan menampilkan        daftar proses aktif beserta PID, ukuran memori, dan namanya.
- rtest: Digunakan untuk menguji system call getreadcount() dan                memverifikasi bahwa counter read() bertambah setelah operasi baca            dilakukan.

## 📷 Hasil Uji
Berikut adalah contoh output terminal dari program uji yang dijalankan di shell xv6:

📍 Contoh Output ptest:
$ ptest
PID	MEM	NAME
1	4096	init
2	2048	sh
3	2048	ptest

📍 Contoh Output rtest:
$ rtest
Read Count Sebelum: 4
Masukkan 5 karakter (lalu tekan Enter): hello
Read Count Setelah: 5

## 📷 Screenshot :
<img width="961" height="524" alt="Screenshot 2025-07-29 115401" src="https://github.com/user-attachments/assets/ac65bb5c-2f45-4243-8685-c87d6796be0f" />

## ⚠️ Kendala yang Dihadapi

Beberapa kendala yang sempat saya hadapi selama pengerjaan modul ini adalah:
- Kesalahan awal dalam menggunakan ptable.proc pada perulangan proses aktif,   yang ternyata harus menggunakan array global proc[NPROC].
- Kesalahan dalam pemrosesan pointer saat memanggil argptr() sehingga sempat   terjadi panic karena pointer tidak valid.
- Ketidaksesuaian definisi struct pinfo antara kernel dan user space           menyebabkan error saat kompilasi.
- Awalnya lupa mendaftarkan program uji ke dalam Makefile, sehingga binary     tidak muncul di shell xv6.
Semua kendala tersebut berhasil diatasi dengan debugging bertahap dan merujuk pada dokumentasi xv6.

---

## 📚 Referensi

* Buku xv6 MIT: [https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
* Repositori xv6-public: [https://github.com/mit-pdos/xv6-public](https://github.com/mit-pdos/xv6-public)
* Stack Overflow, GitHub Issues, diskusi praktikum
*Diskusi praktikum dan pembahasan asisten dosen
*Stack Overflow dan forum GitHub Issues untuk error terkait syscall dan pointer
---

