# 📝 Laporan Tugas Akhir

**Mata Kuliah**: Sistem Operasi
**Semester**: Genap / Tahun Ajaran 2024–2025
**Nama**: `<Nunik Aulia Primadani>`
**NIM**: `<N240202875>`
**Modul yang Dikerjakan**:
`Modul 2 – Penjadwalan CPU Lanjutan (Priority Scheduling Non-Preemptive)`

---

## 📌 Deskripsi Singkat Tugas

Modul 2 – Penjadwalan CPU Lanjutan (Priority Scheduling Non-Preemptive):
Modul ini bertujuan untuk mengubah algoritma penjadwalan proses di sistem operasi xv6 (x86) dari Round Robin standar menjadi Non-Preemptive Priority Scheduling. Implementasi melibatkan penambahan field priority pada setiap struktur proses, penambahan system call set_priority(int) untuk mengatur prioritas proses, dan modifikasi fungsi scheduler agar selalu menjalankan proses RUNNABLE dengan prioritas tertinggi (nilai prioritas terkecil).

---

## 🛠️ Rincian Implementasi

berikut adalah langkah-langkah implementasi yang dilakukan:
* Menambahkan field int priority; ke struct proc di file proc.h.
* Menginisialisasi nilai priority default (60) untuk setiap proses baru di fungsi allocproc() dalam proc.c.
*Menambahkan nomor system call baru SYS_set_priority (24) di syscall.h.
* Menambahkan deklarasi fungsi user-level int set_priority(int priority); di user.h.
*Menambahkan entri stub assembly SYSCALL(set_priority) di usys.S.
*Mendaftarkan system call sys_set_priority di syscall.c dengan menambahkan deklarasi extern int sys_set_priority(void); dan entri [SYS_set_priority] sys_set_priority, ke array sys_calls[].
* Mengimplementasikan fungsi sys_set_priority() di sysproc.c untuk mengatur prioritas proses saat ini berdasarkan argumen yang diberikan, dengan validasi nilai prioritas antara 0 dan 100.
* Memodifikasi fungsi scheduler() di proc.c untuk mencari proses RUNNABLE dengan nilai priority terkecil (prioritas tertinggi) dan menjalankannya. Ini mengubah perilaku scheduler menjadi non-preemptive berdasarkan prioritas.
* Membuat program uji user-level ptest.c yang membuat dua proses anak dengan prioritas berbeda untuk memverifikasi perilaku penjadwalan.
* Mendaftarkan program uji _ptest ke dalam Makefile agar dapat di-build dan dijalankan di xv6.

---

## ✅ Uji Fungsionalitas

Program uji yang digunakan untuk memverifikasi fungsionalitas system call baru dan algoritma penjadwalan adalah:
* ptest: Digunakan untuk menguji set_priority() dan perilaku penjadwalan non-preemptive berbasis prioritas. Program ini membuat dua proses anak yang melakukan pekerjaan sibuk (busy()) dan menetapkan prioritas yang berbeda pada masing-masing.

---

## 📷 Hasil Uji

Berikut adalah contoh output terminal dari program uji ptest yang dijalankan di shell xv6:

📍 Contoh Output ptest:
$ ptest
Child 2 selesai   // prioritas tinggi (10) → selesai duluan
Child 1 selesai   // prioritas rendah (90)
Parent selesai

Hasil ini memvalidasi bahwa proses dengan prioritas lebih tinggi (angka lebih kecil) dieksekusi terlebih dahulu hingga selesai, menunjukkan karakteristik penjadwalan non-preemptive berdasarkan prioritas.

## 📷 Screenshot
<img width="992" height="447" alt="Screenshot 2025-07-18 153617" src="https://github.com/user-attachments/assets/7c0d8aad-c58d-4211-a5d9-023d74e3011f" />

---

## ⚠️ Kendala yang Dihadapi

Beberapa kendala yang ditemui selama implementasi:
* Lupa memodifikasi semua bagian dari scheduler(), sehingga proses tetap dijalankan dengan Round Robin pada awalnya.
* Salah memasukkan prioritas di syscall set_priority(), menyebabkan proses tidak mengalami perubahan prioritas seperti yang diharapkan.
* ptest tidak muncul saat dijalankan karena tidak ditambahkan ke Makefile.
Semua kendala berhasil diatasi dengan debugging dan uji coba bertahap.

---

## 📚 Referensi

* Buku xv6 MIT: [https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
* Repositori xv6-public: [https://github.com/mit-pdos/xv6-public](https://github.com/mit-pdos/xv6-public)
* Diskusi dengan asisten praktikum dan eksperimen mandiri di lingkungan kernel xv6

---

## 📝 Kesimpulan
Dengan modul ini, saya telah berhasil:
* Menambahkan satu field baru pada kernel (priority)
* Membuat satu syscall baru (set_priority)
*Mengubah logika penjadwalan proses dalam kernel menjadi Priority Scheduling Non-Preemptive.
Perubahan ini menunjukkan bagaimana sistem operasi dapat dikustomisasi untuk mendukung algoritma penjadwalan yang lebih deterministik, dengan kontrol lebih besar terhadap urutan eksekusi proses. Modul ini memperkuat pemahaman saya tentang struktur proses di kernel dan interaksi syscall di xv6.
