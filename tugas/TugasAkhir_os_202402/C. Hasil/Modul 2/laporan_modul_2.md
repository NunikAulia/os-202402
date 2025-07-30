# 📝 Laporan Tugas Akhir

**Mata Kuliah**: Sistem Operasi
**Semester**: Genap / Tahun Ajaran 2024–2025
**Nama**: `<Nunik Aulia Primadani>`
**NIM**: `<240202875>`
**Modul yang Dikerjakan**:
`Modul 2 – Penjadwalan CPU Lanjutan (Priority Scheduling Non-Preemptive)`

---

## 📌 Deskripsi Singkat Tugas

Modul ini berfokus pada perubahan algoritma penjadwalan proses di `xv6-public ` dari Round Robin menjadi Non-Preemptive Priority Scheduling. Implementasi ini melibatkan:
  * Penambahan field `priority` pada setiap struktur proses.
  * Penambahan ystem call `set_priority(int)` untuk memungkinkan proses mengatur prioritasnya sendiri.
  * Modifikasi scheduler kernel agar selalu memilih dan menjalankan proses dalam status RUNNABLE yang memiliki prioritas tertinggi (nilai numerik terkecil).

---

## 🛠️ Rincian Implementasi

Berikut adalah langkah-langkah implementasi yang dilakukan:
* `proc.h`:
  * Menambahkan field `priority` (tipe `int`) ke dalam `struct proc` untuk menyimpan nilai prioritas setiap proses (0 = tertinggi, 100 = terendah).
* `proc.c`:
  * Memodifikasi fungsi `allocproc()` untuk menginisialisasi `p->priority` dengan nilai default 60 saat proses baru dialokasikan.
  * Mengubah fungsi `scheduler()` agar mencari proses `RUNNABLE` dengan nilai priority terkecil (prioritas tertinggi) di antara semua proses yang tersedia. Proses ini kemudian dipilih untuk dieksekusi secara non-preemptive.
* `sysproc.c`:
  * Mengimplementasikan fungsi system call `sys_set_priority(void)` yang mengambil argumen prioritas dari pengguna, memvalidasi rentang prioritas (0-100), dan mengatur field priority pada proses yang sedang berjalan (`myproc()`).
* `syscall.h`, `user.h`, `usys.S`, `syscall.c`:
  * Mendaftarkan system call `set_priority` dengan menambahkan nomor system call baru (`SYS_set_priority 24`) di `syscall.h`, mendeklarasikan fungsi `set_priority` di `user.h`, menambahkan entri system call di `usys.S`, dan mendaftarkan `sys_set_priority` di tabel system call `syscall.c`.
* `Makefile`:
  * Menambahkan `_ptest` ke daftar `UPROGS` agar program uji dapat dikompilasi.

---

## ✅ Uji Fungsionalitas

Program uji berikut digunakan untuk memverifikasi fungsionalitas yang telah diimplementasikan:
* `ptest`: untuk menguji system call `set_priority()` dan perilaku penjadwalan non-preemptive berdasarkan prioritas. Program ini membuat dua proses anak dengan prioritas berbeda dan mengamati urutan penyelesaiannya.

---

## 📷 Hasil Uji

Berikut adalah contoh output terminal dari program uji `ptest` yang dijalankan di shell xv6:

📍 Contoh Output ptest:
```
$ ptest
Child 2 selesai   // prioritas tinggi (10) → selesai duluan
Child 1 selesai   // prioritas rendah (90)
Parent selesai
```

Hasil ini memvalidasi bahwa proses dengan prioritas lebih tinggi (angka lebih kecil) dieksekusi terlebih dahulu hingga selesai, menunjukkan karakteristik penjadwalan non-preemptive berdasarkan prioritas.

---
## 📷 Screenshot
<img width="992" height="447" alt="Screenshot 2025-07-18 153617" src="https://github.com/user-attachments/assets/7c0d8aad-c58d-4211-a5d9-023d74e3011f" />

---

## ⚠️ Kendala yang Dihadapi

Selama proses implementasi, beberapa kendala yang mungkin dihadapi antara lain:
* Pemahaman Mekanisme Penjadwalan xv6: Memahami bagaimana `scheduler()` bekerja dan bagaimana memodifikasi loop pencarian proses `RUNNABLE` untuk mengimplementasikan logika prioritas.
* Integrasi System Call: Memastikan semua langkah pendaftaran system call (deklarasi, entri `usys.S`, pendaftaran di `syscall.c`, dan penomoran di `syscall.h`) dilakukan dengan benar dan konsisten.
* Efek Non-Preemption: Memahami implikasi dari penjadwalan non-preemptive, di mana proses dengan prioritas lebih rendah mungkin tidak akan pernah berjalan jika ada proses berprioritas tinggi yang selalu `RUNNABLE` (masalah starvation). Meskipun tidak diatasi di modul ini, ini adalah pertimbangan penting untuk sistem nyata.
* Nilai Prioritas: Menentukan rentang dan interpretasi nilai prioritas (misalnya, angka kecil = prioritas tinggi) dan memastikan konsistensi di seluruh implementasi.

---

## 📚 Referensi

* Buku xv6 MIT: [https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
* Repositori xv6-public: [https://github.com/mit-pdos/xv6-public](https://github.com/mit-pdos/xv6-public)
* Diskusi dengan asisten praktikum dan eksperimen mandiri di lingkungan kernel xv6

---

## 📝 Kesimpulan
Dengan modul ini, saya telah berhasil:
* Menambahkan satu field baru pada kernel (`priority`)
* Membuat satu syscall baru (`set_priority`)
*Mengubah logika penjadwalan proses dalam kernel menjadi Priority Scheduling Non-Preemptive.
Perubahan ini menunjukkan bagaimana sistem operasi dapat dikustomisasi untuk mendukung algoritma penjadwalan yang lebih deterministik, dengan kontrol lebih besar terhadap urutan eksekusi proses. Modul ini memperkuat pemahaman saya tentang struktur proses di kernel dan interaksi syscall di xv6.
