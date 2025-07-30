# 📝 Laporan Tugas Akhir

**Mata Kuliah**: Sistem Operasi
**Semester**: Genap / Tahun Ajaran 2024–2025
**Nama**: `<Nunik Aulia Primadani>`
**NIM**: `<240202875>`
**Modul yang Dikerjakan**:
`Modul 3 – Manajemen Memori Tingkat Lanjut (Copy-on-Write Fork dan Shared Memory)`

---

## 📌 Deskripsi Singkat Tugas

Modul ini berfokus pada implementasi dua teknik manajemen memori tingkat lanjut dalam sistem operasi xv6:
* Copy-on-Write (CoW) Fork: Mengubah perilaku fork() agar tidak lagi menyalin seluruh memori proses secara langsung. Sebaliknya, halaman-halaman memori dibagikan sebagai read-only antara proses induk dan anak. Penyalinan halaman hanya dilakukan saat terjadi percobaan penulisan (melalui page fault). Implementasi ini memanfaatkan reference count untuk manajemen memori fisik yang efisien.
* Shared Memory ala System V: Menambahkan dua system call baru, yaitu shmget(int key) dan shmrelease(int key), yang memungkinkan antar-proses untuk berbagi satu halaman memori fisik. Mekanisme reference count juga digunakan untuk mengelola halaman shared memory.

---

## 🛠️ Rincian Implementasi

Berikut adalah ringkasan modifikasi yang dilakukan pada kernel xv6:

* vm.c:
    *Menambahkan array global ref_count[] untuk melacak jumlah referensi ke setiap halaman fisik.
    * Mengimplementasikan fungsi incref(char *pa) dan decref(char *pa) untuk memanipulasi reference count halaman fisik.
    * Memodifikasi fungsi copyuvm() menjadi cowuvm() untuk mengimplementasikan logika CoW, yaitu menghapus flag PTE_W dan menambahkan flag PTE_COW pada page table entry (PTE) serta memanggil incref().
    * Menambahkan struktur shmtab[] untuk mengelola segmen shared memory.

* trap.c:
    * Menambahkan handler untuk page fault (T_PGFLT). Handler ini bertanggung jawab untuk mendeteksi page fault pada halaman yang ditandai PTE_COW, mengalokasikan halaman fisik baru, menyalin data dari halaman lama ke halaman baru, mengurangi reference count halaman lama, dan memperbarui PTE dengan flag PTE_W (menghapus PTE_COW).

* proc.c:
    * Mengubah implementasi fork() agar memanggil cowuvm() alih-alih copyuvm() untuk mengelola memori proses anak.

* mmu.h:
    * Menambahkan custom flag PTE_COW (nilai 0x200) untuk menandai halaman yang berada dalam mode Copy-on-Write.

* sysproc.c:
    * Mengimplementasikan system call sys_shmget() untuk mengalokasikan atau mendapatkan segmen shared memory berdasarkan kunci (key), serta memetakan halaman tersebut ke ruang alamat proses.
    * Mengimplementasikan system call sys_shmrelease() untuk mengurangi reference count segmen shared memory dan membebaskan halaman fisik jika reference count mencapai nol.

* user.h, usys.S, syscall.c, syscall.h:
    * Mendaftarkan system call shmget dan shmrelease ke dalam tabel system call xv6 agar dapat dipanggil dari aplikasi pengguna.

---

## ✅ Uji Fungsionalitas

Program uji berikut digunakan untuk memverifikasi fungsionalitas yang telah diimplementasikan:
* cowtest: untuk menguji perilaku fork() dengan Copy-on-Write, memastikan bahwa penulisan pada proses anak tidak memengaruhi proses induk.
* shmtest: untuk menguji fungsionalitas shmget() dan shmrelease(), memastikan bahwa proses induk dan anak dapat berbagi dan memodifikasi data pada halaman memori yang sama.

---

## 📷 Hasil Uji

Berikut adalah contoh output terminal dari program uji yang dijalankan:

### 📍 Contoh Output `cowtest`:

```
Child sees: Y
Parent sees: X
```

### 📍 Contoh Output `shmtest`:

```
Child reads: A
Parent reads: B
```

### 📷 Screenshot

<img width="973" height="454" alt="Screenshot 2025-07-28 162834" src="https://github.com/user-attachments/assets/c747727a-16a5-44ad-8589-0a099bfbefa8" />


<img width="1003" height="441" alt="Screenshot 2025-07-28 162757" src="https://github.com/user-attachments/assets/335a85a7-8ae9-4d28-ac95-5dd51ef812a6" />


---

## ⚠️ Kendala yang Dihadapi

Selama proses implementasi, beberapa kendala yang mungkin dihadapi antara lain:
* Pernah terjadi kernel panic karena tidak semua pemanggilan kalloc() atau kfree() dilindungi dengan incref/decref.
* Salah akses ref_count (mengakses indeks negatif saat V2P(pa) di luar rentang) menyebabkan error.
* Page fault handler awalnya tidak memperbarui flag PTE_COW, menyebabkan page fault berulang.
* Pemetaan shared memory ke alamat USERTOP - (i+1)*PGSIZE perlu konsisten antara parent dan child.

---

## 📚 Referensi

Tuliskan sumber referensi yang Anda gunakan, misalnya:

* Buku xv6 MIT: [https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
* Repositori xv6-public: [https://github.com/mit-pdos/xv6-public](https://github.com/mit-pdos/xv6-public)
* Diskusi praktikum dan dokumentasi kode kernel vm.c, proc.c, trap.c, sysproc.c
* Stack Overflow dan GitHub Issues terkait implementasi Copy-on-Write dan shared memory di xv6

---

