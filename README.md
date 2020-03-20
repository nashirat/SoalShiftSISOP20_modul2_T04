# Penyelesaian dan Penjelasan Soal Shift Sistem Operasi Modul 2

## Teknologi Informasi Kelompok T04
__Muhammad Sulthon Nashir (05311840000011)__

__Bagus Farhan Abdillah (05311840000016)__

### SOAL 1

#### Berikut adalah soal 1 :

Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai
c. Program hanya menerima 1 config cron
d. Program berjalan di background (daemon)
e. Tidak boleh menggunakan fungsi system()
Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.

#### Link code soal 1 :

##### Source Code : [Soal 1.sh](https://github.com/nashirat/SoalShiftSISOP20_modul1_T04/blob/master/soal1/soal1.sh)
##### Data : [Sample-Superstore.tsv](https://github.com/nashirat/SoalShiftSISOP20_modul1_T04/blob/master/soal1/Sample-Superstore.tsv)

#### Penyelesaian dan penjelasan soal 1 :
```bash
int main (int argc, char *argv[])
```
* __int argc__ dan __char *argv[]__ sebagai deklarasi argumen

```bash
int sec, min, hr;
hr = min = sec = -5;
time_t t = time(NULL);
struct tm lt = *localtime(&t);
```
* Deklarasi beberapa variabel seperti __sec, min, dan hr__ dalam __int__, __time_t t =  time__ adalah waktu dan __*localtime(%t)__ adalah waktu lokal yang dari __t__.
* Sebenarnya berapa pun nilai negatif untuk min, sec, hr dapat digunakan, karena perhitungan waktu dimulai dari 0.

```bash
if (argc != 5) {
  printf ("Argumen Tidak Sesuai \n");
  return 0;
}
```
* Fungsi jika argumen tidak tepat 5 maka error.

```bash
if ((isalpha(argv[1][0])) || (isalpha(argv[2][0])) || (isalpha(argv[3][0])) ) {
  printf ("Waktu harus angka\n");
  return 0;
}
```
* Fungsi jika argumen 1, 2, dan 3 yang merupakan jam adalah isalpha maka akan error, jika tidak maka lanjut. (\ atau * bukan isalpha).

```bash
if (argv[1][0] != '*') sec = atoi(argv[1]);
if (argv[2][0] != '*') min = atoi(argv[2]);
if (argv[3][0] != '*') hr = atoi(argv[3]);
```
* Jika argumen 1, 2 , 3 tidak * maka rubah argumen 1, 2 ,3 menjadi integer menggunaka __atoi__.

```bash
if ((sec >= 60 || sec < 0 && sec != -5 ) || (min >= 60 || min < 0 && min != -5) || (hr >= 25 || hr < 0 && hr != -5)) {
  printf("Format Waktu Salah\n");
  return 0;
}
```
* Jika __sec, min, dan hr__ lebih dari 60, kurang dari 0, dan tidak -5 maka akan error.

 ```bash
 while (1) {
 t = time(NULL);
 lt = *localtime(&t);
 if ((lt.tm_sec == sec || sec == -5) && (lt.tm_min == min || min == -5) && (lt.tm_hour == hr || hr == -5)) {
   if (fork()==0)
     execl("/bin/bash", "bash", argv[4], NULL);}
     sleep(1);
 }
 }
```
 * Fungsi utama, dengan t dari time, lt adalah localtime dari t.
 * Jika sec, min, dan hour sama dengan lt atau sama dengan -5, maka jalankan bash yang direktorinya dari argumen 4 dengan sleep selama 1 detik.
 ## SOAL 2

#### Tidak mengerjakan soal 2 ####

## SOAL 3

#### Tidak mengerjakan soal 3 ####
