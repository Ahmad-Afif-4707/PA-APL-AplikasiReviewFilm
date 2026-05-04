// FILE BARU - kelolauser.h
// Include: tampilan.h

// tolong dibuat fungsi menuKelolaUser() yang isinya ada:
//
// - Tampilkan seluruh daftar user yang rolenya bukan admin
//
// - Opsi PILIH USER:
//   admin memilih usernya berdasarkan nomor
//   setelah user dipilih, tampilkan detail user:
//     - username
//     - jumlah review milik user tersebut
//     - daftar review beserta nama film dan ratingnya
//       (cari film menggunakan cariFilm() yang tersedia di data.h)
//
//   ini sub-menu setelah memilih user:
//
//   - Opsi HAPUS USER:
//     minta konfirmasi sebelum menghapus
//     jika dikonfirmasi, panggil fungsi hapusUser() yang tersedia di data.h
//     setelah dihapus kembali ke daftar user
//
//   - Opsi HAPUS REVIEW:
//     tampilkan daftar review milik user tersebut dengan nomor urut
//     admin memilih nomor review yang ingin dihapus
//     panggil hapusReviewDi() yang tersedia di data.h
//
//   - Opsi KEMBALI ke daftar user
//
// - Opsi KEMBALI ke menu admin