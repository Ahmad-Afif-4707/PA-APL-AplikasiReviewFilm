// FILE BARU - kelolafilm.h
// Include: tampilan.h

// tolong dibuat fungsi menuKelolaFilm() yang berisi:
//
// - Tampilkan seluruh daftar film beserta jumlah reviewnya
//
// - Opsi TAMBAH FILM:
//   minta input judul, tahun, dan studio
//   lakukan validasi agar tidak ada field yang kosong dan tahun harus angka
//   simpan film baru ke listFilm
//
// - Opsi PILIH FILM:
//   admin memilih film berdasarkan nomor
//   setelah film dipilih, tampilkan sub-menu:
//
//   - Opsi EDIT FILM:
//     tampilkan nilai lama tiap field
//     admin bisa mengubah judul, tahun, dan studio
//     jika input dikosongkan maka field tidak diubah
//
//   - Opsi HAPUS FILM:
//     minta konfirmasi sebelum menghapus
//     kalau konfirmasi, panggil fungsi hapusFilm()
//     yang sudah tersedia di data.h
//
//   - Opsi LIHAT REVIEW:
//     panggil lihatDetailFilm() dengan mode admin (isAdmin = true)
//     yang sudah tersedia di detailfilm.h
//
//   - Opsi KEMBALI ke daftar film
//
// - Opsi KEMBALI ke menu admin